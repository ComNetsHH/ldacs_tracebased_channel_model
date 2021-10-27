#include "inet/physicallayer/common/packetlevel/ListeningDecision.h"
#include "inet/physicallayer/contract/packetlevel/SignalTag_m.h"
#include "inet/physicallayer/unitdisk/UnitDiskListening.h"
#include "inet/physicallayer/unitdisk/UnitDiskNoise.h"
#include "TraceBasedReceiver.h"
#include "inet/physicallayer/unitdisk/UnitDiskReception.h"
#include "inet/common/ModuleAccess.h"
#include "TraceBasedErrorModel.h"
#include "inet/common/INETMath.h"

using namespace inet;
using namespace physicallayer;
using namespace math;

Define_Module(TraceBasedReceiver);

TraceBasedReceiver::TraceBasedReceiver() :
    ReceiverBase(),
    ignoreInterference(false),
    Receiver_bandwidth_in_KHz(NaN),
    Tx_power(NaN),
    Tx_antenna_gain(NaN),
    Rx_antenna_gain(NaN),
    Tx_loss(NaN),
    Rx_loss(NaN),
    Noise_figure(NaN),
    Thermal_noise_density(NaN),
    frequency(NaN),
    SNR_margin(NaN)
{
}

void TraceBasedReceiver::initialize(int stage)
{
    ReceiverBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        errorModel = dynamic_cast<TraceBasedErrorModel *>(getSubmodule("errorModel"));
        ignoreInterference = par("ignoreInterference");
        Receiver_bandwidth_in_KHz = par("Receiver_bandwidth_in_KHz");
        Tx_power = par("Tx_power");
        Tx_antenna_gain = par("Tx_antenna_gain");
        Rx_antenna_gain = par("Rx_antenna_gain");
        Tx_loss = par("Tx_loss");
        Rx_loss = par("Rx_loss");
        Noise_figure = par("Noise_figure");
        Thermal_noise_density = par("Thermal_noise_density");
        frequency = par("frequency");
        SNR_margin =par("SNR_margin");
    }
}


std::ostream& TraceBasedReceiver::printToStream(std::ostream& stream, int level) const
{
    stream << "TraceBasedReceiver";
    if (level <= PRINT_LEVEL_INFO)
        stream << (ignoreInterference ? ", ignoring interference" : ", considering interference")
               << "Receiver_bandwidth_in_KHz = " << Receiver_bandwidth_in_KHz
               << "Tx_power = " << Tx_power
               << "Tx_antenna_gain = " << Tx_antenna_gain
               << "Rx_antenna_gain = " << Rx_antenna_gain
               << "Tx_loss = " << Tx_loss
               << "Rx_loss = " << Rx_loss
               << "Noise_figure = " << Noise_figure
               << "Thermal_noise_density = " << Thermal_noise_density
               << "frequency = " << frequency
               << "SNR_margin = " << SNR_margin;
    return stream;
}

bool TraceBasedReceiver::computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const
{
    auto power = check_and_cast<const UnitDiskReception *>(reception)->getPower();
    return power  == UnitDiskReception::POWER_RECEIVABLE;
}
/*
 * The following method decides a packet is successfully received or not based on packet error rate
 */

bool TraceBasedReceiver::computeIsReceptionSuccessful(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part, const IInterference *interference, const ISnir *snir)const
{
    double Receiver_bandwidth_in_Hz = Receiver_bandwidth_in_KHz*1000;//in Hz

    //getting the position of the Rx
    Coord Rx_position = check_and_cast<IMobility *>(getContainingNode(this)->getSubmodule("mobility"))->getCurrentPosition();

    //getting the position of the Tx
    Coord Tx_position = check_and_cast<const IReception *>(reception)->getTransmission()->getStartPosition();

    //applying the formula sqrt((x_2-x_1)^2+(y_2-y_1)^2) to get the distance between Tx and Rx
    double distance_in_meter = sqrt(pow((Rx_position.x-Tx_position.x),2)+ pow((Rx_position.y-Tx_position.y),2)+ pow((Rx_position.z-Tx_position.z),2));
    EV << " distance between Tx and Rx is in meter: " << distance_in_meter << " \n";// printing to check if the results are correct

    // calculate Radio horizon in meter using the height of the Tx and Rx
    double Radio_horizon = (130.4*(sqrt(Rx_position.z/1000)+sqrt(Tx_position.z/1000)))*1000;
    EV << " value of Radio_horizon in meter: " << Radio_horizon << " \n";

    double Received_Power;
    //comparing distance with Radio Horizon rh(h1, h2)|km = 922.06 to decide for path loss
    //calculating path loss using -> 20 log10(d|km · f |MHz) + 32.4478|dB, for d < rh(h1, h2)
    // as the above distance is in meter we are converting it to kilometer
    double path_loss = 2*(fraction2dB((distance_in_meter/1000)*frequency))+32.4478;

    //calculating Received_Power
    Received_Power = Tx_power + Tx_antenna_gain - Tx_loss + Rx_antenna_gain - Rx_loss - path_loss;

    //calculating Signal-to-Noise Ratio SNR(SNRmargin|dB)
    double SNR = Received_Power -(Noise_figure + Thermal_noise_density + 10*log10(Receiver_bandwidth_in_Hz))-SNR_margin;
    EV << "Signal-to-Noise Ratio, SNR= " << SNR << " \n";

    //calling the error Model to get packet error rate for the calculated SNR
    double PER = ((TraceBasedErrorModel*) errorModel)->snrToPacketErrorRateMapping(SNR);
    EV << "packetErrorRate= " << PER << " \n";

    if(distance_in_meter < Radio_horizon){

        //Deciding a packet is correctly received or not based on PER
        if (PER == 0.0)
            return true;
        else if (PER == 1.0)
            return false;
        else{
            // if the PER is in between 0 and 1 we compare the PER with a random number to decide if the packet is correctly received or not
            double random_value= uniform(0,1);

            if (random_value < PER)
                return false;  //Packet is not successfully received
            else
                return true;  //Packet is successfully received
        }

    }

    //When the distance between the Tx and Rx is greater than the Radio Horizon, packet will be dropped
    else
        return false;
}
const IListening * TraceBasedReceiver::createListening(const IRadio *radio, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition) const
{
    return new UnitDiskListening(radio, startTime, endTime, startPosition, endPosition);
}

const IListeningDecision * TraceBasedReceiver::computeListeningDecision(const IListening *listening, const IInterference *interference) const
{
    auto interferingReceptions = interference->getInterferingReceptions();
    for (auto interferingReception : *interferingReceptions) {
        auto interferingPower = check_and_cast<const UnitDiskReception *>(interferingReception)->getPower();
        if (interferingPower != UnitDiskReception::POWER_UNDETECTABLE)
            return new ListeningDecision(listening, true);
    }
    return new ListeningDecision(listening, false);
}

const IReceptionResult * TraceBasedReceiver::computeReceptionResult(const IListening *listening, const IReception *reception, const IInterference *interference, const ISnir *snir, const std::vector<const IReceptionDecision *> *decisions) const
{
    auto noise = check_and_cast_nullable<const UnitDiskNoise *>(snir->getNoise());
    double errorRate = check_and_cast<const UnitDiskReception *>(reception)->getPower() == UnitDiskReception::POWER_RECEIVABLE && (noise == nullptr || !noise->isInterfering()) ? 0 : 1;
    auto receptionResult = ReceiverBase::computeReceptionResult(listening, reception, interference, snir, decisions);
    auto errorRateInd = const_cast<Packet *>(receptionResult->getPacket())->addTagIfAbsent<ErrorRateInd>();
    errorRateInd->setSymbolErrorRate(errorRate);
    errorRateInd->setBitErrorRate(errorRate);
    errorRateInd->setPacketErrorRate(errorRate);
    return receptionResult;
}


#include "inet/physicallayer/common/packetlevel/ListeningDecision.h"
#include "inet/physicallayer/common/packetlevel/ReceptionDecision.h"
#include "inet/physicallayer/contract/packetlevel/SignalTag_m.h"
#include "inet/physicallayer/unitdisk/UnitDiskListening.h"
#include "inet/physicallayer/unitdisk/UnitDiskNoise.h"
#include "UnitDiskReceiverCustomized.h"
#include "inet/physicallayer/unitdisk/UnitDiskReception.h"
#include "inet/mobility/base/MovingMobilityBase.h"
#include "inet/mobility/base/MobilityBase.h"
#include "inet/common/geometry/common/Quaternion.h"
#include "inet/mobility/contract/IMobility.h"


#include "inet/common/ModuleAccess.h"
#include "inet/physicallayer/contract/packetlevel/IReception.h"
#include "inet/physicallayer/contract/packetlevel/ITransmitter.h"
#include "inet/physicallayer/contract/packetlevel/ITransmission.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using namespace inet;
using namespace physicallayer;

Define_Module(UnitDiskReceiverCustomized);

UnitDiskReceiverCustomized::UnitDiskReceiverCustomized() :
    ReceiverBase(),
    ignoreInterference(false)
{
}

void UnitDiskReceiverCustomized::initialize(int stage)
{
    ReceiverBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        errorModel = dynamic_cast<IErrorModel *>(getSubmodule("errorModel"));

        ignoreInterference = par("ignoreInterference");
    }
}

std::ostream& UnitDiskReceiverCustomized::printToStream(std::ostream& stream, int level) const
{
    stream << "UnitDiskReceiverCustomized";
    if (level <= PRINT_LEVEL_INFO)
        stream << (ignoreInterference ? ", ignoring interference" : ", considering interference");
    return stream;
}

bool UnitDiskReceiverCustomized::computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const
{
    auto power = check_and_cast<const UnitDiskReception *>(reception)->getPower();
    return power  == UnitDiskReception::POWER_RECEIVABLE;
}


bool UnitDiskReceiverCustomized::computeIsReceptionSuccessful(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part, const IInterference *interference, const ISnir *snir) const
{
    //Defining the variables
    double Radio_horizon = 922.06;
    double Tx_power = 50;
    double Tx_antenna_gain = 3;
    double Rx_antenna_gain = 3;
    double Tx_loss = 4;
    double Rx_loss = 4;
    double Noise_figure = 6;
    double Thermal_noise_density = -174;
    double Receiver_bandwidth_in_KHz = 500;//in KHz
    double Receiver_bandwidth = Receiver_bandwidth_in_KHz*1000;//in Hz
    double frequency = 1164; //in MHz

    //getting the position of the Rx
    cModule *host = getContainingNode(this);
    IMobility  *mod = check_and_cast<IMobility *>(host->getSubmodule("mobility"));
    Coord Rx_position = mod->getCurrentPosition();
    double Rx_position_x = Rx_position.x;
    double Rx_position_y = Rx_position.y;
    double Rx_position_z = Rx_position.z;
    EV << " Current Position of Rx = " << Rx_position << " \n";

    //getting the position of the Tx
    auto transmission = check_and_cast<const IReception *>(reception)->getTransmission();
    Coord Tx_position = transmission->getStartPosition();
    double Tx_position_x = Tx_position.x;
    double Tx_position_y = Tx_position.y;
    double Tx_position_z = Tx_position.z;
    EV << " Current Position of Tx = " << Tx_position << " \n";

    //applying the formula sqrt((x_2-x_1)^2+(y_2-y_1)^2) to get the distance between Tx and Rx
    double distance = sqrt(pow((Rx_position_x-Tx_position_x),2)+ pow((Rx_position_y-Tx_position_y),2)+ pow((Rx_position_z-Tx_position_z),2));
    EV << " distance between Tx and Rx is in meter: " << distance << " \n";// printing to check if the results are correct
    // as the above distance is on meter we are converting to kilometer
    distance = distance/1000;

    double Received_Power;
    //comparing distance with Radio Horizon rh(h1, h2)|km = 922.06 to decide for path loss
    if(distance < Radio_horizon){

        //calculating path loss using -> 20 log10(d|km · f |MHz) + 32.4478|dB, for d < rh(h1, h2)
        double path_loss =(20*log10(distance*frequency))+32.4478;
        EV << "path loss = " << path_loss << " \n";

        //calculating Received_Power
        Received_Power = Tx_power + Tx_antenna_gain - Tx_loss + Rx_antenna_gain - Rx_loss - path_loss;
        EV << " Received Signal Power = " << Received_Power << " \n";

        //calculating Signal-to-Noise Ratio SNR(SNRmargin|dB)
        double SNR = Received_Power -(Noise_figure + Thermal_noise_density + 10*log10(Receiver_bandwidth))-10;
        EV << "Signal-to-Noise Ratio, SNR= " << SNR << " \n";

        //reading the .txt file
        int line_number=0,f,g,i,j,q,n;
        int z;

        // Creating a text string, which is used to output the text file
        string myText;
        double a[100][3];

        // Read from the text file
        ifstream MyReadFile("per_snr.txt");

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, myText)) {

            // finding the position of the first ","
            for( i = 0; i < myText.length(); i++){
                if(myText[i]==','){
                    f = i;
                    break;
                }
            }

            // finding the position of the second ","
            for( j = i+1; j < myText.length(); j++){
                if(myText[j]==','){
                    g = j;
                }
            }

            char temp[f];
            char temp2[g-f];

            //asinging the SNR part of the text file into array a
            for( q=0;q<f;q++){
                temp[q]=myText[q];
            }
            temp[q]='\0';
            // convert string to double
            a[line_number][0]= std::stod(temp);
            q++;

            //asinging the SNR part of the text file into array a
            for( i=0;i<g-f-1;i++){
                temp2[i]=myText[q];
                q++;
            }
            temp2[i]='\0';
            a[line_number][1]= std::stod(temp2);
            line_number++;
        }

        // Closing the file
        MyReadFile.close();

        //When SNR is > 10 we assume it equal to 10
        if(SNR > 10)
            SNR=10;

        //When SNR is < -4 we assume it equal to -4
        else if(SNR < -4)
            SNR=-4;

        //finding the corresponding PER of the current SNR when SNR is int
        double PER;
        int SNR_is_float = 1;
        for(int k=0; k<line_number;k++){
            if(a[k][0]== SNR){
                PER = a[k][1];
                EV << "\ncorresponding PER is: ";
                EV << a[k][1];
                SNR_is_float =0;
                break;
            }
        }

        //finding the corresponding PER of the current SNR when SNR is a float
        if(SNR_is_float==1){

            //Separating the int part and decimal part of SNR
            double SNR_dec_part;
            int SNR_int_part = (int)SNR;
            EV << " SNR_int_part= " << SNR_int_part << " \n";
            if(SNR >= 0){
                SNR_dec_part = SNR - SNR_int_part;
                EV << " SNR_dec_part= " << SNR_dec_part << " \n";
            }
            else{
                SNR_dec_part = (SNR - SNR_int_part)*(-1);
                EV << " SNR_dec_part= " << SNR_dec_part << " \n";
            }

            //finding the corresponding PER of the current SNR_int_part
            int k;
            for(k=0; k<line_number;k++){
                if(a[k][0]== SNR_int_part){
                    PER = a[k][1];
                    EV << "\ncorresponding PER is: ";
                    EV << a[k][1];
                    break;
                }
            }

            //finding the corresponding PER of the current SNR_decimal_part
            double fraction_PER;
            if(SNR_int_part >= 0 && SNR > 0){
                fraction_PER=a[k+1][1]*SNR_dec_part;
            }
            else if(SNR_int_part >= 0 && SNR < 0){
                fraction_PER=a[k-1][1]*SNR_dec_part;
            }
            else{
                fraction_PER=a[k-1][1]*SNR_dec_part;
            }
            EV << " fraction_PER= " << fraction_PER << " \n";

            //adding the PER of the current  SNR_int_part and SNR_decimal_part
            PER = (1-SNR_dec_part)*PER + fraction_PER;
            EV << " final_PER= " << PER << " \n";

        }

        //Deciding a packet is correctly received or not based on PER
        if (PER == 0.0){
            EV << "Packet is successfully received" << endl;
            return true;}
        else if (PER == 1.0){
            EV << "Packet is not received" << endl;
            return false;
            }
        else{
            double random_value= uniform(0,1);
            EV << "random_value = " << random_value << " \n";
            if (random_value < PER){
                EV << "Packet is not received" << endl;
                return false;}
            else{
                EV << "Packet is successfully received" << endl;
                return true;}
        }

    }
    //When the distance between the Tx and Rx is greater than the Radio Horizon, packet will be dropped
    else {
        EV << "Packet is not received as the distance between the Tx and Rx is greater than the Radio Horizon" << endl;
        return false;}
}
const IListening *UnitDiskReceiverCustomized::createListening(const IRadio *radio, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition) const
{
    return new UnitDiskListening(radio, startTime, endTime, startPosition, endPosition);
}

const IListeningDecision *UnitDiskReceiverCustomized::computeListeningDecision(const IListening *listening, const IInterference *interference) const
{
    auto interferingReceptions = interference->getInterferingReceptions();
    for (auto interferingReception : *interferingReceptions) {
        auto interferingPower = check_and_cast<const UnitDiskReception *>(interferingReception)->getPower();
        if (interferingPower != UnitDiskReception::POWER_UNDETECTABLE)
            return new ListeningDecision(listening, true);
    }
    return new ListeningDecision(listening, false);
}

const IReceptionResult *UnitDiskReceiverCustomized::computeReceptionResult(const IListening *listening, const IReception *reception, const IInterference *interference, const ISnir *snir, const std::vector<const IReceptionDecision *> *decisions) const
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



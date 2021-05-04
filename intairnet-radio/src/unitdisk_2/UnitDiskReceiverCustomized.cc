#include "inet/physicallayer/common/packetlevel/ListeningDecision.h"
#include "inet/physicallayer/common/packetlevel/ReceptionDecision.h"
#include "inet/physicallayer/contract/packetlevel/SignalTag_m.h"
#include "inet/physicallayer/unitdisk/UnitDiskListening.h"
#include "inet/physicallayer/unitdisk/UnitDiskNoise.h"
#include "inet/physicallayer/unitdisk/UnitDiskReceiverCustomized.h"
#include "inet/physicallayer/unitdisk/UnitDiskReception.h"
#include "inet/mobility/base/MovingMobilityBase.h"
#include "inet/mobility/base/MobilityBase.h"
#include "inet/common/geometry/common/Quaternion.h"
#include "inet/mobility/contract/IMobility.h"


#include "inet/common/ModuleAccess.h"



namespace inet {
namespace physicallayer {

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





//        mobility = dynamic_cast<IMobility *>(getSubmodule("mobility"));
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
   // static std::string result;
   // find out the location of Tx and Rx
   // double result = mobility->getMaxSpeed();
    //EV << " Current Position of Rx = " << result << " \n";
/*
    cModule *host = getContainingNode(this);

    IMobility  *mod = check_and_cast<IMobility *>(host->getSubmodule("mobility"));

    Coord pos = mod->getCurrentPosition();
    EV << " Current Position of Rx = " << pos << " \n";
*/


    double random_value;
    double packetErrorRate = errorModel->computePacketErrorRate(snir,part);

    //deciding a packet is successfully received or not based on packetErrorRate
    if (packetErrorRate == 0.0){
        EV << "Packet is successfully received" << endl;
        return true;}
    else if (packetErrorRate == 1.0){
        EV << "Packet is not received" << endl;
        return false;
        }
    else{
        random_value= uniform(0,1);
        EV << "random_value = " << random_value << " \n";
        if (random_value < packetErrorRate){
            EV << "Packet is successfully received" << endl;
            return true;}
        else{
            EV << "Packet is not received" << endl;
            return false;}

    }
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

} // namespace physicallayer
} // namespace inet


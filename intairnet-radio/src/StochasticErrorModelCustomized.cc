#include "inet/physicallayer/base/packetlevel/FlatTransmissionBase.h"
#include "StochasticErrorModelCustomized.h"

using namespace inet::physicallayer;
using namespace inet;

Define_Module(StochasticErrorModelCustomized);

StochasticErrorModelCustomized::StochasticErrorModelCustomized() :
    packetErrorRate(NaN),
    bitErrorRate(NaN),
    symbolErrorRate(NaN)
{
}

void StochasticErrorModelCustomized::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        packetErrorRate = par("packetErrorRate");
        bitErrorRate = par("bitErrorRate");
        symbolErrorRate = par("symbolErrorRate");
    }
}

std::ostream& StochasticErrorModelCustomized::printToStream(std::ostream& stream, int level) const
{
    if (level <= PRINT_LEVEL_TRACE)
        stream << "StochasticErrorModelCustomized"
               << "packetErrorRate = " << packetErrorRate
               << "bitErrorRate = " << bitErrorRate
               << "symbolErrorRate = " << symbolErrorRate;
    return stream;
}


double StochasticErrorModelCustomized::computePacketErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    return packetErrorRate;
}

double StochasticErrorModelCustomized::computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    EV << "MYMESSAGE" << endl;
    return 0;
}

double StochasticErrorModelCustomized::computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    EV << "MYMESSAGE" << endl;
    return 0;
}


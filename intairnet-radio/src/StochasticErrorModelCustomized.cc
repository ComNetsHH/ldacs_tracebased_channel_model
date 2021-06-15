#include "inet/physicallayer/base/packetlevel/FlatTransmissionBase.h"
#include "StochasticErrorModelCustomized.h"

using namespace inet::physicallayer;
using namespace inet;

Define_Module(StochasticErrorModelCustomized);


StochasticErrorModelCustomized::StochasticErrorModelCustomized() :
    packetErrorRate(NaN),
    bitErrorRate(NaN),
    symbolErrorRate(NaN),
    Signal_to_Noise_Ratio(NaN)
{
}

void StochasticErrorModelCustomized::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        packetErrorRate = par("packetErrorRate");
        bitErrorRate = par("bitErrorRate");
        symbolErrorRate = par("symbolErrorRate");
        Signal_to_Noise_Ratio = par("Signal_to_Noise_Ratio");
    }
}

std::ostream& StochasticErrorModelCustomized::printToStream(std::ostream& stream, int level) const
{
    if (level <= PRINT_LEVEL_TRACE)
        stream << "StochasticErrorModelCustomized"
               << "packetErrorRate = " << packetErrorRate
               << "bitErrorRate = " << bitErrorRate
               << "symbolErrorRate = " << symbolErrorRate
               << "Signal_to_Noise_Ratio = " << Signal_to_Noise_Ratio;
    return stream;
}


/*double StochasticErrorModelCustomized::test_method(double Signal_to_Noise_Ratio)
{
    Enter_Method_Silent();
    EV << "\nMessage from test_method" << endl;
    EV << " \n";
    return packetErrorRate;
}

*/
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

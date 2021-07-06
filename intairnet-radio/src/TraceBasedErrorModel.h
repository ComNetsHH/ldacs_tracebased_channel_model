#ifndef __INET_TraceBasedErrorModel_H
#define __INET_TraceBasedErrorModel_H

#include "inet/physicallayer/base/packetlevel/ErrorModelBase.h"

using namespace inet;
using namespace physicallayer;

class TraceBasedErrorModel: public ErrorModelBase
{
  protected:
    double packetErrorRate;
    double bitErrorRate;
    double symbolErrorRate;
    double SNR;

  protected:
    virtual void initialize(int stage)override;

  public:
    TraceBasedErrorModel();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual double computePacketErrorRate(const ISnir *test_snir, IRadioSignal::SignalPart part) const override;
    virtual double computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;
    virtual double computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;

    //additional method for SNR_to_PER_Mapping
    double snrToPacketErrorRateMapping(double SNR);
};

#endif // ifndef __INET_TraceBasedErrorModel_H


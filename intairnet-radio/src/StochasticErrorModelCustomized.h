#ifndef __INET_STOCHASTICERRORMODELCUSTOMIZED_H
#define __INET_STOCHASTICERRORMODELCUSTOMIZED_H

#include "inet/physicallayer/base/packetlevel/ErrorModelBase.h"

using namespace inet;
using namespace physicallayer;

/**
 * Implements the StochasticErrorModelCustomized model, see the NED file for details.
 */
class StochasticErrorModelCustomized: public ErrorModelBase
{
  protected:
    double packetErrorRate;
    double bitErrorRate;
    double symbolErrorRate;
    double Signal_to_Noise_Ratio;

  protected:
    virtual void initialize(int stage)override;

  public:
    StochasticErrorModelCustomized();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;

    //additional method
    // double test_method(double Signal_to_Noise_Ratio);
    virtual double computePacketErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;
    virtual double computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;
    virtual double computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;

};

#endif // ifndef __INET_STOCHASTICERRORMODELCUSTOMIZED_H


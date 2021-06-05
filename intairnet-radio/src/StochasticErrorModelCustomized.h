#ifndef __INET_STOCHASTICERRORMODELCUSTOMIZED_H
#define __INET_STOCHASTICERRORMODELCUSTOMIZED_H

#include "inet/physicallayer/base/packetlevel/ErrorModelBase.h"

using namespace inet;
using namespace physicallayer;

/**
 * Implements the StochasticErrorModelCustomized model, see the NED file for details.
 */
class StochasticErrorModelCustomized : public ErrorModelBase
{
  protected:
    double packetErrorRate;
    double bitErrorRate;
    double symbolErrorRate;

  protected:
    virtual void initialize(int stage) override;

  public:
    //adding new variable
    double Radio_horizon = 922.06;
    double Tx_power = 50;
    double antenna_gain = 3;
    double Tx_Rx_losses = 4;
    double Noise_figure = 6;
    double Thermal_noise_density = -174;
    double Receiver_bandwidth = 500;
    double distance_Tx_Rx;


    StochasticErrorModelCustomized();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;

    virtual double computePacketErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;
    virtual double computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;
    virtual double computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;

};

#endif // ifndef __INET_STOCHASTICERRORMODELCUSTOMIZED_H


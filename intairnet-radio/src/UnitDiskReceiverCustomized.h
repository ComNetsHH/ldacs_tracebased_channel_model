#ifndef __INET_IDEALRECEIVERCUSTOMIZED_H
#define __INET_IDEALRECEIVERCUSTOMIZED_H

#include "inet/physicallayer/base/packetlevel/ReceiverBase.h"
#include "inet/physicallayer/contract/packetlevel/IErrorModel.h"

using namespace inet;
using namespace physicallayer;

class UnitDiskReceiverCustomized : public ReceiverBase
{
  protected:
    bool ignoreInterference;
    double Receiver_bandwidth_in_KHz;
    double Radio_horizon;
    double Tx_power;
    double Tx_antenna_gain;
    double Rx_antenna_gain;
    double Tx_loss;
    double Rx_loss;
    double Noise_figure;
    double Thermal_noise_density;
    double frequency;
    double SNR_margin;

  protected:
    virtual void initialize(int stage) override;
    const IErrorModel *errorModel;

  public:
    UnitDiskReceiverCustomized();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual bool computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const override;
    virtual bool computeIsReceptionSuccessful(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part, const IInterference *interference, const ISnir *snir) const override;

    virtual const IListening *createListening(const IRadio *radio, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition) const override;
    virtual const IListeningDecision *computeListeningDecision(const IListening *listening, const IInterference *interference) const override;
    virtual const IReceptionResult *computeReceptionResult(const IListening *listening, const IReception *reception, const IInterference *interference, const ISnir *snir, const std::vector<const IReceptionDecision *> *decisions) const override;

};
#endif // ifndef __INET_IDEALRECEIVER_H


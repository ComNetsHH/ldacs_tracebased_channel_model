// The L-Band Digital Aeronautical Communications System (LDACS) Radio Library provides an implementation of a trace-file-based channel model for the LDACS Air-Air Medium Access Control simulator.
// Copyright (C) 2023  Sebastian Lindner, Konrad Fuger, Musab Ahmed Eltayeb Ahmed, Andreas Timm-Giel, Institute of Communication Networks, Hamburg University of Technology, Hamburg, Germany
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __INET_TRACEBASEDRECEIVER_H
#define __INET_TRACEBASEDRECEIVER_H

#include "inet/physicallayer/base/packetlevel/ReceiverBase.h"
#include "inet/physicallayer/contract/packetlevel/IErrorModel.h"
#include "inet/common/INETMath.h"

using namespace inet;
using namespace physicallayer;
/**
 * Implements the TraceBasedReceiver model, see the NED file for details.
 */
class TraceBasedReceiver : public ReceiverBase
{
  protected:
    bool ignoreInterference;
    double Receiver_bandwidth_in_KHz;
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
    TraceBasedReceiver();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual bool computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const override;
    /*
     * The following method decides a packet is successfully received or not based on packet error rate
     */
    virtual bool computeIsReceptionSuccessful(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part, const IInterference *interference, const ISnir *snir) const override;

    virtual const IListening *createListening(const IRadio *radio, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition) const override;
    virtual const IListeningDecision *computeListeningDecision(const IListening *listening, const IInterference *interference) const override;
    virtual const IReceptionResult *computeReceptionResult(const IListening *listening, const IReception *reception, const IInterference *interference, const ISnir *snir, const std::vector<const IReceptionDecision *> *decisions) const override;

};
#endif // ifndef __INET_TRACEBASEDRECEIVER_H


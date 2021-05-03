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
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef INTAIRNETRECEIVER_H_
#define INTAIRNETRECEIVER_H_


#include "inet/physicallayer/base/packetlevel/ReceiverBase.h"

using namespace inet::physicallayer;
using namespace inet;

/**
 * Implements the UnitDiskReceiver model, see the NED file for details.
 */
class IntAirNetReceiver : public ReceiverBase
{
  protected:
    bool ignoreInterference;

  protected:
    virtual void initialize(int stage) override;

  public:
    IntAirNetReceiver();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;

    virtual bool computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const override;
    virtual bool computeIsReceptionSuccessful(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part, const IInterference *interference, const ISnir *snir) const override;

    virtual const IListening *createListening(const IRadio *radio, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition) const override;
    virtual const IListeningDecision *computeListeningDecision(const IListening *listening, const IInterference *interference) const override;
    virtual const IReceptionResult *computeReceptionResult(const IListening *listening, const IReception *reception, const IInterference *interference, const ISnir *snir, const std::vector<const IReceptionDecision *> *decisions) const override;
};

#endif /* INTAIRNETRECEIVER_H_ */

package trace_based_radio;
import inet.physicallayer.common.packetlevel.Radio;
//
// This radio model provides a straight forward but fast and predictable physical
// layer behavior. It is a modified version of the UnitDiskRadio model. It must be
// used in conjunction with the ~UnitDiskRadioMedium model.
//
// The idea behind this radio model is to describe transmissions with a few
// distance based parameters: communication range, interference range, and
// detection range. Whether the reception is successful or not, depends on the
// distance between the transmitter and the receiver.
//

module TraceBasedRadio extends Radio
{    parameters:
        @class(TraceBasedRadio);
        transmitter.typename = default("UnitDiskTransmitter");
        receiver.typename = default("TraceBasedReceiver");
        separateTransmissionParts = default(false);
        separateReceptionParts = default(false);
}
package intairnet_radio;
import inet.physicallayer.common.packetlevel.Radio;

module UnitDiskRadioCustomized extends Radio
{    parameters:
        @class(UnitDiskRadioCustomized);
        transmitter.typename = default("UnitDiskTransmitter");
        receiver.typename = default("UnitDiskReceiverCustomized");
        separateTransmissionParts = default(false);
        separateReceptionParts = default(false);
}
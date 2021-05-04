package inet.physicallayer.unitdisk;
import inet.physicallayer.common.packetlevel.Radio;



module UnitDiskRadioCustomized extends Radio
{    parameters:
        transmitter.typename = default("UnitDiskTransmitter");
        receiver.typename = default("UnitDiskReceiverCustomized");
        separateTransmissionParts = default(false);
        separateReceptionParts = default(false);
        @class(UnitDiskRadioCustomized);
}
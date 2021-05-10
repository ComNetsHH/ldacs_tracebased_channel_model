package intairnet_radio;

import inet.mobility.base.MobilityBase;
import inet.mobility.base.MovingMobilityBase;
import inet.mobility.contract.IMobility;
import inet.physicallayer.contract.packetlevel.IErrorModel;
import inet.physicallayer.contract.packetlevel.IReceiver;


//
// This receiver model receives a transmission succesfully within communication
// range unless there's another interfering transmission within interference
// range. It also supports an ideal communication channel with configuring the
// receiver to ignore interfering transmissions.
//
// @see ~UnitDiskTransmitter, ~UnitDiskRadio, ~UnitDiskRadioMedium,
// ~UnitDiskAnalogModel.
//
module UnitDiskReceiverCustomized like IReceiver
{
    parameters:
        bool ignoreInterference = default(false); // true means interfering transmissions are ignored when determining whether a reception is successful or not
        @class(UnitDiskReceiverCustomized);
        @display("i=block/wrx;bgb=216.57999,104.649994");
    submodules:
       errorModel: StochasticErrorModelCustomized {
            @display("p=39,29");
        }
        
}

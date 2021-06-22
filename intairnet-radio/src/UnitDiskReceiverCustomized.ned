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

module UnitDiskReceiverCustomized like IReceiver
{
    parameters:
        bool ignoreInterference = default(false); // true means interfering transmissions are ignored when determining whether a reception is successful or not
        double Receiver_bandwidth_in_KHz = default(nan); 
        double Radio_horizon = default(nan); 
        double Tx_power = default(nan); 
        double Tx_antenna_gain = default(nan); 
        double Rx_antenna_gain = default(nan); 
        double Tx_loss = default(nan); 
        double Rx_loss = default(nan); 
        double Noise_figure = default(nan); 
        double Thermal_noise_density = default(nan); 
        double frequency = default(nan); 
        double SNR_New = default(nan); 
          
        @class(UnitDiskReceiverCustomized);
        @display("i=block/wrx;bgb=216.57999,104.649994");
    submodules:
       errorModel: StochasticErrorModelCustomized {
            @display("p=39,29");
        }
        
}

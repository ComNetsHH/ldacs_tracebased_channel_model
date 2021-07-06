package intairnet_radio;
import inet.mobility.base.MobilityBase;
import inet.mobility.base.MovingMobilityBase;
import inet.mobility.contract.IMobility;
import inet.physicallayer.contract.packetlevel.IErrorModel;
import inet.physicallayer.contract.packetlevel.IReceiver;

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
        double SNR_margin= default(nan);
        
        @class(UnitDiskReceiverCustomized);
        @display("i=block/wrx;bgb=216.57999,104.649994");
    submodules:
       errorModel: TraceBasedErrorModel {
            @display("p=39,29");
        }
        
}

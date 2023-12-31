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

package trace_based_radio;

import inet.physicallayer.contract.packetlevel.IErrorModel;
import inet.physicallayer.contract.packetlevel.IReceiver;
//
// This receiver model receives a transmission succesfully within communication
// range unless there's another interfering transmission within interference
// range. It also supports an ideal communication channel with configuring the
// receiver to ignore interfering transmissions.
// This receiver model has an error model as a sub module which works based on 
// a trace file to find Packet error rate for corresponding SNR values. 
//
module TraceBasedReceiver like IReceiver
{
    parameters:
        bool ignoreInterference = default(false); // true means interfering transmissions are ignored when determining whether a reception is successful or not
        double Receiver_bandwidth_in_KHz = default(500); 
        double Tx_power = default(42); 
        double Tx_antenna_gain = default(3); 
        double Rx_antenna_gain = default(3); 
        double Tx_loss = default(4); 
        double Rx_loss = default(4); 
        double Noise_figure = default(6); 
        double Thermal_noise_density = default(-174); 
        double frequency = default(960); 
        double SNR_margin= default(10);
        
        @class(TraceBasedReceiver);
        @display("i=block/wrx;bgb=216.57999,104.649994");
    submodules:
       errorModel: TraceBasedErrorModel {
            @display("p=39,29");
        }
        
}

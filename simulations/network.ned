package trace_based_radio.simulations;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.WirelessHost;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.physicallayer.unitdisk.UnitDiskRadio;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.physicallayer.contract.packetlevel.IErrorModel;
import inet.node.inet.INetworkNode;

network traceBasedRadioModel
{
    parameters:
        int numHosts;
        @display("bgb=1900000,1900000;bgg=800,1,grey95");

        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        @figure[rcvdPkText](type=indicatorText; pos=380,20; anchor=w; font=,18; textFormat="packets received: %g"; initialValue=0);
        @statistic[packetReceived](source=host[1].app[0].packetReceived; record=figure(count); targetFigure=rcvdPkText);
    
    submodules:
        iIntegratedVisualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer {
            @display("p=720,113.90401");
        }
        radioMedium: <default("UnitDiskRadioMedium")> like IRadioMedium {
            @display("p=720,275");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=720,200");
        }
	   host[numHosts]: <default("WirelessHost")> like INetworkNode {
        }
}

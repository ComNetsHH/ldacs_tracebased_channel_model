package trace_based_radio;
import inet.physicallayer.base.packetlevel.ErrorModelBase;
//
// This error model provides parameters to specify the Name of the Trace file 
// where constant packet error rate, bit error rate is mentioned for each Signal to Noise Ratio
//
module TraceBasedErrorModel
{
    parameters:
        string TraceFileName =default("per_snr.txt"); //Name of the Trace file where SNR to PER mapping is given
        @class(TraceBasedErrorModel);
}

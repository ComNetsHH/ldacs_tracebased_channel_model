package intairnet_radio;
import inet.physicallayer.base.packetlevel.ErrorModelBase;

module TraceBasedErrorModel
{
    parameters:
        double packetErrorRate = default(nan); // a probability in the range [0, 1] or NaN if not set
        double bitErrorRate = default(nan);    // a probability in the range [0, 1] or NaN if not set
        double symbolErrorRate = default(nan); // a probability in the range [0, 1] or NaN if not set
        double SNR = default(nan);
        @class(TraceBasedErrorModel);
}

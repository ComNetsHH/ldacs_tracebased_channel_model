import inet.physicallayer.errormodel.bitlevel.StochasticLayeredErrorModel;
import inet.physicallayer.base.packetlevel.ErrorModelBase;


import inet.physicallayer.contract.packetlevel.IErrorModel;


//
// TODO documentation
//

//
// This error model provides parameters to specify the constant packet error
// rate, bit error rate, and symbol error rate for receptions independent of
// any interfering transmission or noise.
//
module ErrorModel_customized extends ErrorModelBase
{
    parameters:
        double packetErrorRate = default(nan); // a probability in the range [0, 1] or NaN if not set
        double bitErrorRate = default(nan);    // a probability in the range [0, 1] or NaN if not set
        double symbolErrorRate = default(nan); // a probability in the range [0, 1] or NaN if not set
        @class(ErrorModelBase);
}

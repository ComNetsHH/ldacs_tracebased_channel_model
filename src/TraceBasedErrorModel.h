#ifndef __INET_TraceBasedErrorModel_H
#define __INET_TraceBasedErrorModel_H

#include "inet/physicallayer/base/packetlevel/ErrorModelBase.h"

using namespace std;
using namespace inet;
using namespace physicallayer;
/**
 * Implements the TraceBasedErrorModel, see the NED file for details.
 */
class TraceBasedErrorModel: public ErrorModelBase
{
  protected:
    string TraceFileName;
    cOutVector SNR_Vector;

  protected:
    virtual void initialize(int stage)override;

  public:
    TraceBasedErrorModel();

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual double computePacketErrorRate(const ISnir *test_snir, IRadioSignal::SignalPart part) const override;
    virtual double computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;
    virtual double computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;

    /*This additional snrToPacketErrorRateMapping method takes SNR as an input and
    finds the corresponding PacketErrorRate from a given Trace file
    This trace file name can be given through the parameter of this error model in .ini file
    */
    double snrToPacketErrorRateMapping(double SNR);
    /*This additional snrToBitErrorRateMapping method takes SNR as an input and
    finds the corresponding BitErrorRate from a given Trace file
    This trace file name can be given through the parameter of this error model in .ini file
    */
    double snrToBitErrorRateMapping(double SNR);
    /*This additional find_max_value method takes an array as input and looks for the maximum number
     * in that given array.
     */
    double find_max_value(vector<vector<double>> array);
    /*This additional find_min_value method takes an array as input and looks for the minimum number
     * in that given array.
     */
    double find_min_value(vector<vector<double>> array);

};

#endif // ifndef __INET_TraceBasedErrorModel_H


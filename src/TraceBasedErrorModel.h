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


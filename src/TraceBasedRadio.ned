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
import inet.physicallayer.common.packetlevel.Radio;
//
// This radio model provides a straight forward but fast and predictable physical
// layer behavior. It is a modified version of the UnitDiskRadio model. It must be
// used in conjunction with the ~UnitDiskRadioMedium model.
//
// The idea behind this radio model is to describe transmissions with a few
// distance based parameters: communication range, interference range, and
// detection range. Whether the reception is successful or not, depends on the
// distance between the transmitter and the receiver.
//

module TraceBasedRadio extends Radio
{    parameters:
        @class(TraceBasedRadio);
        transmitter.typename = default("UnitDiskTransmitter");
        receiver.typename = default("TraceBasedReceiver");
        separateTransmissionParts = default(false);
        separateReceptionParts = default(false);
}
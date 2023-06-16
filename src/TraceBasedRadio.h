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

#ifndef __INET_TRACEBASEDRADIO_H
#define __INET_TRACEBASEDRADIO_H

#include "inet/physicallayer/common/packetlevel/Radio.h"

using namespace inet;
using namespace physicallayer;

class TraceBasedRadio : public Radio
{

  protected:
    virtual void encapsulate(Packet *packet) const override;
    virtual void decapsulate(Packet *packet) const override;

  public:
    TraceBasedRadio();
};

#endif // ifndef __INET_TRACEBASEDRADIO_H


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


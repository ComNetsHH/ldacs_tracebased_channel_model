#ifndef __INET_IDEALRADIO_H
#define __INET_IDEALRADIO_H

#include "inet/physicallayer/common/packetlevel/Radio.h"

using namespace inet;
using namespace physicallayer;

class UnitDiskRadioCustomized : public Radio
{
  protected:

    virtual void encapsulate(Packet *packet) const override;
    virtual void decapsulate(Packet *packet) const override;

  public:
    UnitDiskRadioCustomized();
};

#endif // ifndef __INET_IDEALRADIO_H

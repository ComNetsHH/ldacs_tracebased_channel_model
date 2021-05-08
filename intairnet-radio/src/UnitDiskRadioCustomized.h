#ifndef __INET_IDEALRADIO_H
#define __INET_IDEALRADIO_H

#include "inet/physicallayer/common/packetlevel/Radio.h"

namespace inet {

namespace physicallayer {

class INET_API UnitDiskRadioCustomized : public Radio
{

  protected:
    virtual void encapsulate(Packet *packet) const override;
    virtual void decapsulate(Packet *packet) const override;

  public:
    UnitDiskRadioCustomized();
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_IDEALRADIO_H


#include "UnitDiskRadioCustomized.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/physicallayer/unitdisk/UnitDiskPhyHeader_m.h"
#include "inet/physicallayer/unitdisk/UnitDiskTransmitter.h"

using namespace inet;
using namespace physicallayer;

Register_Class(UnitDiskRadioCustomized);

UnitDiskRadioCustomized::UnitDiskRadioCustomized() :
    Radio()
{
}

void UnitDiskRadioCustomized::encapsulate(Packet *packet) const
{
    auto idealTransmitter = check_and_cast<const UnitDiskTransmitter *>(transmitter);
    auto phyHeader = makeShared<UnitDiskPhyHeader>();
    phyHeader->setChunkLength(idealTransmitter->getHeaderLength());
    phyHeader->setPayloadProtocol(packet->getTag<PacketProtocolTag>()->getProtocol());
    packet->insertAtFront(phyHeader);
    packet->getTag<PacketProtocolTag>()->setProtocol(&Protocol::unitDisk);
}

void UnitDiskRadioCustomized::decapsulate(Packet *packet) const
{
    const auto& phyHeader = packet->popAtFront<UnitDiskPhyHeader>();
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(phyHeader->getPayloadProtocol());
}


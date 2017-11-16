#include "GetAccountMoneyPacket.h"

GetAccountMoneyPacket::GetAccountMoneyPacket()
{}

GetAccountMoneyPacket::~GetAccountMoneyPacket()
{}

char GetAccountMoneyPacket::specificGetID() const
{
    return 2;
}

PacketHolder GetAccountMoneyPacket::specificClone() const
{
    return PacketHolder(new GetAccountMoneyPacket(*this));
}

QByteArray GetAccountMoneyPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_accountId, sizeof(_accountId));
    return data;
}

void GetAccountMoneyPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_accountId, sizeof(_accountId));
}

PacketHolder GetAccountMoneyPacket::specificHandle() const
{
    // TODO implement this method.
    // Must return -2 Packet.
    qDebug("MakePaymentPacket is not implemented yet!");
    return PacketHolder(NULL);
}

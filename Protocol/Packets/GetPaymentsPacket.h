#ifndef GETPAYMENTSPACKET_H
#define GETPAYMENTSPACKET_H

#include "../Packet.h"

class GetPaymentsPacket : public Packet
{
private:
    //fields
    quint64 _token;
    quint64 _cardNumber;
    quint32 _terminalId;
    //method setup
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    GetPaymentsPacket();
    GetPaymentsPacket(const quint64 token, const quint64 cardNumber,
                      const quint32 terminalId);
    ~GetPaymentsPacket();
    //selector-modifiers
    quint64& token()
    {
        return _token;
    }
    quint64& cardNumber()
    {
        return _cardNumber;
    }
    //selectors
    quint64 token() const
    {
        return _token;
    }
    quint64 cardNumber() const
    {
        return _cardNumber;
    }
};

#endif // GETPAYMENTSPACKET_H

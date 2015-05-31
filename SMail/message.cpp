#include "message.h"

Message::Message()
{
    sender = "";
    subject = "";
    data = "";
}

Message::Message(QString sender, QString receivers, QString subject, QString data, QString ct, QString cte, QString cs)
{
    this->sender = sender;
    this->subject = subject;
    this->data = data;
    this->receivers = receivers.split(", ");
    this->contentType = ct;
    this->contentTransferEncoding = cte;
    this->charset = cs;
}

QString Message::GetSender()
{
    return sender;
}

QStringList Message::GetReceivers()
{
    return receivers;
}

QString Message::GetSubject()
{
    return subject;
}

QString Message::GetData()
{
    return data;
}

QString Message::GetCT()
{
    return contentType;
}

QString Message::GetCTE()
{
    return contentTransferEncoding;
}

QString Message::GetCS()
{
    return charset;
}

bool Message::operator ==(Message msg)
{
    if(this->GetSender() == msg.GetSender() && this->GetSubject() == msg.GetSubject() && this->GetReceivers()[0] == msg.GetReceivers()[0] && this->GetData() == msg.GetData())
    {
        return true;
    }
    return false;
}

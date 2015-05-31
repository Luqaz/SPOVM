#ifndef MESSAGE_H
#define MESSAGE_H

#include <QtCore>

class Message
{
    QString sender;
    QStringList receivers;
    QString subject;
    QString data;
    QString contentType;
    QString contentTransferEncoding;
    QString charset;
public:
    Message();
    Message(QString sender, QString receivers, QString subject, QString data, QString ct="text/plain", QString cte = "8bit", QString cs = "UTF-8");
    QString GetSender();
    QStringList GetReceivers();
    QString GetSubject();
    QString GetData();
    QString GetCT();
    QString GetCTE();
    QString GetCS();
    bool operator ==(Message msg);
};
#endif // MESSAGE_H


#ifndef POP3RECEIVER_H
#define POP3RECEIVER_H

#include "openssl/ssl.h"
#include "openssl/err.h"
#include <QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include "message.h"
#include "account.h"
#include "mimetic/mimeentity.h"

QList<Message> POP3Receiver(Account &acc)
{
    QSslSocket socket;
    socket.connectToHostEncrypted(acc.GetPOP3Server(), acc.GetPOP3port());
    if (!socket.waitForEncrypted()) {
        qDebug() << socket.errorString();
    }

    // Authorization block

    QString UserName;
    if( acc.GetSMTPServer() == "smtp.aol.com" || acc.GetSMTPServer() == "smtp.yandex.ru")
    {
        QStringList some = acc.GetEmail().split("@");
        UserName = some[0];
        char* asd;
        sprintf(asd, "USER %s", UserName.toUtf8().data());
        socket.write(asd);
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd = "";
        sprintf(asd, "PASS %s", acc.GetPassword().toUtf8().data());
        socket.write(asd);
        socket.write("\r\n");
        while (socket.waitForReadyRead(2000))
            qDebug() << socket.readAll().data();
    }
    else if(acc.GetSMTPServer() == "smtp.mail.yahoo.com" || acc.GetSMTPServer() == "smtp.gmail.com" || acc.GetSMTPServer() == "smtp.mail.ru" || acc.GetSMTPServer() == "mail.rambler.ru")
    {
        char* asd;
        sprintf(asd, "USER %s", acc.GetEmail().toUtf8().data());
        socket.write(asd);
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd = "";
        sprintf(asd, "PASS %s", acc.GetPassword().toUtf8().data());
        socket.write(asd);
        socket.write("\r\n");
        while (socket.waitForReadyRead(2000))
            qDebug() << socket.readAll().data();
    }
    QString stat;
    socket.write("stat");
    while (socket.waitForReadyRead(1000))
        stat = socket.readAll().data();
    QStringList strs = stat.split(" ");
    int num = strs[1].toInt();
    QList<Message> messageList;
    for(int i=1; i<=num; i++)
    {
        std::ostream response(NULL);
        std::stringstream req;
        std::string request = "";
        req << "retr "<< i;
        request = req.str();
        socket.write(request.c_str());
        while (socket.waitForReadyRead())
            response << socket.readAll().data();
        mimetic::MimeEntity mimeEntity((std::istream&)response);
        QString from = mimeEntity.header().from().str().c_str();
        QString to = mimeEntity.header().to().str().c_str();
        QString subject = mimeEntity.header().subject().data();
        QString data = mimeEntity.body().data();
        QString ct = mimeEntity.header().contentType().str().c_str();
        QString cte = mimeEntity.header().contentTransferEncoding().str().c_str();
        Message msg(from, to, subject, data, ct, cte);
        messageList.push_back(msg);
    }
    socket.write("QUIT");
    return messageList;
}
#endif // POP3RECEIVER_H

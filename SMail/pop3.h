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
//#include "mimetic/mimeentity.h"

#include "mimepp/mimepp.h"

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
        QString asd = "USER ";
        asd.push_back(UserName);
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd.clear();
        asd.push_back("PASS ");
        asd.push_back(acc.GetPassword());
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(2000))
            qDebug() << socket.readAll().data();
    }
    else if(acc.GetSMTPServer() == "smtp.mail.yahoo.com" || acc.GetSMTPServer() == "smtp.gmail.com" || acc.GetSMTPServer() == "smtp.mail.ru" || acc.GetSMTPServer() == "mail.rambler.ru")
    {
        QString asd = "USER ";
        asd.push_back(acc.GetEmail());
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd.clear();
        asd.push_back("PASS ");
        asd.push_back(acc.GetPassword());
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(2000))
            qDebug() << socket.readAll().data();
    }
    QString stat;
    socket.write("stat");
    socket.write("\r\n");
    qDebug() << "Stat";
    while (socket.waitForReadyRead(1000))
        stat = socket.readAll().data();
    QStringList strs = stat.split(" ");
    qDebug() << strs[0];
    qDebug() << strs[1];
    int num = strs[1].toInt();
    QList<Message> messageList;
    qDebug() << "mimepp Init";
    mimepp::Initialize();
    for(int i=1; i<=2; i++)
    {
        mimepp::Message newMsg;
        mimepp::String str;
        QString request = "retr %1";
        request = request.arg(i);
        qDebug() << request;
        socket.write(request.toUtf8().data());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            str = socket.readAll().data();
        newMsg.setString(str);
        newMsg.parse();
        QString from = newMsg.headers().from().text().c_str();
        qDebug() << "FROM: ";
        qDebug() << from;
        QString to = newMsg.headers().to().text().c_str();
        qDebug() << "TO: " ;
        qDebug() << to;
        QString subject = newMsg.headers().subject().text().c_str();
        qDebug() << "SUBJECT: ";
        qDebug() << subject;
        QString data = newMsg.body().getString().c_str();
        qDebug() << "BODY: ";
        qDebug() << data;
        QString ct = newMsg.headers().contentType().text().c_str();
        qDebug() << "Content-type: ";
        qDebug() << ct;
        QString cte = newMsg.headers().contentTransferEncoding().text().c_str();
        qDebug() << "Content-transfer-encoding: ";
        qDebug() << cte;
        Message msg(from, to, subject, data, ct, cte);
        messageList.push_back(msg);
    }
    mimepp::Finalize();
    socket.write("QUIT");
    socket.write("\r\n");
    return messageList;
}

int getStat(Account &acc)
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
        QString asd = "USER ";
        asd.push_back(UserName);
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd.clear();
        asd.push_back("PASS ");
        asd.push_back(acc.GetPassword());
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(2000))
            qDebug() << socket.readAll().data();
    }
    else if(acc.GetSMTPServer() == "smtp.mail.yahoo.com" || acc.GetSMTPServer() == "smtp.gmail.com" || acc.GetSMTPServer() == "smtp.mail.ru" || acc.GetSMTPServer() == "mail.rambler.ru")
    {
        QString asd = "USER ";
        asd.push_back(acc.GetEmail());
        socket.write(asd.toStdString().c_str());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd.clear();
        asd.push_back("PASS ");
        asd.push_back(acc.GetPassword());
        socket.write(asd.toStdString().c_str());
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
    return num;
}

#endif // POP3RECEIVER_H

#ifndef SMTPSENDER_H
#define SMTPSENDER_H

#include "openssl/ssl.h"
#include "openssl/err.h"
#include <QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "message.h"
#include "account.h"
#include "base64.h"


void SMTPSender(Message &msg, Account &acc)
{
    QSslSocket socket;
    socket.connectToHostEncrypted(acc.GetSMTPServer(), acc.GetSMTPport());
    if (!socket.waitForEncrypted()) {
        qDebug() << socket.errorString();
    }
    socket.write("EHLO SMail");

        qDebug() << "EHLO SMail";
    socket.write("\r\n");
    while (socket.waitForReadyRead(5000))
        qDebug() << socket.readAll().data();
    socket.write("AUTH LOGIN");
    socket.write("\r\n");
        qDebug() << "AUTH LOGIN";
    while (socket.waitForReadyRead(5000))
        qDebug() << socket.readAll().data();

    QString UserName;
    if(acc.GetSMTPServer() == "smtp.gmail.com" || acc.GetSMTPServer() == "smtp.aol.com" || acc.GetSMTPServer() == "smtp.yandex.ru")
    {
        QStringList some = acc.GetEmail().split("@");
        UserName = some[0];
        char* asd = base64_encode(UserName).toUtf8().data();
        socket.write(asd);
        socket.write("\r\n");
        qDebug() << asd;
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd = base64_encode(acc.GetPassword()).toUtf8().data();
        socket.write(asd);
        socket.write("\r\n");
        qDebug() << asd;
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
    }
    else if(acc.GetSMTPServer() == "smtp.mail.yahoo.com")
    {
        socket.write(base64_encode(acc.GetEmail()).toUtf8().constData());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        socket.write(base64_encode(acc.GetPassword()).toUtf8().constData());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
    }
    else if(acc.GetSMTPServer() == "smtp.mail.ru" || acc.GetSMTPServer() == "mail.rambler.ru")
    {
        socket.write(base64_encode(acc.GetEmail()).toUtf8().constData());
        socket.write("\r\n");
        qDebug() << acc.GetEmail().toUtf8().constData();
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        socket.write(base64_encode(acc.GetPassword()).toUtf8().constData());
        socket.write("\r\n");
        qDebug() << acc.GetPassword().toUtf8().constData();
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
    }
    QString mf = "MAIL FROM:<";
    mf.push_back(msg.GetSender().toStdString().c_str());
    mf.push_back(">");
    qDebug() << mf.toUtf8().constData();
    socket.write(mf.toUtf8().constData());
    socket.write("\r\n");
    while (socket.waitForReadyRead(1000))
        qDebug() << socket.readAll().data();
    for(int i=0; i<msg.GetReceivers().count(); i++)
    {
        mf.clear();
        mf.push_back("RCPT TO:<");
        mf.push_back(msg.GetReceivers()[i]);
        mf.push_back(">");
        qDebug() << mf.toUtf8().constData();
        socket.write(mf.toUtf8().constData());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
    }
    socket.write("DATA");
    socket.write("\r\n");
    while (socket.waitForReadyRead(1000))
        qDebug() << socket.readAll().data();
    mf.clear();
    mf.push_back("Subject: ");
    mf.push_back(msg.GetSubject());
    mf.push_back("\r\n\r\n");
    mf.push_back(msg.GetData());
    mf.push_back("\r\n.\r\n.");
    qDebug() << mf.toUtf8().constData();
    socket.write(mf.toUtf8().constData());
    socket.write("\r\n");
    while (socket.waitForReadyRead(1000))
        qDebug() << socket.readAll().data();
    socket.write("QUIT");
    socket.write("\r\n");
}

bool testAccount(Account &acc)
{
    QSslSocket socket;
    socket.connectToHostEncrypted(acc.GetSMTPServer(), acc.GetSMTPport());
    if (!socket.waitForEncrypted()) {
        qDebug() << socket.errorString();
    }
    socket.write("EHLO SMail");

        qDebug() << "EHLO SMail";
    socket.write("\r\n");
    while (socket.waitForReadyRead(5000))
        qDebug() << socket.readAll().data();
    socket.write("AUTH LOGIN");
    socket.write("\r\n");
        qDebug() << "AUTH LOGIN";
    while (socket.waitForReadyRead(5000))
        qDebug() << socket.readAll().data();

    QString UserName;
    if(acc.GetSMTPServer() == "smtp.gmail.com" || acc.GetSMTPServer() == "smtp.aol.com" || acc.GetSMTPServer() == "smtp.yandex.ru")
    {
        QStringList some = acc.GetEmail().split("@");
        UserName = some[0];
        char* asd = base64_encode(UserName).toUtf8().data();
        socket.write(asd);
        socket.write("\r\n");
        qDebug() << asd;
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        asd = base64_encode(acc.GetPassword()).toUtf8().data();
        socket.write(asd);
        socket.write("\r\n");
        qDebug() << asd;
        QString response;
        while (socket.waitForReadyRead(1000))
            response = socket.readAll().data();
        response = response.split(" ")[0];
        qDebug() << response;
        if(response[0] == '2') return true;
        else return false;
    }
    else if(acc.GetSMTPServer() == "smtp.mail.yahoo.com")
    {
        socket.write(base64_encode(acc.GetEmail()).toUtf8().constData());
        socket.write("\r\n");
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        socket.write(base64_encode(acc.GetPassword()).toUtf8().constData());
        socket.write("\r\n");
        QString response;
        while (socket.waitForReadyRead(1000))
            response = socket.readAll().data();
        response = response.split(" ")[0];
        qDebug() << response;
        if(response[0] == '2') return true;
        else return false;
    }
    else if(acc.GetSMTPServer() == "smtp.mail.ru" || acc.GetSMTPServer() == "mail.rambler.ru")
    {
        socket.write(base64_encode(acc.GetEmail()).toUtf8().constData());
        socket.write("\r\n");
        qDebug() << acc.GetEmail().toUtf8().constData();
        while (socket.waitForReadyRead(1000))
            qDebug() << socket.readAll().data();
        socket.write(base64_encode(acc.GetPassword()).toUtf8().constData());
        socket.write("\r\n");
        qDebug() << acc.GetPassword().toUtf8().constData();
        QString response;
        while (socket.waitForReadyRead(1000))
            response = socket.readAll().data();
        response = response.split(" ")[0];
        qDebug() << response;
        if(response[0] == '2') return true;
        else return false;
    }
}

#endif // SMTPSENDER_H

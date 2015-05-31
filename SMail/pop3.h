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
#include <QProgressDialog>
//#include "mimetic/mimeentity.h"

#include "mimepp/mimepp.h"

QList<Message> POP3Receiver(Account &acc, int frompos)
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

    QProgressDialog progress("Taking emails...", "Cancel", 0, num);
    progress.setWindowModality(Qt::WindowModal);

    for(int i=num; i>=frompos+1; i--)
    {
        progress.setValue(num - i);
        QCoreApplication::processEvents();
        if (progress.wasCanceled())
            break;
        QString data, from, to, subject, ct, cte, charset, hstr;
        QString request = "top %1 10";
        request = request.arg(i);
        qDebug() << request;
        socket.write(request.toUtf8().data());
        socket.write("\r\n");
        while (socket.waitForReadyRead(2000))
            hstr = socket.readAll().data();

        QRegExp headers("(.*)\\r\\n\\r\\n");
        headers.indexIn(hstr);
        QString header = headers.cap(1);

        QStringList lines = header.split("\n");
        foreach (QString line, lines) {
            if(line.contains(": "))
            {
                QRegExp email("([-.\\w]+@(?:[a-z\\d]{2,}\\.)+[a-z]{2,6})");
                QStringList some = line.split(": ");
                if(some[0].contains("From"))
                {
                    email.indexIn(some[1]);
                    from = email.cap(1);
                }
                if(some[0].contains("To"))
                {
                    email.indexIn(some[1]);
                    to = email.cap(1);
                }
                if(some[0].contains("Subject"))
                {
                    subject = some[1];
                }
                if(some[0].contains("Content-Type"))
                {
                    ct = some[1];
                }
                if(some[0].contains("Content-Transfer-Encoding"))
                {
                    cte = some[1];
                }
            }
        }
        qDebug() << "From: " << from <<'\n'
                 << "To: " << to << '\n'
                 << "Subject" << subject << '\n'
                 << "Content-Type: " << ct << '\n'
                 << "Content-Transfer-Encoding" << cte << '\n';

        QRegExp regCs("charset=(.*)");
        int pos = regCs.indexIn(ct);
        if(pos != -1) charset = regCs.cap(1);
        //QStringList css = ct.split("=");
        charset.remove(charset.length() - 1, 1);
        while(charset.contains("\""))
        {
            int p = charset.indexOf("\"");
            charset.remove(p, 1);
        }

        if(ct.contains("multipart")) continue;
        //qDebug() <<"Content-type: "<< ct;
        qDebug() <<"charset: "<< charset;

        request = "retr %1";
        request = request.arg(i);
        qDebug() << request;
        socket.write(request.toUtf8().data());
        socket.write("\r\n");
        QString str2;
        while (socket.waitForReadyRead(5000))
            str2 = socket.readAll().data();
        QRegExp body("\\r\\n\\r\\n((.*\\r\\n)*)\\.");
        pos = body.indexIn(str2);
        if(pos != -1)
        {
            str2 = body.cap(1);
        }
        data = str2;
        if(charset != "")
        {
            QTextCodec* codec = QTextCodec::codecForName(charset.toStdString().c_str());
            QTextDecoder *decoder = new QTextDecoder(codec);
            data = decoder->toUnicode(data.toStdString().c_str(), data.length());
            from = decoder->toUnicode(from.toStdString().c_str(), from.length());
            subject = decoder->toUnicode(subject.toStdString().c_str(), subject.length());
        }
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

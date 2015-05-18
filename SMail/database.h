#ifndef DATABASE
#define DATABASE

#include <QtSql>
#include <QtCore>
#include "account.h"
#include "message.h"
#include "base64.h"

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("smail");
    db.setUserName("root");
    db.setHostName("localhost");
    if(!db.open())
    {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}

void AddAccount(Account acc)
{
    QSqlQuery query;
    QString str = "INSERT INTO accounts (email, password, smtp_server, pop3_server, smtp_port, pop3_port) "
                    "VALUES('%1', '%2', '%3', '%4', %5, %6);";
    str = str.arg(acc.GetEmail())
             .arg(base64_encode(acc.GetPassword()))
             .arg(acc.GetSMTPServer())
             .arg(acc.GetPOP3Server())
             .arg(acc.GetSMTPport())
             .arg(acc.GetPOP3port());
    if(!query.exec(str))
    {
        qDebug() << "Unable to make insert operation";
    }
}

void AddMessage(Message msg, Account acc)
{
    QSqlQueryModel query;
    query.setQuery("SELECT id FROM accounts WHERE email = "+acc.GetEmail()+";");
    if(query.lastError().isValid())
    {
        qDebug() << query.lastError();
    }
    int accId = query.record(1).value("id").toInt();
    QString receivers = "";
    foreach(QString receiver, msg.GetReceivers())
    {
        receivers += receiver;
        receivers += ", ";
    }

    QSqlQuery model;
    QString strs = "INSERT INTO massages (account_id, from, to, subject, data, content_type, content_transfer_encoding, charset)"
                   "VALUES(%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8');";
    strs = strs.arg(accId)
             .arg(msg.GetSender())
             .arg(receivers)
             .arg(msg.GetSubject())
             .arg(msg.GetData())
             .arg(msg.GetCT())
             .arg(msg.GetCTE())
             .arg(msg.GetCS());
    if(!model.exec(strs))
    {
        qDebug() << "Unable to make insert operation";
    }
}

QList<Message> GetMessages(Account acc)
{
    QSqlQueryModel query;
    QList<Message> msgList;
    query.setQuery("SELECT id FROM accounts WHERE email = "+acc.GetEmail()+";");
    if(query.lastError().isValid())
    {
        qDebug() << query.lastError();
    }
    int accId = query.record(1).value("id").toInt();
    QString str = "SELECT * FROM messages WHERE account_id = %1;";
    str = str.arg(accId);
    query.setQuery(str);
    if(query.lastError().isValid())
    {
        qDebug() << query.lastError();
    }
    for(int i=0; i < query.rowCount(); i++)
    {
        QString from = query.record(i+1).value("sender").toString();
        QString to = query.record(i+1).value("receivers").toString();
        QString subject = query.record(i+1).value("subject").toString();
        QString data = query.record(i+1).value("data").toString();
        QString ct = query.record(i+1).value("content_type").toString();
        QString cte = query.record(i+1).value("content_transfer_encoding").toString();
        QString cs = query.record(i+1).value("charset").toString();
        Message msg(from, to, subject, data, ct, cte, cs);
        msgList.push_back(msg);
    }
    return msgList;
}

QList<Account> GetAccounts()
{
    QSqlQueryModel query;
    QList<Account> accList;
    query.setQuery("SELECT * FROM accounts;");
    if(query.lastError().isValid())
    {
        qDebug() << query.lastError();
    }
    for(int i=0; i < query.rowCount(); i++)
    {
        QString email = query.record(i+1).value("email").toString();
        QString pass = query.record(i+1).value("password").toString();
        QString smtpServer = query.record(i+1).value("smtp_server").toString();
        QString pop3Server = query.record(i+1).value("pop3_server").toString();
        int smtpPort = query.record(i+1).value("smtp_port").toInt();
        int pop3Port = query.record(i+1).value("pop3_port").toInt();
        Account acc(email, base64_decode(pass), smtpServer, pop3Server, smtpPort, pop3Port);
        accList.push_back(acc);
    }
    return accList;
}

#endif

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QtCore>

class Account
{
    QString Email;
    QString Password;
    QString SMTPServer;
    QString POP3Server;
    int SMTPport;
    int POP3port;
    bool isSSL;
public:
    Account();
    Account(QString email, QString password, QString server);
    Account(QString email, QString password, QString smtp_server, QString pop3_server, int smtp_port, int pop3_port, bool isssl = true);
    QString GetEmail();
    QString GetSMTPServer();
    QString GetPOP3Server();
    QString GetPassword();
    int GetSMTPport();
    int GetPOP3port();
    bool operator==(Account some);
};

#endif // ACCOUNT_H

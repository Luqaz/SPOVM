#include "account.h"

Account::Account()
{
    Email = "";
    Password = "";
    SMTPServer = "";
    SMTPport = 0;
    POP3Server = "";
    POP3port = 0;
    isSSL = false;
}

Account::Account(QString email, QString password, QString smtp_server, QString pop3_server, int smtp_port, int pop3_port, bool isssl)
{
    Email = email;
    Password = password;
    SMTPServer = smtp_server;
    SMTPport = smtp_port;
    POP3Server = pop3_server;
    POP3port = pop3_port;
    isSSL = isssl;
}

Account::Account(QString email, QString password, QString server)
{
    Email = email;
    Password = password;
    SMTPServer = server;
    if(SMTPServer == "smtp.gmail.com")
    {
        POP3Server = "pop.gmail.com";
        POP3port = 995;
        SMTPport = 465;
        isSSL = true;
    }
    else if(SMTPServer == "smtp.mail.yahoo.com")
    {
        POP3Server = "pop.mail.yahoo.com";
        POP3port = 995;
        SMTPport = 465;
        isSSL = true;
    }
    else if(SMTPServer == "smtp.mail.ru")
    {
        POP3Server = "pop.mail.ru";
        POP3port = 995;
        SMTPport = 465;
        isSSL = true;
    }
    else if(SMTPServer == "smtp.yandex.ru")
    {
        POP3Server = "pop.yandex.ru";
        POP3port = 995;
        SMTPport = 465;
        isSSL = true;
    }
    else if(SMTPServer == "mail.rambler.ru")
    {
        POP3Server = "mail.rambler.ru";
        POP3port = 995;
        SMTPport = 465;
        isSSL = true;
    }
    else if(SMTPServer == "smtp.aol.com")
    {
        POP3Server = "pop.aol.com";
        POP3port = 995;
        SMTPport = 587;
        isSSL = true;
    }
    else
    {
        POP3Server = "";
        POP3port = 995;
        SMTPport = 0;
        isSSL = false;
    }

}

QString Account::GetEmail()
{
    return Email;
}
QString Account::GetPassword()
{
    return Password;
}
int Account::GetPOP3port()
{
    return POP3port;
}
QString Account::GetPOP3Server()
{
    return POP3Server;
}
int Account::GetSMTPport()
{
    return SMTPport;
}
QString Account::GetSMTPServer()
{
    return SMTPServer;
}


bool Account::operator ==(Account some)
{
    if(this->Email == some.GetEmail())
    {
        return true;
    }
    else return false;
}

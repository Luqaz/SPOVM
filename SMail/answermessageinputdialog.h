#ifndef ANSWERMESSAGEINPUTDIALOG_H
#define ANSWERMESSAGEINPUTDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QLineEdit>
#include <QTextEdit>
#include "account.h"
#include "message.h"

class AnswerMessageInputDialog : public QDialog
{
Q_OBJECT
private:
    QTextEdit* data;
public:
    AnswerMessageInputDialog(Account &acc, Message &msg, QWidget *pwgt = 0);
    QString getData();
};

#endif // ANSWERMESSAGEINPUTDIALOG_H

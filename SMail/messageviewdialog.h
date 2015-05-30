#ifndef MESSAGEVIEWDIALOG_H
#define MESSAGEVIEWDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QLineEdit>
#include <QTextBrowser>
#include "message.h"

class MessageViewDialog : public QDialog
{
    Q_OBJECT

public:
    MessageViewDialog(Message &msg, QWidget *pwgt = 0);
};

#endif // MESSAGEVIEWDIALOG_H

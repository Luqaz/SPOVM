#ifndef NEWMESSAGEINPUTDIALOG_H
#define NEWMESSAGEINPUTDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QLineEdit>
#include <QTextEdit>

class NewMessageInputDialog : public QDialog
{
Q_OBJECT
private:
    QLineEdit* receivers;
    QLineEdit* subject;
    QTextEdit* data;
public:
    NewMessageInputDialog(QWidget *pwgt = 0);
    QString getReceivers() const;
    QString getSubject() const;
    QString getData() const;
};


#endif // NEWMESSAGEINPUTDIALOG_H

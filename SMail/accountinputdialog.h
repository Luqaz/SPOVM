#ifndef ACCOUNTINPUTDIALOG_H
#define ACCOUNTINPUTDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QLineEdit>

class AccountInputDialog : public QDialog
{
Q_OBJECT
private:
    QLineEdit* email;
    QLineEdit* password;
    QLineEdit* host;
public:
    AccountInputDialog(QWidget *pwgt = 0);
    QString getEmail() const;
    QString getPassword() const;
    QString getHost() const;
};

#endif // ACCOUNTINPUTDIALOG_H

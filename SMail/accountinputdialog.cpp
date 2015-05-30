#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "accountinputdialog.h"

AccountInputDialog::AccountInputDialog(QWidget* pwgt/*= 0*/)
    : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    email = new QLineEdit;
    password = new QLineEdit;
    host = new QLineEdit;

    password->setEchoMode(QLineEdit::EchoMode::Password);

    QLabel* lbl_email = new QLabel("&Email: ");
    QLabel* lbl_password = new QLabel("&Password: ");
    QLabel* lbl_host = new QLabel("&Host: ");

    lbl_email->setBuddy(email);
    lbl_host->setBuddy(host);
    lbl_password->setBuddy(password);

    QPushButton* btn_OK = new QPushButton("&Login");
    QPushButton* btn_Cancel = new QPushButton("&Cancel");

    connect(btn_OK, SIGNAL(clicked()), SLOT(accept()));
    connect(btn_Cancel, SIGNAL(clicked()), SLOT(reject()));

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(lbl_email, 0, 0);
    ptopLayout->addWidget(lbl_password, 1, 0);
    ptopLayout->addWidget(lbl_host, 2, 0);
    ptopLayout->addWidget(email, 0, 1);
    ptopLayout->addWidget(password, 1, 1);
    ptopLayout->addWidget(host, 2, 1);
    ptopLayout->addWidget(btn_OK, 3, 0);
    ptopLayout->addWidget(btn_Cancel, 3, 1);
    setLayout(ptopLayout);
}

QString AccountInputDialog::getEmail() const
{
    return email->text();
}

QString AccountInputDialog::getPassword() const
{
    return password->text();
}

QString AccountInputDialog::getHost() const
{
    return host->text();
}

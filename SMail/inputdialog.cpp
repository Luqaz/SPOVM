#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include "inputdialog.h"

NewMessageInputDialog::NewMessageInputDialog(QWidget* pwgt/*= 0*/)
    : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    receivers = new QLineEdit;
    subject = new QLineEdit;
    data = new QTextEdit;

    QPushButton* btn_OK = new QPushButton("&Send");
    QPushButton* btn_Cancel = new QPushButton("&Cancel");

    connect(btn_OK, SIGNAL(clicked()), SLOT(accept()));
    connect(btn_Cancel, SIGNAL(clicked()), SLOT(reject()));

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(receivers, 0, 0);
    ptopLayout->addWidget(subject, 1, 0);
    ptopLayout->addWidget(data, 2, 0);
    QGridLayout* btn_layout = new QGridLayout;
    btn_layout->addWidget(btn_OK, 0, 0);
    btn_layout->addWidget(btn_Cancel, 0, 1);
    ptopLayout->addLayout(btn_layout, 3, 0);
    setLayout(ptopLayout);
}

QString NewMessageInputDialog::getReceivers() const
{
    return receivers->text();
}

QString NewMessageInputDialog::getSubject() const
{
    return subject->text();
}

QString NewMessageInputDialog::getData() const
{
    return data->toPlainText();
}

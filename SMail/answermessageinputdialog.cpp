#include <QDialog>
#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include "answermessageinputdialog.h"

AnswerMessageInputDialog::AnswerMessageInputDialog(Account &acc, Message &msg, QWidget *pwgt)
    : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    data = new QTextEdit;

    QString str = "Sender: ";
    str.push_back(acc.GetEmail());
    QLabel* lbl_sender = new QLabel(str.toUtf8().constData());
    str.clear();
    str.push_back("Receiver: ");
    str.push_back(msg.GetSender());
    QLabel* lbl_receiver = new QLabel(str.toUtf8().constData());
    str.clear();
    str.push_back("Subject: ");
    str.push_back(msg.GetSubject());
    QLabel* lbl_Subject = new QLabel(str.toUtf8().constData());

    QPushButton* btn_OK = new QPushButton("&Send");
    QPushButton* btn_Cancel = new QPushButton("&Cancel");

    connect(btn_OK, SIGNAL(clicked()), SLOT(accept()));
    connect(btn_Cancel, SIGNAL(clicked()), SLOT(reject()));

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(lbl_sender, 0, 0);
    ptopLayout->addWidget(lbl_receiver, 1, 0);
    ptopLayout->addWidget(lbl_Subject, 2, 0);
    ptopLayout->addWidget(data, 3, 0);
    QGridLayout* btn_layout = new QGridLayout;
    btn_layout->addWidget(btn_OK, 0, 0);
    btn_layout->addWidget(btn_Cancel, 0, 1);
    ptopLayout->addLayout(btn_layout, 4, 0);
    setLayout(ptopLayout);
}

QString AnswerMessageInputDialog::getData()
{
    return data->toPlainText();
}


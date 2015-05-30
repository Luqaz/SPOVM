#include <QGridLayout>
#include "messageviewdialog.h"

MessageViewDialog::MessageViewDialog(Message &msg, QWidget *pwgt)
    :QDialog(pwgt)
{
    QLineEdit *le_sender = new QLineEdit(msg.GetSender());
    QLineEdit *le_receiver = new QLineEdit(msg.GetReceivers()[0]);
    QLineEdit *le_subject = new QLineEdit(msg.GetSubject());

    le_sender->setReadOnly(true);
    le_receiver->setReadOnly(true);
    le_subject->setReadOnly(true);

    QTextBrowser *dataBrowser = new QTextBrowser;
    dataBrowser->append(msg.GetData());
    dataBrowser->setReadOnly(true);

    QGridLayout *ptop_layout = new QGridLayout;
    ptop_layout->addWidget(le_sender, 0, 0);
    ptop_layout->addWidget(le_receiver, 1, 0);
    ptop_layout->addWidget(le_subject, 2, 0);
    ptop_layout->addWidget(dataBrowser, 3, 0, 4, 1);
    setLayout(ptop_layout);
}


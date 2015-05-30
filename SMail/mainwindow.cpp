#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accountinputdialog.h"
#include "inputdialog.h"
#include "answermessageinputdialog.h"
#include "messageviewdialog.h"
#include "account.h"
#include "message.h"
#include "pop3.h"
#include "smtp.h"
#include "database.h"
#include <QStandardItemModel>
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = createConnection();
    userAccounts = GetAccounts();
    foreach(Account user, userAccounts)
    {
        userNames.push_back(user.GetEmail());
        userMessages.push_back(GetMessages(user));
    }
    foreach(QString user, userNames)
    {
        ui->AccountList->addItem(user);
    }
    
    db.close();
}

MainWindow::~MainWindow()
{
    QList<Account> oldUserAccounts = GetAccounts();
    foreach(Account user, userAccounts)
    {
        if(!oldUserAccounts.contains(user))
        {
            AddAccount(user);
        }
    }
    delete ui;
}


void MainWindow::on_addAccountButton_clicked()
{
    AccountInputDialog* inputDialog = new AccountInputDialog;
    if(inputDialog->exec() == QDialog::Accepted)
    {
        Account newAcc(inputDialog->getEmail(), inputDialog->getPassword(), inputDialog->getHost());
        userAccounts.push_back(newAcc);
        userNames.push_back(inputDialog->getEmail());
        ui->AccountList->addItem(newAcc.GetEmail());
        AddAccount(newAcc);
    }
    delete inputDialog;
}

void MainWindow::on_AccountList_itemDoubleClicked(QListWidgetItem *item)
{
    int i = userNames.indexOf(item->text());
    if(userMessages.isEmpty())
    {
        QList<Message> newmsgl;
        userMessages.push_back(newmsgl);
    }
    if(userMessages[i].isEmpty() || userMessages[i].count() < getStat(userAccounts[i]))
    {
        userMessages[i] = POP3Receiver(userAccounts[i]);
    }
    ui->MessageList->clear();
    foreach (Message msg, userMessages[i])
    {
        ui->MessageList->addItem(msg.GetSubject());
    }
}


void MainWindow::on_sendButton_clicked()
{
    NewMessageInputDialog* inputDialog = new NewMessageInputDialog;
    if(inputDialog->exec() == QDialog::Accepted)
    {
        if(ui->AccountList->currentItem()->text() != NULL)
        {
            Message msg(ui->AccountList->currentItem()->text(),
                        inputDialog->getReceivers(),
                        inputDialog->getSubject(),
                        inputDialog->getData());
            int i = ui->AccountList->currentIndex().row();
            std::thread some(SMTPSender, msg, userAccounts[i]);
            some.detach();
        }
    }
    delete inputDialog;
}

void MainWindow::on_MessageList_itemDoubleClicked(QListWidgetItem *item)
{
    Account acc = userAccounts[ui->AccountList->currentIndex().row()];
    Message msg = userMessages[ui->AccountList->currentIndex().row()][ui->MessageList->currentIndex().row()];
    AnswerMessageInputDialog* inputDialog = new AnswerMessageInputDialog(acc, msg);
    if(inputDialog->exec() == QDialog::Accepted)
    {
        Message answer(acc.GetEmail(), msg.GetReceivers()[0], msg.GetSubject(), inputDialog->getData());
        std::thread some(SMTPSender, answer, acc);
        some.detach();
    }
    delete inputDialog;
}

void MainWindow::on_MessageList_itemClicked(QListWidgetItem *item)
{
    MessageViewDialog* dialog = new MessageViewDialog(userMessages[ui->AccountList->currentIndex().row()][ui->MessageList->currentIndex().row()], this);
    dialog->setModal(false);
    dialog->show();
}

void MainWindow::on_deleteButton_clicked()
{
    Account acc = userAccounts[ui->AccountList->currentIndex().row()];
    DeleteAccount(acc);
    userAccounts.removeAt(ui->AccountList->currentIndex().row());
    QListWidgetItem *it = ui->AccountList->currentItem();
    delete it;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include "account.h"
#include "message.h"
#include "inputdialog.h"
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_addAccountButton_clicked();

    void on_AccountList_itemDoubleClicked(QListWidgetItem *item);

    void on_sendButton_clicked();

    void on_MessageList_itemDoubleClicked(QListWidgetItem *item);

    void on_MessageList_itemClicked(QListWidgetItem *item);

    void on_deleteButton_clicked();

private:
    QList<Account> userAccounts;
    QList<QList<Message>> userMessages;
    QStringList userNames;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListWidget *AccountList;
    QListWidget *MessageList;
    QPushButton *sendButton;
    QPushButton *addAccountButton;
    QPushButton *deleteButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(813, 493);
        MainWindow->setMinimumSize(QSize(813, 493));
        MainWindow->setMaximumSize(QSize(813, 493));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color:  rgb(255, 255, 255)"));
        AccountList = new QListWidget(centralWidget);
        AccountList->setObjectName(QStringLiteral("AccountList"));
        AccountList->setGeometry(QRect(10, 100, 256, 351));
        AccountList->setResizeMode(QListView::Adjust);
        MessageList = new QListWidget(centralWidget);
        MessageList->setObjectName(QStringLiteral("MessageList"));
        MessageList->setGeometry(QRect(270, 100, 521, 351));
        MessageList->setResizeMode(QListView::Adjust);
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(714, 460, 81, 23));
        addAccountButton = new QPushButton(centralWidget);
        addAccountButton->setObjectName(QStringLiteral("addAccountButton"));
        addAccountButton->setGeometry(QRect(110, 460, 75, 23));
        deleteButton = new QPushButton(centralWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(190, 460, 75, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        sendButton->setText(QApplication::translate("MainWindow", "Send Message", 0));
        addAccountButton->setText(QApplication::translate("MainWindow", "Add Account", 0));
        deleteButton->setText(QApplication::translate("MainWindow", "Delete", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

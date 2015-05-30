/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
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
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListView *AccountList;
    QListView *MessageList;
    QPushButton *answerButton;
    QPushButton *addAccountButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(813, 493);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color:  rgb(255, 255, 255)"));
        AccountList = new QListView(centralWidget);
        AccountList->setObjectName(QStringLiteral("AccountList"));
        AccountList->setGeometry(QRect(10, 100, 256, 351));
        MessageList = new QListView(centralWidget);
        MessageList->setObjectName(QStringLiteral("MessageList"));
        MessageList->setGeometry(QRect(270, 100, 521, 351));
        answerButton = new QPushButton(centralWidget);
        answerButton->setObjectName(QStringLiteral("answerButton"));
        answerButton->setGeometry(QRect(720, 460, 75, 23));
        addAccountButton = new QPushButton(centralWidget);
        addAccountButton->setObjectName(QStringLiteral("addAccountButton"));
        addAccountButton->setGeometry(QRect(190, 460, 75, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        answerButton->setText(QApplication::translate("MainWindow", "Answer", 0));
        addAccountButton->setText(QApplication::translate("MainWindow", "Add Account", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

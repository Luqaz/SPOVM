#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget wgt;

    QPushButton* AddBtn = new QPushButton("Add");
    QPushButton* AnswerBtn = new QPushButton("Answer");

    MainWindow w;
    QVBoxLayout* layout = new QVBoxLayout();

    QFile file("C:\\6 sem\\Kursach\\SPOVM\\SMail\\style.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet = QString(file.readAll());
        a.setStyleSheet(styleSheet);
    }
    file.close();

    layout->addWidget(AddBtn);
    layout->addWidget(AnswerBtn);

    wgt.setLayout(layout);
    wgt.show();
    return a.exec();
}

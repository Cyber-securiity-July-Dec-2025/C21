/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topRow;
    QPushButton *btnConnect;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnDisconnect;
    QSpacerItem *horizontalSpacer;
    QLabel *lblStatus;
    QLabel *lblRound;
    QTextEdit *txtLog;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(780, 520);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        topRow = new QHBoxLayout();
        topRow->setObjectName(QString::fromUtf8("topRow"));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        topRow->addWidget(btnConnect);

        btnStart = new QPushButton(centralWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        topRow->addWidget(btnStart);

        btnStop = new QPushButton(centralWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        topRow->addWidget(btnStop);

        btnDisconnect = new QPushButton(centralWidget);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));

        topRow->addWidget(btnDisconnect);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topRow->addItem(horizontalSpacer);

        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));

        topRow->addWidget(lblStatus);

        lblRound = new QLabel(centralWidget);
        lblRound->setObjectName(QString::fromUtf8("lblRound"));

        topRow->addWidget(lblRound);


        verticalLayout->addLayout(topRow);

        txtLog = new QTextEdit(centralWidget);
        txtLog->setObjectName(QString::fromUtf8("txtLog"));
        txtLog->setReadOnly(true);

        verticalLayout->addWidget(txtLog);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Lamport Auth Demo", nullptr));
        btnConnect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        btnStart->setText(QApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        btnDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        lblStatus->setText(QApplication::translate("MainWindow", "Status: Idle", nullptr));
        lblRound->setText(QApplication::translate("MainWindow", "Round: 0 / 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

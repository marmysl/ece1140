/********************************************************************************
** Form generated from reading UI file 'TrainController.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAINCONTROLLER_H
#define UI_TRAINCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *kp_label;
    QLabel *ki_label;
    QPlainTextEdit *kp_textbox;
    QPlainTextEdit *ki_textbox;
    QPushButton *submit;
    QLabel *pcmd_label;
    QLabel *p_out_label;
    QLabel *kW_label;
    QPushButton *sendPowerButton;
    QPushButton *getCircuitInfoButton;
    QPushButton *decodeButton;
    QLabel *circuitInfo;
    QLabel *sugspeedlabel;
    QLabel *authlabel;
    QLabel *suggested_speed_label;
    QLabel *authority_label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(949, 594);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        kp_label = new QLabel(centralwidget);
        kp_label->setObjectName(QString::fromUtf8("kp_label"));
        kp_label->setGeometry(QRect(100, 60, 58, 16));
        ki_label = new QLabel(centralwidget);
        ki_label->setObjectName(QString::fromUtf8("ki_label"));
        ki_label->setGeometry(QRect(100, 120, 58, 16));
        kp_textbox = new QPlainTextEdit(centralwidget);
        kp_textbox->setObjectName(QString::fromUtf8("kp_textbox"));
        kp_textbox->setGeometry(QRect(160, 60, 91, 31));
        ki_textbox = new QPlainTextEdit(centralwidget);
        ki_textbox->setObjectName(QString::fromUtf8("ki_textbox"));
        ki_textbox->setGeometry(QRect(160, 110, 91, 31));
        submit = new QPushButton(centralwidget);
        submit->setObjectName(QString::fromUtf8("submit"));
        submit->setGeometry(QRect(290, 90, 80, 24));
        pcmd_label = new QLabel(centralwidget);
        pcmd_label->setObjectName(QString::fromUtf8("pcmd_label"));
        pcmd_label->setGeometry(QRect(500, 80, 171, 21));
        p_out_label = new QLabel(centralwidget);
        p_out_label->setObjectName(QString::fromUtf8("p_out_label"));
        p_out_label->setGeometry(QRect(710, 80, 58, 16));
        kW_label = new QLabel(centralwidget);
        kW_label->setObjectName(QString::fromUtf8("kW_label"));
        kW_label->setGeometry(QRect(760, 80, 58, 16));
        sendPowerButton = new QPushButton(centralwidget);
        sendPowerButton->setObjectName(QString::fromUtf8("sendPowerButton"));
        sendPowerButton->setGeometry(QRect(570, 120, 141, 61));
        getCircuitInfoButton = new QPushButton(centralwidget);
        getCircuitInfoButton->setObjectName(QString::fromUtf8("getCircuitInfoButton"));
        getCircuitInfoButton->setGeometry(QRect(130, 280, 201, 41));
        decodeButton = new QPushButton(centralwidget);
        decodeButton->setObjectName(QString::fromUtf8("decodeButton"));
        decodeButton->setGeometry(QRect(190, 350, 201, 41));
        circuitInfo = new QLabel(centralwidget);
        circuitInfo->setObjectName(QString::fromUtf8("circuitInfo"));
        circuitInfo->setGeometry(QRect(540, 320, 101, 21));
        sugspeedlabel = new QLabel(centralwidget);
        sugspeedlabel->setObjectName(QString::fromUtf8("sugspeedlabel"));
        sugspeedlabel->setGeometry(QRect(480, 370, 121, 21));
        authlabel = new QLabel(centralwidget);
        authlabel->setObjectName(QString::fromUtf8("authlabel"));
        authlabel->setGeometry(QRect(480, 410, 58, 16));
        suggested_speed_label = new QLabel(centralwidget);
        suggested_speed_label->setObjectName(QString::fromUtf8("suggested_speed_label"));
        suggested_speed_label->setGeometry(QRect(630, 370, 58, 16));
        authority_label = new QLabel(centralwidget);
        authority_label->setObjectName(QString::fromUtf8("authority_label"));
        authority_label->setGeometry(QRect(620, 410, 58, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 949, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        kp_label->setText(QCoreApplication::translate("MainWindow", "Kp:", nullptr));
        ki_label->setText(QCoreApplication::translate("MainWindow", "Ki:", nullptr));
        submit->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        pcmd_label->setText(QCoreApplication::translate("MainWindow", "The power commanded is:", nullptr));
        p_out_label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        kW_label->setText(QCoreApplication::translate("MainWindow", "kW", nullptr));
        sendPowerButton->setText(QCoreApplication::translate("MainWindow", "SET POWER", nullptr));
        getCircuitInfoButton->setText(QCoreApplication::translate("MainWindow", "Get Track Circuit Info", nullptr));
        decodeButton->setText(QCoreApplication::translate("MainWindow", "Decode Circuit Info", nullptr));
        circuitInfo->setText(QCoreApplication::translate("MainWindow", "Circuit info:", nullptr));
        sugspeedlabel->setText(QCoreApplication::translate("MainWindow", "Suggested Speed:", nullptr));
        authlabel->setText(QCoreApplication::translate("MainWindow", "Authority:", nullptr));
        suggested_speed_label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        authority_label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAINCONTROLLER_H

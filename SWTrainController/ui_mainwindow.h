/********************************************************************************
** Form generated from reading UI file 'traincontrollerGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
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
    QTextEdit *test_box;
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
        submit->setGeometry(QRect(420, 90, 80, 24));
        pcmd_label = new QLabel(centralwidget);
        pcmd_label->setObjectName(QString::fromUtf8("pcmd_label"));
        pcmd_label->setGeometry(QRect(140, 250, 171, 21));
        p_out_label = new QLabel(centralwidget);
        p_out_label->setObjectName(QString::fromUtf8("p_out_label"));
        p_out_label->setGeometry(QRect(350, 250, 58, 16));
        kW_label = new QLabel(centralwidget);
        kW_label->setObjectName(QString::fromUtf8("kW_label"));
        kW_label->setGeometry(QRect(400, 250, 58, 16));
        test_box = new QTextEdit(centralwidget);
        test_box->setObjectName(QString::fromUtf8("test_box"));
        test_box->setGeometry(QRect(250, 400, 431, 71));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

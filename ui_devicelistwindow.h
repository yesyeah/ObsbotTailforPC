/********************************************************************************
** Form generated from reading UI file 'devicelistwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICELISTWINDOW_H
#define UI_DEVICELISTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_devicelistwindow
{
public:
    QWidget *centralwidget;
    QLabel *deviceLabel;
    QListView *deviceList;
    QLabel *deviceLabel_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *devicelistwindow)
    {
        if (devicelistwindow->objectName().isEmpty())
            devicelistwindow->setObjectName(QString::fromUtf8("devicelistwindow"));
        devicelistwindow->resize(400, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon/defaultlaunch.png"), QSize(), QIcon::Normal, QIcon::Off);
        devicelistwindow->setWindowIcon(icon);
        devicelistwindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(devicelistwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        deviceLabel = new QLabel(centralwidget);
        deviceLabel->setObjectName(QString::fromUtf8("deviceLabel"));
        deviceLabel->setGeometry(QRect(30, 20, 311, 16));
        deviceLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        deviceList = new QListView(centralwidget);
        deviceList->setObjectName(QString::fromUtf8("deviceList"));
        deviceList->setGeometry(QRect(30, 50, 341, 461));
        deviceList->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);"));
        deviceLabel_2 = new QLabel(centralwidget);
        deviceLabel_2->setObjectName(QString::fromUtf8("deviceLabel_2"));
        deviceLabel_2->setGeometry(QRect(30, 520, 311, 16));
        deviceLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(140, 140, 140);"));
        devicelistwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(devicelistwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 25));
        devicelistwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(devicelistwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        devicelistwindow->setStatusBar(statusbar);

        retranslateUi(devicelistwindow);

        QMetaObject::connectSlotsByName(devicelistwindow);
    } // setupUi

    void retranslateUi(QMainWindow *devicelistwindow)
    {
        devicelistwindow->setWindowTitle(QCoreApplication::translate("devicelistwindow", "\346\220\234\347\264\242\350\256\276\345\244\207", nullptr));
        deviceLabel->setText(QCoreApplication::translate("devicelistwindow", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        deviceLabel_2->setText(QCoreApplication::translate("devicelistwindow", "\346\220\234\347\264\242\350\256\276\345\244\207\351\234\200\344\270\200\344\272\233\346\227\266\351\227\264\357\274\214\350\257\267\350\200\220\345\277\203\347\255\211\345\276\205\342\200\246\342\200\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class devicelistwindow: public Ui_devicelistwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICELISTWINDOW_H

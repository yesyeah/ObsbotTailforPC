/********************************************************************************
** Form generated from reading UI file 'netcfgdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETCFGDIALOG_H
#define UI_NETCFGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NetCfgDialog
{
public:
    QPushButton *pushButton;
    QLineEdit *wifiSSIDEdit;
    QLineEdit *wifiPasswordEdit;
    QLabel *ssidLabel;
    QLabel *passwordLabel;
    QLabel *label;

    void setupUi(QDialog *NetCfgDialog)
    {
        if (NetCfgDialog->objectName().isEmpty())
            NetCfgDialog->setObjectName(QString::fromUtf8("NetCfgDialog"));
        NetCfgDialog->resize(400, 300);
        NetCfgDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);"));
        pushButton = new QPushButton(NetCfgDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 120, 89, 24));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);\n"
"color: rgb(255, 255, 255);"));
        wifiSSIDEdit = new QLineEdit(NetCfgDialog);
        wifiSSIDEdit->setObjectName(QString::fromUtf8("wifiSSIDEdit"));
        wifiSSIDEdit->setGeometry(QRect(50, 80, 221, 31));
        wifiSSIDEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        wifiPasswordEdit = new QLineEdit(NetCfgDialog);
        wifiPasswordEdit->setObjectName(QString::fromUtf8("wifiPasswordEdit"));
        wifiPasswordEdit->setGeometry(QRect(50, 150, 221, 31));
        wifiPasswordEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        ssidLabel = new QLabel(NetCfgDialog);
        ssidLabel->setObjectName(QString::fromUtf8("ssidLabel"));
        ssidLabel->setGeometry(QRect(50, 60, 72, 15));
        ssidLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        passwordLabel = new QLabel(NetCfgDialog);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setGeometry(QRect(50, 130, 72, 15));
        passwordLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label = new QLabel(NetCfgDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 210, 351, 41));
        label->setStyleSheet(QString::fromUtf8("color: rgb(140, 140, 140);"));
        label->setWordWrap(true);

        retranslateUi(NetCfgDialog);

        QMetaObject::connectSlotsByName(NetCfgDialog);
    } // setupUi

    void retranslateUi(QDialog *NetCfgDialog)
    {
        NetCfgDialog->setWindowTitle(QCoreApplication::translate("NetCfgDialog", "\347\275\221\347\273\234\351\205\215\347\275\256", nullptr));
        pushButton->setText(QCoreApplication::translate("NetCfgDialog", "\347\241\256\345\256\232", nullptr));
        ssidLabel->setText(QCoreApplication::translate("NetCfgDialog", "WiFi SSID", nullptr));
        passwordLabel->setText(QCoreApplication::translate("NetCfgDialog", "WiFi \345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("NetCfgDialog", "\345\275\223\350\256\276\345\244\207\345\270\270\344\272\256\347\264\253\347\201\257\346\227\266\357\274\214\347\275\221\347\273\234\351\205\215\347\275\256\345\256\214\346\210\220\343\200\202\350\257\267\345\205\263\351\227\255\350\257\245\347\252\227\345\217\243\357\274\214\344\275\277\347\224\250station\346\250\241\345\274\217\350\277\236\346\216\245\347\233\270\346\234\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetCfgDialog: public Ui_NetCfgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETCFGDIALOG_H

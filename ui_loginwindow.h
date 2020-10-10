/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginWindow
{
public:
    QWidget *centralwidget;
    QPushButton *deviceSearchButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *connectLabel;
    QComboBox *connectComboBox;
    QPushButton *cameraNetCfgButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *loginWindow)
    {
        if (loginWindow->objectName().isEmpty())
            loginWindow->setObjectName(QString::fromUtf8("loginWindow"));
        loginWindow->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon/defaultlaunch.png"), QSize(), QIcon::Normal, QIcon::Off);
        loginWindow->setWindowIcon(icon);
        loginWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        loginWindow->setAnimated(false);
        centralwidget = new QWidget(loginWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        deviceSearchButton = new QPushButton(centralwidget);
        deviceSearchButton->setObjectName(QString::fromUtf8("deviceSearchButton"));
        deviceSearchButton->setGeometry(QRect(190, 130, 100, 40));
        deviceSearchButton->setMinimumSize(QSize(100, 40));
        deviceSearchButton->setMaximumSize(QSize(100, 40));
        deviceSearchButton->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);\n"
"color: rgb(255, 255, 255);"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 20, 211, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        connectLabel = new QLabel(layoutWidget);
        connectLabel->setObjectName(QString::fromUtf8("connectLabel"));
        connectLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(connectLabel);

        connectComboBox = new QComboBox(layoutWidget);
        connectComboBox->addItem(QString());
        connectComboBox->addItem(QString());
        connectComboBox->setObjectName(QString::fromUtf8("connectComboBox"));
        connectComboBox->setMinimumSize(QSize(0, 40));
        connectComboBox->setMaximumSize(QSize(16777215, 40));
        connectComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);\n"
"selection-background-color: rgb(30,30,30);\n"
"color: rgb(255, 255, 255);"));
        connectComboBox->setEditable(false);

        verticalLayout->addWidget(connectComboBox);

        cameraNetCfgButton = new QPushButton(centralwidget);
        cameraNetCfgButton->setObjectName(QString::fromUtf8("cameraNetCfgButton"));
        cameraNetCfgButton->setGeometry(QRect(80, 130, 100, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Arabic"));
        cameraNetCfgButton->setFont(font);
        cameraNetCfgButton->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);\n"
"color: rgb(255, 255, 255);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 200, 371, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SimSun-ExtB"));
        font1.setPointSize(9);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(150, 150, 150);"));
        label->setTextFormat(Qt::PlainText);
        label->setWordWrap(true);
        loginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(loginWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 25));
        loginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(loginWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        loginWindow->setStatusBar(statusbar);

        retranslateUi(loginWindow);

        QMetaObject::connectSlotsByName(loginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *loginWindow)
    {
        loginWindow->setWindowTitle(QCoreApplication::translate("loginWindow", "\346\254\242\350\277\216\344\275\277\347\224\250CECV\347\233\270\346\234\272\346\216\247\345\210\266\345\271\263\345\217\260", nullptr));
        deviceSearchButton->setText(QCoreApplication::translate("loginWindow", "\346\220\234\347\264\242\350\256\276\345\244\207", nullptr));
        connectLabel->setText(QCoreApplication::translate("loginWindow", "\350\277\236\346\216\245\346\226\271\345\274\217", nullptr));
        connectComboBox->setItemText(0, QCoreApplication::translate("loginWindow", "Station mode", nullptr));
        connectComboBox->setItemText(1, QCoreApplication::translate("loginWindow", "AP mode", nullptr));

        connectComboBox->setCurrentText(QCoreApplication::translate("loginWindow", "Station mode", nullptr));
        cameraNetCfgButton->setText(QCoreApplication::translate("loginWindow", "\347\233\270\346\234\272\351\205\215\347\275\221", nullptr));
        label->setText(QCoreApplication::translate("loginWindow", "\351\200\232\350\277\207station\346\250\241\345\274\217\350\277\236\346\216\245\347\233\270\346\234\272\345\211\215\357\274\214\350\257\267\345\205\210\347\224\250\347\224\265\350\204\221\347\275\221\347\273\234\350\277\236\346\216\245\345\210\260\350\256\276\345\244\207\347\203\255\347\202\271\357\274\214\345\206\215\351\200\232\350\277\207\347\233\270\346\234\272\351\205\215\347\275\221\357\274\214\345\260\206\347\233\270\346\234\272\350\277\236\346\216\245\345\210\260\350\267\257\347\224\261\345\231\250WiFi\357\274\214\346\234\200\345\220\216\345\260\206\347\224\265\350\204\221\344\271\237\350\277\236\345\205\245\350\267\257\347\224\261\345\231\250\347\275\221\347\273\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginWindow: public Ui_loginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

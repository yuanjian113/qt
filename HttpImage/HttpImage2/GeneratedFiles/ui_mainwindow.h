/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Mar 7 21:18:31 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QLabel *label;
    QPushButton *searchBtn;
    QLineEdit *urlLineEdit;
    QGroupBox *groupBox;
    QListView *listView;
    QLabel *countLbl;
    QPushButton *saveBtn;
    QPushButton *pathSetBtn;

    void setupUi(QDialog *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(455, 441);
        label = new QLabel(MainWindowClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 54, 12));
        searchBtn = new QPushButton(MainWindowClass);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));
        searchBtn->setGeometry(QRect(190, 60, 75, 23));
        urlLineEdit = new QLineEdit(MainWindowClass);
        urlLineEdit->setObjectName(QString::fromUtf8("urlLineEdit"));
        urlLineEdit->setGeometry(QRect(80, 20, 321, 20));
        groupBox = new QGroupBox(MainWindowClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 90, 411, 291));
        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(25, 50, 371, 231));
        countLbl = new QLabel(groupBox);
        countLbl->setObjectName(QString::fromUtf8("countLbl"));
        countLbl->setGeometry(QRect(30, 20, 351, 16));
        saveBtn = new QPushButton(MainWindowClass);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setGeometry(QRect(350, 400, 75, 23));
        pathSetBtn = new QPushButton(MainWindowClass);
        pathSetBtn->setObjectName(QString::fromUtf8("pathSetBtn"));
        pathSetBtn->setGeometry(QRect(250, 400, 75, 23));

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QDialog *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "URL\357\274\232", 0, QApplication::UnicodeUTF8));
        searchBtn->setText(QApplication::translate("MainWindowClass", "Search", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "Result", 0, QApplication::UnicodeUTF8));
        countLbl->setText(QApplication::translate("MainWindowClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        saveBtn->setText(QApplication::translate("MainWindowClass", "save", 0, QApplication::UnicodeUTF8));
        pathSetBtn->setText(QApplication::translate("MainWindowClass", "savePath...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

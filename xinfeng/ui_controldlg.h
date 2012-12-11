/********************************************************************************
** Form generated from reading UI file 'controldlg.ui'
**
** Created: Wed Jul 4 22:08:18 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLDLG_H
#define UI_CONTROLDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ControlDlg
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *textEditName;
    QTextEdit *textEditNumber;
    QTextEdit *textEditEmail;
    QTextEdit *textEditAddress;
    QPushButton *pushButtonUpadte;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ControlDlg)
    {
        if (ControlDlg->objectName().isEmpty())
            ControlDlg->setObjectName(QString::fromUtf8("ControlDlg"));
        ControlDlg->resize(349, 269);
        label = new QLabel(ControlDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 54, 12));
        label_2 = new QLabel(ControlDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 80, 54, 12));
        label_3 = new QLabel(ControlDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 41, 16));
        label_4 = new QLabel(ControlDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 160, 41, 16));
        textEditName = new QTextEdit(ControlDlg);
        textEditName->setObjectName(QString::fromUtf8("textEditName"));
        textEditName->setGeometry(QRect(100, 30, 181, 31));
        textEditNumber = new QTextEdit(ControlDlg);
        textEditNumber->setObjectName(QString::fromUtf8("textEditNumber"));
        textEditNumber->setGeometry(QRect(100, 70, 181, 31));
        textEditEmail = new QTextEdit(ControlDlg);
        textEditEmail->setObjectName(QString::fromUtf8("textEditEmail"));
        textEditEmail->setGeometry(QRect(100, 110, 181, 31));
        textEditAddress = new QTextEdit(ControlDlg);
        textEditAddress->setObjectName(QString::fromUtf8("textEditAddress"));
        textEditAddress->setGeometry(QRect(100, 150, 181, 31));
        pushButtonUpadte = new QPushButton(ControlDlg);
        pushButtonUpadte->setObjectName(QString::fromUtf8("pushButtonUpadte"));
        pushButtonUpadte->setGeometry(QRect(40, 210, 75, 23));
        pushButtonCancel = new QPushButton(ControlDlg);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(210, 210, 75, 23));

        retranslateUi(ControlDlg);

        QMetaObject::connectSlotsByName(ControlDlg);
    } // setupUi

    void retranslateUi(QDialog *ControlDlg)
    {
        ControlDlg->setWindowTitle(QApplication::translate("ControlDlg", "\344\270\252\344\272\272\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ControlDlg", "\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ControlDlg", "\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ControlDlg", "\351\202\256\347\256\261\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ControlDlg", "\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButtonUpadte->setText(QApplication::translate("ControlDlg", "\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("ControlDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControlDlg: public Ui_ControlDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLDLG_H

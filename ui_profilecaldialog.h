/********************************************************************************
** Form generated from reading UI file 'profilecaldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILECALDIALOG_H
#define UI_PROFILECALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ProfileCalDialog
{
public:
    QToolButton *savedata;
    QLabel *label_5;
    QLabel *label_4;
    QToolButton *calculate;
    QLabel *label_3;
    QLabel *label_6;
    QTextBrowser *textBrowser;
    QLineEdit *deepth1;
    QLineEdit *deepth2;
    QToolButton *openfile;
    QGraphicsView *graphicsView;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_7;

    void setupUi(QDialog *ProfileCalDialog)
    {
        if (ProfileCalDialog->objectName().isEmpty())
            ProfileCalDialog->setObjectName(QStringLiteral("ProfileCalDialog"));
        ProfileCalDialog->resize(1042, 592);
        savedata = new QToolButton(ProfileCalDialog);
        savedata->setObjectName(QStringLiteral("savedata"));
        savedata->setGeometry(QRect(850, 560, 71, 18));
        label_5 = new QLabel(ProfileCalDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(750, 310, 161, 20));
        label_4 = new QLabel(ProfileCalDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(750, 290, 261, 21));
        calculate = new QToolButton(ProfileCalDialog);
        calculate->setObjectName(QStringLiteral("calculate"));
        calculate->setGeometry(QRect(850, 530, 71, 18));
        label_3 = new QLabel(ProfileCalDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(770, 220, 54, 12));
        label_6 = new QLabel(ProfileCalDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(750, 190, 261, 21));
        textBrowser = new QTextBrowser(ProfileCalDialog);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(750, 40, 261, 141));
        deepth1 = new QLineEdit(ProfileCalDialog);
        deepth1->setObjectName(QStringLiteral("deepth1"));
        deepth1->setGeometry(QRect(890, 220, 61, 20));
        deepth2 = new QLineEdit(ProfileCalDialog);
        deepth2->setObjectName(QStringLiteral("deepth2"));
        deepth2->setGeometry(QRect(890, 250, 61, 20));
        openfile = new QToolButton(ProfileCalDialog);
        openfile->setObjectName(QStringLiteral("openfile"));
        openfile->setGeometry(QRect(840, 10, 91, 18));
        graphicsView = new QGraphicsView(ProfileCalDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(30, 20, 701, 551));
        plainTextEdit = new QPlainTextEdit(ProfileCalDialog);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(740, 380, 271, 141));
        label_7 = new QLabel(ProfileCalDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(770, 250, 54, 12));

        retranslateUi(ProfileCalDialog);

        QMetaObject::connectSlotsByName(ProfileCalDialog);
    } // setupUi

    void retranslateUi(QDialog *ProfileCalDialog)
    {
        ProfileCalDialog->setWindowTitle(QApplication::translate("ProfileCalDialog", "Dialog", 0));
        savedata->setText(QApplication::translate("ProfileCalDialog", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        label_5->setText(QApplication::translate("ProfileCalDialog", "\345\241\253\345\205\245\344\270\213\351\235\242\357\274\214\346\240\274\345\274\217\345\246\202\344\270\213", 0));
        label_4->setText(QApplication::translate("ProfileCalDialog", "\350\257\267\345\260\206\345\211\251\344\270\213\347\232\204\344\272\225\347\202\271\344\273\216\345\267\246\345\210\260\345\217\263\346\214\211\351\241\272\345\272\217\346\240\207\350\256\260\357\274\214\345\271\266\345\260\206\345\235\220\346\240\207", 0));
        calculate->setText(QApplication::translate("ProfileCalDialog", "\350\256\241\347\256\227", 0));
        label_3->setText(QApplication::translate("ProfileCalDialog", "Z1", 0));
        label_6->setText(QApplication::translate("ProfileCalDialog", "\350\257\267\345\260\206\345\234\250\345\233\276\344\270\255Z\345\235\220\346\240\207\345\260\272\351\200\211\346\213\251\344\270\244\344\270\252\347\202\271\357\274\214\345\271\266\345\241\253\345\206\231\345\205\266\346\267\261\345\272\246", 0));
        deepth1->setText(QApplication::translate("ProfileCalDialog", " -16000 ", 0));
        deepth2->setText(QApplication::translate("ProfileCalDialog", " -28000 ", 0));
        openfile->setText(QApplication::translate("ProfileCalDialog", "\346\211\223\345\274\200\350\277\236\344\272\225\345\211\226\351\235\242\345\233\276", 0));
        plainTextEdit->setPlainText(QApplication::translate("ProfileCalDialog", "15263550.05 4965333.35 \344\272\2251\n"
"15270689.93 4965651.65 \344\272\2252\n"
"15277180.23 4966450.02 \344\272\2253\n"
"15282490.27 4966610.31 \344\272\2254\n"
"15286231.42 4966455.20 \344\272\2255", 0));
        label_7->setText(QApplication::translate("ProfileCalDialog", "Z2", 0));
    } // retranslateUi

};

namespace Ui {
    class ProfileCalDialog: public Ui_ProfileCalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILECALDIALOG_H

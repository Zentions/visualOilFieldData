/********************************************************************************
** Form generated from reading UI file 'checkdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKDIALOG_H
#define UI_CHECKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckDialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTreeWidget *treeWidget;
    QPushButton *pushButton_4;

    void setupUi(QDialog *CheckDialog)
    {
        if (CheckDialog->objectName().isEmpty())
            CheckDialog->setObjectName(QStringLiteral("CheckDialog"));
        CheckDialog->resize(723, 442);
        pushButton = new QPushButton(CheckDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 20, 101, 23));
        pushButton_2 = new QPushButton(CheckDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(420, 20, 101, 23));
        pushButton_3 = new QPushButton(CheckDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 410, 101, 23));
        treeWidget = new QTreeWidget(CheckDialog);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(30, 50, 651, 321));
        pushButton_4 = new QPushButton(CheckDialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(390, 410, 101, 23));

        retranslateUi(CheckDialog);

        QMetaObject::connectSlotsByName(CheckDialog);
    } // setupUi

    void retranslateUi(QDialog *CheckDialog)
    {
        CheckDialog->setWindowTitle(QApplication::translate("CheckDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("CheckDialog", "\345\213\230\346\216\242\346\210\220\346\236\234\345\233\276", 0));
        pushButton_2->setText(QApplication::translate("CheckDialog", "\350\277\236\344\272\225\345\211\226\351\235\242\345\233\276", 0));
        pushButton_3->setText(QApplication::translate("CheckDialog", "\351\200\211\346\213\251\346\200\247\346\240\241\346\255\243", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("CheckDialog", "\345\235\220\346\240\207\345\200\274", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("CheckDialog", "\344\272\225\345\220\215", 0));
        pushButton_4->setText(QApplication::translate("CheckDialog", "\345\205\250\351\203\250\346\240\241\346\255\243", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckDialog: public Ui_CheckDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKDIALOG_H

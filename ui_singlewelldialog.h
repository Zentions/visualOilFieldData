/********************************************************************************
** Form generated from reading UI file 'singlewelldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEWELLDIALOG_H
#define UI_SINGLEWELLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SingleWellDialog
{
public:
    QGraphicsView *graphicsView;
    QLabel *label;
    QLineEdit *lineEdit;
    QToolButton *toolButton_5;
    QLabel *label_8;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QToolButton *toolButton_6;
    QLabel *label_2;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QLabel *label_6;

    void setupUi(QDialog *SingleWellDialog)
    {
        if (SingleWellDialog->objectName().isEmpty())
            SingleWellDialog->setObjectName(QStringLiteral("SingleWellDialog"));
        SingleWellDialog->resize(998, 622);
        graphicsView = new QGraphicsView(SingleWellDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 20, 691, 581));
        label = new QLabel(SingleWellDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(740, 200, 54, 12));
        lineEdit = new QLineEdit(SingleWellDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(720, 220, 251, 20));
        toolButton_5 = new QToolButton(SingleWellDialog);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        toolButton_5->setGeometry(QRect(790, 130, 121, 18));
        label_8 = new QLabel(SingleWellDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(810, 250, 54, 12));
        lineEdit_2 = new QLineEdit(SingleWellDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(790, 270, 101, 20));
        label_3 = new QLabel(SingleWellDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(890, 200, 54, 12));
        toolButton_6 = new QToolButton(SingleWellDialog);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));
        toolButton_6->setGeometry(QRect(790, 370, 121, 18));
        label_2 = new QLabel(SingleWellDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(820, 200, 54, 12));
        label_7 = new QLabel(SingleWellDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(830, 300, 54, 12));
        lineEdit_3 = new QLineEdit(SingleWellDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(790, 320, 101, 20));
        label_6 = new QLabel(SingleWellDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(730, 170, 261, 21));

        retranslateUi(SingleWellDialog);

        QMetaObject::connectSlotsByName(SingleWellDialog);
    } // setupUi

    void retranslateUi(QDialog *SingleWellDialog)
    {
        SingleWellDialog->setWindowTitle(QApplication::translate("SingleWellDialog", "Dialog", 0));
        label->setText(QApplication::translate("SingleWellDialog", "X", 0));
        lineEdit->setText(QApplication::translate("SingleWellDialog", "15270689.93 4965651.65 -17000", 0));
        toolButton_5->setText(QApplication::translate("SingleWellDialog", "\346\211\223\345\274\200\345\215\225\344\272\225\347\273\274\345\220\210\346\237\261\347\212\266\345\233\276", 0));
        label_8->setText(QApplication::translate("SingleWellDialog", "\347\274\251\346\224\276\346\257\224\344\276\213", 0));
        lineEdit_2->setText(QApplication::translate("SingleWellDialog", "10", 0));
        label_3->setText(QApplication::translate("SingleWellDialog", "Z", 0));
        toolButton_6->setText(QApplication::translate("SingleWellDialog", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        label_2->setText(QApplication::translate("SingleWellDialog", "Y", 0));
        label_7->setText(QApplication::translate("SingleWellDialog", "\344\272\225\345\220\215", 0));
        lineEdit_3->setText(QString());
        label_6->setText(QApplication::translate("SingleWellDialog", "\350\257\267\345\260\206\345\234\250\345\233\276\344\270\255\351\200\211\346\213\251\344\270\244\344\270\252\347\202\271\357\274\214\345\271\266\345\241\253\345\206\231\344\273\245\344\270\213\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class SingleWellDialog: public Ui_SingleWellDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEWELLDIALOG_H

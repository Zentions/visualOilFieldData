/********************************************************************************
** Form generated from reading UI file 'layerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYERDIALOG_H
#define UI_LAYERDIALOG_H

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

class Ui_LayerDialog
{
public:
    QToolButton *toolButton_3;
    QLabel *label_2;
    QLabel *label;
    QToolButton *toolButton_4;
    QLabel *label_5;
    QLabel *label_4;
    QToolButton *toolButton;
    QLabel *label_3;
    QLabel *label_6;
    QTextBrowser *textBrowser;
    QLabel *label_7;
    QLineEdit *lineEdit;
    QToolButton *toolButton_2;
    QLineEdit *lineEdit_2;
    QGraphicsView *graphicsView;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *LayerDialog)
    {
        if (LayerDialog->objectName().isEmpty())
            LayerDialog->setObjectName(QStringLiteral("LayerDialog"));
        LayerDialog->resize(1042, 592);
        toolButton_3 = new QToolButton(LayerDialog);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        toolButton_3->setGeometry(QRect(850, 560, 71, 18));
        label_2 = new QLabel(LayerDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(840, 220, 54, 12));
        label = new QLabel(LayerDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(770, 220, 54, 12));
        toolButton_4 = new QToolButton(LayerDialog);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setGeometry(QRect(830, 10, 101, 20));
        label_5 = new QLabel(LayerDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(830, 350, 161, 20));
        label_4 = new QLabel(LayerDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(750, 330, 261, 21));
        toolButton = new QToolButton(LayerDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(830, 300, 41, 18));
        label_3 = new QLabel(LayerDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(900, 220, 54, 12));
        label_6 = new QLabel(LayerDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(760, 190, 261, 21));
        textBrowser = new QTextBrowser(LayerDialog);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(750, 40, 261, 141));
        label_7 = new QLabel(LayerDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(970, 220, 54, 12));
        lineEdit = new QLineEdit(LayerDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(750, 240, 251, 20));
        toolButton_2 = new QToolButton(LayerDialog);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(850, 530, 71, 18));
        lineEdit_2 = new QLineEdit(LayerDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(750, 270, 251, 20));
        graphicsView = new QGraphicsView(LayerDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(30, 20, 701, 551));
        plainTextEdit = new QPlainTextEdit(LayerDialog);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(740, 380, 271, 141));

        retranslateUi(LayerDialog);

        QMetaObject::connectSlotsByName(LayerDialog);
    } // setupUi

    void retranslateUi(QDialog *LayerDialog)
    {
        LayerDialog->setWindowTitle(QApplication::translate("LayerDialog", "Dialog", 0));
        toolButton_3->setText(QApplication::translate("LayerDialog", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        label_2->setText(QApplication::translate("LayerDialog", "Y", 0));
        label->setText(QApplication::translate("LayerDialog", "X", 0));
        toolButton_4->setText(QApplication::translate("LayerDialog", "\346\211\223\345\274\200\345\213\230\346\216\242\346\210\220\346\236\234\345\233\276", 0));
        label_5->setText(QApplication::translate("LayerDialog", "\346\240\274\345\274\217\345\246\202\344\270\213", 0));
        label_4->setText(QApplication::translate("LayerDialog", "\350\257\267\345\260\206\345\211\251\344\270\213\347\232\204\344\272\225\347\202\271\345\235\220\346\240\207\346\214\211\345\246\202\344\270\213\346\240\274\345\274\217\345\244\215\345\210\266\345\210\260\346\226\207\346\234\254\346\241\206\345\206\205", 0));
        toolButton->setText(QApplication::translate("LayerDialog", "OK", 0));
        label_3->setText(QApplication::translate("LayerDialog", "Z", 0));
        label_6->setText(QApplication::translate("LayerDialog", "\350\257\267\345\260\206\345\234\250\345\233\276\344\270\255\351\200\211\346\213\251\344\270\244\344\270\252\347\202\271\357\274\214\345\271\266\345\241\253\345\206\231\344\273\245\344\270\213\344\277\241\346\201\257", 0));
        label_7->setText(QApplication::translate("LayerDialog", "\344\272\225\345\220\215", 0));
        lineEdit->setText(QApplication::translate("LayerDialog", "15270689.93 4965651.65 -17000 \344\272\225\345\220\2151", 0));
        toolButton_2->setText(QApplication::translate("LayerDialog", "\346\267\273\345\212\240\346\226\260\347\202\271", 0));
        lineEdit_2->setText(QApplication::translate("LayerDialog", "15270689.93 4965651.65 -17000 \344\272\225\345\220\2152", 0));
        plainTextEdit->setPlainText(QApplication::translate("LayerDialog", "15270689.93 4965651.65 -17000 \344\272\225\345\220\2153\n"
"15276829.63 4973590.04 -13680 \344\272\225\345\220\2154", 0));
    } // retranslateUi

};

namespace Ui {
    class LayerDialog: public Ui_LayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERDIALOG_H

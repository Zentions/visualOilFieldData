/********************************************************************************
** Form generated from reading UI file 'colorsetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORSETDIALOG_H
#define UI_COLORSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <xgradientslider.hpp>

QT_BEGIN_NAMESPACE

class Ui_ColorSetDialog
{
public:
    QLabel *label;
    QLabel *label_1;
    QLabel *label_cool;
    QLabel *label_warm;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_ok;
    XGradientSlider *Slider_cool;
    XGradientSlider *Slider_warm;

    void setupUi(QDialog *ColorSetDialog)
    {
        if (ColorSetDialog->objectName().isEmpty())
            ColorSetDialog->setObjectName(QStringLiteral("ColorSetDialog"));
        ColorSetDialog->resize(400, 300);
        label = new QLabel(ColorSetDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 220, 54, 12));
        label_1 = new QLabel(ColorSetDialog);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(200, 220, 54, 12));
        label_cool = new QLabel(ColorSetDialog);
        label_cool->setObjectName(QStringLiteral("label_cool"));
        label_cool->setGeometry(QRect(100, 200, 54, 12));
        label_warm = new QLabel(ColorSetDialog);
        label_warm->setObjectName(QStringLiteral("label_warm"));
        label_warm->setGeometry(QRect(190, 200, 54, 12));
        pushButton_cancel = new QPushButton(ColorSetDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(30, 250, 75, 23));
        pushButton_ok = new QPushButton(ColorSetDialog);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(250, 250, 75, 23));
        Slider_cool = new XGradientSlider(ColorSetDialog);
        Slider_cool->setObjectName(QStringLiteral("Slider_cool"));
        Slider_cool->setGeometry(QRect(120, 20, 22, 160));
        Slider_cool->setOrientation(Qt::Vertical);
        Slider_warm = new XGradientSlider(ColorSetDialog);
        Slider_warm->setObjectName(QStringLiteral("Slider_warm"));
        Slider_warm->setGeometry(QRect(210, 20, 22, 160));
        Slider_warm->setValue(99);
        Slider_warm->setOrientation(Qt::Vertical);

        retranslateUi(ColorSetDialog);

        QMetaObject::connectSlotsByName(ColorSetDialog);
    } // setupUi

    void retranslateUi(QDialog *ColorSetDialog)
    {
        ColorSetDialog->setWindowTitle(QApplication::translate("ColorSetDialog", "Dialog", 0));
        label->setText(QApplication::translate("ColorSetDialog", "\346\234\200\345\206\267\350\211\262", 0));
        label_1->setText(QApplication::translate("ColorSetDialog", "\346\234\200\346\232\226\350\211\262", 0));
        label_cool->setText(QApplication::translate("ColorSetDialog", "#ff00ff", 0));
        label_warm->setText(QApplication::translate("ColorSetDialog", "#ff0000", 0));
        pushButton_cancel->setText(QApplication::translate("ColorSetDialog", "\345\217\226\346\266\210", 0));
        pushButton_ok->setText(QApplication::translate("ColorSetDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ColorSetDialog: public Ui_ColorSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORSETDIALOG_H

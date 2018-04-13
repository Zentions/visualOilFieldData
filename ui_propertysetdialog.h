/********************************************************************************
** Form generated from reading UI file 'propertysetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSETDIALOG_H
#define UI_PROPERTYSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PropertySetDialog
{
public:
    QListView *listView;
    QPushButton *ok;
    QPushButton *pushButton_2;

    void setupUi(QDialog *PropertySetDialog)
    {
        if (PropertySetDialog->objectName().isEmpty())
            PropertySetDialog->setObjectName(QStringLiteral("PropertySetDialog"));
        PropertySetDialog->resize(400, 300);
        listView = new QListView(PropertySetDialog);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(40, 20, 256, 192));
        ok = new QPushButton(PropertySetDialog);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(260, 250, 75, 23));
        pushButton_2 = new QPushButton(PropertySetDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 250, 75, 23));

        retranslateUi(PropertySetDialog);

        QMetaObject::connectSlotsByName(PropertySetDialog);
    } // setupUi

    void retranslateUi(QDialog *PropertySetDialog)
    {
        PropertySetDialog->setWindowTitle(QApplication::translate("PropertySetDialog", "Dialog", 0));
        ok->setText(QApplication::translate("PropertySetDialog", "\347\241\256\350\256\244", 0));
        pushButton_2->setText(QApplication::translate("PropertySetDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertySetDialog: public Ui_PropertySetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSETDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'projectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTDIALOG_H
#define UI_PROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectDialog
{
public:
    QLabel *label;
    QLineEdit *projectName;
    QPushButton *confirmBtn;
    QPushButton *concelBtn;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *strataSurface;
    QCheckBox *fault;
    QCheckBox *well;
    QCheckBox *surfaceStrataModel;
    QCheckBox *volumeStrataModel;
    QCheckBox *explorationResult;
    QCheckBox *profile;
    QCheckBox *compositeColumn;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *projectPath;
    QPushButton *browseBtn;

    void setupUi(QDialog *ProjectDialog)
    {
        if (ProjectDialog->objectName().isEmpty())
            ProjectDialog->setObjectName(QStringLiteral("ProjectDialog"));
        ProjectDialog->setEnabled(true);
        ProjectDialog->resize(441, 362);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProjectDialog->sizePolicy().hasHeightForWidth());
        ProjectDialog->setSizePolicy(sizePolicy);
        ProjectDialog->setSizeGripEnabled(false);
        label = new QLabel(ProjectDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 221, 41));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        label->setFont(font);
        projectName = new QLineEdit(ProjectDialog);
        projectName->setObjectName(QStringLiteral("projectName"));
        projectName->setGeometry(QRect(150, 40, 181, 21));
        confirmBtn = new QPushButton(ProjectDialog);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setGeometry(QRect(142, 289, 75, 23));
        concelBtn = new QPushButton(ProjectDialog);
        concelBtn->setObjectName(QStringLiteral("concelBtn"));
        concelBtn->setGeometry(QRect(252, 289, 75, 23));
        verticalLayoutWidget = new QWidget(ProjectDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(150, 80, 181, 172));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        strataSurface = new QCheckBox(verticalLayoutWidget);
        strataSurface->setObjectName(QStringLiteral("strataSurface"));
        strataSurface->setChecked(true);

        verticalLayout->addWidget(strataSurface);

        fault = new QCheckBox(verticalLayoutWidget);
        fault->setObjectName(QStringLiteral("fault"));

        verticalLayout->addWidget(fault);

        well = new QCheckBox(verticalLayoutWidget);
        well->setObjectName(QStringLiteral("well"));

        verticalLayout->addWidget(well);

        surfaceStrataModel = new QCheckBox(verticalLayoutWidget);
        surfaceStrataModel->setObjectName(QStringLiteral("surfaceStrataModel"));

        verticalLayout->addWidget(surfaceStrataModel);

        volumeStrataModel = new QCheckBox(verticalLayoutWidget);
        volumeStrataModel->setObjectName(QStringLiteral("volumeStrataModel"));

        verticalLayout->addWidget(volumeStrataModel);

        explorationResult = new QCheckBox(verticalLayoutWidget);
        explorationResult->setObjectName(QStringLiteral("explorationResult"));

        verticalLayout->addWidget(explorationResult);

        profile = new QCheckBox(verticalLayoutWidget);
        profile->setObjectName(QStringLiteral("profile"));

        verticalLayout->addWidget(profile);

        compositeColumn = new QCheckBox(verticalLayoutWidget);
        compositeColumn->setObjectName(QStringLiteral("compositeColumn"));

        verticalLayout->addWidget(compositeColumn);

        label_2 = new QLabel(ProjectDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 70, 81, 21));
        label_2->setFont(font);
        label_3 = new QLabel(ProjectDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 262, 81, 21));
        label_3->setFont(font);
        projectPath = new QLineEdit(ProjectDialog);
        projectPath->setObjectName(QStringLiteral("projectPath"));
        projectPath->setEnabled(false);
        projectPath->setGeometry(QRect(150, 262, 181, 21));
        projectPath->setReadOnly(true);
        browseBtn = new QPushButton(ProjectDialog);
        browseBtn->setObjectName(QStringLiteral("browseBtn"));
        browseBtn->setGeometry(QRect(340, 262, 31, 21));

        retranslateUi(ProjectDialog);

        QMetaObject::connectSlotsByName(ProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *ProjectDialog)
    {
        ProjectDialog->setWindowTitle(QApplication::translate("ProjectDialog", "\346\226\260\345\273\272\345\267\245\347\250\213\345\257\271\350\257\235\346\241\206", 0));
        label->setText(QApplication::translate("ProjectDialog", "\345\267\245\347\250\213\345\220\215\347\247\260\357\274\232", 0));
        projectName->setText(QApplication::translate("ProjectDialog", "\345\234\260\345\261\202\351\235\242\346\265\213\350\257\225", 0));
        confirmBtn->setText(QApplication::translate("ProjectDialog", "\347\241\256\345\256\232", 0));
        concelBtn->setText(QApplication::translate("ProjectDialog", "\345\217\226\346\266\210", 0));
        strataSurface->setText(QApplication::translate("ProjectDialog", "\345\234\260\345\261\202\351\235\242", 0));
        fault->setText(QApplication::translate("ProjectDialog", "\346\226\255\345\261\202\351\235\242", 0));
        well->setText(QApplication::translate("ProjectDialog", "\344\272\225", 0));
        surfaceStrataModel->setText(QApplication::translate("ProjectDialog", "\345\234\260\345\261\202\346\250\241\345\236\213\357\274\210\350\241\250\351\235\242\357\274\211", 0));
        volumeStrataModel->setText(QApplication::translate("ProjectDialog", "\345\234\260\345\261\202\346\250\241\345\236\213\357\274\210\344\275\223\345\205\203\357\274\211", 0));
        explorationResult->setText(QApplication::translate("ProjectDialog", "\345\213\230\346\216\242\346\210\220\346\236\234\345\233\276", 0));
        profile->setText(QApplication::translate("ProjectDialog", "\350\277\236\344\272\225\345\211\226\351\235\242\345\233\276", 0));
        compositeColumn->setText(QApplication::translate("ProjectDialog", "\345\215\225\344\272\225\347\273\274\345\220\210\346\237\261\347\212\266\345\233\276", 0));
        label_2->setText(QApplication::translate("ProjectDialog", "\345\267\245\347\250\213\345\206\205\345\256\271\357\274\232", 0));
        label_3->setText(QApplication::translate("ProjectDialog", "\345\267\245\347\250\213\350\267\257\345\276\204\357\274\232", 0));
        projectPath->setText(QApplication::translate("ProjectDialog", "E:\\workspace", 0));
        browseBtn->setText(QApplication::translate("ProjectDialog", "\351\200\211\346\213\251", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectDialog: public Ui_ProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTDIALOG_H

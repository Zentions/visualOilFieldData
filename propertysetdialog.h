#ifndef PROPERTYSETDIALOG_H
#define PROPERTYSETDIALOG_H

#include <QDialog>

namespace Ui {
class PropertySetDialog;
}

class PropertySetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertySetDialog(QWidget *parent = 0);
    ~PropertySetDialog();

    void getPropertyData(QStringList propertyname);
    int getchoice();

private slots:

    void on_ok_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::PropertySetDialog *ui;
    int confirm;
};

#endif // PROPERTYSETDIALOG_H

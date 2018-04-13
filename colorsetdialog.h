#ifndef COLORSETDIALOG_H
#define COLORSETDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QMessageBox>

namespace Ui {
class ColorSetDialog;
}

class ColorSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorSetDialog(QWidget *parent = 0);
    ~ColorSetDialog();

    QColor * getColorset(){return colorset;}

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
    void warmcolor_changed(int);
    void coolcolor_changed(int);


signals:
    void setColor(QColor,QColor);

private:
    Ui::ColorSetDialog *ui;
    QColor coolcolor;
    QColor warmcolor;
    QColor *colorset;
};

#endif // ColorSetDIALOG_H

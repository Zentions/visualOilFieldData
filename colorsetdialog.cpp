#include "colorsetdialog.h"
#include "ui_colorsetdialog.h"

ColorSetDialog::ColorSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorSetDialog)
{
    ui->setupUi(this);
    this->warmcolor = Qt::red;
    this->coolcolor = Qt::magenta;

    connect(this->ui->Slider_warm, SIGNAL(valueChanged(int)), this, SLOT(warmcolor_changed(int)));
    connect(this->ui->Slider_cool, SIGNAL(valueChanged(int)), this, SLOT(coolcolor_changed(int)));
}

ColorSetDialog::~ColorSetDialog()
{
    delete ui;
}



void ColorSetDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

void ColorSetDialog::on_pushButton_ok_clicked()
{
    colorset = new QColor [2];
    colorset[0] = this->coolcolor;
    colorset[1] = this->warmcolor;
    this->close();
}

void ColorSetDialog::warmcolor_changed(int value){
    int min = this->ui->Slider_warm->minimum();
    int max = this->ui->Slider_warm->maximum();
    int size =  this->ui->Slider_warm->col_list.size();

    //由于滑块上值的大小和颜色数组的渐变方向正好相反，所以对值进行调整
    value = max - value;

    //获取选择的颜色
    if(value==min){
        this->warmcolor = this->ui->Slider_warm->col_list[0];
        ui->label_warm->setText(this->warmcolor.name());
        return;
    }
    //获取选择的颜色
    if(value==max){
        this->warmcolor = this->ui->Slider_warm->col_list[size-1];
        ui->label_warm->setText(this->warmcolor.name());
        return;
    }


    double val = (double)value/max;
    int col1 = val*(size-1);
    int col2 = col1+1;

    QColor colorfirt = this->ui->Slider_warm->col_list[col1];
    QColor colorlast = this->ui->Slider_warm->col_list[col2];

    //颜色渐变是两个颜色之间的渐变 调整颜色选取滑块的值

    double pos1 =  (double)col1/(size-1);
    double pos2 =  (double)col2/(size-1);
    val = (val-pos1)/(pos2-pos1);


    this->warmcolor.setRed(colorfirt.red()+(double)(colorlast.red()-colorfirt.red())*val);
    this->warmcolor.setGreen(colorfirt.green()+(double)(colorlast.green()-colorfirt.green())*val);
    this->warmcolor.setBlue(colorfirt.blue()+(double)(colorlast.blue()-colorfirt.blue())*val);

    ui->label_warm->setText(this->warmcolor.name());
}

void ColorSetDialog::coolcolor_changed(int value){


    int min = this->ui->Slider_cool->minimum();
    int max = this->ui->Slider_cool->maximum();
    int size =  this->ui->Slider_warm->col_list.size();

    //由于滑块上值的大小和颜色数组的渐变方向正好相反，所以对值进行调整
    value = max - value;

    //获取选择的颜色
    if(value==min){
        this->coolcolor = this->ui->Slider_cool->col_list[0];
        ui->label_cool->setText(this->coolcolor.name());
        return;
    }
    //获取选择的颜色
    if(value==max){
        this->coolcolor = this->ui->Slider_cool->col_list[size-1];
        ui->label_cool->setText(this->coolcolor.name());
        return;
    }


    double val = (double)value/max;



    int col1 = val*(size-1);
    int col2 = col1+1;
    QColor colorfirt = this->ui->Slider_cool->col_list[col1];
    QColor colorlast = this->ui->Slider_cool->col_list[col2];

    //颜色渐变是两个颜色之间的渐变 调整颜色选取滑块的值

    double pos1 =  (double)col1/(size-1);
    double pos2 =  (double)col2/(size-1);
    val = (val-pos1)/(pos2-pos1);

    this->coolcolor.setRed(colorfirt.red()+((double)(colorlast.red()-colorfirt.red()))*val);
    this->coolcolor.setGreen(colorfirt.green()+((double)(colorlast.green()-colorfirt.green()))*val);
    this->coolcolor.setBlue(colorfirt.blue()+((double)(colorlast.blue()-colorfirt.blue()))*val);
    ui->label_cool->setText(this->coolcolor.name());
}

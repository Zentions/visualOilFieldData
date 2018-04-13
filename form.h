#ifndef FORM_H
#define FORM_H

#include <QWidget>

struct Data{
    QString path;
    QString start;
    QString end;
};
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    Data provide();
    bool isChoosed();
private slots:

    void on_choose_clicked();


private:
    Ui::Form *ui;
};

#endif // FORM_H

#ifndef TEXTUREDIALOG_H
#define TEXTUREDIALOG_H
#include <QVBoxLayout>
#include <QDialog>
#include <string>
#include <QObjectList>
#include <osg/ref_ptr>
#include "form.h"
namespace Ui {
class TextureDialog;
}

class TextureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextureDialog(double start,double end,QWidget *parent = 0);
    ~TextureDialog();
    QList<Data> getQList(){
        return boxList;
    }
private slots:


    void on_confirmBtn_clicked();

    void on_concelBtn_clicked();

    void on_p1_clicked();

    void on_p2_clicked();

    void on_p3_clicked();


    void on_pushButton_clicked();

private:
    Ui::TextureDialog *ui;
    QList<Data> boxList;
    QList<Form*> formList;
    QVBoxLayout *e;
};

#endif // TEXTUREDIALOG_H

#ifndef ProjectDialog_H
#define ProjectDialog_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "common.h"
#include "projectOperation.h"
namespace Ui {
class ProjectDialog;
}

class ProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectDialog(QWidget *parent = 0);
    QString getName();
    void setTypeName(QString typeName);
    ~ProjectDialog();

private slots:

    void on_confirmBtn_clicked();

    void on_concelBtn_clicked();



    void on_browseBtn_clicked();

signals:
    //void sendData(QString,QList<QCheckBox*>*);
    void sendData(QString,QList<PROJECTITEM*>*);
    //void sendData(QString,QString,QList<PROJECTITEM*>*);

private:
    Ui::ProjectDialog *ui;
    QList<QCheckBox*>* itemList;
    QList<PROJECTITEM*>* itemStructList;
    PROJECTITEM* itemStruct;
    void createResourceFolder();
};

#endif // ProjectDialog_H

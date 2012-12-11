#ifndef CONTROLDLG_H
#define CONTROLDLG_H
#include<QDialog>
#include "ui_controldlg.h"

class ControlDlg:public QDialog,public Ui::ControlDlg
{
    Q_OBJECT

public:
    ControlDlg(QWidget *parent = 0);
private slots:
    void UpadteControl();

};

#endif

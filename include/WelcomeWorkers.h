#ifndef WELCOMEWORKERS_H
#define WELCOMEWORKERS_H

#include <QDialog>
#include "ui_workers.h"

class WelcomeWorkers : public QDialog , public Ui_Dialog
{
    Q_OBJECT

public:

    explicit WelcomeWorkers(QWidget *parent = 0);

    //print the logged workers' data
    void workers_load();

private slots:

    void workers_updatepasswd();
    void workers_updatepasswd_cancel();

    void workers_updatepay(QDate date);
    void workers_updateattend(QDate date);

    void workers_updatedata();
    void displayTime();

};

#endif // WELCOMEWORKERS_H

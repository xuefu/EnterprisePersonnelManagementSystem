#ifndef EDITWORKERSINFO_H
#define EDITWORKERSINFO_H

#include <QDialog>
#include "ui_editworkersinfo.h"

class EditWorkersInfo : public QDialog , public Ui_editworkers
{
    Q_OBJECT

public:

    explicit EditWorkersInfo(int id, QWidget *parent=0);

private slots:

    void editworkers_load();
    void managers_updatepay(QDate);
    void managers_updateattend(QDate);
    void editpayinfo();
    void editattendinfo();
    void editbasicinfo();
    void againbasicinfo();

    void firstupdate();
    void previousupdate();
    void nextupdate();
    void lastupdate();

private:

    QString workersid;
    int basicinfoid;
    int maxbasicinfoid;


};

#endif // EDITWORKERSINFO_H

#ifndef WELCOMEMANAGERS_H
#define WELCOMEMANAGERS_H

#include "ui_managers.h"
#include "EditWorkersInfo.h"

class QDialog;
class QSqlTableModel;

enum {
    BasicInfo_Id = 0,
    Workers_Id = 1,
    Workers_Name = 2,
    Workers_Sex = 3,
    Workers_Age = 4,
    Workers_IdCard = 5,
    Workers_Address =6,
    Workers_Birthdate = 7,
    Workers_Telephone =8,
    Workers_Personnel =9,
    Workers_Position =10,
    Workers_Passwd =11
};

class WelcomeManagers : public QDialog , public Ui_Dialog_2
{
   Q_OBJECT

public:

    explicit WelcomeManagers(QWidget *parent = 0);
    void managers_load();


private:

    //EditWorkersInfo editworkersinfo;
    QSqlTableModel *tableModel;

private slots:

    void jumpToEditWorkersInfo();
   // void backToWelcomeManagers();
    void displayCurrentTime();
    void department_select();
    void username_search();
    void wokers_delete();
    void workers_add();
    void managers_updatepasswd();

};

#endif // WELCOMEMANAGERS_H

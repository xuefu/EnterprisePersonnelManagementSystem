#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include "WelcomeManagers.h"

extern QString managersId;

WelcomeManagers::WelcomeManagers(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setWindowTitle(tr("managers"));

    //connect the frame of managers.ui
    connect(managers_tab_editpushButton,SIGNAL(clicked()),this,SLOT(jumpToEditWorkersInfo()));
    connect(managers_tab_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(department_select()));
    connect(managers_tab_searchpushButton,SIGNAL(clicked()),this,SLOT(username_search()));
    connect(managers_tab_deletepushButton,SIGNAL(clicked()),this,SLOT(wokers_delete()));
    connect(managers_tab_okpushButton,SIGNAL(clicked()),this,SLOT(workers_add()));
    connect(managers_tab_okpushButton_2,SIGNAL(clicked()),this,SLOT(managers_updatepasswd()));

    //show the current date and time
    QTimer *timer = new QTimer(this);
    displayCurrentTime();
    connect(timer, SIGNAL(timeout()),this, SLOT(displayCurrentTime()));
    timer->start(1000);

    managers_load();

}

void WelcomeManagers::managers_load()
{
    //display all workers in the table view
    tableModel = new QSqlTableModel(this);
    tableModel->setTable("workers_basicinfo");
    tableModel->setSort(Workers_Name,Qt::AscendingOrder);
    tableModel->setHeaderData(Workers_Id,Qt::Horizontal,QString::fromLocal8Bit("学号"));
    tableModel->setHeaderData(Workers_Name,Qt::Horizontal,QString::fromLocal8Bit("姓名"));
    tableModel->setHeaderData(Workers_Sex,Qt::Horizontal,QString::fromLocal8Bit("性别"));
    tableModel->setHeaderData(Workers_Age,Qt::Horizontal,QString::fromLocal8Bit("年龄"));
    tableModel->setHeaderData(Workers_IdCard,Qt::Horizontal,QString::fromLocal8Bit("身份证号"));
    tableModel->setHeaderData(Workers_Address,Qt::Horizontal,QString::fromLocal8Bit("家庭住址"));
    tableModel->setHeaderData(Workers_Birthdate,Qt::Horizontal,QString::fromLocal8Bit("出生年月"));
    tableModel->setHeaderData(Workers_Telephone,Qt::Horizontal,QString::fromLocal8Bit("联系方式"));
    tableModel->setHeaderData(Workers_Personnel,Qt::Horizontal,QString::fromLocal8Bit("部门"));
    tableModel->setHeaderData(Workers_Position,Qt::Horizontal,QString::fromLocal8Bit("职位"));
    tableModel->setHeaderData(Workers_Passwd,Qt::Horizontal,QString::fromLocal8Bit("密码"));

    tableModel->select();

    managers_tab_tableView->setModel(tableModel);
    managers_tab_tableView->setSelectionMode(QTableView::SingleSelection);
    managers_tab_tableView->setSelectionBehavior(QTableView::SelectRows);
    managers_tab_tableView->resizeColumnsToContents();
    managers_tab_tableView->horizontalHeader()->setStretchLastSection(true);
    managers_tab_tableView->setEditTriggers(QTableView::NoEditTriggers);
    managers_tab_tableView->setColumnHidden(BasicInfo_Id,true);

}

void WelcomeManagers::jumpToEditWorkersInfo()
{
    int id = -1;
    QModelIndex index = managers_tab_tableView->currentIndex();
    if(index.isValid())
    {
        QSqlRecord record = tableModel->record(index.row());
        id = record.value(BasicInfo_Id).toInt();
    }
    EditWorkersInfo editworkersinfo(id,this);
    editworkersinfo.exec();
   // managers_load();

}

void WelcomeManagers::displayCurrentTime()
{
    QDateTime dt;
    QTime time;
    QDate date;

    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());

    QString currentDate = dt.toString("yyyy-MM-dd/hh:mm:ss");
    managers_datetime->setText(currentDate);
}

void WelcomeManagers::department_select()
{
    int department_id;
    QString department_name;

    department_id = managers_tab_comboBox->currentIndex();
    department_name = managers_tab_comboBox->currentText();

    if(department_id == 0)
    {
        managers_load();
    }
    else
    {
    tableModel->setFilter(QObject::tr("workers_personnel = '%1'").arg(department_name));
    tableModel->select();
    }
}

void WelcomeManagers::username_search()
{
    QString username;
    username = managers_tab_lineEdit->text();

    if(username.isEmpty())
    {
        tableModel->setFilter(QObject::tr("workers_name like '%1'").arg("%"));
        tableModel->select();
    }
    else
    {
        tableModel->setFilter(QObject::tr("workers_name like '%1'").arg(QString("%")+username+QString("%")));
        tableModel->select();
    }
}

void WelcomeManagers::wokers_delete()
{
    int currentRow = managers_tab_tableView->currentIndex().row();
    QSqlQuery query;
    QString current_workers_id,queryString_1,queryString_2,queryString_3;

    current_workers_id = tableModel->record(currentRow).value("workers_id").toString();


    int ok = QMessageBox::warning(this,QString::fromLocal8Bit("删除当前行!"),QString::fromLocal8Bit("你确定删除当前行吗？"),QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::No)
    {

        tableModel->revertAll();
    }
    else
    {
        tableModel->removeRow(currentRow);
        tableModel->submitAll();
        queryString_1 = "delete from workers where workers_id='"+current_workers_id+"'";
        queryString_2 = "delete from workers_attendinfo where workers_id='"+current_workers_id+"'";
        queryString_3 = "delete from workers_payinfo where workers_id='"+current_workers_id+"'";

        if(query.exec(queryString_1) && query.exec(queryString_2) && query.exec(queryString_3))
            QMessageBox::about(this, QString::fromLocal8Bit("删除用户"),QString::fromLocal8Bit("删除成功!"));

    }

    managers_load();

}

void WelcomeManagers::workers_add()
{

    bool ok =(managers_tab_idlineEdit->text().isEmpty() || managers_tab_namelineEdit->text().isEmpty() ||
            managers_tab_passwdlineEdit->text().isEmpty() || managers_tab_passwdlineEdit_2->text().isEmpty() |
            managers_tab_phonelineEdit->text().isEmpty() || managers_tab_sexlineEdit->text().isEmpty() ||
            managers_tab_personnellineEdit->text().isEmpty() || managers_tab_idcardlineEdit->text().isEmpty() ||
            managers_tab_birthlineEdit->text().isEmpty() || managers_tab_agelineEdit->text().isEmpty() ||
            managers_tab_addresslineEdit->text().isEmpty() || managers_tab_positionlineEdit->text().isEmpty());
    if(ok == true || (managers_tab_passwdlineEdit_2->text() != managers_tab_passwdlineEdit->text()))
        QMessageBox::warning(this,QString::fromLocal8Bit("信息不完整！"),QString::fromLocal8Bit("信息不完整，请重新输入！"));
    else
    {
        QString str_1,str_2;
        QSqlQuery query;
        str_1 = "select * from workers where workers_id='"+managers_tab_idlineEdit->text()+"'";
        query.exec(str_1);
        if(query.next())
            QMessageBox::warning(this,QString::fromLocal8Bit("该职工已存在！"),QString::fromLocal8Bit("该职工已存在！"));
        else
        {
        str_1 = "insert into workers values('"+managers_tab_idlineEdit->text()+"','"+managers_tab_passwdlineEdit->text()+"')";
        str_2 = "insert into workers_basicinfo(workers_id,workers_name,workers_sex,workers_age,workers_idcard,workers_address,"
                "workers_birthdate,workers_telephone,workers_personnel,workers_position,workers_passwd)"
                "values('"+managers_tab_idlineEdit->text()+"','"+managers_tab_namelineEdit->text()+"','"+managers_tab_sexlineEdit->text()+"',"
                "'"+managers_tab_agelineEdit->text()+"','"+managers_tab_idcardlineEdit->text()+"','"+managers_tab_addresslineEdit->text()+"',"
                "'"+managers_tab_birthlineEdit->text()+"','"+managers_tab_phonelineEdit->text()+"','"+managers_tab_personnellineEdit->text()+"',"
                "'"+managers_tab_positionlineEdit->text()+"','"+managers_tab_passwdlineEdit->text()+"')";

        if(query.exec(str_1) && query.exec(str_2))
        {
            QMessageBox::information(this,QString::fromLocal8Bit("添加成功"),QString::fromLocal8Bit("用户添加成功！"));

             managers_load();

        }
        }
    }
}

void WelcomeManagers::managers_updatepasswd()
{
    QSqlQuery query;
    QString str;

    //judge the passwd of inputted whether is valid
    if(this->managers_tab_oldpasswdlineEdit->text().isEmpty() || this->managers_tab_newpasswdlineEdit->text().isEmpty() || this->managers_tab_newpasswdlineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("输入错误"),QString::fromLocal8Bit("输入数据不完整,请重新输入"));
    }
    else if(this->managers_tab_newpasswdlineEdit->text() != this->managers_tab_newpasswdlineEdit_2->text()) //judge the two newpasswds whether is valid
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("输入错误"),QString::fromLocal8Bit("输入新密码不匹配,请重新输入"));
        managers_tab_oldpasswdlineEdit->setFocus();
    }
    else //update the passwd
    {
        str = "select managers_passwd from managers where managers_id='"+managersId+"'";
        query.exec(str);
        query.first();
        if(query.value(0).toString() == this->managers_tab_oldpasswdlineEdit->text())
        {
            str = "update managers set managers_passwd='"+this->managers_tab_newpasswdlineEdit->text()+"'where managers_id='"+managersId+"'";

            if(query.exec(str))
                QMessageBox::warning(this,QString::fromLocal8Bit("更新密码"),QString::fromLocal8Bit("您的密码已经更新"));
                managers_tab_oldpasswdlineEdit->setFocus();
        }
        else
        {
                QMessageBox::warning(this,QString::fromLocal8Bit("更新错误"),QString::fromLocal8Bit("用户名或密码错误"));
                managers_tab_oldpasswdlineEdit->setFocus();
        }
    }

    this->managers_tab_oldpasswdlineEdit->clear();
    this->managers_tab_newpasswdlineEdit->clear();
    this->managers_tab_newpasswdlineEdit_2->clear();
}

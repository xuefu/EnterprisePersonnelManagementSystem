#include <QDialog>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QModelIndex>
#include <QVariant>
#include <QMessageBox>
#include "WelcomeWorkers.h"

extern QString workersId;

WelcomeWorkers::WelcomeWorkers(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setWindowTitle("worker");

    //connect the signals and slots
    connect(workers_table_okpushButton_2,SIGNAL(clicked()),this,SLOT(workers_updatepasswd()));
    connect(workers_table_cancelpushButton,SIGNAL(clicked()),this,SLOT(workers_updatepasswd_cancel()));
    connect(workers_table_dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(workers_updatepay(QDate)));
    connect(workers_table_dateEdit_2,SIGNAL(dateChanged(QDate)),this,SLOT(workers_updateattend(QDate)));
    connect(workers_table_okpushButton,SIGNAL(clicked()),this,SLOT(workers_updatedata()));

    //connect the event with button when ENTER is pressed after the passwd has been complete
    connect(workers_table_newpasswdlineEdit_2, SIGNAL(returnPressed()), workers_table_okpushButton_2, SIGNAL(clicked()), Qt::UniqueConnection);

    //hide the text of login_lineEdit_passwd
    workers_table_oldpasswdlineEdit->setEchoMode(QLineEdit::Password);
    workers_table_newpasswdlineEdit->setEchoMode(QLineEdit::Password);
    workers_table_newpasswdlineEdit_2->setEchoMode(QLineEdit::Password);

    //show the current date and time
    QTimer *timer = new QTimer(this);
    displayTime();
    connect(timer, SIGNAL(timeout()),this, SLOT(displayTime()));
    timer->start(1000);

}

void WelcomeWorkers::displayTime()
{
    QDateTime dt;
    QTime time;
    QDate date;

    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());

    QString currentDate = dt.toString("yyyy-MM-dd/hh:mm:ss");
    workers_datetime->setText(currentDate);
}

void WelcomeWorkers::workers_load()
{
    QSqlQuery query;
    QString str_info = "select * from workers_basicinfo where workers_id='"+workersId+"'";
    QString str_attend = "select * from workers_attendinfo where workers_id='"+workersId+"'";
    QString str_pay = "select * from workers_payinfo where workers_id='"+workersId+"'";

    query.exec(str_info);

    if(query.next())
    {
        this->workers_table_idlineEdit->setText(query.value(1).toString());
        this->workers_table_namelineEdit->setText(query.value(2).toString());
        this->workers_table_phonelineEdit->setText(query.value(8).toString());
        this->workers_table_sexlineEdit->setText(query.value(3).toString());
        this->workers_table_personnellineEdit->setText(query.value(9).toString());
        this->workers_table_idcardlineEdit->setText(query.value(5).toString());
        this->workers_table_birthlineEdit->setText(query.value(7).toString());
        this->workers_table_agelineEdit->setText(query.value(4).toString());
        this->workers_table_addresslineEdit->setText(query.value(6).toString());
        this->workers_table_positionlineEdit->setText(query.value(10).toString());

        query.exec(str_pay);

        query.first();
        QString date_1 = query.value(2).toString()+"-02";
       // qDebug() << date_1;
        QVariant date_v = (QVariant)date_1;
        this->workers_table_dateEdit->setDate(date_v.toDate());
        this->workers_table_totalpaylineEdit->setText(query.value(3).toString());
        this->workers_table_taxlineEdit->setText(query.value(4).toString());
        this->workers_table_incomelineEdit->setText(query.value(5).toString());

       query.exec(str_attend);

       query.first();

       date_1 = query.value(2).toString()+"-02";
       date_v = (QVariant)date_1;
       this->workers_table_dateEdit_2->setDate(date_v.toDate());
       this->workers_table_latelineEdit->setText(query.value(4).toString());
       this->workers_table_leavelineEdit->setText(query.value(5).toString());
       this->workers_table_absentlineEdit->setText(query.value(3).toString());

    }
    else
    {
        QMessageBox::warning(this,tr("错误"),tr("数据读取失败!"));
    }
}

void WelcomeWorkers::workers_updatepasswd()   //update the passwd of workers
{
    QSqlQuery query;
    QString str;
    QString str_1;

    qDebug() << workersId;
    //judge the passwd of inputted whether is valid
    if(this->workers_table_oldpasswdlineEdit->text().isEmpty() || this->workers_table_newpasswdlineEdit->text().isEmpty() || this->workers_table_newpasswdlineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this,tr("输入数据不完整"),tr("请重新输入"));
    }
    else if(this->workers_table_newpasswdlineEdit->text() != this->workers_table_newpasswdlineEdit_2->text()) //judge the two newpasswds whether is valid
    {
        QMessageBox::warning(this,tr("输入新密码不匹配"),tr("请重新输入"));
        workers_table_oldpasswdlineEdit->setFocus();
    }
    else //update the passwd
    {
        str = "select workers_passwd from workers where workers_id='"+workersId+"'";
        query.exec(str);
        query.first();
        if(query.value(0).toString() == this->workers_table_oldpasswdlineEdit->text())
        {
            str = "update workers set workers_passwd='"+this->workers_table_newpasswdlineEdit->text()+"'where workers_id='"+workersId+"'";
            str_1 = "update workers_basicinfo set workers_passwd='"+this->workers_table_newpasswdlineEdit->text()+"'where workers_id='"+workersId+"'";

            if(query.exec(str) && query.exec(str_1))
                QMessageBox::warning(this,tr("更新密码"),tr("您的密码已经更新"));
                workers_table_oldpasswdlineEdit->setFocus();
        }
        else
        {
                QMessageBox::warning(this,tr("更新错误"),tr("用户名或密码错误"));
                workers_table_oldpasswdlineEdit->setFocus();
        }
    }

    workers_updatepasswd_cancel();

}

void WelcomeWorkers::workers_updatepasswd_cancel()
{
    this->workers_table_oldpasswdlineEdit->clear();
    this->workers_table_newpasswdlineEdit->clear();
    this->workers_table_newpasswdlineEdit_2->clear();
}

void WelcomeWorkers::workers_updatepay(QDate date)
{
    QSqlQuery query;
    QString str = "select * from workers_payinfo where payinfo_date='"+date.toString("yyyy-MM")+"'";

    query.exec(str);

    if(query.next())
    {
        workers_table_totalpaylineEdit->setText(query.value(3).toString());
        workers_table_taxlineEdit->setText(query.value(4).toString());
        workers_table_incomelineEdit->setText(query.value(5).toString());
    }
    else
    {
        workers_table_totalpaylineEdit->setText("none");
        workers_table_taxlineEdit->setText("none");
        workers_table_incomelineEdit->setText("none");
    }
}

void WelcomeWorkers::workers_updateattend(QDate date)
{
    QSqlQuery query;
    QString str = "select * from workers_attendinfo where attendinfo_date='"+date.toString("yyyy-MM")+"'";

    query.exec(str);

    if(query.next())
    {
        workers_table_absentlineEdit->setText(query.value(3).toString());
        workers_table_latelineEdit->setText(query.value(4).toString());
        workers_table_leavelineEdit->setText(query.value(5).toString());
    }
    else
    {
        workers_table_absentlineEdit->setText("none");
        workers_table_latelineEdit->setText("none");
        workers_table_leavelineEdit->setText("none");
    }
}

void WelcomeWorkers::workers_updatedata()
{
    bool dataIfChanged = (workers_table_phonelineEdit->isModified() || workers_table_birthlineEdit->isModified() || workers_table_agelineEdit->isModified() || workers_table_addresslineEdit->isModified());

    if(dataIfChanged)
    {
        QSqlQuery query;
        QString str;


        int ok = QMessageBox::warning(this,tr("更改数据？"),tr("信息有改动，确认更改数据？"),QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            if(workers_table_phonelineEdit->isModified())
            {
                str = "update workers_basicinfo set workers_telephone='"+workers_table_phonelineEdit->text()+"'where workers_id='"+workersId+"'";
                query.exec(str);
            }

            if(workers_table_birthlineEdit->isModified())
            {
                str = "update workers_basicinfo set workers_birthdate='"+workers_table_birthlineEdit->text()+"'where workers_id='"+workersId+"'";
                query.exec(str);
            }

            if(workers_table_agelineEdit->isModified())
            {
                str = "update workers_basicinfo set workers_age='"+workers_table_agelineEdit->text()+"'where workers_id='"+workersId+"'";
                query.exec(str);
            }

            if(workers_table_addresslineEdit->isModified())
            {
                str = "update workers_basicinfo set workers_address='"+workers_table_addresslineEdit->text()+"'where workers_id='"+workersId+"'";
                query.exec(str);
            }

            QMessageBox::information(this,tr("更新成功！"),tr("数据更新成功！"));
        }
            workers_load();


       }

    }

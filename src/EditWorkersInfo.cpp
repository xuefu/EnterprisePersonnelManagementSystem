#include <QSqlQuery>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <QString>
#include "EditWorkersInfo.h"

EditWorkersInfo::EditWorkersInfo(int id, QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    setWindowTitle(tr("EditWorkersInfo"));

    connect(managers_closepushButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(managers_closepushButton_2,SIGNAL(clicked()),this,SLOT(accept()));
    connect(managers_closepushButton_3,SIGNAL(clicked()),this,SLOT(accept()));
    connect(managers_dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(managers_updatepay(QDate)));
    connect(managers_dateEdit_2,SIGNAL(dateChanged(QDate)),this,SLOT(managers_updateattend(QDate)));

    connect(managers_firstpushButton,SIGNAL(clicked()),this,SLOT(firstupdate()));
    connect(managers_previouspushButton,SIGNAL(clicked()),this,SLOT(previousupdate()));
    connect(managers_nextpushButton,SIGNAL(clicked()),this,SLOT(nextupdate()));
    connect(managers_lastpushButton,SIGNAL(clicked()),this,SLOT(lastupdate()));

    connect(managers_okpushButton,SIGNAL(clicked()),this,SLOT(editbasicinfo()));
    connect(managers_okpushButton_2,SIGNAL(clicked()),this,SLOT(editpayinfo()));
    connect(managers_okpushButton_3,SIGNAL(clicked()),this,SLOT(editattendinfo()));
    connect(managers_againpushButton,SIGNAL(clicked()),this,SLOT(againbasicinfo()));

    QSqlQuery query;
    QString str;
    basicinfoid = id;

    str = "select max(basicinfo_id) from workers_basicinfo";
    query.exec(str);

        if(query.next())
            maxbasicinfoid = query.value(0).toInt();

    str = QString("select workers_id from workers_basicinfo where basicinfo_id = %1").arg(id);
    query.exec(str);

    if(query.next())
    {
        workersid = query.value(0).toString();
    }

    editworkers_load();

}

void EditWorkersInfo::editworkers_load()
{
    QString str_info = "select * from workers_basicinfo where workers_id='"+workersid+"'";
    QString str_attend = "select * from workers_attendinfo where workers_id='"+workersid+"'";
    QString str_pay = "select * from workers_payinfo where workers_id='"+workersid+"'";

    QSqlQuery query;
    query.exec(str_info);

    if(query.next())
    {
        this->managers_idlineEdit->setText(query.value(1).toString());
        this->managers_namelineEdit->setText(query.value(2).toString());
        this->managers_phonelineEdit->setText(query.value(8).toString());
        this->managers_sexlineEdit->setText(query.value(3).toString());
        this->managers_personnellineEdit->setText(query.value(9).toString());
        this->managers_idcardlineEdit->setText(query.value(5).toString());
        this->managers_birthlineEdit->setText(query.value(7).toString());
        this->managers_agelineEdit->setText(query.value(4).toString());
        this->managers_addresslineEdit->setText(query.value(6).toString());
        this->managers_positionlineEdit->setText(query.value(10).toString());

        query.exec(str_pay);

        query.first();
        QString date_1 = query.value(2).toString()+"-02";
       // qDebug() << date_1;
        QVariant date_v = (QVariant)date_1;
        this->managers_dateEdit->setDate(date_v.toDate());
        this->managers_totalpaylineEdit->setText(query.value(3).toString());
        this->managers_taxlineEdit->setText(query.value(4).toString());
        this->managers_incomelineEdit->setText(query.value(5).toString());

       query.exec(str_attend);

       query.first();

       date_1 = query.value(2).toString()+"-02";
       date_v = (QVariant)date_1;
       this->managers_dateEdit_2->setDate(date_v.toDate());
       this->managers_latelineEdit->setText(query.value(4).toString());
       this->managers_leavelineEdit->setText(query.value(5).toString());
       this->managers_absentlineEdit->setText(query.value(3).toString());

    }
    else
    {
        QMessageBox::warning(this,tr("错误"),tr("数据读取失败"));
    }

}

void EditWorkersInfo::managers_updateattend(QDate date)
{
    QSqlQuery query;
    QString str = "select * from workers_attendinfo where attendinfo_date='"+date.toString("yyyy-MM")+"'";

    query.exec(str);

    if(query.next())
    {
        managers_absentlineEdit->setText(query.value(3).toString());
        managers_latelineEdit->setText(query.value(4).toString());
        managers_leavelineEdit->setText(query.value(5).toString());
    }
    else
    {
        managers_absentlineEdit->setText("none");
        managers_latelineEdit->setText("none");
        managers_leavelineEdit->setText("none");
    }
}

void EditWorkersInfo::managers_updatepay(QDate date)
{
    QSqlQuery query;
    QString str = "select * from workers_payinfo where payinfo_date='"+date.toString("yyyy-MM")+"'";

    query.exec(str);

    if(query.next())
    {
        managers_totalpaylineEdit->setText(query.value(3).toString());
        managers_taxlineEdit->setText(query.value(4).toString());
        managers_incomelineEdit->setText(query.value(5).toString());
    }
    else
    {
        managers_totalpaylineEdit->setText("none");
        managers_taxlineEdit->setText("none");
        managers_incomelineEdit->setText("none");
    }
}

void EditWorkersInfo::editbasicinfo()
{
    QSqlQuery query;
    QString str;

    if(managers_idlineEdit->isModified() && !(managers_idlineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_id='"+managers_idlineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_namelineEdit->isModified() && !(managers_namelineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_name='"+managers_namelineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_phonelineEdit->isModified() && !(managers_phonelineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_telephone='"+managers_phonelineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_sexlineEdit->isModified() && !(managers_sexlineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_sex='"+managers_sexlineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_personnellineEdit->isModified() && !(managers_personnellineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_personnel='"+managers_personnellineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_idcardlineEdit->isModified() && !(managers_idcardlineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_sex='"+managers_idcardlineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_birthlineEdit->isModified() && !(managers_birthlineEdit->text().isEmpty()))
    {
        str = "udpate workers_basicinfo set workers_birthdate='"+managers_birthlineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_agelineEdit->isModified() && !(managers_agelineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_age='"+managers_agelineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_addresslineEdit->isModified() && !(managers_addresslineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_address='"+managers_addresslineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }
    if(managers_positionlineEdit->isModified() && !(managers_positionlineEdit->text().isEmpty()))
    {
        str = "update workers_basicinfo set workers_position='"+managers_positionlineEdit->text()+"' where workers_id='"+workersid+"'";
        query.exec(str);
    }

    QMessageBox::information(this,QString::fromLocal8Bit("修改成功！"),QString::fromLocal8Bit("用户信息修改成功！"));
}

void EditWorkersInfo::editpayinfo()
{
    QSqlQuery query;
    QString paydate,str;

    paydate = managers_dateEdit->date().toString("yyyy-MM");
    str = "select * from workers_payinfo where payinfo_date='"+paydate+"' and workers_id='"+workersid+"'";

    query.exec(str);

    if(query.next())
    {
        if(managers_totalpaylineEdit->isModified() && !(managers_totalpaylineEdit->text().isEmpty()))
        {
            str = "update workers_payinfo set payinfo_total='"+managers_totalpaylineEdit->text()+"' where payinfo_date='"+paydate+"' and workers_id='"+workersid+"'";
            query.exec(str);
        }
        if(managers_taxlineEdit->isModified() && !(managers_taxlineEdit->text().isEmpty()))
        {
            str = "update workers_payinfo set payinfo_tax='"+managers_taxlineEdit->text()+"' where payinfo_date='"+paydate+"' and workers_id='"+workersid+"'";
            query.exec(str);
        }
        if(managers_incomelineEdit->isModified() && !(managers_incomelineEdit->text().isEmpty()))
        {
            str = "update workers_payinfo set payinfo_income='"+managers_incomelineEdit->text()+"' where payinfo_date='"+paydate+"' and workers_id='"+workersid+"'";
            query.exec(str);
        }

        QMessageBox::information(this,QString::fromLocal8Bit("修改成功！"),QString::fromLocal8Bit("工资信息修改成功！"));
    }
    else
    {
        if(managers_totalpaylineEdit->text() == "none" || managers_taxlineEdit->text() == "none" || managers_incomelineEdit->text() == "none")
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("数据不完整!"),QString::fromLocal8Bit("数据不完整，请重新输入！"));

        }
        else
        {
            str = "insert into workers_payinfo(workers_id,payinfo_date,payinfo_total,payinfo_tax,payinfo_income)"
                    "values('"+workersid+"','"+paydate+"','"+managers_totalpaylineEdit->text()+"','"+managers_taxlineEdit->text()+"',"
                    "'"+managers_incomelineEdit->text()+"')";
            if(query.exec(str))
                QMessageBox::information(this,QString::fromLocal8Bit("修改成功！"),QString::fromLocal8Bit("工资信息修改成功！"));
        }
    }
}

void EditWorkersInfo::editattendinfo()
{

    QSqlQuery query;
    QString attenddate,str;

    attenddate = managers_dateEdit_2->date().toString("yyyy-MM");
    str = "select * from workers_attendinfo where attendinfo_date='"+attenddate+"' and workers_id='"+workersid+"'";

    query.exec(str);

    if(query.next())
    {
        if(managers_latelineEdit->isModified() && !(managers_latelineEdit->text().isEmpty()))
        {
            str = "update workers_attendinfo set attendinfo_latetimes='"+managers_latelineEdit->text()+"' where attendinfo_date='"+attenddate+"' and workers_id='"+workersid+"'";
            query.exec(str);
        }
        if(managers_leavelineEdit->isModified() && !(managers_leavelineEdit->text().isEmpty()))
        {
            str = "update workers_attendinfo set attendinfo_leavetimes='"+managers_leavelineEdit->text()+"' where attendinfo_date='"+attenddate+"' and workers_id='"+workersid+"'";
            query.exec(str);
        }
        if(managers_absentlineEdit->isModified() && !(managers_absentlineEdit->text().isEmpty()))
        {
            str = "update workers_attendinfo set attendinfo_absencetimes='"+managers_absentlineEdit->text()+"' where attendinfo_date='"+attenddate+"' and workers_id='"+workersid+"'";
            query.exec(str);
        }

        QMessageBox::information(this,QString::fromLocal8Bit("修改成功！"),QString::fromLocal8Bit("考勤信息修改成功！"));
    }
    else
    {
        if(managers_latelineEdit->text() == "none" || managers_leavelineEdit->text() == "none" || managers_absentlineEdit->text() == "none")
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("数据不完整!"),QString::fromLocal8Bit("数据不完整，请重新输入！"));

        }
        else
        {
            str = "insert into workers_attendinfo(workers_id,attendinfo_date,attendinfo_absencetimes,attendinfo_latetimes,attendinfo_leavetimes)"
                    "values('"+workersid+"','"+attenddate+"','"+managers_latelineEdit->text()+"','"+managers_leavelineEdit->text()+"',"
                    "'"+managers_absentlineEdit->text()+"')";
            if(query.exec(str))
                QMessageBox::information(this,QString::fromLocal8Bit("修改成功！"),QString::fromLocal8Bit("考勤信息修改成功！"));
        }
    }
}

void EditWorkersInfo::againbasicinfo()
{
    editworkers_load();
}

void EditWorkersInfo::firstupdate()
{
    QString str;
    QSqlQuery query;

    basicinfoid = 1;

    str = "select workers_id from workers_basicinfo where basicinfo_id = 1";
    query.exec(str);

    if(query.next())
        workersid = query.value(0).toString();
    editworkers_load();

}

void EditWorkersInfo::previousupdate()
{
    QSqlQuery query;
    QString str;

    basicinfoid--;

    if(basicinfoid == 0)
        basicinfoid = maxbasicinfoid;

    str = QString("select workers_id from workers_basicinfo where basicinfo_id = %1").arg(basicinfoid);
    query.exec(str);

    if(query.next())
        workersid = query.value(0).toString();

        editworkers_load();


}

void EditWorkersInfo::nextupdate()
{
    QSqlQuery query;
    QString str;

    basicinfoid++;

    if(basicinfoid == (maxbasicinfoid+1))
        basicinfoid = 1;

    str = QString("select workers_id from workers_basicinfo where basicinfo_id = %1").arg(basicinfoid);
    query.exec(str);

    if(query.next())
        workersid = query.value(0).toString();

        editworkers_load();
}

void EditWorkersInfo::lastupdate()
{

    QString str;
    QSqlQuery query;

        str = QString("select workers_id from workers_basicinfo where basicinfo_id = %1").arg(maxbasicinfoid);
        query.exec(str);

        if(query.next())
            workersid = query.value(0).toString();

            editworkers_load();
}

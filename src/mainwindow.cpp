#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QModelIndex>
#include <QWidget>
#include <QCompleter>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

QString workersId;      //save the workers' id of the logging
QString managersId;     //save the managers' id of the logging


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("log in");

    //log out and back to the login
    connect(welworkers.workers_table_signoutpushButton,SIGNAL(clicked()),this,SLOT(backToLogin()));
    connect(welworkers.workers_table_signoutpushButton_2,SIGNAL(clicked()),this,SLOT(backToLogin()));
    connect(welworkers.workers_table_signoutpushButton_3,SIGNAL(clicked()),this,SLOT(backToLogin()));

    connect(welmanagers.managers_signoutpushButton,SIGNAL(clicked()),this,SLOT(backToLogin()));

    //hide the text of login_lineEdit_passwd
    ui->login_lineEdit_passwd->setEchoMode(QLineEdit::Password);

    //connect the event with login_login button when ENTER is pressed after the passwd has been complete
    connect(ui->login_lineEdit_passwd, SIGNAL(returnPressed()), ui->login_login, SIGNAL(clicked()), Qt::UniqueConnection);

    QStringList userList;
    userList << "20111602310027" << "20111602310029";

    QCompleter *completer = new QCompleter(userList,this);
    ui->login_lineEdit_userName->setCompleter(completer);

    //set the background of login
    QPalette plt;
    plt.setBrush(QPalette::Window, QBrush(QPixmap("://images/backgroud.jpg")));
    this->setPalette(plt);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_login_clicked()
{
    int userType = ui->login_comboBox_userType->currentIndex();
    QString newComerNumber,newComerPasswd;
    newComerNumber = ui->login_lineEdit_userName->text();
    newComerPasswd = ui->login_lineEdit_passwd->text();

    if(newComerNumber.isEmpty() || newComerPasswd.isEmpty())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("错误!"),QString::fromLocal8Bit("用户名或密码为空!"));
    }
    else
    {
        QSqlQuery query;
        switch(userType)
        {
        case 0:
            query.exec("select * from workers where workers_id='"+newComerNumber+"' and workers_passwd='"+newComerPasswd+"'");
            if(query.next())
            {
                workersId = newComerNumber;
                welworkers.workers_load();
                welworkers.show();
                this->hide();
            }
            else
            {
                QMessageBox::warning(this , tr("登录失败"),tr("用户名或密码错误!"));
            }
            break;
        case 1:
            query.exec("select * from managers where managers_id='"+newComerNumber+"' and managers_passwd='"+newComerPasswd+"'");
            if(query.next())
            {
                managersId = newComerNumber;
                welmanagers.show();
                this->hide();
            }
            else
            {
                 QMessageBox::warning(this, tr("登录失败"),tr("用户名或密码错误!"));
            }
            break;
        };
    }

   ui->login_lineEdit_passwd->clear();
   ui->login_lineEdit_userName->setFocus();
}

void MainWindow::backToLogin()
{
    this->show();
    welworkers.hide();
    welmanagers.hide();
}


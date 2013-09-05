#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QTextCodec>

bool createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("127.0.0.1");
    	db.setDatabaseName("EnterprisePersonnelManagementSystem");
    	db.setUserName("root");
	db.setPassword("xtiprfw");
	if(!db.open())
	{
        QMessageBox::critical(0,QObject::tr("Database Error"),
				db.lastError().text());
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection())
	    return 1;
    MainWindow w;
    w.show();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    //  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
     
    return a.exec();
}

#ifndef GLOBLE_CPP
#define GLOBLE_CPP
#include "globle.h"
#include <QtDebug>
#include <QSqlError>

//globle::globle()
//{

//}
QString dataBaseName = "student_manage";
QVariantList list_all_student;
QString sqluser="root";
QString sqlpass="12345678";

QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

// Open the Database
bool openDatabase()
{
    db.setHostName("localhost");
    db.setDatabaseName(dataBaseName);
    db.setUserName(sqluser);
    db.setPassword(sqlpass);
    db.setPort(3306);

    if (!db.open()) {
           qDebug() << "打开数据库时出错："<< db.lastError().text();
           return false;
       }

           qDebug() << "成功打开数据库！";
    return true;
}

// Close Database
void closeDatabase()
{
    db.close();
}

#endif // VARIATE_H

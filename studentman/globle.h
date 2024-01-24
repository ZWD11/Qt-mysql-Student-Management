#ifndef GLOBLE_H
#define GLOBLE_H
#include <QString>
#include <QSqlQuery>
#include <QVariantList>
#include <QMessageBox>


extern int num01;
extern QString dataBaseName;
extern QVariantList list_all_student;
extern QString sqluser;
extern QString sqlpass;

extern bool openDatabase();
extern void closeDatabase();
extern QSqlDatabase db;

//class globle
//{
//public:
//    globle();
//};

#endif // GLOBLE_H

#include "student.h"
#include "ui_student.h"
#include "mainwindow.h"
#include "globle.h"
#include  <QtDebug>
#include "student_info.h"
#include "student_course.h"
#include "contact_manage.h"

student::student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    setWindowTitle("学生所有信息界面");

    ui->tableWidget->hide();
    headers_info<<"学号"<<"姓名"<<"性别"<<"年龄"<<"专业"<<"登录密码";
    headers_course<<"已选课程"<<"教师"<<"学分";
    headers_grade<<"课程"<<"成绩"<<"绩点";
    on_infoButton_clicked();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("student{border-image:url(:/jpg/3.jpg);}");
}

student::~student()
{
    delete ui;
}


void student::setID(QString Sno){
    id = Sno;
     on_infoButton_clicked();
}

//读取学生信息并显示
void student::on_infoButton_clicked()
{
    ui->tableWidget->show();
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setVerticalHeaderLabels(headers_info);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QSqlQuery query;
    QString sql = QString("select * from student where Sno = '%1'").arg(id);
    query.exec(sql);

    if(query.next())
    {
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(1,0,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(2,0,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(3,0,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(4,0,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(5,0,new QTableWidgetItem(query.value(5).toString()));
    }
    else{
        qDebug()<<"未找到该生的信息";
    }

}

//查看已选课程
void student::on_courseButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->show();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(headers_course);
    ui->tableWidget->horizontalHeader()->show();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSqlQuery query;
    QString sql = QString("select name,teacher,credit from Course,SCore where Course.Cno=SCore.Cno and SCore.Sno = '%1'").arg(id);
    query.exec(sql);

    int row=0;
    while(query.next())
    {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(2).toString()));

        row++;
    }
}

//查看成绩
void student::on_scoreButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->show();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(headers_grade);
    ui->tableWidget->horizontalHeader()->show();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QSqlQuery query;
    QString sql = QString("select name,grade from Course,SCore where Course.Cno=SCore.Cno and SCore.Sno = '%1'").arg(id);
    query.exec(sql);

    int row=0;
    while(query.next())
    {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(query.value(1).toDouble()/10-5)));  //计算绩点

        row++;
    }
}

//修改信息
void student::on_pushButton_clicked()
{
    student_info *ww=new student_info;
    ww->setID(id);
    ww->show();
}

//选课退课
void student::on_pushButton_2_clicked()
{
    student_course* bb=new student_course;
    bb->setID(id);
    bb->show();
}

//计算总学分（已经选的课程的学分总和）
void student::on_sumcreditBtn_clicked()
{
    QSqlQuery query;
    QString sql_1=QString("select sum(credit) from score join course on score.cno = course.cno where Sno='%1'").arg(id);
    query.exec(sql_1);
    query.first();
        if(query.value(0).isNull()==false)
        {
             QString credit=query.value(0).toString();
             QMessageBox::information(this ,tr("提示") , QString("总目标已选学分为 %1 ").arg(credit) );

        }
        else{

                QMessageBox::information(this ,tr("提示") , tr("总目标已选学分为 0 "));
        }
}

//已获得学分（大于等于60则为已获得）
void student::on_cmpcreditBtn_clicked()
{
    QSqlQuery query;
    QString sql_1=QString("select sum(credit) from score join course on score.cno = course.cno where score.grade >= 60 and Sno='%1'").arg(id);
    query.exec(sql_1);
    query.first();
        if(query.value(0).isNull()==false)
        {
             QString credit=query.value(0).toString();
             QMessageBox::information(this ,tr("提示") , QString("已获得学分为 %1 ").arg(credit) );

        }
        else{

                QMessageBox::information(this ,tr("提示") , tr("已获得学分为 0 "));
        }
}

//重新登录
void student::on_pushButton_3_clicked()
{
    MainWindow *re;
    this->hide();
    re = new MainWindow;
    re->show();
}

void student::on_contactmanage_clicked()
{
    contact_manage *cm;
    cm = new contact_manage;
    cm->show();
}

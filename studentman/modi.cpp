#include "modi.h"
#include "ui_modi.h"
#include "QDebug"
#include "globle.h"
#include <QDesktopServices>
#include <QUrl>
#include <mainwindow.h>

modi::modi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modi)
{
    ui->setupUi(this);
    setWindowTitle("密码重置");
    ui->modi_password->setEchoMode(QLineEdit::Password); //设置密码框内的样式
    connect(ui->modi_password,&QLineEdit::returnPressed,this,&modi::on_modiButton_clicked);//与ui界面连接
    ui->modi_password_old->setEchoMode(QLineEdit::Password);
    connect(ui->modi_password_old,&QLineEdit::returnPressed,this,&modi::on_modiButton_clicked);
    this->move(800,300);

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("modi{border-image:url(:/jpg/3.jpg);}");
}

modi::~modi()
{
    delete ui;
}

void modi::on_modiButton_clicked(){
    QString id = ui->modi_username->text();
    QString old_password = ui->modi_password_old->text();
    QString new_password = ui->modi_password->text();
    qDebug()<<"用户名:"<<id<<"密码:"<<new_password;

    if (!openDatabase())
    {
        QMessageBox::warning(this, tr("错误"), tr("打开数据库失败!"));
        return ;
    }
   if(ui->radioButton->isChecked()){
    //管理员密码修改
        QSqlQuery query;
        query.exec("select id,password from Admin");
        bool T2=true;
        while(query.next())
        {
            QString id1 = query.value(0).toString();
            QString id2 = query.value(1).toString();
            if (id.compare(id1) == 0&&old_password.compare(id2) == 0) {
                            QString sql = "UPDATE Admin SET password = :newPassword WHERE id = :userId and password = :oldPassword";
                            QSqlQuery updateQuery;
                            updateQuery.prepare(sql);
                            updateQuery.bindValue(":newPassword", new_password);
                            updateQuery.bindValue(":userId", id);
                            updateQuery.bindValue(":oldPassword", old_password);
                if(updateQuery.exec()&&id!=nullptr&&old_password!=nullptr&&new_password!=nullptr)
                {
                    QMessageBox::information(this ,tr("提示") , tr("重置密码成功,请登录"));
                    T2=false;
                    MainWindow *m;
                    this->hide();
                    m = new MainWindow;
                    m->show();
                }
                else
                {
                    QMessageBox::information(this ,tr("提示") , tr("重置失败，请重新输入！"));
                    T2=false;
                    MainWindow *m;
                    this->hide();
                    m = new MainWindow;
                    m->show();
                }

            }
        }
        if(T2==true){
            QMessageBox::information(this ,tr("提示") , tr("旧密码错误，无法更改"));
            MainWindow *m;
            this->hide();
            m = new MainWindow;
            m->show();
        }
   }
   if(ui->radioButton_2->isChecked()){
       //学生密码修改
           QSqlQuery query;
           query.exec("select sno,password from student");
           bool T2=true;
           while(query.next())
           {
               QString id1= query.value(0).toString();
               QString id2= query.value(1).toString();
               if (id.compare(id1) == 0&&old_password.compare(id2) == 0) {
                               QString sql = "UPDATE student SET password = :newPassword WHERE sno = :userId and password = :oldPassword";
                               QSqlQuery updateQuery;
                               updateQuery.prepare(sql);
                               updateQuery.bindValue(":newPassword", new_password);
                               updateQuery.bindValue(":userId", id);
                               updateQuery.bindValue(":oldPassword", old_password);
                   if(updateQuery.exec())
                   {
                       QMessageBox::information(this ,tr("提示") , tr("重置密码成功，请登录!"));
                       T2=false;
                       MainWindow *m;
                       this->hide();
                       m = new MainWindow;
                       m->show();                   }
                   else
                   {
                       QMessageBox::information(this ,tr("提示") , tr("输入信息有误，重置密码失败！"));
                       T2=false;
                       MainWindow *m;
                       this->hide();
                       m = new MainWindow;
                       m->show();
                   }

               }
           }
           if(T2==true){
               QMessageBox::information(this ,tr("提示") , tr("无法更改，请联系管理员"));
               MainWindow *m;
               this->hide();
               m = new MainWindow;
               m->show();

           }

   }
   if(!ui->radioButton->isChecked()&&!ui->radioButton_2->isChecked()&&id==nullptr&&old_password==nullptr&&new_password==nullptr){
       QMessageBox::information(this ,tr("提示") , tr("请输入"));
   }
 }

void modi::on_zwdzyctxq_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://blog.zwdblog.online")));
}

void modi::on_backButton_clicked()
{
    MainWindow *m;
    this->hide();
    m = new MainWindow;
    m->show();
}

#include "contact_manage.h"
#include "ui_contact_manage.h"
#include "mainwindow.h"
#include <QtDebug>
#include <QSqlError>

contact_manage::contact_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contact_manage)
{
    ui->setupUi(this);
    setWindowTitle("联系管理员");

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("contact_manage{border-image:url(:/jpg/3.jpg);}");
}

contact_manage::~contact_manage()
{
    delete ui;
}

void contact_manage::on_sendButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString username=ui->idLineEdit_2->text();
    QString aff=ui->idLineEdit_3->text();

    QSqlQuery query;
    query.exec("select Sno from student");
    bool T2=true;
    while(query.next())
    {
        QString id1= query.value(0).toString();
        if(id.compare(id1)==0){
            QString sql = "INSERT INTO affairs (id, username, something) VALUES (:id, :username, :something)";
            QSqlQuery sendQuery;
            sendQuery.prepare(sql);
            sendQuery.bindValue(":id", id);
            sendQuery.bindValue(":username", username);
            sendQuery.bindValue(":something", aff);

            bool ok = sendQuery.exec();

            if (ok&&id!=nullptr&&username!=nullptr&&aff!=nullptr) {
                QMessageBox::information(this, tr("提示"), tr("发送成功!"));
                T2 = false;
            } else {
                QMessageBox::critical(this, tr("错误"), tr("发送失败,请重试！"));
                T2 = false;
            }
        }
    }
    if(T2 == true){
        QMessageBox::information(this ,tr("提示") , tr("请输入正确的学号"));
    }

}

void contact_manage::on_backButton_clicked()
{
    this->hide();
}

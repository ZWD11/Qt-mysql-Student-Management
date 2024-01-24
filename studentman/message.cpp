#include "message.h"
#include "ui_message.h"
#include "globle.h"
#include "QSqlError"
#include "manage.h"
#include "look_message.h"
#include <QtDebug>

message::message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message)
{
    ui->setupUi(this);
    setWindowTitle("查看信箱");

    ui->seeAllButton->hide();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    headers<<"学号"<<"姓名"<<"事务";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(50);
    on_seeAllButton_clicked();

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("message{border-image:url(:/jpg/3.jpg);}");
}

message::~message()
{
    delete ui;
}

void message::on_seeAllButton_clicked()
{

    QSqlQuery query;

    query.exec("select id,username,something from affairs");
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int row=0;
    while(query.next())
    {
        for(int i  = 0 ; i <3; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(query.value(i).toString());
            ui->tableWidget->setItem(row, i, item);
        }
        row++;
    }

}

void message::on_deletemess_clicked()
{
    QString id = ui->idLineEdit->text();

    QMessageBox::StandardButton confirmation = QMessageBox::question(
            this,
            tr("确认删除"),
            tr("确定要删除吗？"),
            QMessageBox::Yes | QMessageBox::No
        );

    if (confirmation == QMessageBox::Yes) {
    QSqlQuery query;
    query.exec("select id from affairs");

    bool found = false;  // 标记是否找到匹配的ID

    while (query.next()) {
        QString id1 = query.value(0).toString();

        if (id.compare(id1) == 0) {
            QString sql;
            sql = QString("DELETE FROM affairs WHERE id = '%1' ").arg(id);

            QSqlQuery deleteQuery;
            bool deleteOk = deleteQuery.exec(sql);

            if (deleteOk) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        QMessageBox::information(this, tr("提示"), tr("删除成功!"));
    } else {
        QMessageBox::information(this, tr("提示"), tr("查无此学号，无法删除！"));
    }
}
    on_seeAllButton_clicked();
}

void message::on_backButton_clicked()
{
    this->hide();
}

void message::on_lookmessage_clicked()
{
    QString id = ui->idLineEdit->text();
    qDebug()<<"用户名:"<<id;
    QSqlQuery query;
    query.exec("select id from affairs");
    bool T1 = true;
    while(query.next()){
    QString id1 = query.value(0).toString();
    if(id == id1){
        T1 = false;
    }
   }
    if(T1==true){
        QMessageBox::information(this, tr("提示"), tr("查无此人，请重新输入！"));
    }
    if(T1==false){
        look_message *m;
        m = new look_message;
        m->setID(id);
        m->show();
    }
}

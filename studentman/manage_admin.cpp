#include "manage_admin.h"
#include "ui_manage_admin.h"
#include "manage.h"
#include "globle.h"
manage_admin::manage_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manage_admin)
{
    ui->setupUi(this);
    setWindowTitle("管理管理员界面");

    ui->seeAllButton->hide();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //显示列名并自动调整显示大小
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //表格不可编辑

    headers<<"编号"<<"姓名"<<"密码";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(50);
    on_seeAllButton_clicked();

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("manage_admin{border-image:url(:/jpg/3.jpg);}");

}

manage_admin::~manage_admin()
{
    delete ui;
}

void manage_admin::on_insertButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString username=ui->nameLineEdit->text();
    QString password=ui->passwardLineEdit->text();

    QSqlQuery query;
    query.exec("select id from Admin");
    bool T2=true;
    while(query.next())
    {
        QString id1= query.value(0).toString();

        if(id.compare(id1)==0)
        {
            QMessageBox::information(this ,tr("提示") , tr("该编号已存在不允许再次添加!"));
            T2=false;
        }
    }
    if(T2==true&&id!=nullptr&&username!=nullptr&&password!=nullptr)
    {
        QString sql;
        sql = QString("insert into Admin (id,username,password)"
                      " VALUES ('%1', '%2' , '%3' )")
                .arg(id).arg(username).arg(password);

        bool ok = query.exec(sql);
        if(ok)
            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        else
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));

    }
    if(id==nullptr||username==nullptr||password==nullptr){
        QMessageBox::information(this ,tr("提示") , tr("信息为空，不能添加"));
    }
    on_seeAllButton_clicked();

}

void manage_admin::on_updateButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString username=ui->nameLineEdit->text();
    QString password=ui->passwardLineEdit->text();

    QSqlQuery query;
    query.exec("select id from Admin");
    bool T2=true;
    while(query.next())
    {
        QString id1= query.value(0).toString();
        if(id.compare(id1)==0)
        {
            QString sql;
            sql = QString("UPDATE Admin "
                          "set username = '%0',password = '%1'"
                          " where id = '%2' ")
                    .arg(username).arg(password).arg(id);


            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                QMessageBox::information(this ,tr("提示") , tr("更改成功!"));
                T2=false;
            }
            else
            {
                QMessageBox::information(this ,tr("提示") , tr("更改失败!"));
                T2=false;
            }

        }
    }
    if(T2==true)
        QMessageBox::information(this ,tr("提示") , tr("该编号不存在，无法更改"));

    on_seeAllButton_clicked();
}

void manage_admin::on_deleteButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString username=ui->nameLineEdit->text();
    QString password=ui->passwardLineEdit->text();

    QMessageBox::StandardButton confirmation = QMessageBox::question(
            this,
            tr("确认删除"),
            tr("确定要删除该管理员吗？"),
            QMessageBox::Yes | QMessageBox::No
        );

    if (confirmation == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("select id from Admin");
        bool T2=true;
        while(query.next())
        {
            QString id1= query.value(0).toString();

            if(id.compare(id1)==0)
            {
                QString sql;
                sql = QString("DELETE FROM Admin "
                              " where id = '%1' ").arg(id);

                QSqlQuery query;
                bool ok = query.exec(sql);
                if(ok)
                {

                    QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
                    T2=false;
                }
                else
                {
                    QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
                    T2=false;
                }

            }
        }
        if(T2==true)
            QMessageBox::information(this ,tr("提示") , tr("信息为空，不能添加"));
}
    on_seeAllButton_clicked();
}

void manage_admin::on_seeAllButton_clicked()
{

    QSqlQuery query;

    query.exec("select id,username,password from Admin");
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int row=0;
    //按行填充列
    while(query.next())
    {
        for(int i = 0 ; i < 3; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(query.value(i).toString());
            ui->tableWidget->setItem(row, i, item);
        }
        row++;
    }

}

void manage_admin::on_backButton_clicked(){
   // manage *dh;
    this->hide();
    //dh=new manage ;
   // dh->show();
}

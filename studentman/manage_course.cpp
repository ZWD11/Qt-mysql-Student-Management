#include "manage_course.h"
#include "ui_manage_course.h"
#include "manage.h"
#include "globle.h"

manage_course::manage_course(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manage_course)
{
    ui->setupUi(this);
    setWindowTitle("课程管理界面");

    ui->seeAllButton->hide();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    headers<<"课程号"<<"课程名"<<"教师"<<"学分";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(100);
    on_seeAllButton_clicked();

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("manage_course{border-image:url(:/jpg/3.jpg);}");
}

manage_course::~manage_course()
{
    delete ui;
}



void manage_course::on_insertButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString cname=ui->nameLineEdit->text();
    QString teacher=ui->teacherLineEdit->text();
    QString credit=ui->creditLineEdit->text();

    QSqlQuery query;
    query.exec("select Cno from course");
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
    if(T2==true)
    {
        QString sql;
        sql = QString("insert into Course  VALUES ('%1', '%2' , '%3', %4 )")
                .arg(id).arg(cname).arg(teacher).arg(credit);


        bool ok = query.exec(sql);
        if(ok)
            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        else
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));

    }
    on_seeAllButton_clicked();

}

void manage_course::on_updateButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString cname=ui->nameLineEdit->text();
    QString teacher=ui->teacherLineEdit->text();
    QString credit=ui->creditLineEdit->text();

    QSqlQuery query;
    query.exec("select Cno from course");
    bool T2=true;
    while(query.next())
    {
        QString id1= query.value(0).toString();
        if(id.compare(id1)==0)
        {
            QString sql;
            sql = QString("UPDATE course "
                          "set name= '%2',teacher = '%3',credit=%4"
                          " where Cno = '%1' ")
                    .arg(id).arg(cname).arg(teacher).arg(credit);


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
        QMessageBox::information(this ,tr("提示") , tr("该课程号不存在，无法更改"));

    on_seeAllButton_clicked();
}

void manage_course::on_deleteButton_clicked()
{
    QString id=ui->idLineEdit->text();

    QMessageBox::StandardButton confirmation = QMessageBox::question(
            this,
            tr("确认删除"),
            tr("确定要删除吗？"),
            QMessageBox::Yes | QMessageBox::No
        );

    if (confirmation == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("select Cno from course");
        bool T2=true;
        while(query.next())
        {
            QString id1= query.value(0).toString();

            if(id.compare(id1)==0)
            {
                QString sql;
                sql = QString("DELETE FROM Course where Cno = '%1' ").arg(id);

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
            QMessageBox::information(this ,tr("提示") , tr("该课程号不存在无法删除"));
}
    on_seeAllButton_clicked();
}

void manage_course::on_seeAllButton_clicked()
{

    QSqlQuery query;
    query.exec("select * from course");
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int row=0;
    while(query.next())
    {
        for(int i  = 0 ; i <4; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(query.value(i).toString());
            ui->tableWidget->setItem(row, i, item);
        }
        row++;
    }

}

void manage_course::on_backButton_clicked(){
    //manage *dh;
    this->hide();
   // dh=new manage ;
    //dh->show();
}

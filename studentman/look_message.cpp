#include "look_message.h"
#include "ui_look_message.h"
#include "globle.h"
#include <QtDebug>
#include <QSqlError>

look_message::look_message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::look_message)
{
    ui->setupUi(this);

    setWindowTitle("查看内容");

    ui->seeAllButton->hide();
    ui->seeAllButton->hide();

    ui->textEdit->show();     // 显示 QTextEdit

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    headers << "事务";
    ui->textEdit->clear();  // 清空文本框

    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("look_message{border-image:url(:/jpg/3.jpg);}");
}

look_message::~look_message()
{
    delete ui;
}

void look_message::setID(QString Sno){
     id1 = Sno;
     on_seeAllButton_clicked();
}

void look_message::on_backButton_clicked()
{
    this->hide();
}

void look_message::on_seeAllButton_clicked()
{
    QString sql = QString("select something from affairs where id = '%1'").arg(id1);

    QSqlQuery query;
    query.exec(sql);

    while (query.next())
    {
        ui->textEdit->append(query.value(0).toString());
        ui->textEdit->append("----------------------大佬专用分割线---------------------------");  // 分割线
    }
}

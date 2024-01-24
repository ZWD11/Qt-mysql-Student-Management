#include "manage.h"
#include "ui_manage.h"
#include "globle.h"
#include "mainwindow.h"
#include "manage_admin.h"
#include "manage_student.h"
#include "manage_grade.h"
#include "manage_course.h"
#include "manage_teacher.h"
#include "message.h"


manage::manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manage)
{
    ui->setupUi(this);
    setWindowTitle("管理员管理界面");
    setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("manage{border-image:url(:/jpg/3.jpg);}");
}

manage::~manage()
{
    delete ui;
}

void manage::on_manage_adminButton_clicked()
{
    manage_admin *ti=new manage_admin;
    ti->show();
}

void manage::on_stu_inform_guanlipushButton_clicked()
{
    manage_student *ij=new manage_student;
    ij->show();
}



void manage::on_manage_gradepushButton_clicked()
{
    manage_grade *pk=new manage_grade;
    pk->show();
}

void manage::on_course_manageButton_clicked()
{
    manage_course *ew=new manage_course;
    ew->show();
}


void manage::on_manage_teacherBtn_clicked()
{
    manage_teacher *vw=new manage_teacher;
    vw->show();
}

void manage::on_reloginButton_clicked()
{
    MainWindow *re;
    this->hide();
    re=new MainWindow;
    re->show();
}

void manage::on_lookmess_clicked()
{
    message *m = new message;
    m->show();
}

#ifndef LOOK_MESSAGE_H
#define LOOK_MESSAGE_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <globle.h>

namespace Ui {
class look_message;
}

class look_message : public QWidget
{
    Q_OBJECT

public:
    explicit look_message(QWidget *parent = nullptr);
    ~look_message();
    void setID(QString Sno);

private slots:
    void on_backButton_clicked();

    void on_seeAllButton_clicked();

private:
    Ui::look_message *ui;
    QStringList headers;
    QString id1;
};

#endif // LOOK_MESSAGE_H

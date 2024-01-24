#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <globle.h>
#include <QtDebug>

namespace Ui {
class message;
}

class message : public QWidget
{
    Q_OBJECT

public:
    explicit message(QWidget *parent = nullptr);
    ~message();

private slots:
    void on_seeAllButton_clicked();

    void on_deletemess_clicked();

    void on_backButton_clicked();

    void on_lookmessage_clicked();

private:
    Ui::message *ui;
    QStringList headers;

};

#endif // MESSAGE_H

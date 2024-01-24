#ifndef CONTACT_MANAGE_H
#define CONTACT_MANAGE_H

#include <QWidget>

namespace Ui {
class contact_manage;
}

class contact_manage : public QWidget
{
    Q_OBJECT

public:
    explicit contact_manage(QWidget *parent = nullptr);
    ~contact_manage();

private slots:
    void on_sendButton_clicked();

    void on_backButton_clicked();

private:
    Ui::contact_manage *ui;
        contact_manage *m;

};

#endif // CONTACT_MANAGE_H

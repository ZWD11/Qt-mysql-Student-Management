#ifndef MODI_H
#define MODI_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class modi;
}

class modi : public QWidget
{
    Q_OBJECT

public:
    explicit modi(QWidget *parent = nullptr);
    ~modi();

private:
    Ui::modi *ui;

private slots:
    void on_modiButton_clicked();

    void on_zwdzyctxq_clicked();
    void on_backButton_clicked();
};

#endif // MODI_H

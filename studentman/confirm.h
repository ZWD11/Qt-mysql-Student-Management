#ifndef CONFIRM_H
#define CONFIRM_H

#include <QWidget>

namespace Ui {
class confirm;
}

class confirm : public QWidget
{
    Q_OBJECT

public:
    explicit confirm(QWidget *parent = nullptr);
    ~confirm();

private slots:


    void on_confirm_2_clicked();

private:
    Ui::confirm *ui;
};

#endif // CONFIRM_H

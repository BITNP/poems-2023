#ifndef ENTER_RECIPE_H
#define ENTER_RECIPE_H

#include <QWidget>

namespace Ui {
class enter_recipe;
}

class enter_recipe : public QWidget
{
    Q_OBJECT

public:
    explicit enter_recipe(QWidget *parent = nullptr);
    ~enter_recipe();

private slots:
    void on_enter_recipe_back_clicked();
    void on_ok_clicked();

signals:
    void change_main_again();

private:
    Ui::enter_recipe *ui;
};

#endif // ENTER_RECIPE_H

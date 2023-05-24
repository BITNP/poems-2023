#ifndef CHOOSE_RECIPE_H
#define CHOOSE_RECIPE_H

#include <QMainWindow>

namespace Ui {
class choose_recipe;
}

class choose_recipe : public QMainWindow
{
    Q_OBJECT

public:
    explicit choose_recipe(QWidget *parent = nullptr);
    ~choose_recipe();

private slots:
    void on_choose_recipe_back_clicked();
    void on_ok_clicked();
    void on_again_clicked();
    void on_confirmation_clicked();

signals:
    void change_main();


private:
    Ui::choose_recipe *ui;
};

#endif // CHOOSE_RECIPE_H



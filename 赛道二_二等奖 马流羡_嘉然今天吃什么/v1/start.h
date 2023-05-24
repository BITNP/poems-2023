#ifndef START_H
#define START_H

#include <QMainWindow>
#include "choose_recipe.h"
#include "enter_recipe.h"
#include "evaluate_recipe.h"

namespace Ui {
class Start;
}

class Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();

private:
    Ui::Start *ui;


private slots:
    void on_goto_recipe_clicked();
    void on_goto_enter_recipe_clicked();
    void on_goto_evaluate_recipe_clicked();

    void back_from_choose_recipe();
    void back_from_enter_recipe();
    void back_from_evaluate_recipe();


private:
    choose_recipe recipe;
    enter_recipe E_recipe;
    evaluate_recipe Ev_recipe;

signals:
   void show_the_chosen_recipe();
};

#endif // START_H

#ifndef EVALUATE_RECIPE_H
#define EVALUATE_RECIPE_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class evaluate_recipe;
}

class evaluate_recipe : public QWidget
{
    Q_OBJECT

public:
    explicit evaluate_recipe(QWidget *parent = nullptr);
    ~evaluate_recipe();

    QButtonGroup * Score_star;
    QButtonGroup * Waiting_star;
    bool eventFilter(QObject *, QEvent *);

private slots:
    void on_evaluate_recipe_back_clicked();
    void on_certainty_clicked();
    void back();
    void on_clear_clicked();


public slots:
    void show_chosen_recipe();
    void on_score_star();
    void on_waiting_star();

signals:
    void change_main_again_again();


private:
    Ui::evaluate_recipe *ui;
};

#endif // EVALUATE_RECIPE_H

#include "start.h"
#include "ui_start.h"
#include "choose_recipe.h"
#include <QMovie>


Start::Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    ui->gif->lower();
    QMovie *movie = new QMovie(":/1/backgif.gif");
    ui->gif->setMovie(movie);
    movie->start();
    ui->goto_recipe->setFixedSize(200,200);
    ui->goto_recipe->setStyleSheet("QPushButton{border-image:url(:/1/2.JPG);}"
                           "QPushButton:hover{border-image:url(:/1/1.png);}"
                           "QPushButton:pressed{border-image:url(:/1/1.png);}"
                           );
    ui->goto_enter_recipe->setFixedSize(200,200);
    ui->goto_enter_recipe->setStyleSheet("QPushButton{border-image:url(:/1/3.JPG);}"
                           "QPushButton:hover{border-image:url(:/1/2.png);}"
                           "QPushButton:pressed{border-image:url(:/1/2.png);}"
                           );
    ui->goto_evaluate_recipe->setFixedSize(200,200);
    ui->goto_evaluate_recipe->setStyleSheet("QPushButton{border-image:url(:/1/11.png);}"
                           "QPushButton:hover{border-image:url(:/1/3.png);}"
                           "QPushButton:pressed{border-image:url(:/1/3.png);}"
                           );

    connect(&recipe,&choose_recipe::change_main,this,&Start::back_from_choose_recipe);
    connect(&E_recipe,&enter_recipe::change_main_again,this,&Start::back_from_enter_recipe);
    connect(&Ev_recipe,&evaluate_recipe::change_main_again_again,this,&Start::back_from_evaluate_recipe);
    connect(this,&Start::show_the_chosen_recipe,&Ev_recipe,&evaluate_recipe::show_chosen_recipe);
}

Start::~Start()
{
    delete ui;
}


void Start::on_goto_recipe_clicked()
{
    this->hide();
    recipe.setFixedSize(1600,800);
    recipe.show();
}

void Start::on_goto_enter_recipe_clicked()
{
    this->hide();
    E_recipe.setFixedSize(1600,800);
    E_recipe.show();
}

void Start::on_goto_evaluate_recipe_clicked()
{
    this->hide();
    emit show_the_chosen_recipe();
    Ev_recipe.setFixedSize(1600,800);
    Ev_recipe.show();
}

void Start::back_from_choose_recipe()
{
    this->show();
    recipe.hide();
}

void Start::back_from_enter_recipe()
{
    this->show();
    E_recipe.hide();
}

void Start::back_from_evaluate_recipe()
{
    this->show();
    Ev_recipe.hide();
}

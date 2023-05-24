#include "evaluate_recipe.h"
#include "ui_evaluate_recipe.h"
#include "start.h"
#include "project_feedback.h"

#include <QButtonGroup>
#include <QFile>
#include <QComboBox>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QDebug>

evaluate_recipe::evaluate_recipe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::evaluate_recipe)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("QWidget{ border-image: url(:/1/background.png)}");

    Score_star = new QButtonGroup(this);
    Score_star->addButton(ui->score_star1,1);
    Score_star->addButton(ui->score_star2,2);
    Score_star->addButton(ui->score_star3,3);
    Score_star->addButton(ui->score_star4,4);
    Score_star->addButton(ui->score_star5,5);
    Waiting_star = new QButtonGroup(this);
    Waiting_star->addButton(ui->waiting_star1,1);
    Waiting_star->addButton(ui->waiting_star2,2);
    Waiting_star->addButton(ui->waiting_star3,3);
    Waiting_star->addButton(ui->waiting_star4,4);
    Waiting_star->addButton(ui->waiting_star5,5);

    connect(ui->score_star1,SIGNAL(clicked()),this,SLOT(on_score_star()));
    connect(ui->score_star2,SIGNAL(clicked()),this,SLOT(on_score_star()));
    connect(ui->score_star3,SIGNAL(clicked()),this,SLOT(on_score_star()));
    connect(ui->score_star4,SIGNAL(clicked()),this,SLOT(on_score_star()));
    connect(ui->score_star5,SIGNAL(clicked()),this,SLOT(on_score_star()));
    connect(ui->waiting_star1,SIGNAL(clicked()),this,SLOT(on_waiting_star()));
    connect(ui->waiting_star2,SIGNAL(clicked()),this,SLOT(on_waiting_star()));
    connect(ui->waiting_star3,SIGNAL(clicked()),this,SLOT(on_waiting_star()));
    connect(ui->waiting_star4,SIGNAL(clicked()),this,SLOT(on_waiting_star()));
    connect(ui->waiting_star5,SIGNAL(clicked()),this,SLOT(on_waiting_star()));

    ui->score_star1->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->score_star1->installEventFilter(this);       //安装事件过滤器
    ui->score_star2->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->score_star2->installEventFilter(this);       //安装事件过滤器
    ui->score_star3->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->score_star3->installEventFilter(this);       //安装事件过滤器
    ui->score_star4->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->score_star4->installEventFilter(this);       //安装事件过滤器
    ui->score_star5->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->score_star5->installEventFilter(this);
    ui->waiting_star1->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->waiting_star1->installEventFilter(this);       //安装事件过滤器
    ui->waiting_star2->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->waiting_star2->installEventFilter(this);       //安装事件过滤器
    ui->waiting_star3->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->waiting_star3->installEventFilter(this);       //安装事件过滤器
    ui->waiting_star4->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->waiting_star4->installEventFilter(this);       //安装事件过滤器
    ui->waiting_star5->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->waiting_star5->installEventFilter(this);

    ui->evaluate_recipe_back->setGeometry(1470,0,130,130);
    ui->evaluate_recipe_back->setStyleSheet("QPushButton{border-image:url(:/1/PB1.png);}"
                           "QPushButton:hover{border-image:url(:/1/4.png);}"
                           "QPushButton:pressed{border-image:url(:/1/4.png);}"
                           );

    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&evaluate_recipe::back);


}

evaluate_recipe::~evaluate_recipe()
{
    delete ui;
}


void evaluate_recipe::show_chosen_recipe()
{
    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/should be reviewed.csv"));
    QFile outshow(path);
    if(!outshow.open(QIODevice::ReadOnly))
    {
        exit(0);
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QString content = codec->toUnicode(outshow.readAll());
    outshow.close();
    QStringList Data =content.split("\r",QString::SkipEmptyParts);
    for(int i=0;i<Data.count();++i)
    {
        QStringList strLine = Data.at(i).split(",");     //一行中的单元格以，区分
        QString temp=strLine.at(1)+" "+strLine.at(2)+ "("+strLine.at(0)+")";
        Data.replace(i,temp);
    }

    ui->comboBox->addItems(Data);
    if(QString::compare(content,"")==0){
        ui->certainty->setEnabled(false);
        ui->clear->setEnabled(false);
    }
    else {
        ui->certainty->setEnabled(true);
        ui->clear->setEnabled(true);
    }

}


void evaluate_recipe::on_score_star()
{
    ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    ui->score_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    switch(Score_star->checkedId())
    {

        case 1:
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star1.png);}"
                                          );
            break;
        case 2:
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            break;
        case 3:
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            break;
        case 4:
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            break;
        case 5:
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            ui->score_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star1.png);}"
                                      );
            break;
    }
}

void evaluate_recipe::on_waiting_star()
{
    ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    ui->waiting_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                               "QRadioButton{image: url(:/1/star0.png);}"
                              );
    switch(Waiting_star->checkedId())
    {

        case 1:
            ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star2.png);}"
                                          );
            break;
        case 2:
            ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            break;
        case 3:
            ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            break;
        case 4:
            ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            break;
        case 5:
            ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            ui->waiting_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
            break;
    }
}

bool evaluate_recipe::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->score_star1) {
        if(event->type() == QEvent::HoverEnter) {
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            return true;
        }
        else if(event->type() == QEvent::HoverLeave){
            if(Score_star->checkedId() < 1){
                ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            return true;
        }
    }
    else if(obj == ui->score_star2) {
        if(event->type() == QEvent::HoverEnter) {
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            return true;
        }
        else if(event->type() == QEvent::HoverLeave){
            if(Score_star->checkedId() < 1){
                ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 2){
                ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            return true;
        }
    }
    else if(obj == ui->score_star3) {
        if(event->type() == QEvent::HoverEnter) {
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            return true;
        }
        else if(event->type() == QEvent::HoverLeave){
            if(Score_star->checkedId() < 1){
                ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 2){
                ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 3){
                ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            return true;
        }
    }
    else if(obj == ui->score_star4) {
        if(event->type() == QEvent::HoverEnter) {
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            return true;
        }
        else if(event->type() == QEvent::HoverLeave){
            if(Score_star->checkedId() < 1){
                ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 2){
                ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 3){
                ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 4){
                ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            return true;
        }}

        //------------------------------------------------------//
        else if(obj == ui->waiting_star1) {
            if(event->type() == QEvent::HoverEnter) {
                ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                return true;
            }
            else if(event->type() == QEvent::HoverLeave){
                if(Waiting_star->checkedId() < 1){
                    ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                return true;
            }
        }
        else if(obj == ui->waiting_star2) {
            if(event->type() == QEvent::HoverEnter) {
                ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                return true;
            }
            else if(event->type() == QEvent::HoverLeave){
                if(Waiting_star->checkedId() < 1){
                    ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                if(Score_star->checkedId() < 2){
                    ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                return true;
            }
        }
        else if(obj == ui->waiting_star3) {
            if(event->type() == QEvent::HoverEnter) {
                ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                return true;
            }
            else if(event->type() == QEvent::HoverLeave){
                if(Waiting_star->checkedId() < 1){
                    ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                if(Waiting_star->checkedId() < 2){
                    ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                if(Waiting_star->checkedId() < 3){
                    ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                return true;
            }
        }
        else if(obj == ui->waiting_star4) {
            if(event->type() == QEvent::HoverEnter) {
                ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star2.png);}"
                                      );
                return true;
            }
            else if(event->type() == QEvent::HoverLeave){
                if(Waiting_star->checkedId() < 1){
                    ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                if(Waiting_star->checkedId() < 2){
                    ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                if(Waiting_star->checkedId() < 3){
                    ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                if(Waiting_star->checkedId() < 4){
                    ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                           "QRadioButton{image: url(:/1/star0.png);}"
                                          );
                }
                return true;
            }
    }
    else if(obj == ui->waiting_star5) {
        if(event->type() == QEvent::HoverEnter) {
            ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            ui->waiting_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star2.png);}"
                                  );
            return true;
        }
        else if(event->type() == QEvent::HoverLeave){
            if(Waiting_star->checkedId() < 1){
                ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Waiting_star->checkedId() < 2){
                ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }

            if(Waiting_star->checkedId() < 3){
                ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Waiting_star->checkedId() < 4){
                ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(ui->score_star5->isChecked()==false){
                ui->waiting_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }

            return true;
        }
    }
    else if(obj == ui->score_star5) {
        if(event->type() == QEvent::HoverEnter) {
            ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            ui->score_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                   "QRadioButton{image: url(:/1/star1.png);}"
                                  );
            return true;
        }
        else if(event->type() == QEvent::HoverLeave){
            if(Score_star->checkedId() < 1){
                ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 2){
                ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }

            if(Score_star->checkedId() < 3){
                ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(Score_star->checkedId() < 4){
                ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }
            if(ui->score_star5->isChecked()==false){
                ui->score_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                                       "QRadioButton{image: url(:/1/star0.png);}"
                                      );
            }

            return true;
        }
    }
    return QWidget::eventFilter(obj,event);
}


void evaluate_recipe::on_evaluate_recipe_back_clicked()
{
    emit change_main_again_again();

    ui->comboBox->clear();
}

void evaluate_recipe::back()
{
    ui->score_star3->setChecked(true);
    ui->score_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->score_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->score_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->score_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->score_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->waiting_star3->setChecked(true);
    ui->waiting_star1->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->waiting_star2->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->waiting_star3->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->waiting_star4->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );
    ui->waiting_star5->setStyleSheet("QRadioButton::indicator {width: 0px;height: 0px;}"
                           "QRadioButton{image: url(:/1/star0.png);}"
                          );

}

void evaluate_recipe::on_certainty_clicked()
{

  //  QMessageBox::StandardButton result = QMessageBox::question(&evaluate_recipe, "嘉然开始打分啦！","确定此次评分吗？");

    if(QMessageBox::information(this,  "嘉然开始打分啦！",  "确定此次评分吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)==QMessageBox::Yes)
    {
        int score = Score_star->checkedId();
        int waiting_time = Waiting_star->checkedId();
        QString path1 = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/data.csv"));
        QByteArray temp1 = path1.toLatin1();
        char *Path1 = temp1.data();
        QString temp = ui->comboBox->currentText();
        int number = temp.indexOf(" ");
        temp=temp.left(number);
        int id = temp.toInt();

        project_Feedback(Path1, id, score, waiting_time );

        back();

        QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/should be reviewed.csv"));
        QFile recordmenu(path);
        if(!recordmenu.open(QIODevice::ReadOnly))
        {
            qDebug()<<"请正确选择csv文件";
            exit(0);
        }
        QTextCodec *codec = QTextCodec::codecForName("UTF8");
        QString content = codec->toUnicode(recordmenu.readAll());
        QStringList rowmenu =content.split("\r",QString::SkipEmptyParts);
        recordmenu.close();
        QString current=ui->comboBox->currentText();
        current=current.right(20);
        current=current.left(19);
        int index = ui->comboBox->currentIndex();
        ui->comboBox->removeItem(index);
        for(int i=0;i<rowmenu.count();i++){
            QString temp = rowmenu.at(i);
            if(QString::compare(temp.left(19),current)==0){
                rowmenu.removeAt(i);
                i--;
                break;
            }
        }


        QFile outsertfile(path);
        if(!outsertfile.open(QIODevice::WriteOnly))
        {
            qDebug()<<"请正确选择csv文件";
            exit(0);
        }
        for(int i=0;i<rowmenu.count();i++){outsertfile.write(rowmenu.at(i).toStdString().c_str());}

        outsertfile.close();
    }


}

void evaluate_recipe::on_clear_clicked()
{
    if(QMessageBox::information(this,  "嘉然不想打分啦！",  "确定清除需评分菜品名单吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)==QMessageBox::Yes)
    {
        ui->comboBox->clear();
        QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/should be reviewed.csv"));
        QFile recordmenu(path);
        if(!recordmenu.open(QIODevice::WriteOnly))
        {
            qDebug()<<"请正确选择csv文件";
            exit(0);
        }
        recordmenu.close();
    }

}

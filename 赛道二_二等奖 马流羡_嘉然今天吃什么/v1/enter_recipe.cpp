#include "enter_recipe.h"
#include "ui_enter_recipe.h"
#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <cstring>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QTime>
#include <QTextCodec>

enter_recipe::enter_recipe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enter_recipe)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("#enter_recipe{ border-image: url(:/1/background.png)}");

    ui->enter_recipe_back->setFixedSize(130,130);
    ui->enter_recipe_back->setStyleSheet("QPushButton{border-image:url(:/1/PB1.png);}"
                           "QPushButton:hover{border-image:url(:/1/4.png);}"
                           "QPushButton:pressed{border-image:url(:/1/4.png);}"
                           );

    QStringList location;
    location<<"南食堂"<<"北食堂"<<"东食堂"<<"清真食堂";
    ui->input_location->addItems(location);
    QStringList location2;
    location2<<"一楼"<<"二楼"<<"三楼";
    ui->input_location2->addItems(location2);
    QStringList kind;
    kind<<"早餐"<<"米饭"<<"面"<<"快餐"<<"带馅儿的"<<"其他";
    ui->input_kind->addItems(kind);
    QStringList time;
    time<<"早餐"<<"中餐/晚餐"<<"夜宵";
    ui->input_time->addItems(time);
}

enter_recipe::~enter_recipe()
{
    delete ui;
}

void enter_recipe::on_ok_clicked()
{
    QString name;
    name = ui->input_name->toPlainText()+",";
    QString location;
    int loca1_num = ui->input_location->currentIndex();
    int loca2_num = ui->input_location2->currentIndex();
    switch (loca1_num) {
    case 0:
        location="A";
        break;
    case 1:
        location="B";
        break;
    case 2:
        location="D";
        break;
    case 3:
        location="C";
        break;
    }
    QString temp = QString::number(loca2_num+1,10);
    location = location+temp+",";
    int spicy_num = ui->input_spicy->value();
    QString spicy = QString::number(spicy_num,10)+",";
    int sweet_num = ui->input_sweet->value();
    QString sweet = QString::number(sweet_num,10)+",";
    int price_num = ui->input_price->value();
    QString price = QString::number(price_num,10)+",";
    int kind_num = ui->input_kind->currentIndex();
    QString kind = QString::number(kind_num+1,10)+",";
    int time_num = ui->input_time->currentIndex();
    QString time = QString::number(time_num+1,10)+",";
    int score_num = ui->input_score->value();
    QString score = QString::number(score_num,10)+",";
    int waiting_num = ui->input_waiting->value();
    QString waiting = QString::number(waiting_num,10)+",";

    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/data.csv"));
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"请正确选择csv文件";
        exit(0);
    }
    QTextStream * read = new QTextStream(&file);
    QStringList Data = read->readAll().split("\r",QString::SkipEmptyParts);

    QString id = Data.at(0);
    QStringList infom = id.split(",",QString::SkipEmptyParts);
    id = infom.at(0);
    int id_num = id.toInt();
    id=QString::number(id_num+1,10);
    file.close();

    QString text = id+","+name+time+location+"0,"+price+sweet+spicy+kind+waiting+score+"0,0\r";

    if(QString::compare(",",name)==0){
        QMessageBox::critical(this,"警告","您还没有输入菜名哦！");
    }
    else
    {
        if(QMessageBox::information(this,"嘉然有了新发现！","确定录入菜谱吗？",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)==QMessageBox::Yes)
        {
            QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

            QTextCodec::setCodecForLocale(utf8);

            QTextCodec* gbk = QTextCodec::codecForName("gbk");

            //1. utf8 -> unicode
            QString strUnicode= utf8->toUnicode(text.toLocal8Bit().data());
            //2. unicode -> gbk, 得到QByteArray
            QByteArray gb_bytes= gbk->fromUnicode(strUnicode);

            QFile outsertfile(path);
            if(!outsertfile.open(QIODevice::Append))
            {
                qDebug()<<"请正确选择csv文件";
                exit(0);
            }
            outsertfile.write(gb_bytes.toStdString().c_str());
            outsertfile.close();

            QFile changefile(path);
            if(!changefile.open(QIODevice::ReadWrite))
            {
                qDebug()<<"请正确选择csv文件";
                exit(0);
            }
            id=id+",,,,,,,,,,,"+"\n";
            changefile.write(id.toStdString().c_str());
            QMessageBox::information(this,"嘉然有了新发现！","录入成功！",QMessageBox::Yes);
            ui->input_name->clear();
        }
    }
}

void enter_recipe::on_enter_recipe_back_clicked()
{
    emit change_main_again();
}

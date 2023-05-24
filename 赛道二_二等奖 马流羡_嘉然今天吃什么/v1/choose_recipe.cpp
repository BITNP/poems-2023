#include "choose_recipe.h"
#include "fu.h"
#include "ui_choose_recipe.h"
#include "rand.h"

#include <QDebug>
#include <cstring>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTime>
#include <QDir>

choose_recipe::choose_recipe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::choose_recipe)
{
    ui->setupUi(this);
    ui->listWidget->hide();
    ui->again->hide();
    ui->confirmation->hide();
    //辣度按钮
    ui->spicy_box->setEnabled(false);
    connect(ui->spicy_chioce, &QRadioButton::toggled, [=](bool isChecked){
        if (isChecked == true)
            ui->spicy_box->setEnabled(true);
        else if (isChecked == false)
            ui->spicy_box->setEnabled(false);
    });

    //甜度按钮
    ui->sweet_box->setEnabled(false);
    connect(ui->sweet_choice, &QRadioButton::toggled, [=](bool isChecked){
        if(isChecked == true)
            ui->sweet_box->setEnabled(true);
        else if(isChecked ==false)
            ui->sweet_box->setEnabled((false));
    });

    //价格按钮
    ui->maxprice_box->setEnabled(false);
    connect(ui->maxprice_choice, &QRadioButton::toggled,[=](bool ischecked){
        if(ischecked == true)
            ui->maxprice_box->setEnabled(true);
        else if(ischecked ==false)
            ui->maxprice_box->setEnabled(false);
    });

    ui->minprice_box->setEnabled(false);
    connect(ui->minprice_choice, &QRadioButton::toggled,[=](bool ischecked){
        if(ischecked == true)
            ui->minprice_box->setEnabled(true);
        else if(ischecked ==false)
            ui->minprice_box->setEnabled(false);
    });

    //回到主页
    ui->choose_recipe_back->setFixedSize(130,130);
    ui->choose_recipe_back->setStyleSheet("QPushButton{border-image:url(:/1/PB1.png);}"
                           "QPushButton:hover{border-image:url(:/1/4.png);}"
                           "QPushButton:pressed{border-image:url(:/1/4.png);}"
                           );
    ui->listWidget->setFrameShape(QListWidget::NoFrame);


}

choose_recipe::~choose_recipe()
{
    delete ui;
}

void choose_recipe::on_choose_recipe_back_clicked()
{
    emit change_main();

    //初始化整个窗口
    ui->listWidget->hide();
    ui->again->hide();
    ui->again->setStyleSheet("color: rgb(255, 85, 255);font: 12pt '华文彩云'");
    ui->again->setDisabled(false);

    ui->confirmation->hide();
    ui->confirmation->setStyleSheet("color: rgb(255, 85, 255);font: 12pt '华文彩云'");
    ui->confirmation->setGeometry(440,720,161,41);
    ui->confirmation->setText("就吃它了！");

    ui->ok->setStyleSheet("color: rgb(255, 85, 255);font: 12pt '华文彩云'");
    ui->ok->setDisabled(false);

    ui->maxprice_choice->setChecked(false);
    ui->maxprice_box->setValue(25);
    ui->minprice_choice->setChecked(false);
    ui->minprice_box->setValue(5);
    ui->breakfast_choice->setChecked(true);
    ui->spicy_chioce->setChecked(false);
    ui->spicy_box->setValue(1);
    ui->sweet_choice->setChecked(false);
    ui->sweet_box->setValue(1);
    ui->place_choice->setChecked(true);
    ui->kind_choice->setChecked(true);

}

void choose_recipe::on_ok_clicked() //开始选菜
{
    ui->confirmation->setEnabled(true);
    ui->again->show();
    ui->confirmation->show();
    int spicy=0,sweet=0,maxprice=0,minprice=0;
    char argument[8][10];//这里的九个 参数分别为0time 1location 2window 3price 4sweet 5hot 6kind 7waiting
    memset(argument,'0',sizeof(argument));

    if(ui->breakfast_choice->isChecked()){
        argument[0][0]='1';
    }
    else if(ui->lunch_choice->isChecked()||ui->dinner_choice->isChecked()){
        argument[0][0]='2';
    }
    else if(ui->supper_choice->isChecked()){
        argument[0][0]='3';
    }
//
    if(ui->maxprice_choice->isChecked()){
        maxprice=ui->maxprice_box->value();
    }
    else{
        maxprice=1000;
    }
    if(ui->minprice_choice->isChecked()){
        minprice=ui->minprice_box->value();
    }
    else{
        minprice=-1;
    }
//
    if(ui->sweet_choice->isChecked()){
        sweet=ui->sweet_box->value();
        argument[4][0]='0'+sweet;
    }
    if(ui->spicy_chioce->isChecked()){
        spicy=ui->spicy_box->value();
        argument[5][0]='0'+spicy;
    }
//
    if(ui->place_choice->isChecked()){
        argument[1][0]='0';
    }
    else if(ui->south_choice->isChecked()){
        argument[1][0]='A';
    }
    else if(ui->north_choice->isChecked()){
        argument[1][0]='B';
    }
    else if(ui->qingzhen_choice->isChecked()){
        argument[1][0]='C';
    }
    else if(ui->east_choice->isChecked()){
        argument[1][0]='D';
    }

    if(ui->kind_choice->isChecked()){
        argument[6][0]='0';
    }
    else if(ui->rice_choice->isChecked()){
        argument[6][0]='2';
    }
    else if(ui->noodle_choice->isChecked()){
        argument[6][0]='3';
    }
    else if(ui->fastfood_choice->isChecked()){
        argument[6][0]='4';
    }
    else if(ui->dumpling_choice->isChecked()){
        argument[6][0]='5';
    }
    else if(ui->other_choice->isChecked()){
        argument[6][0]='6';
    }


    int menu_number = function1(minprice,maxprice,argument);

    random_start(menu_number);

    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/transfer station.csv"));
    QFile file(path);

    /*如果以ReadWrite方式打开，不会把所有数据清除，若文件原来的长度为100字节，写操作写入了30字节，那还剩余70字节，并且这70字节和文件打开之前保持一致*/
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"请正确选择csv文件";
        exit(0);
    }

    QTextStream * read = new QTextStream(&file);
    QStringList Data = read->readAll().split("\n",QString::SkipEmptyParts);   //每行以\n区分
    QStringList strLine = Data.at(0).split(",");

    file.close();
    QString linehead1 = "菜名：";
    if(QString::compare(strLine.at(0),"0")==0||menu_number==0){
        ui->listWidget->item(1)->setText("呜＞︿＜糟了......");
        ui->listWidget->item(2)->setText("似乎没有符合条件的菜哦");
        ui->listWidget->item(3)->setText("");
        ui->listWidget->item(4)->setText("");
        ui->listWidget->item(5)->setText("");
        ui->listWidget->item(6)->setText("");
        ui->listWidget->item(7)->setText("");
        ui->listWidget->item(8)->setText("");
        ui->listWidget->item(9)->setText("");
        ui->confirmation->setEnabled(false);
    }
    else{
    ui->listWidget->item(1)->setText("就决定是你啦！");
    QString name_of_recipe = linehead1.append(strLine.at(1));
    ui->listWidget->item(2)->setText(name_of_recipe);

    if(QString::compare(strLine.at(2), "1", Qt::CaseInsensitive)==0){
        ui->listWidget->item(3)->setText("时间：早餐");
    }
    else if(QString::compare(strLine.at(2), "2", Qt::CaseInsensitive)==0){
        ui->listWidget->item(3)->setText("时间：午餐/晚餐");
    }
    else if(QString::compare(strLine.at(2), "3", Qt::CaseInsensitive)==0){
        ui->listWidget->item(3)->setText("时间：夜宵");
    }

    QString more_location = "第"+strLine.at(4)+"窗口（从左到右）";
    if(QString::compare(strLine.at(3), "A1", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：南食堂一楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "A2", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：南食堂二楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "A3", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：南食堂三楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "B1", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：北食堂一楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "B2", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：北食堂二楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "B3", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：北食堂三楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "D1", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：东食堂一楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "D2", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：东食堂二楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "D3", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：东食堂三楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "C1", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：清真食堂一楼"+more_location);
    }
    else if(QString::compare(strLine.at(3), "C2", Qt::CaseInsensitive)==0){
        ui->listWidget->item(4)->setText("地点：清真食堂二楼"+more_location);
    }


    QString pricetemp=strLine.at(5).left(1);
    if(QString::compare(pricetemp, "~", Qt::CaseInsensitive)==0)
    {
        QString linehead22 = "价格约为：";
        QString price_of_recipe_temp = strLine.at(5).mid(1);
        QString price_of_recipe = linehead22.append(price_of_recipe_temp);
        price_of_recipe=price_of_recipe.append("元");
        ui->listWidget->item(5)->setText(price_of_recipe);
    }
    else {
        QString linehead2 = "价格：";
        QString price_of_recipe = linehead2.append(strLine.at(5));
        price_of_recipe=price_of_recipe.append("元");
        ui->listWidget->item(5)->setText(price_of_recipe);
    }

    QString linehead3 = "甜度：";
    QString sweet_of_recipe = linehead3.append(strLine.at(6));
    ui->listWidget->item(6)->setText(sweet_of_recipe);

    QString linehead4 = "辣度：";
    QString spicy_of_recipe = linehead4.append(strLine.at(7));
    ui->listWidget->item(7)->setText(spicy_of_recipe);

    if(QString::compare(strLine.at(8), "1", Qt::CaseInsensitive)==0){
        ui->listWidget->item(8)->setText("种类：早餐");
    }
    else if(QString::compare(strLine.at(8), "2", Qt::CaseInsensitive)==0){
        ui->listWidget->item(8)->setText("种类：米饭");
    }
    else if(QString::compare(strLine.at(8), "3", Qt::CaseInsensitive)==0){
        ui->listWidget->item(8)->setText("种类：面类");
    }
    else if(QString::compare(strLine.at(8), "4", Qt::CaseInsensitive)==0){
        ui->listWidget->item(8)->setText("种类：快餐");
    }
    else if(QString::compare(strLine.at(8), "5", Qt::CaseInsensitive)==0){
        ui->listWidget->item(8)->setText("种类：带馅类");
    }
    else if(QString::compare(strLine.at(8), "6", Qt::CaseInsensitive)==0){
        ui->listWidget->item(8)->setText("种类：其他");
    }

    QString linehead5 = "评分：";
    QString score_of_recipe = linehead5.append(strLine.at(10));
    score_of_recipe=score_of_recipe.append("分（满分5分）");
    ui->listWidget->item(9)->setText(score_of_recipe);
    }
    ui->listWidget->show();
    return ;
}




void choose_recipe::on_again_clicked()
{
    ui->listWidget->hide();
    ui->again->hide();
    ui->confirmation->hide();
}

void choose_recipe::on_confirmation_clicked()
{
    ui->confirmation->setStyleSheet("color: rgb(255, 170, 0);font: 12pt '华文彩云'");
    ui->confirmation->setGeometry(370,720,311,41);
    ui->confirmation->setText("嘉然祝您用餐愉快(●'◡'●)");
    ui->again->setStyleSheet("color: rgb(255, 170, 0);font: 12pt '华文彩云'");
    ui->ok->setStyleSheet("color: rgb(255, 170, 0);font: 12pt '华文彩云'");
    ui->again->setDisabled(true);
    ui->ok->setDisabled(true);
    ui->confirmation->setDisabled(true);

    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/transfer station.csv"));

    QFile insertfile(path);
    if(!insertfile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"请正确选择csv文件";
        exit(0);
    }
    QTextStream * read = new QTextStream(&insertfile);
    QStringList chosen_recipe = read->readAll().split("\n",QString::SkipEmptyParts);
    insertfile.close();


    chosen_recipe.append("\n");
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString eating_time = dateTime .toString("yyyy-MM-dd hh:mm:ss");

    QString path1 = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/should be reviewed.csv"));
    QFile outsertfile(path1);
    if(!outsertfile.open(QIODevice::Append))
    {
        qDebug()<<"请正确选择csv文件";
        exit(0);
    }
    eating_time = eating_time.append(",");
    outsertfile.write(eating_time.toStdString().c_str());
    outsertfile.write(chosen_recipe[0].toStdString().c_str());/*写入每一行数据到文件*/
    outsertfile.close();
}


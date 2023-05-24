#include"fu.h"
#include<iostream>
#include<math.h>
#include<string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <QString>
#include <QApplication>
#include <QDir>

void menu::input(FILE *file)
{
    memset(information,0,sizeof(information));
    for(int j=0;j<13;j++){
        fscanf(file,"%[^,\n]",information[j]);  // 读到逗号或\n为止
        //cout<<information[j]<<",";
        fgetc(file); // 读取一个字符(逗号或\n)
    }
}
bool menu::check()
{
    for(int j=0;j<8;++j){
        //cout<<a[j][0]<<endl;
        if(a[j][0]!='0'){
            if(j==3){//这个位置是价格，一会单独处理，这里直接跳过
                continue ;
            }
            if(information[j+2][0]!=a[j][0]){
                //cout<<"test";		//因为要求最长的也只有两个字符，所以直接字符比较了
                return false;
            }
        }
    }
    return true;
}
bool menu::checkprice()
{
    int r=0;
    int t=0;
    double y=1;
    double price=0;
    if(information[5][r]=='~'){//价格会有约//等于的字符，直接丢掉
        ++r;
    }
    while(information[5][r]!='\0'){
        if(information[5][r]=='.'){
            t=1;
            ++r;
            continue;
        }
        if(t==1){
            y/=10;
            price+=(information[5][r]-'0')*y;
        }else{
            price*=10;
            price+=information[5][r]-'0';
        }
        ++r;//把价格算出来
    }
    if(price<Min||price>Max){
        return false;
    }
    return true;
}
int menu::output(ofstream& outFile){
    //cout<<information[0]<<endl;
    if(checkprice()&&check()){
        for(int k=0;k<13;++k){
            outFile <<information[k]<<',';
        }
        outFile <<endl;
        return 1;
    }
    return 0;
}
int function1(int min,int max,char charactorss[][10]){
    int number=0;
    menu::Seta(charactorss);
    menu::SetMax(max);
    menu::SetMin(min);
    FILE *file;
    int N=10;
    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/data.csv"));
    QByteArray temp = path.toLatin1();
    char* Path = temp.data();
    if ((file = fopen(Path, "r")) == NULL){
        printf("Can't open the file!\n");
        exit(0);
    }
    fscanf(file,"%d",&N);
    fgetc(file);
    menu *p=new menu[N];
    char test[1000];
    memset(test,0,sizeof(test));
    fscanf(file, "%[^\n]%*c", test);
    for(int i=0;i<N;i++){
        p[i].input(file);
    }
    ofstream outFile;
    QString path1 = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/transfer station.csv"));
    QByteArray temp1 = path1.toLatin1();
    char *Path1 = temp1.data();
    outFile.open(Path1, ios::out); // 打开模式可省略
    for(int i=0;i<N;++i){
        number+=p[i].output(outFile);
    }
    delete[] p;
    return number;
}

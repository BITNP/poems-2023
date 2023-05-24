#include "start.h"
#include <QApplication>
#include "fu.h"
#include <QTextCodec>
#include <QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
    w.setFixedSize(1600,900);
    w.show();
    return a.exec();
}
int menu :: Max=0;
int menu :: Min=0;
char menu :: a[8][10]={"666"};

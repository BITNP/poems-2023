#ifndef FU_H
#define FU_H
#include<iostream>
#include<math.h>
#include<string.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class menu
{
    private:
        char information[16][40] ;//姣忎釜鑿滃搧鐨勫悇绉嶅弬鏁?
        static int Max;//鍥犱负鍏朵粬鏁版嵁鍙渶瑕佹瘮杈冨瓧绗︿覆灏辫锛岃€屼环鏍艰缃殑鏄尯闂达紝鎵€浠ュ緱鍗曠嫭鎷垮嚭鏉ュ鐞?
        static int Min;//max鍜宮in鏄鑿滃搧鐨勪环鏍艰姹傚尯闂?
        static char a[8][10]; //a閲屽瓨鐨勬槸瀵硅彍鍝佺殑瑕佹眰 鍏朵腑闆朵负娌℃湁瑕佹眰
    public:

        static int GetMax(){return Max;}
        static void Seta(char charactorss[9][10]){
            for(int i=0;i<8;++i){
                for(int j=0;j<10;++j){
                    a[i][j]=charactorss[i][j];
                }
            }
        }
        static void SetMax(int max){Max=max;}
        static int GetMin(){return Min;}
        static void SetMin(int min){Min=min;}
        void input(FILE *);//璇诲叆
        bool check();//妫€鏌ラ櫎浜嗕环鏍煎鏄惁绗﹀悎瑕佹眰.
        bool checkprice();//妫€鏌ヤ环鏍?
        int output(ofstream& );//杈撳嚭

};
int function1(int ,int ,char [8][10]);

#endif

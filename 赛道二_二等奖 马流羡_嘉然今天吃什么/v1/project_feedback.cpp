#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "project_feedback.h"
#include <QApplication>
#include <QDir>
#include <QString>

using namespace std;

void project_Copy();

void project_Feedback( char *File_Name, int ID, int Score, int Waiting_Time )
{
    class Food_Class
    {
        public:
            string Name, Location, Price;
            int ID, Time, Window, Sweet, Hot, Kind, Waiting_Time, Score, Line, History, Token;
    };

    Food_Class Temp;
    ifstream File;
    ofstream File_t;
    string Line;
    File.open( File_Name, ios::in );
    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/temp.csv"));
    QByteArray temp = path.toLatin1();
    char *Path = temp.data();
    File_t.open(Path, ios::out );
    if( !File.is_open() )
    {
        cout << "ERROR" << endl;
        return;
    }
    istringstream Sin;
    getline( File, Line );
    File_t << Line << endl;
    getline( File, Line );
    File_t << Line << endl;
    int t=1, n=0;
    while( getline( File, Line ) )
    {
        string Word;
        Sin.clear();
        Sin.str( Line );
        getline( Sin, Word, ',' );
        Temp.ID = atoi( Word.c_str() );
        if( Temp.ID == ID )
        {
            File_t << Temp.ID << ',';
            getline( Sin, Word, ',' );
            //Temp.Name = Word;
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Time = atoi( Word.c_str() );
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Location = Word;
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Window = atoi( Word.c_str() );
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Price = Word;
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Sweet = atoi( Word.c_str() );
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Hot = atoi( Word.c_str() );
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Kind = atoi( Word.c_str() );
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Waiting_Time = atoi( Word.c_str() );
            File_t << Waiting_Time << ',';
            getline( Sin, Word, ',' );
            //Temp.Score = atoi( Word.c_str() );
            File_t << Score << ',';
            getline( Sin, Word, ',' );
            //Temp.History = atoi( Word.c_str() );
            File_t << Word << ',';
            getline( Sin, Word, ',' );
            //Temp.Token = atoi( Word.c_str() );
            File_t << Word << endl;
            //Temp.Line = t++;
        }
        else File_t << Line << endl;
    }
    File.close();
    File_t.close();
    project_Copy();
}

void project_Copy()
{
    ifstream File_t;
    ofstream File;
    string Line, Word;
    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/temp.csv"));
    QString path2 = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/data.csv"));
    QByteArray temp1 = path.toLatin1();
    QByteArray temp2 = path2.toLatin1();
    char *Path= temp1.data();
    char *Path2 = temp2.data();
    File_t.open(Path, ios::in );
    File.open( Path2, ios::out );
    if( !File_t.is_open() || !File.is_open() )
    {
        cout << "ERROR" << endl;
        return;
    }
    istringstream Sin;
    getline( File_t, Line );
    Sin.str( Line );
    for(int cent=0; getline( Sin, Word, ',' );cent++ ){
        if(cent==0){File << Word;}
        else{
            File << "," << Word;
        }
    }
    File << endl;
    while( getline( File_t, Line ) )
    {
        Sin.clear();
        Sin.str( Line );
        for(int cent=0; getline( Sin, Word, ',' );cent++ ){
            if(cent==0){File << Word;}
            else{
                File << "," << Word;
            }
        }
        File << endl;
    }
    return;
}

void project_Remove()
{
    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/temp.csv"));
    QByteArray temp = path.toLatin1();
    char * Path = temp.data();
    remove( Path);
}

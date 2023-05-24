#include "rand.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
#include <QString>
#include <QDir>
#include <QApplication>


const int csvColumnAmount = 13;
const int csvIDColumnNo = 0;
const int csvNameColumnNo = 1;
const int csvTimeColumnNo = 2;
const int csvLocationColumnNo = 3;
const int csvWindowColumnNo = 4;
const int csvPriceColumnNo = 5;
const int csvSweetColumnNo = 6;
const int csvHotColumnNo = 7;
const int csvKindColumnNo = 8;
const int csvWaiting_TimeColumnNo = 9;
const int csvScoreColumnNo = 10;//imp
const int csvHistoryColumnNo = 11;
const int csvTokenColumnNo = 12;
const int magicRandomNumber = 113;
const int magicBaseNumber = 10;
const string csvHead = "ID,Name,Time,Location,Window,Price,Sweet,Hot,Kind,Waiting_Time,Score,History,Token";

struct dish {
    string Name, Location, Price, Token;
    int ID, Time, Window, Sweet, Hot, Kind, Waiting_Time, weight, History, Score;
};
dish selectedDish[1000], randomDishResult[1000];


void random_start(int selectedDishNumber) {
    char *outputFileName;
    char *inputFileName;
    int  expectRandomResultNumber;
    srand((unsigned)time(NULL));
    QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/transfer station.csv"));
    QByteArray temp = path.toLatin1();
    outputFileName = temp.data();
    inputFileName = temp.data();
    expectRandomResultNumber = 1;
    if (readSelectedDishResult(inputFileName, selectedDishNumber) != 1)
        cout << "Runtime error, error code:114514" << endl;
    randomSelectDishFunction(selectedDishNumber, expectRandomResultNumber);
    if (outputRandomResult(outputFileName, expectRandomResultNumber) != 1)
        cout << "Runtime error, error code:1919810" << endl;
    return ;
}

int outputRandomResult(char *outputFileName, int outputDishNumber) {
    ofstream outFile(outputFileName);
    if (outputDishNumber == 0) {
        for (int i = 0; i < csvColumnAmount; i++) {
            outFile << 0 << ",";
        }
        outFile << endl;
        return 1;
    }
    for (int i = 0; i < outputDishNumber; i++) {
        for (int j = 0; j < csvColumnAmount; j++) {
            if (j == csvIDColumnNo) {
                outFile << randomDishResult[i].ID;
            }
            if (j == csvNameColumnNo) {
                outFile << randomDishResult[i].Name;
            }
            if (j == csvTimeColumnNo) {
                outFile << randomDishResult[i].Time;
            }
            if (j == csvLocationColumnNo) {
                outFile << randomDishResult[i].Location;
            }
            if (j == csvWindowColumnNo) {
                outFile << randomDishResult[i].Window;
            }
            if (j == csvPriceColumnNo) {
                outFile << randomDishResult[i].Price;
            }
            if (j == csvSweetColumnNo) {
                outFile << randomDishResult[i].Sweet;
            }
            if (j == csvHotColumnNo) {
                outFile << randomDishResult[i].Hot;
            }
            if (j == csvKindColumnNo) {
                outFile << randomDishResult[i].Kind;
            }
            if (j == csvWaiting_TimeColumnNo) {
                outFile << randomDishResult[i].Waiting_Time;
            }
            if (j == csvScoreColumnNo) {
                outFile << randomDishResult[i].Score;
            }
            if (j == csvHistoryColumnNo) {
                outFile << randomDishResult[i].History;
            }
            if (j == csvTokenColumnNo) {
                outFile << randomDishResult[i].Token;
            }
            outFile << ",";
        }
        outFile << endl;
    }
    outFile.close();
    return 1;
}

int readSelectedDishResult(char *inputFileName, int selectedDishNumber) {
    string temp;
    ifstream inputFile(inputFileName);
    getline(inputFile, temp);
    for (int i = 0; i < selectedDishNumber; i++) {
        for (int j = 0; j < csvColumnAmount; j++) {
            getline(inputFile, temp, ',');
            if (j == csvIDColumnNo) {
                selectedDish[i].ID = atoi(temp.c_str());
            }
            if (j == csvTimeColumnNo) {
                selectedDish[i].Time = atoi(temp.c_str());
            }
            if (j == csvWindowColumnNo) {
                selectedDish[i].Window = atoi(temp.c_str());
            }
            if (j == csvSweetColumnNo) {
                selectedDish[i].Sweet = atoi(temp.c_str());
            }
            if (j == csvHotColumnNo) {
                selectedDish[i].Hot = atoi(temp.c_str());
            }
            if (j == csvKindColumnNo) {
                selectedDish[i].Kind = atoi(temp.c_str());
            }
            if (j == csvWaiting_TimeColumnNo) {
                selectedDish[i].Waiting_Time = atoi(temp.c_str());
            }
            if (j == csvScoreColumnNo) {
                selectedDish[i].Score = atoi(temp.c_str());
                selectedDish[i].weight = atoi(temp.c_str());
            }
            if (j == csvHistoryColumnNo) {
                selectedDish[i].History = atoi(temp.c_str());
            }
            if (j == csvNameColumnNo) {
                selectedDish[i].Name = temp.c_str();
            }
            if (j == csvLocationColumnNo) {
                selectedDish[i].Location = temp.c_str();
            }
            if (j == csvPriceColumnNo) {
                selectedDish[i].Price = temp.c_str();
            }
            if (j == csvTokenColumnNo) {
                selectedDish[i].Token = temp.c_str();
            }
        }
    }
    inputFile.close();
    return 1;
}

int randomSelectDishFunction(int selectedDishNumber, int expectRandomResultNumber) {
    int temporaryRandomNumber;
    for (int i = 0; i < selectedDishNumber; i++) {
        temporaryRandomNumber = rand() % magicRandomNumber + magicBaseNumber;
        selectedDish[i].weight *= temporaryRandomNumber;
    }
    quickSort(0, selectedDishNumber);
    for (int i = 0; i < expectRandomResultNumber; i++) {
        randomDishResult[i] = selectedDish[i];
    }
    return 1;
}

void quickSort(int l, int r) {
    int i = l, j = r, flag = selectedDish[(l + r) / 2].weight;
    dish temp;
    do {
        while (selectedDish[i].weight > flag)
            i++;
        while (selectedDish[j].weight < flag)
            j--;
        if (i <= j) {
            temp = selectedDish[i];
            selectedDish[i] = selectedDish[j];
            selectedDish[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j)
        quickSort(l, j);
    if (i < r)
        quickSort(i, r);
    return;
}

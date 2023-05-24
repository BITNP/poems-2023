#ifndef RAND_H
#define RAND_H
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>

using namespace std;

int outputRandomResult(char *outputFileName, int outputDishNumber);
int readSelectedDishResult(char *inputFileName, int selectedDishNumber);
int randomSelectDishFunction(int selectedDishNumber, int expectRandomResultNumber);
void quickSort(int l, int r);
void random_start(int );


#endif // RAND_H

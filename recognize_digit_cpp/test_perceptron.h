
#pragma once
//#include "stdafx.h"
//количество элементов в столбце
//#define column 5
//количество элементов в ряду
//#define row 3
//Количество данных для обучения
#define numberDataTraining 1000000
#define bias 7;

using namespace std;

class Recog
{
    //входной параметр
    bool number[5][3];
    //весы входных параметров
    //int weight[column][row];
    int ** weight = new int *[5];
public:
    Recog();
    ~Recog();
    //Функция активации
    bool proceed();
    //Функция распознавания
    bool recognize(int **inp, int **loadweghts, int &rows, int &colums);
    //установка входного параметра
    void setNumber(const bool number[5][3]);
    void setNumber(int& number);
    //Увеличение весов
    void increase();
    //Уменьшение весов
    void decrease();
    //Получение весов
    int **getWeights();
    //static void setNumber(const bool number[column][row]);
    //static void setNumber(int number);
    static void learn(QImage &input_image, QString &FileName);
    static bool proceed(vector<int> inp_vec);
    static void increase(vector<int> inp_vec);
    static void decrease(vector<int> inp_vec);
    static void setweights(vector<int> &inp_weight);
    static vector<int> GetWeigts();
};



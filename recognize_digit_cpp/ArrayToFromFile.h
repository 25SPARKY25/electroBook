
#pragma once
//#include <iostream>
//#include <fstream>
//#include <istream>
//#include "ImageToArray.h"
//#include <vector>
//#include <string>

#include "neuron.h"
#include "net.h"

class ArrayToFromFile
{
public:
	//запись массива в файл
	static void VecToFile(std::vector<std::vector<int>> blackwhitevec, int x, int y);
	static void SingleVecToFile(std::vector<int> weights);
	static void SingleVecToFileTest(std::vector<int> weights);//тестовый///для просмотра матрицы изображения

	void ArrayToFile(int ** arr, int column, int row, std::string name);


	//запись массива среднего значения на пиксель в файл
	static void Avg_VecToFile(std::vector<std::vector<int>> Sum_Avg_Vec);
	//чтение из файла
	static std::vector<std::vector<int>> FileToVec(std::ifstream &f);
	static std::vector<std::vector<int>> Avg_FileToVec(std::ifstream &ff);
    static int ** FileToArray(std::ifstream &f);
    //для диплома магистратуры
    static void WriteWeights(int** arr, QImage &img, char const *name);

    static void SaveNueralNetwork(std::vector<std::vector<neuron>> &inp_net);
    static std::vector<std::vector<neuron>> LoadNetwork();
//    static void WriteWeights(std::vector<std::vector<double>> &inp_vec, char const *name);
    int **LoadWeights(std::ifstream& in);
    std::size_t &GetRows();
    std::size_t &GetColumns();
    ArrayToFromFile();
    ~ArrayToFromFile();
private:
    std::size_t rows, columns;
    int** load_weights;
    /////////////////////////////////////////////////////////////////////







};



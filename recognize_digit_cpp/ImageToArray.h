
#pragma once
//#include <QPixmap>
//#include <vector>
#include "ArrayToFromFile.h"
using namespace std;
////vector<std::vector<double>> AVG_Color;



class ImageToArray
{
public:

//	//static vector<int> SingleOutputBlackWhiteVec;
//	//через вектор
//    static vector<std::vector<int>> ImgToVec(const QImage &img);//переводим картинку в двумерный вектор
//	//среднеарифметических значений 3 каналов на пиксель
//    static vector<std::vector<int>> InpVecBin(QBitmap *img);//получаем вектор 0 и 1 входного изображения
//    static vector<std::vector<int>> BWImageToVector(QBitmap &img);//из ЧБ картинки и получаём её массив
//    static vector<int> SingleBinVectro(QBitmap &img); //получаем одномерный вектор 0 и 1
//	//получение чб картнки из вектора загруженного из файла
//	//static std::vector<int> BWImage(Bitmap ^img, std::vector<int> single_inputvec); //получаем одномерный vector пиксилей
//	//нужно хорошенько обдумать как загружать и хранить массив средних значений на пиксель
//	//static vector<std::vector<int>> Sum_AVG_Color(Bitmap ^img);//получаем двумерный вектор суммы средних цветов на пиксель
//	static vector<std::vector<int>> AVG_Color(vector<std::vector<int>> Sum_AVG_Color, int counter);//получаем финальный двумерный вектор суммы средних цветов на пиксель

//	//через массивы
//    static int** ImgToArr(QBitmap &img, int** InputColorArr);//переводим картинку в массив
//    static QBitmap BWImage(QBitmap &img); //переводим картинку в ЧБ
    static int** BWImageToArray( QImage &img);//из ЧБ картинки и получаём её массив
    static std::vector<double> BWImageToVector(const QImage &img);//из ЧБ картинки и получаём её в вектор
    static void getBoldImage(QImage &img);

    ImageToArray();
    ~ImageToArray();
//private:
//	int** InputColorArr;		//массив 0 и 1 исходного изображения
//	int** OutputBlackWhiteArr;	//массив 0 и 1 ЧБ изображения
};



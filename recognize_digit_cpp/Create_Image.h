#pragma once
//#include <iostream>
//#include <fstream>
//#include <istream>
//#include <vector>
//#include <string>
//#include "stdafx.h"
using namespace std;


class Create_Image
{
private:
    QImage *imgperc;
public:
	//создать картинку
//	static Bitmap^ Cr_image();//метод отвечающий за генерацию картинки
//	static void void_Cr_image(String^ path, int x);//void-метод отвечающий за генерацию картинки
    const QImage& GetImage();//возврат картинки

    static void getBoldImage(QImage &img);

    static void ImageFromArrayTest(int **arr, size_t &rows, size_t &columns); //тестовый метод дл проверки правильности преобразования картиник в массив
    Create_Image(int **load_arr, int **digit_arr, size_t &rows, size_t &colums);
	~Create_Image();
};


#include "stdafx.h"
#include "ImageToArray.h"


//static vector<int> SingleOutputBlackWhiteVec;

////через вектора
//vector<std::vector<int>> ImageToArray::ImgToVec(const QImage &img)
//{
//    vector<std::vector<int>> inputvec(img.width(), vector <int>(img.height()));
//    for (int x = 0; x < img.width(); x++)
//    {
//        for (int y = 0; y < img.height(); y++)
//        {
//            inputvec[x][y] = (Convert::ToInt16(Color(img.GetPixel(x, y)).R) + Convert::ToInt16(Color(img->GetPixel(x, y)).G) + Convert::ToInt16(Color(img->GetPixel(x, y)).B))/3 ;
//        }
//    }
//    return inputvec;
//}

//vector<std::vector<int>> ImageToArray::InpVecBin(Bitmap ^ img)
//{
//    vector<std::vector<int>> inputvec(img->Width, vector <int>(img->Height));
//    inputvec = ImageToArray::ImgToVec(img);
//    for (int x = 0; x < img->Width; x++)
//    {
//        for (int y = 0; y < img->Height; y++)
//        {
//            inputvec[x][y] = inputvec[x][y] >= 130 ? 0 : 1;
//        }
//    }
//    return inputvec;
//}

//vector<std::vector<int>> ImageToArray::BWImageToVector(Bitmap ^ img)
//{
//    Bitmap ^img1 = ImageToArray::BWImage(img);//получаем картинку из метода, который превращает её в ЧБ
//    vector<std::vector<int>> OutputBlackWhiteVec= ImageToArray::ImgToVec(img1);
//    for (int x = 0; x < img1->Width; x++)
//    {
//        for (int y = 0; y < img1->Height; y++)
//        {
//            OutputBlackWhiteVec[x][y] = OutputBlackWhiteVec[x][y] >= 130 ? 0 : 1;
//        }
//    }
//    return OutputBlackWhiteVec;
//}

//vector<int> ImageToArray::SingleBinVectro(Bitmap ^ img)
//{
//    //Bitmap ^img = img;
//    vector<std::vector<int>> OutputBlackWhiteVec = ImageToArray::ImgToVec(img);
//    SingleOutputBlackWhiteVec.clear();
//    for (int x = 0; x < img->Width; x++)
//    {
//        for (int y = 0; y < img->Height; y++)
//        {
//            //img->GetPixel(x, y) == Color::White ? SingleOutputBlackWhiteVec.push_back(0) : SingleOutputBlackWhiteVec.push_back(1);
//            OutputBlackWhiteVec[x][y] >= 130 ? SingleOutputBlackWhiteVec.push_back(0) : SingleOutputBlackWhiteVec.push_back(1);
//            //img->GetPixel(x,y) == Color::White ? SingleOutputBlackWhiteVec.push_back(0) : SingleOutputBlackWhiteVec.push_back(1);
//            /*String^ str = Convert::ToString(img->GetPixel(x, y));*/
//        }
//    }
//    return SingleOutputBlackWhiteVec;
	
//}

////std::vector<int> ImageToArray::BWImage(Bitmap ^img, std::vector<int> single_inputvec)
////{
////	//int i = 0;
////	for (int x = 0; x < img->Width; x++)
////	{
////		for (int y = 0; y < img->Height; y++)
////		{
////			single_inputvec.push_back(Convert::ToInt16(Color(img->GetPixel(x, y)).R) >= 130 && Convert::ToInt16(Color(img->GetPixel(x, y)).G) >= 130 && Convert::ToInt16(Color(img->GetPixel(x, y)).B) >= 130 ? 0 : 1);
////			//i++;
////		}
////	}
////	return single_inputvec;
////}


////vector<std::vector<int>> ImageToArray::Sum_AVG_Color(Bitmap ^img)
////{
////	vector<std::vector<int>> Sum_AVG_Color(img->Width, vector <int>(img->Height));
////	vector<std::vector<int>> templ= ImageToArray::ImgToVec(img);
////	for (int x = 0; x < Sum_AVG_Color.size(); x++)
////	{
////		for (int y = 0; y <Sum_AVG_Color[0].size(); y++)
////		{
////			Sum_AVG_Color[x][y] += templ[x][y];
////			//i++;
////		}
////	}
////	return Sum_AVG_Color;
////}

//vector<std::vector<int>> ImageToArray::AVG_Color(vector<std::vector<int>> Sum_AVG_Color, int counter)
//{
//    //vector<std::vector<int>> AVG_Color= ImageToArray::Sum_AVG_Color(img);
//    for (int x = 0; x < Sum_AVG_Color.size(); x++)
//    {
//        for (int y = 0; y < Sum_AVG_Color[0].size(); y++)
//        {
//            Sum_AVG_Color[x][y] = (Sum_AVG_Color[x][y])/counter;
//            //i++;
//        }
//    }
//    return Sum_AVG_Color;
//}

//int ** ImageToArray::ImgToArr(Bitmap ^ img, int ** InputColorArr)
// {
//     //массив пикселей
//    /* int **InputColorArr = new int *[img->Width];
//     for (int i = 0; i < img->Width; ++i)
//     {
//         InputColorArr[i] = new int[img->Height];
//     }*/
//     //разбиение изображения на RGB-канал и заполнение датагрида
//     for (int x = 0; x < img->Width; x++)
//     {
//         for (int y = 0; y < img->Height; y++)
//         {
//             InputColorArr[x][y] = Convert::ToInt16(Color(img->GetPixel(x, y)).R) >= 130 && Convert::ToInt16(Color(img->GetPixel(x, y)).G) >= 130 && Convert::ToInt16(Color(img->GetPixel(x, y)).B) >= 130 ? 0 : 1;
//         }
//     }
//     return InputColorArr;
// }

// Bitmap^ ImageToArray::BWImage(Bitmap ^ img)
// {
//    Bitmap ^image=gcnew Bitmap(img);
//    int averageValueColor = 0;	//среднее арифметическое значения RGB для каждого пикселя
//     for (int x = 0; x < img->Width; x++)
//     {
//         for (int y = 0; y < img->Height; y++)
//         {
//             //узнаём средне рифметическое
//             averageValueColor = (Convert::ToInt16(Color(img->GetPixel(x, y)).R) + Convert::ToInt16(Color(img->GetPixel(x, y)).G) + Convert::ToInt16(Color(img->GetPixel(x, y)).B))/3;
//             //делаем картинку ЧБ
//             image->SetPixel(x, y, Color::FromArgb(averageValueColor, averageValueColor, averageValueColor));
//         }
//     }
//     return image;
// }

 int ** ImageToArray::BWImageToArray(QImage &img)
 {
     int **OutputBlackWhiteArr = new int* [img.height()];
     for (int x = 0; x < img.height(); x++)
     {
         OutputBlackWhiteArr[x]=new int[img.width()];
         for (int y = 0; y < img.width(); y++)
         {
             QColor clrCurrent(img.pixel(x, y));
             OutputBlackWhiteArr[x][y] = (clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3;
         }
     }
     return OutputBlackWhiteArr;
 }

 std::vector<double>  ImageToArray::BWImageToVector(const QImage &img)
 {
     std::vector<double> output_Black_White_Vec;
     double tmp=0;
     for (int x = 0; x < img.height(); x++)
     {
         for (int y = 0; y < img.width(); y++)
         {
             QColor clrCurrent(img.pixel(x, y));
             if(((clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3)==0)
             {
                 output_Black_White_Vec.push_back(0);
             }
             else
             {
                 tmp = ((clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3);
                 output_Black_White_Vec.push_back(1/tmp); //сразу нормализуем данные
             }
         }
     }
     return output_Black_White_Vec;
 }

 void ImageToArray::getBoldImage(QImage &img)
 {
     for (int i =0; i< img.height(); i++)
     {
         for (int j =0; j < img.width(); j++)
         {
            if (img.pixelColor(i, j)==Qt::black){continue;}
            else {img.setPixelColor(i, j, Qt::white);}
         }
     }
 }

// ImageToArray::ImageToArray()
//{
//}


//ImageToArray::~ImageToArray()
//{
//}

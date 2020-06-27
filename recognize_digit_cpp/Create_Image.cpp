#include "stdafx.h"
#include "Create_Image.h"

#define DEBUG 0

//Create_Image::Create_Image()
//{
//}

// Bitmap ^ Create_Image::Cr_image()
//{
//	// TODO: вставьте здесь оператор return
//	Bitmap ^image = gcnew Bitmap(100,100);
//	Graphics ^ g = Graphics::FromImage(image);//создаём объект Graphics
//	SolidBrush^ Blackbrush = gcnew SolidBrush(Color::Black);//создаём кисть brush
//	SolidBrush^ Whitebrush = gcnew SolidBrush(Color::White);//создаём кисть brush
//	//Pen^ BlackPen = gcnew Pen(Color::Black);//создаём ручку
//	//g -> DrawRectangle(BlackPen, 40, 40, 25, 25);//рисуем квадрат
//	int w = rand() % 50;//размер стороны квадрата
//	g->FillRectangle(Whitebrush, 0, 0, 100, 100);//заливаем цветом квадрат
//	g->FillRectangle(Blackbrush, rand()%75 , rand() % 75, w, w);//заливаем цветом квадрат
//	return image;
//}

// void Create_Image::void_Cr_image(String^ path, int x)
// {
//	 enum figures { Rectangle, Triangle, Circle, Elipse, NUM_FIGURES};//создаём перечисление геометрических фигур для случайного выбора
//	 figures fig =static_cast<figures>(rand() % NUM_FIGURES);//генерируем номер для выбора фигуры из перечисления figures
//	 Bitmap ^image = gcnew Bitmap(100, 100);
//	 Graphics ^ g = Graphics::FromImage(image);//создаём объект Graphics
//	 SolidBrush^ Blackbrush = gcnew SolidBrush(Color::Black);//создаём кисть brush
//	 SolidBrush^ Whitebrush = gcnew SolidBrush(Color::White);//создаём кисть brush
//															 //Pen^ BlackPen = gcnew Pen(Color::Black);//создаём ручку
//															 //g -> DrawRectangle(BlackPen, 40, 40, 25, 25);//рисуем квадрат
//	 //int w = rand() % 250;//размер стороны квадрата
//	 //int z = rand() % 250;//размер стороны ограничивающего квадрата

//	/* Point point1 = Point(rand() % 500, rand() % 500);
//	 Point point2 = Point(rand() % 500, rand() % 500);
//	 Point point3 = Point(rand() % 500, rand() % 500);
//	 cli::array<Point, 1>^ TrianglePoints = { point1, point2, point3 };*/
//	 g->FillRectangle(Whitebrush, 0, 0, 100, 100);//заливаем цветом фон

//	 switch (fig)
//	 {
//		case 0:
//				{ //квадрат
//					int w = rand() % 50;//размер стороны квадрата
//					g->FillRectangle(Blackbrush, rand() % 50, rand() % 50, w, w);//заливаем цветом квадрат
//					image->Save(path + "\\Rectangle" + x + ".bmp");
//					break;
//				}
//		case 1:
//				{ //треугольник
//					// Создаём массив координат для треугольника
//					//TrianglePoints = gcnew array<Point, 1>(3);
//					//Point TrianglePoints[3] = { Point(rand() % 500, rand() % 500),Point(rand() % 500, rand() % 500), Point(rand() % 500, rand() % 500) };
//					Point point1 = Point(rand() % 100, rand() % 100);
//					Point point2 = Point(rand() % 100, rand() % 100);
//					Point point3 = Point(rand() % 100, rand() % 100);
//					cli::array<Point, 1>^ TrianglePoints = { point1, point2, point3 };
//					g->FillPolygon(Blackbrush, TrianglePoints);//заливаем цветом треугольник
//					image->Save(path + "\\Triangle" + x + ".bmp");
//					break;
//				}
//		 case 2:
//				{ //окружность
//					//int z = rand() % 250;//размер стороны ограничивающего квадрата
//					int z = rand() % 50;//размер стороны ограничивающего квадрата
//					g->FillEllipse(Blackbrush, rand() % 50, rand() % 50, z, z);//заливаем цветом окружность
//					image->Save(path + "\\Circle" + x + ".bmp");
//					break;
//				}
//		 case 3:
//				{	//эллипс
//					g->FillEllipse(Blackbrush, rand() % 50, rand() % 50, rand() % 50, rand() % 50);//заливаем цветом треугольник
//					image->Save(path + "\\Elipse" + x + ".bmp");
//					break;
//				}
//	 }
//}

 const QImage &Create_Image::GetImage()
 {
     return *imgperc;
 }

 void Create_Image::getBoldImage(QImage &img)
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

 void Create_Image::ImageFromArrayTest(int **arr, size_t &rows, size_t &columns)
 {
     QImage *img = new QImage(static_cast<int>(rows), static_cast<int>(columns), QImage::Format_RGB32);
     QRgb value;
     //QPainter *g = new QPainter(img);//создаём объект Graphics
     for (size_t i =0; i< rows; i++)
     {
         for (size_t j =0; j < columns; j++)
         {
             value = qRgb(arr[i][j], arr[i][j], arr[i][j]);
            img->setPixel(static_cast<int>(i), static_cast<int>(j), value);
         }
     }
     img->save("test_digit.png");
 }

 Create_Image::Create_Image(int **load_arr, int **digit_arr, size_t &rows, size_t &colums)
 {
     imgperc = new QImage(600, 600, QImage::Format_RGB32);
     QPainter *g = new QPainter(imgperc);//создаём объект Graphics
     QBrush blackBrush(Qt::black, Qt::SolidPattern);
     QBrush whiteBrush(Qt::white, Qt::SolidPattern);
     QBrush redBrush(Qt::red, Qt::SolidPattern);
     QBrush greenBrush(Qt::green, Qt::SolidPattern);
     QBrush yellowBrush(Qt::yellow, Qt::SolidPattern);
     QBrush grayBrush(Qt::gray, Qt::SolidPattern);
     QBrush orangeBrush(QColor(255, 160, 0),Qt::SolidPattern);
     //orangeBrush.setColor("orange");

     QPen blackPen(Qt::black, Qt::SolidLine);
     QPen whitePen(Qt::white, Qt::SolidLine);
     QFont font = g->font();
     font.setPixelSize(15);
     font.setStyleHint(QFont::Times);
     g->setFont(font);
     g->setRenderHint(QPainter::Antialiasing, true);
     g->setBrush(grayBrush);
     g->drawRect(0, 0, 600, 600);//заливаем цветом фон

     int cnt=0, rez=0;
     for (size_t i = 0; i < rows; i++)
     {
         for (size_t j = 0; j < colums; j++)
         {
             g->setPen(blackPen);
             g->drawLine(75, cnt * 40 + 20, 250, cnt * 40 + 20);//рисуем линию
             g->drawLine(250, cnt * 40 + 20, 550, 7 * 40 + 20);//рисуем линию
             ////////////////////////////////////////////////////////////////////////////////////////////
             if (digit_arr[i][j] == 0)
             {
                 g->setBrush(whiteBrush);
                 g->drawEllipse(50, cnt * 40 + 5, 30, 30);//заливаем цветом окружность
                 g->setPen(blackPen);
                 g->drawText(60, cnt * 40 + 25, QString::number(digit_arr[i][j]));
             }
             else
             {
                 g->setBrush(blackBrush);
                 g->drawEllipse(50, cnt * 40 + 5, 30, 30);//заливаем цветом окружность
                 g->setPen(whitePen);
                 g->drawText(60, cnt * 40 + 25, QString::number(digit_arr[i][j]));
             }
             ////////////////////////////////////////////////////////////////////////////////////////////
             if (load_arr[i][j] < 0)
             {
                 g->setBrush(redBrush);
                 g->drawEllipse(250, cnt * 40 + 5, 30, 30);//заливаем цветом окружность
//                 g->setPen(blackPen);
//                 g->drawText(265, cnt * 40 + 20, QString::number(load_arr[i][j]));
             }
             else if (load_arr[i][j] == 0)
             {
                 g->setBrush(yellowBrush);
                 g->drawEllipse(250, cnt * 40 + 5, 30, 30);//заливаем цветом окружность
//                 g->setPen(blackPen);
//                 g->drawText(265, cnt * 40 + 20, QString::number(load_arr[i][j]));
             }
             else
             {
                 g->setBrush(greenBrush);
                 g->drawEllipse(250, cnt * 40 + 5, 30, 30);//заливаем цветом окружность
//                 g->setPen(blackPen);
//                 g->drawText(265, cnt * 40 + 20, QString::number(load_arr[i][j]));
             }
             g->setPen(blackPen);
             g->drawText(260, cnt * 40 + 25, QString::number(load_arr[i][j]));
             cnt++;
             rez += load_arr[i][j] * digit_arr[i][j];
         }
     }
     g->setBrush(orangeBrush);
     g->drawEllipse(550, 285, 30, 30);//заливаем цветом окружность
     g->setPen(blackPen);
     g->drawText(555, 305, QString::number(rez));

     imgperc->save("D:\\Qt_projects/diploma/test.bmp");
 }

 Create_Image::~Create_Image()
 {
 }

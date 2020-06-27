#include "recognize_digit_cpp/stdafx.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PDFReader->setVisible(false);
   connect(ui->pushButton, &QPushButton::clicked, ui->PDFReader, QOverload<>::of(&QAxWidget::repaint), Qt::DirectConnection); // попытка перерисовать виджет путём использования сигналов и слотов
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ////////////////////////////////////////////// //рабочий фрагмент////////////////////////////////////

//    QAxWidget *axWidget = new QAxWidget( "PowerPoint.Application", this);


    /////////////////////////////////////////в качестве перзентации в отдельном окне//////////////////////////////////////
    QAxObject *axObject_0 = new QAxObject("PowerPoint.Application");
    QAxObject *axObject_1 = axObject_0->querySubObject("Presentations");
   /* QAxObject *axObject_2 =*/ axObject_1->querySubObject( "Open(const QVariant&)", QVariant("D:\\conf_2019.ppt") );

    // более менее рабочиё вариант
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////внутри контейнера///////////////////////////////////

//    ui->PDFReader->setControl("PowerPoint.Application");
//    ui->PDFReader->setControl("D:\\conf_2019.pptx");
//    ui->PDFReader->show();

    ///////////////////////////////////////////////////////////////////


    QImage *img = new QImage("D:\\Qt_projects/diploma/mnist_png/training/8/528.png");
    ArrayToFromFile::WriteWeights(ImageToArray::BWImageToArray(*img), *img, "test_weghts_1.txt");
//CoUninitialize();


    ifstream in;
    in.open("D:\\Qt_projects/build-diploma-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/test_weghts_1.txt");//открываем файл для вывода инфы из файла в прогу
        if (!in.is_open()) // если файл не открыт
            QMessageBox::critical(this, "Файл не найден!", "Файл с весами не найден!");
        else
        {
           // std::unique_ptr<Recog> one(new Recog());
            std::unique_ptr<ArrayToFromFile> fileread(new ArrayToFromFile());
            fileread->LoadWeights(in);
            Create_Image::ImageFromArrayTest(fileread->LoadWeights(in), fileread->GetRows(), fileread->GetColumns());
            fileread.reset();
        }
    in.close(); // закрываем файл


//////////////////////////////////////рабочий фрагмент////////////////////////////////////////////////

/*
 * //segmentation fault
    QAxWidget *axWidget = new QAxWidget( "PowerPoint.Application", this);
    ui->PDFReader = qobject_cast<QAxWidget*>(axWidget->querySubObject("Presentations"));
    ui->PDFReader->querySubObject( "Open(const QVariant&)", QVariant("D:\\conf_2019.ppt") );

    QAxObject *present =*/

//ui->PDFReader->dynamicCall("LoadFile(QString)", "D:\\honda_cr_v_2006_benzin_anta_eko.pdf");
/*
    QAxObject *axObject = ui->PDFReader->querySubObject("Documents");
    axObject ->querySubObject( "Open(const QVariant&)", QVariant("D:\\honda_cr_v_2006_benzin_anta_eko.pdf") );
    */
    /*
ui->PDFReader->setControl("Adobe PDF Reader");
ui->PDFReader->dynamicCall("LoadFile(const QString&)", "D:\\StarUML.pdf");
*/

    /*
    QAxWidget* WordDocument=new QAxWidget ("PowerPoint.Application", nullptr);
      // V.addWidget(WordDocument);

      // window.setLayout(&V);

       WordDocument-> setGeometry (QRect (10, 10, 621, 471));
       WordDocument->setControl ("D:\\conf_2019.ppt");
       WordDocument-> show();
       */
}

void MainWindow::on_pushButton_2_clicked()
{
    ifstream in;
    in.open("D:\\Qt_projects/diploma/weights_one.txt");//открываем файл для вывода инфы из файла в прогу
        if (!in.is_open()) // если файл не открыт
            QMessageBox::critical(this, "Файл не найден!", "Файл с весами не найден!");
        else
        {
            std::unique_ptr<Recog> one(new Recog());
            std::unique_ptr<ArrayToFromFile> fileread(new ArrayToFromFile());
            fileread->LoadWeights(in);
            size_t x=fileread->GetRows(), y=fileread->GetColumns();
            int **inparr = new int*[x];//получив размер создаём его
            for (int i = 0; i < static_cast<int>(x); i++)
            {
                inparr[i] = new int[y];
                for (int j = 0; j < static_cast<int>(y); j++)
                {
                    inparr[i][j] = ui->tableWidget->item(i, j)->text().toInt();
                }
            }
            unique_ptr<Create_Image> one_im(new Create_Image(fileread->LoadWeights(in), inparr, x, y));
            QGraphicsScene *scene = new QGraphicsScene(this);
                scene->addPixmap(QPixmap::fromImage(one_im->GetImage()));
                ui->graphicsView->setScene(scene);
            for (size_t i = 0; i < x; i++)
            {
                delete[] inparr[i];
            }
            delete[] inparr;
            fileread.reset();
            one.reset();
            one_im.reset();
        }
    in.close(); // закрываем файл
}

void MainWindow::on_pushButton_3_clicked()
{
    lec_window_01 *lec_1 = new lec_window_01();
    lec_1->show();
}

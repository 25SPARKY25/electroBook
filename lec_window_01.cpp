#include "recognize_digit_cpp/stdafx.h"
#include "lec_window_01.h"
#include "ui_lec_window_01.h"

Q_DECLARE_METATYPE(std::vector<int>)
Q_DECLARE_METATYPE(std::vector<Example>)

lec_window_01::lec_window_01(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lec_window_01)
{
    ui->setupUi(this);
    this->ui->label_2->setVisible(false);
    if (scene == nullptr)
    {
        scene = new paintscene();       // Инициализируем графическую сцену
    }

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену

    if (timer == nullptr)
    {
        timer = new QTimer();       // Инициализируем таймер
    }

    connect(timer, &QTimer::timeout, this, &lec_window_01::slotTimer);
    timer->start(100);          // Запускаем таймер
    qRegisterMetaType <std::vector<int>> ("std::vector<int>");
    qRegisterMetaType <std::vector<Example>> ("std::vector<Example>&");
    qRegisterMetaType<std::map<QString, QString>>("std::map<QString, QString>&");

    if (net_2 == nullptr)
    {
       net_2 = new net();
    }

    if (th_1 == nullptr)
    {
        th_1 = new QThread(this);
    }

    connect(this, &lec_window_01::destroyed, th_1, &QThread::quit);

    this->ui->learnBars->hide();
    this->ui->customPlot->hide();

    if (anim_scene == nullptr)
    {
        anim_scene = new QGraphicsScene(ui->graphicsView_2);
    }

    anim_scene->setSceneRect(0,0, ui->graphicsView_2->width() - 20, ui->graphicsView_2->height() - 20);
    this->ui->graphicsView_2->setScene(anim_scene);
    this->ui->graphicsView_2->setRenderHints(QPainter::Antialiasing);

    connect(this->ui->horizontalSlider, &QSlider::valueChanged, this->scene, &paintscene::setPenRadius);

    if (an == nullptr)
    {
       an = new animatedPerceptrone(*anim_scene, *this->ui->tb_schema_description);
    }

    if (forwardAnimMethods == nullptr)
    {
        forwardAnimMethods = new QStack<PvoidAnimPerc>;
        forwardAnimMethods->push(&animatedPerceptrone::blinkSecondConnection);
        forwardAnimMethods->push(&animatedPerceptrone::blinkFirstConnection);
        forwardAnimMethods->push(&animatedPerceptrone::blinkSensConnection);

        forwardAnimMethods->push(&animatedPerceptrone::animateBackInpSignals);
        forwardAnimMethods->push(&animatedPerceptrone::animateBackHidSignals);

        forwardAnimMethods->push(&animatedPerceptrone::animateHidSignals);
        forwardAnimMethods->push(&animatedPerceptrone::animateInpSignals);
        forwardAnimMethods->push(&animatedPerceptrone::animateSensSignals);

        forwardAnimMethods->push(&animatedPerceptrone::animateLayerLable);
        forwardAnimMethods->push(&animatedPerceptrone::animateLabels);
        forwardAnimMethods->push(&animatedPerceptrone::animateOutputNeuronLabels);
        forwardAnimMethods->push(&animatedPerceptrone::animateOutputLayer);

        forwardAnimMethods->push(&animatedPerceptrone::animateOutputConnections);
        forwardAnimMethods->push(&animatedPerceptrone::animateSecondNeuronLabels);
        forwardAnimMethods->push(&animatedPerceptrone::animateHidenLayer);

        forwardAnimMethods->push(&animatedPerceptrone::animateHidenConnections);
        forwardAnimMethods->push(&animatedPerceptrone::animateFirstNeuronLabels);
        forwardAnimMethods->push(&animatedPerceptrone::animateInpuLayer);

        forwardAnimMethods->push(&animatedPerceptrone::animateSensorConnections);
        forwardAnimMethods->push(&animatedPerceptrone::animateSensorLabels);
        forwardAnimMethods->push(&animatedPerceptrone::animateSensors);
    }

    if (backwardAnimMethods == nullptr)
    {
        backwardAnimMethods = new QStack<PvoidAnimPerc>;
    }



    connect(this->ui->pb_nextAnim, &QPushButton::clicked, [this]()
    {
        this->an->setAnimateFlag(true);
        if(!forwardAnimMethods->isEmpty())
        {
            currMet = forwardAnimMethods->last();
            backwardAnimMethods->push(currMet);
            (this->an->*forwardAnimMethods->pop())();
        }
    });
    connect(this->ui->pb_previousAnim, &QPushButton::clicked, [this]()
    {
        this->an->setAnimateFlag(false);
        if(!backwardAnimMethods->isEmpty())
        {
            currMet = backwardAnimMethods->last();
            forwardAnimMethods->push(currMet);
            (this->an->*backwardAnimMethods->pop())();
        }
    });
    connect(this->ui->pb_repeatAnim, &QPushButton::clicked, [this] ()
    {
        if (currMet!=nullptr)
        {
          (this->an->*currMet)();
        }
    });
    connect(this->ui->pushButton_5, &QPushButton::clicked, this->ui->textBrowser, &QTextBrowser::home);
    this->ui->textBrowser->setSource(QUrl("qrc:/res/Lessons/home.html"));

    connect(this->an, &animatedPerceptrone::animationFinished, this, &lec_window_01::enableButtons);
    connect(this->ui->pb_nextAnim, &QPushButton::clicked, [this]()
    {
        if(!forwardAnimMethods->isEmpty())
        {
            this->ui->pb_nextAnim->setEnabled(false);
            this->ui->pb_repeatAnim->setEnabled(false);
            this->ui->pb_previousAnim->setEnabled(false);
        }
    });
    connect(this->ui->pb_repeatAnim, &QPushButton::clicked, [this]()
    {
        if(!forwardAnimMethods->isEmpty() && !backwardAnimMethods->isEmpty())
        {
            this->ui->pb_nextAnim->setEnabled(false);
            this->ui->pb_repeatAnim->setEnabled(false);
            this->ui->pb_previousAnim->setEnabled(false);
        }
    });
    connect(this->ui->pb_previousAnim, &QPushButton::clicked, [this]()
    {
        if(!backwardAnimMethods->isEmpty())
        {
            this->ui->pb_nextAnim->setEnabled(false);
            this->ui->pb_repeatAnim->setEnabled(false);
            this->ui->pb_previousAnim->setEnabled(false);
        }
    });

    this->ui->customPlot->addGraph();
    this->ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    QSharedPointer<QCPAxisTickerFixed> countTicker(new QCPAxisTickerFixed);
    this->ui->customPlot->xAxis->setTicker(countTicker);
    countTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);

    this->ui->customPlot->axisRect()->setupFullAxesBox();
    this->ui->customPlot->yAxis->setRange(0, 100);
    this->ui->customPlot->yAxis->setLabel("Точность, в %");

    connect(this->ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(this->ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));


}

lec_window_01::~lec_window_01()
{
    if(!th_1->wait(3000))
    {
        th_1->terminate();
        th_1->wait();
    }
    delete ui;
}

void lec_window_01::enableButtons()
{
    this->ui->pb_nextAnim->setEnabled(true);
    this->ui->pb_repeatAnim->setEnabled(true);
    this->ui->pb_previousAnim->setEnabled(true);
}

void lec_window_01::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    anim_scene->setSceneRect(0,0, ui->graphicsView_2->width() - 20, ui->graphicsView_2->height() - 20);
}

void lec_window_01::slotProgressBarLearn()
{

    double q;
    double w, e, z;
    double r;
    w=net_1->getCounter() ;   
    ui->label_5->setText(QString::number(w));    

    if (!isLearned)
    {
        e = ui->spinBox->value();
        z = number_of_examples;
        r = w/(e*z);
    }
    else
    {
        z = number_of_tests;
        r = w/z;
    }
    q = r*100;
    ui->progressBar->setValue(static_cast<int>(q));
    ui->progressBar->update();
}

void lec_window_01::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}


void lec_window_01::on_pushButton_2_clicked()
{
    scene->clear();
    this->ui->label_2->clear();
}

void lec_window_01::on_pushButton_clicked()
{
    QPixmap pixMap = this->ui->graphicsView->grab();
    QPixmap scaled_pixMap = pixMap.scaled(QSize(28, 28),Qt::IgnoreAspectRatio);
    scaled_pixMap.save("test.png");
    std::vector<std::vector<neuron>> net = ArrayToFromFile::LoadNetwork();
    net_2->createNet(net);
    this->ui->label_2->setText(QString::number(net_2->recognize(scaled_pixMap.toImage())));
    this->ui->label_2->setVisible(true);

    ///более мене рабочий метод получения картинки из виджета
    //    QString fileName = "file_name.png";
    //    QPixmap pixMap = QPixmap::grabWidget(ui->graphicsView);
    //    pixMap.save(fileName);

    ///ещё 1 рабочи метод получения картинки из виджета
    //        QImage image(static_cast<int>(scene->width()) , static_cast<int>(scene->height()) , QImage::Format_ARGB32_Premultiplied);
    //        image.fill(QColor(Qt::white).rgb());
    //        QPainter painter(&image);
    //        scene->render(&painter);
    //        painter.end();
    //        image.save("puti_save.png");
}

void lec_window_01::on_pushButton_3_clicked()
{
    //загрузка обучающей выборки в контейнер map
    if (net_1!=nullptr)
    {
        delete net_1;
        net_1 = new net();
        isLearned = false;
        numDirectories = 0;
    }
    if (net_1 == nullptr)
    {
       net_1 = new net();
    }

    net_1->moveToThread(th_1);
    th_1->start();

    connect(this, &lec_window_01::startLearn, net_1, &net::startLearn);
    connect(this->net_1, &net::netIsLearned, this, &lec_window_01::setLearnedStatus);

    std::map<QString, QString> learn;
    QString path = QFileDialog::getExistingDirectory(this, "Выберите директорию для обучения.", "D:\\Qt_projects/diploma/mnist_png" ,QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDirIterator it(path, QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
    std::vector<Example> examples;
    QDir tmpdir; //имя директория для сравнения
    while (it.hasNext())
    {
        it.next();
        QFileInfo f_inf(it.fileInfo()); //получаем имя файла
        QDir cur_dir(f_inf.dir());      //получаем имя текущего директория
        if(cur_dir!=tmpdir)
        {
            numDirectories++;           //считаем количество директорий
        }
        tmpdir=cur_dir;
        examples.push_back({it.filePath(), cur_dir.dirName()});
    }
    //    cout<<numDirectories<<endl;
    number_of_examples = static_cast<int>(examples.size());
    QPixmap tmp_img = QPixmap(examples[0].path);
    height = tmp_img.height();
    width = tmp_img.height();
    //создание нейросети
    std::vector<int> topology = {height*width, 128, numDirectories};

    //загрузка тестовой выборки в контейнер map
    std::vector<Example> test;
    QString path_t = QFileDialog::getExistingDirectory(this, "Выберите директорию для тестирования.", "D:\\Qt_projects/diploma/mnist_png" ,QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDirIterator it_t(path_t, QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);

    while (it_t.hasNext())
    {
        it_t.next();
        QFileInfo f_inf(it_t.fileInfo()); //получаем имя файла
        QDir cur_dir(f_inf.dir());      //получаем имя текущего директория
        test.push_back({it.filePath(), cur_dir.dirName()});
    }
    number_of_tests = static_cast<int>(test.size());
    if (dataTimer != nullptr)
    {
        delete dataTimer;
       dataTimer = new QTimer();
    }

    if (dataTimer == nullptr)
    {
       dataTimer = new QTimer();
    }

    if (progressTimer == nullptr)
    {
      progressTimer = new QTimer();
    }

    ui->customPlot->graph(0)->data()->clear();

    if(regen==nullptr)
    {regen = new QCPBars(this->ui->learnBars->xAxis, this->ui->learnBars->yAxis);}
    regen->data()->clear();
    regen->setAntialiased(false);
    regen->setStackingGap(1);

    regen->setName("Количество верно\nраспознанных чисел");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));

    QVector<double> ticks {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    QVector<QString> labels {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    this->ui->learnBars->xAxis->setTicker(textTicker);
    this->ui->learnBars->xAxis->setTickLabelRotation(0);
    this->ui->learnBars->xAxis->setSubTicks(false);
    this->ui->learnBars->xAxis->setTickLength(0, 1);
    this->ui->learnBars->xAxis->setRange(-1, 17);
    this->ui->learnBars->xAxis->setBasePen(QPen(Qt::black));
    this->ui->learnBars->xAxis->setTickPen(QPen(Qt::black));
    this->ui->learnBars->xAxis->grid()->setVisible(true);
    this->ui->learnBars->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    this->ui->learnBars->xAxis->setTickLabelColor(Qt::black);
    this->ui->learnBars->xAxis->setLabelColor(Qt::black);

    this->ui->learnBars->yAxis->setRange(0, 10000);
    this->ui->learnBars->yAxis->setPadding(5); // a bit more space to the left border
    this->ui->learnBars->yAxis->setLabel("Количество верно распознанных чисел");
    this->ui->learnBars->yAxis->setBasePen(QPen(Qt::black));
    this->ui->learnBars->yAxis->setTickPen(QPen(Qt::black));
    this->ui->learnBars->yAxis->setSubTickPen(QPen(Qt::black));
    this->ui->learnBars->yAxis->grid()->setSubGridVisible(true);
    this->ui->learnBars->yAxis->setTickLabelColor(Qt::black);
    this->ui->learnBars->yAxis->setLabelColor(Qt::black);
    this->ui->learnBars->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    this->ui->learnBars->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    this->ui->learnBars->legend->setVisible(true);
    this->ui->learnBars->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    this->ui->learnBars->legend->setBrush(QColor(255, 255, 255, 100));
    this->ui->learnBars->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    this->ui->learnBars->legend->setFont(legendFont);

    connect(dataTimer, &QTimer::timeout, this, &lec_window_01::realtimeDataSlot);

    connect(progressTimer, &QTimer::timeout, this, &lec_window_01::slotProgressBarLearn);
    dataTimer->start(0);
    progressTimer->start(0);

    emit startLearn(topology, examples, this->ui->spinBox->value(), this->ui->doubleSpinBox->value(),test);
    this->ui->learnBars->show();
    this->ui->customPlot->show();
}

void lec_window_01::on_pushButton_4_clicked()
{
    QPixmap pixMap = QFileDialog::getOpenFileName(this, "Выберите файл.", "D:\\Qt_projects/diploma/mnist_png", "*.png");
    if(pixMap.isNull()==false)
    {
        QImage img = pixMap.toImage();
        Create_Image::getBoldImage(img);

        std::vector<std::vector<neuron>> net = ArrayToFromFile::LoadNetwork();
        net_2->createNet(net);
        this->ui->label_2->setText(QString::number(net_2->recognize(img)));
        this->ui->label_2->setVisible(true);

        scene->addPixmap(pixMap.fromImage(img).scaled(QSize(560, 560), Qt::AspectRatioMode::IgnoreAspectRatio));
        this->ui->graphicsView->setScene(scene);
    }

}

void lec_window_01::on_toolButton_2_clicked()
{
this->ui->stackedWidget->setCurrentIndex(0);
}

void lec_window_01::on_toolButton_clicked()
{
this->ui->stackedWidget->setCurrentIndex(1);
}

void lec_window_01::realtimeDataSlot()
{
        if (!isLearned)
        {
            ui->customPlot->graph(0)->addData(net_1->getCounter(), static_cast<double>(net_1->getCorrect())/static_cast<double>(net_1->getCounter()) *100.0);
        }

    regen->setData(keys, net_1->getCorrectData(), true );

ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
    ui->learnBars->rescaleAxes();
    ui->learnBars->replot();
}

void lec_window_01::on_toolButton_4_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
    anim_scene->setSceneRect(0,0, ui->graphicsView_2->width() - 20, ui->graphicsView_2->height() - 20);
    qDebug()<<ui->graphicsView_2->size();
    qDebug()<<anim_scene->sceneRect().size();

}

void lec_window_01::on_toolButton_3_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}

void lec_window_01::on_toolButton_5_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(4);
}

void lec_window_01::on_pb_repeatAnim_clicked()
{

}

void lec_window_01::setLearnedStatus()
{
 this->isLearned = true;
}

void lec_window_01::on_lec_window_01_destroyed()
{

}

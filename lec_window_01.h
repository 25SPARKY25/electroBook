#ifndef LEC_WINDOW_01_H
#define LEC_WINDOW_01_H

#include "animatedperceptrone.h"
#include "paintscene.h"
#include "net.h"
#include "neuron.h"
#include "recognize_digit_cpp/ArrayToFromFile.h"
#include "recognize_digit_cpp/Create_Image.h"

namespace Ui {
class lec_window_01;
}

class lec_window_01 : public QMainWindow
{
    Q_OBJECT

public:
    explicit lec_window_01(QWidget *parent = nullptr);
    ~lec_window_01();

public slots:
    void enableButtons();

private:
    Ui::lec_window_01 *ui;
    QTimer *timer = nullptr;      /* Определяем таймер для подготовки актуальных размеров
                            * графической сцены
                            * */
    paintscene *scene = nullptr;  // Объявляем кастомную графическую сцену

    QGraphicsScene *anim_scene = nullptr;

    /* Переопределяем событие изменения размера окна
        * для пересчёта размеров графической сцены
        * */

    void resizeEvent(QResizeEvent * event);

    QTimer *dataTimer = nullptr;
    QTimer *progressTimer = nullptr;
    net *net_1 = nullptr, *net_2 = nullptr; //первый для обучения, второй для распознавания
    QThread *th_1 = nullptr;
    int height = 0, width = 0, numDirectories = 0, number_of_examples, number_of_tests;
    QVector<double> keys {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    QCPBars *regen =nullptr;
    bool isLearned=false; //обучена ли сеть.

    QGraphicsLineItem *myLine;
    QGraphicsLineItem *myLine_1;
    animatedPerceptrone *an = nullptr;

    typedef void (animatedPerceptrone:: * PvoidAnimPerc)();
    QStack<PvoidAnimPerc> *forwardAnimMethods = nullptr;
    QStack<PvoidAnimPerc> *backwardAnimMethods = nullptr;
    PvoidAnimPerc currMet = nullptr;

private: signals:
    void startLearn(const std::vector<int> &topology, std::vector<Example> &examples, int num_epochs, double learn_speed, std::vector<Example> &test);

private slots:
    void slotTimer();
    void slotProgressBarLearn();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_clicked();
    void realtimeDataSlot();
    void on_toolButton_4_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_5_clicked();
    void on_pb_repeatAnim_clicked();
    void setLearnedStatus();
    void on_lec_window_01_destroyed();
};

#endif // LEC_WINDOW_01_H

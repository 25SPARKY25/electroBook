#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lec_window_01.h"
#include "recognize_digit_cpp/Create_Image.h"
#include "recognize_digit_cpp/test_perceptron.h"
#include "recognize_digit_cpp/ArrayToFromFile.h"
#include "recognize_digit_cpp/ImageToArray.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public: signals:
    void click();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

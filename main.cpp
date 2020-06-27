//#include "mainwindow.h"
#include "lec_window_01.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lec_window_01 w;
    w.showMaximized();
    return a.exec();
}

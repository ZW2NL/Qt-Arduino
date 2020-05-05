#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(624,350);
    w.setWindowTitle("RGB LED Controller");
    return a.exec();
}

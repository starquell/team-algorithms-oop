#include "MainWindow.hpp"
#include <QApplication>
#include <iostream>
using namespace lab;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}

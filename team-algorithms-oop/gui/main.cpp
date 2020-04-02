#include "mainwindow.h"
#include <QApplication>

#include <SplayTree.hpp>
#include <RedBlackTree.hpp>
#include <UndoableTree.hpp>


using namespace lab;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

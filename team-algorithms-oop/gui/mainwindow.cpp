#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <SplayTree.hpp>
#include <RedBlackTree.hpp>
#include <UndoableTree.hpp>
#include <AnyTree.hpp>
#include <TreeDB.hpp>

namespace lab {



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    _curTreeName = "";
    _state = CurPage::Pills;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BluePill_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_RedPill_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

}

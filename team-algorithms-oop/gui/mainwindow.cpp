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
    ui(new Ui::MainWindow),
    _db(TreeDatabase::instance())
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    _curTreeName = "";
    _state = CurPage::Pills;
    _getToDBPage();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_getToDBPage(){
    ui->stackedWidget->setCurrentIndex(1);
    _dbModel = new QStringListModel(this);
    auto namesFromDB = _db.loadNames();
    QStringList treeNames;
    for (const auto& name: _db.loadNames())
        treeNames << QString::fromStdString(name);
    _dbModel->setStringList(treeNames);
    ui->DBlist->setModel(_dbModel);

}

void MainWindow::_getToPillsPage(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::_getToTreeUIPage(){
    ui->stackedWidget->setCurrentIndex(2);
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

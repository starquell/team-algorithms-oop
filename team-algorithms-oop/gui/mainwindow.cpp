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
    _curTreeName = "Default Tree";
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

    auto loadedTree = _db.load<forest::SplayTree<std::string, std::greater<>>>(_curTreeName);

    if(loadedTree == std::nullopt)
        _tree.setTree(forest::SplayTree<std::string>());
    else
        _tree.setTree(loadedTree);
    _getToTreeUIPage();
}

void MainWindow::on_RedPill_clicked()
{
    _getToTreeUIPage();
}

void MainWindow::on_CreateNew_clicked()
{
    if (ui->Less->isChecked())
        _cmp = CmpType::Less;
    else
        _cmp = CmpType::Greater;
    _curTreeName = ui->lineEdit->text().toStdString();
    _getToPillsPage();
}




void MainWindow::on_LoadButton_clicked()
{

}

void MainWindow::on_Undo_clicked()
{

}

void MainWindow::on_Redo_clicked()
{

}

void MainWindow::on_InsertButton_clicked()
{

}

void MainWindow::on_Search_clicked()
{

}

void MainWindow::on_DeleteButton_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{

}

}//kjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjnnnnnnnnnnnnnnnnnnnn

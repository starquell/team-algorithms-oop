#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <string>

#include <SplayTree.hpp>
#include <RedBlackTree.hpp>
#include <UndoableTree.hpp>
#include <AnyTree.hpp>

namespace Ui {
class MainWindow;
}


namespace lab {

class TreeDatabase;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BluePill_clicked();

    void on_RedPill_clicked();

    void on_CreateNew_clicked();

    void on_LoadButton_clicked();

    void on_Undo_clicked();

    void on_Redo_clicked();

    void on_InsertButton_clicked();

    void on_Search_clicked();

    void on_DeleteButton_clicked();

    void on_pushButton_clicked();

    void on_SaveButton_clicked();

private:

    enum CmpType{Less, Greater};
    Ui::MainWindow *ui;
    CmpType _cmp;
    std::string _curTreeName;
    TreeDatabase& _db;
    forest::AnyTree<SupportedValueType<std::string>, SupportedComparators<std::less<>, std::greater<>>> _tree;
    QStringListModel* _dbModel;
    std::vector<std::string> _loadedNames;

    void _getToDBPage();

    void _getToPillsPage();

    void _getToTreeUIPage();

    void _setCmp();

    void _printTree();

};
}
#endif // MAINWINDOW_H

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z

LIBS += -lsqlite3
TARGET = team-algorithms-oop
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include \
            src \
            src/SplayTree \
            srs/RedBlackTree \
            deps \
            deps/cereal/include

SOURCES += \
        gui/main.cpp \
        gui/mainwindow.cpp  


HEADERS += \
        gui/mainwindow.h \
	src/AnyTree.tpp \
	src/AnyTreeDetail.hpp \
	src/BSTBase.hpp \
	src/BSTBase.tpp \
	src/BSTIterator.hpp \
	src/BSTIterator.tpp \
	src/NodeBase.hpp \
	src/NodeUtilities.hpp \
	src/TreeDB.tpp \
	src/UndoableTree.tpp \
	src/SplayTree/SplayTree.tpp \
	src/SplayTree/Splayer.hpp \
	src/RedBlackTree/DeletionFixRBTree.hpp \
	src/RedBlackTree/InsertionFixRBTree.hpp \
	src/RedBlackTree/RBNodeUtilities.hpp \
	src/RedBlackTree/RedBlackTree.tpp \
        include/AnyTree.hpp \
        include/RedBlackTree.hpp \
        include/SplayTree.hpp \
        include/TreeDB.hpp \
        include/UndoableTree.hpp
	

FORMS += \
        gui/mainwindow.ui

RESOURCES += \
    resourses.qrc


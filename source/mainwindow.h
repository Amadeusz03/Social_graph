#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QFile>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
#include <string>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileDialog>
#include <QVector>
#include <QListWidget>
#include <QDockWidget>
#include <QObject>

#include "list.h"
#include "person.h"
#include "graphwidget.h"
#include "datainput.h"
#include "node.h"

class Node;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVector<Person> personList;
public:
    MainWindow(QVector<Person>& data, QWidget* parent = nullptr);
    void add( );
    void newGraph( );
    static QDockWidget* bar;

public slots:
    void listUpdate(Node* node);

};

#endif
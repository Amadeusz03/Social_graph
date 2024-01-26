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
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <iostream>
#include <QSignalMapper>

#include "list.h"
#include "person.h"
#include "graphwidget.h"
#include "datainput.h"
#include "node.h"
#include "dialog.h"

class Node;
class Edge;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVector<Person*>* personList;
    QTableWidget* headingTable;
    QListWidget* linksList;
    QTableWidget* connectionsTable;
    Node* activatedNode;
    static QAction* findAct;
public:
    MainWindow(QVector<Person*>* data, QWidget* parent = nullptr);
    void open( );
    void newGraph( );


public slots:
    void listUpdate(Node* node);
    void connectionsUpdate(QListWidgetItem* person);
    void addPerson( );

};

#endif
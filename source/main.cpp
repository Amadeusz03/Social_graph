#include <iostream>
#include <QApplication>
#include <QVector>

#include "node.h"
#include "graphwidget.h"
#include "datainput.h"
#include "mainwindow.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QVector<Person> graphPerson;

    DataInput input;
    input.getData(graphPerson, "dupa.txt");
    
    MainWindow* window = new MainWindow(graphPerson);
    window->show( );

    return a.exec( );
}
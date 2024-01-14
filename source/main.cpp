#include <iostream>
#include <QApplication>
#include <QVector>

int nodes;

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
    //input.getData(graphPerson, "dupa1.txt");
    // input.getData(graphPerson, "C:\\dupa2.txt");
    // input.getData(graphPerson, "C:\\dupa3.txt");
    // input.getData(graphPerson, "C:\\dupa4.txt");
    nodes = graphPerson.size( );
    cout << (graphPerson.back( ).getData());
    for (auto i : graphPerson.back( ).getFriends( ))
    {
        std::cout << i.getData( ) << std::flush;
    }
    //GraphWidget graph(graphPerson);
    //graph.show( );
    MainWindow* window = new MainWindow(graphPerson);
    window->show( );

    return a.exec( );
}
#ifndef DATAINPUT_H
#define DATAINPUT_H
#include <fstream>
#include <iostream>
#include <QVector>
#include "person.h"
#include "list.h"

using namespace std;

/**
 * @brief DataInput is class that handles every data input operations important for graph.
 */
class DataInput
{
public:
    DataInput( ) = default; // default constructor
    static void getData(QVector<Person>& personsList, string file);
};

#endif // DATAINPUT_H

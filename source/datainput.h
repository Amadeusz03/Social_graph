#ifndef DATAINPUT_H
#define DATAINPUT_H
#include <fstream>
#include <iostream>
#include <QVector>
#include <sstream>

#include "person.h"
#include "list.h"

using namespace std;

/**
 * @brief DataInput is class that handles every data input operations important for graph.
 */
class DataInput
{
private:

public:
    static string curr_file;

    DataInput( ) = default; // default constructor
    static void getData(QVector<Person*>* personsList, string file);
    static bool addData(QVector<Person*>* personList, QStringList& list);
};

#endif // DATAINPUT_H

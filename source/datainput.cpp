#include "datainput.h"

/**
 * @brief Extracting data from files. Using fstreams. First line is main person, and every other line is friend of this person. First word is firstname, second lastname. For now empty line is also interpreted as person (maybe change later!).
 * @param personList List of Person objects to which data shall be extracted.
 * @param file String containg absolute path to file.
 * @throw Throws string "could not open file", when file doesnt exist or any problem occured.
 */
void DataInput::getData(pro::list<Person> &personList, string file)
{
    ifstream stream;
    stream.open(file);
    if (stream.fail()) {
        throw("couldnt open file");
    }
    string line;
    Person *thisPerson;
    bool exists = false;

    if (!stream.eof()) {
        getline(stream, line);
        string first = line.substr(0, line.find(' '));
        string last = line.substr(line.find(' ') + 1, string::npos);

        for (pro::list<Person>::iterator i = personList.begin(); i != personList.end(); ++i) {
            if (i->getData() == line) {
                thisPerson = &*i;
                exists = true;
                break;
            }
        }
        if(!exists)
        {
            thisPerson = new Person(first, last);
        }
    }

    while (!stream.eof()) {
        getline(stream, line);
        string first(line.substr(0, line.find(' ')));
        string last(line.substr(line.find(' ') + 1, string::npos));

        bool change = true;
        for (pro::list<Person>::iterator i = personList.begin(); i != personList.end(); ++i) {
            if (i->getData() == line) {
                change = false;
                thisPerson->addfriend(&*i);
                break;
            }
        }
        if (change) {
            personList.push_back(*new Person(first, last));
            thisPerson->addfriend(&personList.back());
        }

    }
    if(!exists)
    {
            personList.push_back(*thisPerson);
    }
}

#include "datainput.h"

/**
 * @brief Extracting data from files. Using fstreams. First line is main person, and every other line is friend of this person. First word is firstname, second lastname. For now empty line is also interpreted as person (maybe change later!).
 * @param personList List of Person objects to which data shall be extracted.
 * @param file String containg absolute path to file.
 * @throw Throws string "could not open file", when file doesnt exist or any problem occured.
 */
void DataInput::getData(QVector<Person*>* personList, string file)
{
    ifstream stream;
    stream.open(file);
    if (stream.fail( ))
    {
        throw("couldnt open file");
    }
    string line;
    Person* thisPerson;
    bool exists = false;

    if (!stream.eof( ))
    {
    //         std::string firstname;
    // std::string lastname;
    // std::string city;
    // std::string street;
    // std::string house_nr;
    // QVector<std::string> hobby;
    // int age;
    // std::string workplace;
    // sex personSex;
    // znajomy (imie nazwisko)
        while (!stream.eof( ))
        {
            getline(stream, line);
            string first = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            string last = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            string city = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            string street = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            string house_nr = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            string hobby_0 = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            QVector<string> hobby;
            hobby.push_back(hobby_0);
            int age;
            bool is_age = true;
            do
            {
                string temp = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1, string::npos);
                stringstream ss(temp);
                ss >> age;
                if (!ss.fail( ))
                {
                    is_age = false;
                }
                else
                {
                    hobby.push_back(temp);
                }
            } while (is_age);
            string workplace = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            string temp = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1, string::npos);
            Person::sex i_sex = (temp == "M" ? Person::sex::M : Person::sex::F);


            for (QVector<Person*>::iterator i = personList->begin( ); i != personList->end( ); ++i)
            {
                if ((*i)->getData( ) == line)
                {
                    thisPerson = *i;
                    exists = true;
                    thisPerson->completeData(city, street, house_nr, hobby, age, workplace, i_sex);
                    break;
                }
            }
            if (!exists)
            {
                thisPerson = new Person(first, last, city, street, house_nr, hobby, age, workplace, i_sex);
            }


            while (!line.empty( ))
            {
                string first = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1, string::npos);
                string last = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1, string::npos);

                bool change = true;
                for (QVector<Person*>::iterator i = personList->begin( ); i != personList->end( ); ++i)
                {
                    if ((*i)->getData( ) == first + ' ' + last)
                    {
                        change = false;
                        thisPerson->addfriend(*i);
                        (*i)->addfriend(thisPerson);
                        break;
                    }
                }
                if (change)
                {
                    Person* t = new Person(first, last);
                    personList->push_back(t);
                    //std::cout << personList.back( ).getData( ) << std::flush;
                    thisPerson->addfriend(t);
                    t->addfriend(thisPerson);
                    //std::cout << thisPerson->getFriends( ).back( )->getData( ) << std::flush;
                }
            }

            if (!exists)
            {
                personList->push_back(thisPerson);
            }
        }
    }
}

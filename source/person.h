#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <QPair>

#include "list.h"
#include "node.h"

/**
 * @brief Person is class representing persons in graph.
 */
class Person
{
public:
    enum sex { M, F, U };

    std::string city;
    std::string street;
    std::string house_nr;
    QVector<std::string> hobby;
    int age;
    std::string workplace;
    sex personSex;
    std::string lastname;
    std::string firstname;

    QVector<Person*> friends;

    //Person( ) = default; // default constructor
    Person(std::string input_firstname, std::string input_lastname, std::string input_city = "", std::string input_street = "", std::string input_house_nr = "", QVector<std::string> input_hobby = QVector<std::string>( ), int input_age = 0, std::string input_workplace = "", sex input_sex = sex::U) : firstname(input_firstname), lastname(input_lastname), city(input_city), street(input_street), house_nr(input_house_nr), hobby(input_hobby), age(input_age), workplace(input_workplace), personSex(input_sex)
    { }
    void completeData(std::string input_city = "", std::string input_street = "", std::string input_house_nr = "", QVector<std::string> input_hobby = QVector<std::string>( ), int input_age = 0, std::string input_workplace = "", sex input_sex = sex::U);
    void addfriend(Person* myFriend);
    std::string getData( );
    QVector<Person*> getFriends( );

    bool operator<(Person other);

private:

     // dont know why pointers doesnt work seems lika a fucking bloat
};

#endif // PERSON_H
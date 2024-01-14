#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
#include "list.h"
#include "node.h"

/**
 * @brief Person is class representing persons in graph.
 */
class Person
{
public:
    Person( ) = default; // default constructor
    Person(std::string input_firstname, std::string input_lastname)
        : firstname(input_firstname), lastname(input_lastname)
    { }
    void addfriend(Person myFriend);
    std::string getData( );
    QVector<Person>& getFriends( );

    bool operator<(Person other);

private:
    std::string firstname;
    std::string lastname;
    QVector<Person> friends; // dont know why pointers doesnt work seems lika a fucking bloat
};

#endif // PERSON_H
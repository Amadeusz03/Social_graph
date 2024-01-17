#include "person.h"

/**
 * @brief Add person(class Person) to list of friends(vector<Person*> friends).
 * @param myFriend A person to add to list of friends.
 */
void Person::addfriend(Person* myFriend)
{
    friends.push_back(myFriend);
}

/**
 * @brief Returns combined firstname and lastname.
 * @return String of combined names.
 */
std::string Person::getData( )
{
    return firstname + ' ' + lastname;
}

/**
 * @brief Returns vector of pointers to persons which are friends with this object.
 * @return Vector of poibnters to friends (vector<Persons *>).
 */
QVector<Person*> Person::getFriends( )
{
    return friends;
}

bool Person::operator<(Person other)
{
    return this->friends.size( ) > other.friends.size( );
}

void Person::completeData(std::string input_city, std::string input_street, std::string input_house_nr, QVector<std::string> input_hobby, int input_age, std::string input_workplace, sex input_sex)
{
    city = input_city;
    street = input_city;
    house_nr = input_house_nr;
    hobby = input_hobby;
    age = input_age;
    workplace = input_workplace;
    personSex = input_sex;
}
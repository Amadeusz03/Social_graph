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
std::vector<Person*>& Person::getFriends( )
{
    return friends;
}

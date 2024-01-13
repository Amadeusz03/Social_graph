#ifndef LIST_H
#define LIST_H

#pragma once
#include <iterator>
namespace pro {
namespace internal {
struct Base_node
{
    Base_node *next;
    Base_node *prev;

    Base_node() { this->next = this->prev = this; }

    void Node_hook(Base_node *const position)
    {
        this->next = position;
        this->prev = position->prev;
        position->prev->next = this;
        position->prev = this;
    }

    void Node_unhook()
    {
        Base_node *next = this->next;
        Base_node *prev = this->prev;
        prev->next = next;
        next->prev = prev;
    }
};

template <typename T> struct List_node : public Base_node
{
    T val;

    List_node( ) = default;

    T *Node_valptr( ) { return &val; }
};

} // namespace internal

/**
     * @brief Iterator class is used to point to element in lists.
     */
template <typename T> struct List_iterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = ptrdiff_t;
    using self = List_iterator;
    using value_type = T;
    using reference = T &;
    using pointer = T *;

    internal::Base_node *node;

    List_iterator( ) = default;

    List_iterator(internal::Base_node *init) : node(init) {}

    /**
         * @brief Moving to next element in rane.
         * @return *this, reference to moved iterator.
         */
    self &operator++( )
    {
        node = node->next;
        return *this;
    }

    /**
         * @brief Moving to next element in rane(postfix).
         * @return An iterator that point to old value.
         */
    self operator++(int)
    {
        List_iterator temp = *this;
        node = node->next;
        return temp;
    }

    /**
         * @brief Moving to previous element in rane(postfix).
         * @return An iterator that point to old value.
         */
    self operator--(int)
    {
        List_iterator temp = *this;
        node = node->prev;
        return temp;
    }

    /**
         * @brief Moving to previous element in rane.
         * @return *this, reference to moved iterator.
         */
    self &operator--( )
    {
        node = node->prev;
        return *this;
    }

    /**
         * @brief Comparing two iterators. Checks if both are pointing to
         * the same element.
         * @param other Other iterator to compare with.
         * @return true if pointing at the same element, false otherwise.
         */
    bool operator==(const List_iterator &other) const
    {
        return node == other.node;
    }

    /**
         * @brief Opposite as in operator==()
         * @param other Other iterator to compare with.
         * @return true if pointing at  same element, false otherwise.
         */
    bool operator!=(const List_iterator &other) const
    {
        return node != other.node;
    }

    /**
         * @brief Referencing to value in element that is pointed by
         * iterator.
         * @return Reference to value.
         */
    reference operator*( ) const
    {
        return *static_cast<internal::List_node<T> *>(node)->Node_valptr( );
    }

    /**
         * @brief Referencing to members of element that is pointed by
         * iterator.
         * @return Pointer to member.
         */
    pointer operator->( ) const
    {
        return static_cast<internal::List_node<T> *>(node)->Node_valptr( );
    }
};

template <typename T> struct List_const_iterator
{
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using self = List_const_iterator;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;

    const internal::Base_node *node;

    List_const_iterator( ) = default;

    List_const_iterator(const internal::Base_node *init) : node(init) {}

    /**
         * @brief Moving to next element in rane.
         * @return *this, reference to moved iterator.
         */
    self &operator++( )
    {
        node = node->next;
        return *this;
    }

    /**
         * @brief Moving to next element in rane(postfix).
         * @return An iterator that point to old value.
         */
    self operator++(int)
    {
        List_const_iterator temp = *this;
        node = node->next;
        return temp;
    }

    /**
         * @brief Moving to previous element in rane(postfix).
         * @return An iterator that point to old value.
         */
    self operator--(int)
    {
        List_const_iterator temp = *this;
        node = node->prev;
        return temp;
    }

    /**
         * @brief Moving to previous element in rane.
         * @return *this, reference to moved iterator.
         */
    List_const_iterator &operator--( )
    {
        node = node->prev;
        return *this;
    }

    /**
         * @brief Comparing two iterators. Checks if both are pointing to
         * the same element.
         * @param other Other iterator to compare with.
         * @return true if pointing at the same element, false otherwise.
         */
    bool operator==(const List_const_iterator &other) const
    {
        return node == other.node;
    }

    /**
         * @brief Opposite as in operator==()
         * @param other Other iterator to compare with.
         * @return true if pointing at  same element, false otherwise.
         */
    bool operator!=(const List_const_iterator &other) const
    {
        return node != other.node;
    }

    /**
         * @brief Referencing to value in element that is pointed by
         * iterator.
         * @return Reference to value.
         */
    reference operator*( ) const
    {
        return static_cast<internal::List_node<T> *>(node)->val;
    }

    /**
         * @brief Referencing to members of element that is pointed by
         * iterator.
         * @return Pointer to member.
         */
    pointer operator->( ) const
    {
        return &(static_cast<internal::List_node<T> *>(node)->value);
    }
};

template <typename T> class List_base
{
protected:
    internal::List_node<T> Node;
    List_base( ) = default;

    ~List_base( )
    {
        internal::Base_node *curr = Node.next;
        while (curr != &Node )
        {
            internal::Base_node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};

/**
     * @brief Container type of two-way linked list.
     * @tparam T Type of elements that list contains.
     */
template <typename T> class list : protected List_base<T>
{
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = List_iterator<T>;
    using const_iterator = const List_iterator<T>;

    /**
         * @brief Constructor, sets all pointers to nullnext.
         */
    list( ) : List_base<T>( ), size_(0) {}

    /**
         * @brief Destructor, deletes all elements in list.
         */
    ~list( ) = default;
    /**
         * @brief Put new element in front of the list.
         * @param obj Value to copy in to the new element.
         */
    void push_front(const_reference obj) { insert(begin( ), obj); }
    /**
         * @brief Put new lement at back of the list.
         * @param obj Value to copy in to the new element.
         */
    void push_back(const_reference obj) { insert(end( ), obj); }

    /**
         * @brief Inserts new element at the specified position.
         * @param pos Position where to put new element.
         * @param val Value to be copied to the new element.
         * @return Iterator that points to newly inserted element.
         */
    iterator insert(const_iterator pos, const_reference obj)
    {
        auto temp = new internal::List_node<T>;
        temp->val = obj;
        temp->Node_hook(pos.node);
        size_++;
        return pos;
    }

    /**
         * @brief Deletes first element of list.
         */
    void pop_front( ) { erase(begin( )); }

    /**
         * @brief Deletes last element of list.
         */
    void pop_back( ) { erase(this->Node.prev); }

    /**
         * @brief Deletes element of list pointed by iterator.
         * @param iter Which element to delete.
         */
    void erase(iterator iter)
    {
        iter.node->Node_unhook( );
        delete iter.node;
        --size_;
    }

    /**
         * @brief Delete all elemnts which have given value.
         * @param val Value to delete from list.
         */
    void remove(const_reference val) // remove by value
    {
        for (iterator i = begin( ); i != end( ); ++i)
        {
            if (*i == val)
            {
                iterator temp = i++;
                erase(temp);
            }
        }
    }

    /**
         * @brief Remove elements if given condition is fulfilled
         * @param pred Object that predicates if element should be deleted
         */
    template <class Predicate>
    void remove_if(Predicate pred) // remove by predicate function(functor)
    {
        for (iterator i = begin( ); i != end( ); ++i)
        {
            if (pred(*i))
            {
                erase(i);
            }
        }
    }

    /**
         * @brief Returns how many elements list contains.
         * @return Number of elements in list.
         */
    size_t size( ) const { return size_; }

    /**
         * @brief Returns whether the list is empty.
         * @return true if empty, false otherwise.
         */
    bool empty( ) const { return this->Node == this->Node->prev; }

    /**
         * @fn sort(Compare fun)
         * @brief Sorts elements in the list.
         * @param comp Predicate that, taking two values of the same type as
         * in list, returns true if first should go before second, otherwise
         * false. Function pointer of function object.
         */
    template <class Compare>
    void sort(Compare comp) // sort by Comparator function(functor)
    {
        for (iterator i = begin( ); ++i != end( );)
        {
            iterator j_ = begin( );
            for (iterator j = begin( ); ++j_ != end( ); j++)
            {
                if (comp(*j, *j_))
                {
                    std::swap(*j, *j_);
                }
            }
        }
    }

    /**
         * @fn sort()
         * @brief Sorts elements in the list.
         */
    void sort( )
    {
        for (iterator i = begin( ); ++i != end( );)
        {
            iterator j_ = begin( );
            for (iterator j = begin( ); ++j_ != end( ); ++j)
            {
                if (*j < *j_)
                {
                    std::swap(*j, *j_);
                }
            }
        }
    }

    reference front( ) { return *static_cast<internal::List_node<T>*>(this->Node.next)->Node_valptr( ); }

    reference back( ) { return *static_cast<internal::List_node<T>*>(this->Node.prev)->Node_valptr(); }
    /**
         * @brief Returns iterator that points to first elemeint in the
         * list.
         * @return iterator to fist element of list.
         */
    iterator begin( ) { return iterator(this->Node.next); }

    /**
         * @brief Returns iterator that points to last elemeint in the list.
         * @return iterator to last element of list.
         */
    iterator end( ) { return iterator(&this->Node); }

private:
    size_t size_;
};
} // namespace aisd

#endif // LIST_H

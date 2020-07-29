/*
    HW06 Emire Korkmaz
*/

#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include <iostream>
#include <memory>
#include <exception>

using namespace std;

namespace Korkmaz{
    template<class T>
    class GTUIterator;

    template<class T>
    class GTUSetBase{

    public:
        GTUSetBase() :SIZE(30), setSize(0), baseIndex(0) {}
        int baseIndex;
        int SIZE;
        int setSize;
        shared_ptr<T> set=make_shared<T>(SIZE);
        shared_ptr<T> intersection=make_shared<T>(SIZE);
    protected:
        virtual bool empty()=0; //Test whether container is empty
        virtual int size()=0; // Return container size
        virtual int max_size()=0; // Return maximum size
        virtual GTUIterator<T> insert(T element) throw(exception)=0; // Insert element, throws exception std::bad_pafram if the element is already in the set
                                                    // returns an iterator pointing to either the newly inserted element
        virtual int erase(T element)=0; // Erase element, returns the number of elements erased.
        virtual void clear()=0; // Clear all content
        virtual GTUIterator<T> find(T element)=0; // Get iterator to element
        virtual int count(T element)=0; // Count elements with a specific value, returns 1 or 0 for the set type.
        virtual GTUIterator<T> begin()=0; // Return iterator to beginning
        virtual GTUIterator<T> end()=0; // Return iterator to end*/

    };
}
#endif

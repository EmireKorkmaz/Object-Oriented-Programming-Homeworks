/*
	HW06 Emire Korkmaz
*/

#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <iostream>
#include <memory>
#include <string>

using namespace std;
namespace Korkmaz{
	template<class T>
	class GTUIterator {
	public:
	    int index;
	    int SIZE;
	    shared_ptr<T> ptr=make_shared<T>(SIZE); // iterator pointer to calling object

	    GTUIterator(){
	        SIZE=30;
	        index=0;
	    }
	    T operator *(){ 
	        return *ptr.get();
	    }
	    T* operator->(){
	    	T* t = &(*ptr);
	    	return t;
	    }
	    GTUIterator<T> operator ++() // post-pre unutma
	    {
	        ptr.get()[++index];
	        return *this;
	    }
	    GTUIterator<T> operator --() // post-pre unutma
	    {
	        ptr.get()[--index];
	        return *this;
	    }
	    GTUIterator<T> operator = (const GTUIterator& right){
	        ptr=right.ptr;
	        return *this;
	    }
	    GTUIterator<T> operator = (shared_ptr<T> right){
	        ptr=right;
	        return *this;
	    }
	    bool operator ==(const GTUIterator& right){
	        return ptr==right.ptr;
	    }

	    friend ostream& operator<<(ostream& os, const GTUIterator<T>& other)
		{
		    os << other.ptr.get()[other.index] << endl;
		    return os;
		}

	};

}
#endif
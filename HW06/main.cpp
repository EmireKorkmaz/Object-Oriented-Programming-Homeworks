/*
	HW06 Emire Korkmaz

	In this homework, we were asked to write a templated class hierarchy for sets and maps.
	Base class is GTUSetBase which is pure virtual abstract class, first derived class is
	GTUSet which is	derived from GTUSetBase, and the second derived class is GTUMap class
	which is derived from GTUSet class. GTUSetBase has empty, size, max_size, insert, erase
	clear, find, count, begin and end functions' signatures and also a shared_ptr array which
	is called 'set' to hold the datas. There is also another class, GTUIterator which has a 'hasA'
	relation between GTUSetBase class, implements iterator operators such as *, ->, ++, --, =, and ==.
	GTUMap supposed to work like a STL Map but whenever I tried to create it, it failed. I believe
	that i did everything right, but no matter what i did, i couldn't make it work properly. That's
	why I didn't write a test code for GTUMap. But I did all the necesary implementations in GTUMap
	header. I also had another error that i couldn't solve, that's why i used only one header files
	instead of using header and implementation files seperately.
*/
#include <iostream>
#include <utility>

#include "GTUSetBase.h"
#include "GTUSet.h"
#include "GTUMap.h"


using namespace std;
using namespace Korkmaz;


// returns the intersection of the two sets.
template <class T>
shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>& obj1, const GTUSetBase<T>& obj2){
	int newSize = ((obj1.setSize > obj2.setSize) ? obj1.setSize : obj2.setSize);
	int index=0;
	shared_ptr<GTUSet<T> > temp(new GTUSet<T>()); // a shared_ptr object to hold the intersection
												 // of the two sets.
	for (int i = 0; i < newSize; ++i){
		for (int j = 0; j < newSize; ++j)
		{
			if (obj1.set.get()[i]==obj2.set.get()[j]){ // checks if there is a common element
				temp.get()->set.get()[index]=obj1.set.get()[i]; // adds common element to temp.
				index++;
			}
		}
	}
	temp.get()->baseIndex=index;
	temp.get()->setSize=newSize;
	return temp;
}

int main(int argc, char const *argv[])
{
	try{

		//GTUMap<int, int> mymap; this line gives the error that i couldn't solve.

	    GTUSet<char > mySet;
	    GTUSet<char> mySet2;

	    // empty function
	    cout<< "Is empty? " << mySet.empty()<<endl;
	   
	    // insert function
	    cout << "Insert function" << endl;
	    mySet.insert('a');
	    mySet.insert('h');
	    mySet.insert('d');
	    mySet2.insert('a');
	    mySet2.insert('d');
	    mySet2.insert('l');
	    mySet2.insert('e');
	    mySet2.insert('g');
	    mySet2.insert('k');

	    cout << "Set's elements: ";
	    for (int i = 0; i < mySet2.setSize; ++i)
	    	cout << mySet2.set.get()[i]<< " ";
	    cout << endl;

	    // setIntersection function
	    auto x = setIntersection(mySet, mySet2);

	    // size function
	    cout << "Size function" << endl;
	    cout << mySet2.size() << endl;

	    // printing intersection set
	    for (int i = 0; i < (x.get())->baseIndex; ++i)
	    	cout << x.get()->set.get()[i]<<endl;

	    // max_size function
	    cout << "max_size function:  " << mySet.max_size() << endl;
	   
	    // count function
	    cout << "Count function" << endl;
	    cout<< mySet.count('p')<<endl;

	    //find function
	    cout << "Find function: ";
	    GTUIterator<char> o = mySet2.find('g');

	    // ++ operator for the iterator
	    // before
	    cout << "++ operator for the iterator\nBefore: ";
	    cout << o.ptr.get()[o.index] << endl;
	    ++o;
	    //after
	    cout << "After:  ";
	    cout << o.ptr.get()[o.index] << endl;

	    // begin function
	    GTUIterator<char> g = mySet.begin();

	    // end function
	    GTUIterator<char> g1 = mySet.end();

	    // -- operator for the iterator
	    // before
	    cout << "-- operator for the iterator (for end function)\nBefore: ";
	    cout << g1.ptr.get()[g1.index] << endl;
	    --g1;
	    // after
	    cout << "After:  ";
	    cout << g1.ptr.get()[g1.index] << endl;
	    --g1;
	    // once again
	    cout << "Once again:  ";
	    cout << g1.ptr.get()[g1.index] << endl;

	    // erase function
	    mySet.erase('a');
	    mySet.erase('d');

	    // find function again
	    cout << "Find function:  ";
	    mySet.find('a');
	    cout << mySet.set.get()[0]<<endl;
	    // clear function
	    mySet2.clear();

	    // GTUIterator tests

	    cout << "*g:   " << *g << endl;
	    cout << "++g:  " << ++g << endl;
	    cout << "--g:  " << --g << endl;
	    cout << "g==g: " << (g==g1) << endl;
	}
	catch(exception e){
		cout << e.what() << endl;
		cout << "Exception has thrown.\n";
	}

    
    return 0;
}
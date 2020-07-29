/*
	HW06 Emire Korkmaz
*/

#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include <memory>
#include <string>

#include "GTUIterator.h"
#include "GTUSetBase.h"

using namespace std;
namespace Korkmaz{

    template<class T>
    class GTUSet: public GTUSetBase<T>{
    public:
        int index;
		GTUSet() :GTUSetBase<T>(),index(0)
		{}
        virtual bool empty(){         //Test whether container is empty
            return (GTUSetBase <T> ::setSize==0);
        }
        virtual int size(){         // Return container size
            return GTUSetBase <T> ::setSize;
        }
        virtual int max_size(){     // Return maximum size
            return GTUSetBase <T> ::SIZE;
        }
        virtual GTUIterator<T> insert(T element) throw (exception){     // Insert element, throws exception std::bad_pafram if the element is already in the set
                                                    // returns an iterator pointing to either the newly inserted element
            for (int i = 0; i <= size(); ++i){
                if (GTUSetBase <T> ::set.get()[i]==element)
                    throw invalid_argument("Element already exists.");
            }
            GTUSetBase <T> ::set.get()[index]=element;
            GTUSetBase <T> ::setSize++;
    
            index++;
            GTUIterator<T> g;
            g.ptr=GTUSetBase <T> ::set;
            g.SIZE=GTUSetBase <T> ::SIZE;
            g.index=index;
            return g;
        }
        virtual int erase(T element){                 // Erase element, returns the number of elements erased.

            for (int i = 0; i < GTUSetBase <T> ::setSize; ++i){

                if (GTUSetBase <T> ::set.get()[i]==element){
                    for (int j = i; j < GTUSetBase <T> ::setSize-1; ++j)
                    {
                        GTUSetBase <T> ::set.get()[j]=GTUSetBase <T> ::set.get()[j+1];
                    }
                    break;
                }
            }
            GTUSetBase <T> ::setSize--;
            return 1;
        }

        virtual void clear(){                         // Clear all content
            GTUSetBase <T> ::set.reset(new T);
            GTUSetBase <T> ::setSize=0;
            index=0;
        }
        virtual GTUIterator<T> find(T element){     // Get iterator to element
            GTUIterator<T> obj;
            obj.ptr=GTUSetBase <T> ::set;
            obj.index=GTUSetBase <T> ::setSize+2;     // gives index a value to test if it'll change
            for (int i = 0; i < GTUSetBase <T> ::setSize; ++i){
                if (GTUSetBase <T> ::set.get()[i]==element)
                    obj.index=i;
            }
            if (obj.index==GTUSetBase <T> ::setSize+2) // test to see if it's changed. if it is, it wont be size+2
                cerr << "not found\n";
            cout << obj.ptr.get()[obj.index] << " found.\n";
            return obj;
        }
        virtual int count(T element){                 	    // looks for given character in the set and returns the number of occurence
	    												// since given set is an actual set, number of occurence must be zero or one.
            for (int i = 0; i < size(); ++i){
                if (GTUSetBase <T> ::set.get()[i]==element)
                    return 1;
            }
            return 0;
        }
        virtual GTUIterator<T> begin(){             // Return iterator to beginning
            GTUIterator<T> obj;
            obj.index=0;
            obj.ptr = GTUSetBase <T> ::set;
            return obj;
        }
        virtual GTUIterator<T> end(){                 // Return iterator to end
            GTUIterator<T> obj;
            obj.index=GTUSetBase <T> ::setSize-1;
            obj.ptr = GTUSetBase <T> ::set;
            return obj;
        }
    };
}
#endif


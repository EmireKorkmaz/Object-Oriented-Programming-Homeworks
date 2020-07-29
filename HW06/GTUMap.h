/*
	HW06 Emire Korkmaz
*/

#ifndef GTUMAP_H
#define GTUMAP_H

#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <utility>

#include "GTUIterator.h"
#include "GTUSetBase.h"
#include "GTUSet.h"


using namespace std;

namespace Korkmaz{

	template< class K, class V >
	class GTUMap: public GTUSet <pair<K,V> > {

	public:
		int index;
		GTUMap() :GTUSet<pair<K,V> >(), index(0){
		}
		virtual GTUIterator<pair<K,V> > insert(pair<K,V> element) throw (exception) {     // Insert element, throws exception std::bad_pafram if the element is already in the set
                                                    // returns an iterator pointing to either the newly inserted element

			for (int i = 0; i <= size(); ++i){
                if (GTUSetBase <pair<K,V> > ::set.get()[i]==element)
                    throw invalid_argument("Element already exists.");
            }

            GTUSetBase <pair<K,V> > ::set.get()[index].first=element.first;
            GTUSetBase <pair<K,V> > ::set.get()[index].second=element.second;
            GTUSetBase <pair<K,V> > ::setSize++;
    
            index++;
            GTUIterator<pair<K,V> > g;
            g.ptr=GTUSetBase <pair<K,V> > ::set;
            g.SIZE=GTUSetBase <pair<K,V> > ::SIZE;
            g.index=index;
            return g;
        }

        virtual int size(){         // Return container size
            return GTUSetBase <pair<K,V> > ::setSize;
        }

        virtual int count(pair<K,V> element){    
        	int total=0;             // Count elements with a specific value, returns 1 or 0 for the set type.
            for (int i = 0; i < size(); ++i){
                if (GTUSetBase <pair<K,V> > ::set.get()[i].first==element.first && GTUSetBase <pair<K,V> > ::set.get()[i].second==element.second)
                    total++;
            }
            return total;
        }
        V& operator[] (const K& k){
        	for (int i = 0; i < size(); ++i){
                if (GTUSetBase <pair<K,V> > ::set.get()[i].first==k)
                    return GTUSetBase <pair<K,V> > ::set.get()[i].second;
            }
        }
	};
}
#endif
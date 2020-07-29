/*
 * HW07 141044043 Emire Korkmaz
 */
package javaapplication1;

import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import javafx.util.Pair;

public class GTUMap<K,V> extends GTUSet<javafx.util.Pair<K,V>> {
    Class<Pair<K,V> > type;
    
    public GTUMap(Class<Pair<K, V> > c) {
        super(c);
        this.type = c;
    }
    
    // Insert element, throws exception std::bad_pafram if the element is already in the set
    // returns an iterator pointing to either the newly inserted element
    @Override
    public GTUIterator< Pair<K,V> > insert(Pair<K,V> element) throws InvalidParameterException{
       // checks if element is already in the set                                                    
	for (int i = 0; i <= size(); ++i){
            if (set[i]==element)
                throw new InvalidParameterException();
        }
        
        Pair<K,V> p = new Pair<>(element.getKey(), element.getValue());
        
        set[index]=p;
        setSize++;
        
        GTUIterator<Pair<K, V> > g= new GTUIterator< >((Class<Pair<K, V> >) p.getClass() );
        
        g.ptr=set;
        g.index=index;
        g.size=setSize;
        index++;
        return g;
    }
    
    public GTUSetInt<Pair<K, V> > intersection(GTUSetInt<Pair<K, V> > obj2){        
        // creates two objects; one to return the other one to hold the data
        GTUMap<K, V > obj = new GTUMap<K, V >((Class<Pair<K,V> >) type.getComponentType());
        GTUMap<K, V> other= new GTUMap<K, V >((Class<Pair<K,V> >) type.getComponentType());
        
        other=(GTUMap<K, V>) obj2; // upcasting
        
        int tempIndex=0;
        // finds the max number of loop
        int newSize = ((this.setSize > other.size()) ? this.setSize : other.size());
        
        for (int i = 0; i < newSize; ++i){
            for (int j = 0; j < newSize; ++j)
            {
                // checks if there is a common element
                if (this.set[i].getKey()==other.set[j].getKey() && this.set[i].getValue()==other.set[j].getValue()){
                        obj.set[tempIndex]=other.set[j]; // adds common element to temp object.
                        tempIndex++;
                }
            }
        }
        obj.index=tempIndex;
        obj.setSize=newSize;
        return obj;
    }

    @Override
    public int erase(Pair<K,V> element){
        for (int i = 0; i < setSize; ++i){
            // finds the the element to erase and then erases
            if (set[i].getKey()==element.getKey() && set[i].getValue()==element.getValue()){
                for (int j = i; j < setSize-1; ++j){
                    set[j]=set[j+1];
                }
                break;
            }
        }
        setSize--;
        return 1;
    }
    @Override
    public int count(Pair<K,V> element){
        for(Pair<K,V> e : set)  // it if finds the element returns 1, since all the elements must be unique
            if(e.getKey()==element.getKey())
                return 1;
        return 0;          
    }
    @Override
    public GTUIterator<Pair<K, V> > find(Pair<K,V> element){
        
        GTUIterator<Pair<K, V> > obj= new GTUIterator< >((Class<Pair<K, V> >) element.getClass() );
        if(element==null){
           System.out.println(element + " not found\n");
            return obj; 
        }
        obj.ptr=set;
        obj.index=setSize+2;     // gives index a value to test if it'll change
        for (int i = 0; i <setSize; ++i){
            if (set[i].getKey()==element.getKey() && set[i].getValue()==element.getValue()){
                obj.index=i;
                break;
            }
        }
        if (obj.index==setSize+2){ // test to see if it's changed. if it is, it wont be size+2
            System.out.println(element + " not found\n");
            return obj;
        }
        System.out.println(obj.ptr[obj.index]+" found.\n");
        obj.size=setSize;
        return obj;
    }
    public V at(K k){ // returns the value of the given key.
        for(Pair<K,V> p : set){
            if(p.getKey()==k)
                return p.getValue();
        }
        return null;
    }
    
}

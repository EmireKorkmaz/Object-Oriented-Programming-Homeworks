/*
 * HW07 Emire Korkmaz
*/
package javaapplication1;

import java.lang.reflect.Array;
import java.lang.Class;

public class GTUIterator<T> {
    public int index;
    public T[] ptr;
    public int size;
    
    GTUIterator(Class<T> c){
        ptr = (T[]) Array.newInstance(c, 50);
        index=0;
        size=0;
    }
    //Returns true if this list iterator has more elements when traversing the list in the forward direction.
    boolean hasNext(){ 
        if(ptr[index+1]==null)
            return false;
        else
            return true;
    }
    //Returns true if this list iterator has more elements when traversing the list in the reverse direction.
    boolean hasPrevious(){
        if(index==0)
            return false;
        if(ptr[index-1]==null)
            return false;
        else
            return true;
    }
    //Returns the next element in the list and advances the cursor position.
    T next(){
        if(index==size)
            return ptr[index-1];
        if(hasNext()){
            index++;
            return ptr[index];            
        }   
        else
            return ptr[index]; // if iterator has not next object, returns
                                // its value.
    }
    //Returns the previous element in the list and moves the cursor position backwards.
    T previous(){
        if(index==0)
            return ptr[index];
        if(index==size){
            index--;
            return ptr[index-1];
        }
        if(hasPrevious()){
            index--;
            return ptr[index];            
        }
        else
            return ptr[index]; // if iterator has not previous object, returns
                                // its value.
    }
}

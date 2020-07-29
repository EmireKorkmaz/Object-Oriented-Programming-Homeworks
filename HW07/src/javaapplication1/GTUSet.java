/*
 * HW07 Emire Korkmaz
 */
package javaapplication1;

import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import java.util.Arrays;

public class GTUSet<T> implements GTUSetInt<T>{
    protected int index;
    public int setSize;
    public T[] set;
    protected int SIZE;
    Class<T> type;
    
    GTUSet(Class<T> c){
        this.type = c;
        SIZE=50;
        set = (T[]) Array.newInstance(c, SIZE);
        index=0;
        setSize=0;
        
    }
    // Insert element, throws exception std::bad_pafram if the element is already in the set
    // returns an iterator pointing to either the newly inserted element
    @Override
    public GTUIterator<T> insert(T element) throws InvalidParameterException{
        // checks if element is already in the set           
        for (int i = 0; i <= size(); ++i){
            if (set[i]==element)
                throw new InvalidParameterException();
        }
        set[index]=element;
        
        GTUIterator<T> obj= new GTUIterator<>((Class<T>) type.getClass());
        obj.index=index;
        obj.ptr=set;
        obj.size=setSize;
        setSize++;
        index++;
    
        return obj;
    }
    @Override
    public int erase(T element){
        for (int i = 0; i < setSize; ++i){
            // finds the the element to erase and then erases
            if (set[i]==element){
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
    public boolean empty(){
        if(setSize==0)
            return true;
        else
            return false;
    }
    @Override
    public int max_size(){
        return SIZE;
    }
    @Override
    public int size(){
        return setSize;
    }
    @Override
    public GTUIterator<T> find(T element){
        GTUIterator<T> obj= new GTUIterator<>((Class<T>) type.getClass());
        obj.ptr=set;
        obj.index=setSize+2;     // gives index a value to test if it'll change
        for (int i = 0; i <setSize; ++i){
            if (set[i]==element){
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
    @Override
    public int count(T element){
         // it if finds the element returns 1, since all the elements must be unique
        for(T e : set)
            if(e==element)
                return 1;
        return 0;          
    }
    @Override
    public void clear(){
        set = (T[]) Array.newInstance(type.getClass(), SIZE);
        setSize=0;
    }
    
   public GTUSetInt<T> intersection(GTUSetInt<T> obj2){
       // creates two objects; one to return the other one to hold the data
        GTUSet<T> obj= new GTUSet<>((Class<T>) type.getClass());
        GTUSet<T> other= new GTUSet<>((Class<T>) type.getClass());
        
        other=(GTUSet<T>) obj2; // upcasting
        int tempIndex=0;
        // finds the max number of loop
        int newSize = ((this.setSize > other.size()) ? this.setSize : other.size());
        
        T[] tempSet = (T[]) new Object[newSize];
        for (int i = 0; i < newSize; ++i){
                for (int j = 0; j < newSize; ++j)
                {
                    if (this.set[i]==other.set[j]){ // checks if there is a common element
                            tempSet[tempIndex]=other.set[j]; // adds common element to temp.
                            tempIndex++;
                    }
                }
        }
        // this code deletes all the null's from the array for a cleaner array
        int tempIndex2=0;
        T[] tempSet2 = (T[]) new Object[tempIndex];
        for(T s: tempSet){
            if(s !=null){
                tempSet2[tempIndex2]=s;
                tempIndex2++;
            }
        }
        obj.index=tempIndex;
        obj.set=tempSet2;
        obj.setSize=newSize;
        return obj;
    }
    
    @Override
    public GTUIterator<T> begin(){
        GTUIterator<T> obj= new GTUIterator<>((Class<T>) type.getClass());
        obj.index=0;
        obj.ptr=set;
        obj.size=setSize;
        return obj;
    }
    @Override
    public GTUIterator<T> end(){
        GTUIterator<T> obj= new GTUIterator<>((Class<T>) type.getClass());
        obj.index=setSize;
        obj.ptr=set;
        obj.size=setSize;
        return obj;
    }
    public String toString(){
        return Arrays.toString(set); // prints the array
    }
}

/*
 * HW07 Emire Korkmaz
 */
package javaapplication1;

import java.security.InvalidParameterException;

public interface GTUSetInt<T> {
    
    public boolean empty(); //Test whether container is empty
    public int size(); //Return container size
    public int max_size(); //Return maximum size
    public GTUIterator<T> insert(T element); //Insert element, throws exception.
    public int erase(T element)throws InvalidParameterException; // Erase element
    public GTUSetInt<T> intersection(GTUSetInt<T> obj2); // intersection, the returned set is the intersection of this set and the given set
    public void clear(); //Clear all content
    public GTUIterator<T> find(T element); //Get iterator to element
    public int count(T element); //Count elements with a specific value
    public GTUIterator<T> begin(); //Return iterator to beginning
    public GTUIterator<T> end(); // Return iterator to end
    
}

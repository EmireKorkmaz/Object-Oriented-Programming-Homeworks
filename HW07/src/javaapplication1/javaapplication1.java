/*
    HW07 Emire Korkmaz

    In this homework, I wrote a generic class hierarchy for sets and maps for Java.
    -GTUSetInt<T> is a Java interface with the following methods empty, size,
    max_size, insert, intersection, erase, clear, find, count, begin and end
    -The class GTUSet<T> implements the GTUSetInt interface. It will keep its
    data using Java arrays. 
    -The class GTUMap<K, V> extends from GTUSet< javafx.util.Pair <K, V> >
    implements the at method.
    - The class GTUIterator implements hasNext, hasPrevious, next and previous
    methods.
 */
package javaapplication1;
import java.io.*;
import java.lang.reflect.Array;
import javafx.util.Pair;

public class javaapplication1 {

    public static void main(String[] args) {
        try{
        System.out.println("---GTUMap Test---\n");

        Pair<Integer,Integer> p = new Pair<>(1,1);
        Pair<Integer,Integer> p1 = new Pair<>(7,7);
        Pair<Integer,Integer> p2 = new Pair<>(2,5);
        Pair<Integer,Integer> p3 = new Pair<>(4,9);
        Pair<Integer,Integer> p4 = new Pair<>(0,9);

        GTUMap<Integer, Integer> myMap = new GTUMap<Integer, Integer>((Class<Pair<Integer, Integer>>) p.getClass());
        
        // insert function
        myMap.insert(p);
        myMap.insert(p1);
        myMap.insert(p2);
        myMap.insert(p3);
        //myMap.insert(p3); // this line test for exception
                            // if we remove the comment it'll throw an exception

      // empty function
        System.out.println("Is empty? " + myMap.empty());

        // size function
        System.out.println("Size= " + myMap.size());

        // max_size function
        System.out.println("Maximum size= " + myMap.max_size());

        // find function
        myMap.find(p);
        // at function
        System.out.println("at "+  myMap.at(4));

        //creating GTUIterator object for return values.
        GTUIterator<Pair<Integer, Integer> > mapIter = new GTUIterator<>((Class<Pair<Integer, Integer>>) p.getClass());

        mapIter = myMap.insert(p4);
        myMap.find(p4);

         // erase function
        // before
        myMap.find(p1);
        myMap.erase(p1);
        myMap.find(p1); // after p1 was erased

        // count function
        System.out.println(myMap.count(p3));

        // begin function
        mapIter = myMap.begin();

        // test for GTUIterator object's previous and next functions after begin function
        System.out.println("Does it have previous? " + mapIter.hasPrevious()+" Does it have next? " +mapIter.hasNext());

        // test for GTUIterator object's previous and next functions after begin function
        System.out.println(mapIter.previous());
        System.out.println(mapIter.next());

        // end function
        mapIter = myMap.end();

        // test for GTUIterator object's previous and next functions after end function
        System.out.println("Does it have previous? " + mapIter.hasPrevious()+" Does it have next? " +mapIter.hasNext());

        // test for GTUIterator object's previous and next functions after end function
        System.out.println(mapIter.previous());
        System.out.println(mapIter.next());

        // clear function
        myMap.clear();
        myMap.find(p); // caling find function after calling clear function

        System.out.println("---GTUSet Test---\n");

        GTUSet<String> x = new GTUSet<>(String.class);
        GTUSet<String> y = new GTUSet<>(String.class);
        GTUSet<String> z = new GTUSet<>(String.class);

        // insert function
        x.insert("a");
        x.insert("s");
        x.insert("d");
        x.insert("f");
        x.insert("g");
        
        y.insert("a");
        y.insert("t");
        y.insert("d");
        
        // intersection function
        z =(GTUSet<String>) y.intersection(x);
        
        System.out.println("Intersection\n" + z.toString());
        
        // empty function
        System.out.println("Is empty? " + x.empty());

        // size function
        System.out.println("Size= " + x.size());

        // max_size function
        System.out.println("Maximum size= " + x.max_size());

        // count function
        System.out.println(x.count("a"));

        //creating GTUIterator object for return values.
        GTUIterator<String> setIter = new GTUIterator<>(String.class);

        // begin function
        setIter = x.begin();

        // test for GTUIterator object's previous and next functions after begin function
        System.out.println("Does it have previous? " + setIter.hasPrevious()+" Does it have next? " +setIter.hasNext());

        // test for GTUIterator object's previous and next functions after begin function
        System.out.println(setIter.previous());
        
        System.out.println(setIter.next());

        // end function
        setIter = x.end();
        // test for GTUIterator object's previous and next functions after end function
        System.out.println("Does it have previous? " + setIter.hasPrevious()+" Does it have next? " +setIter.hasNext());

        // test for GTUIterator object's previous and next functions after end function
        System.out.println(setIter.previous());
        System.out.println(setIter.next());

        // erase function
        // before erase function
        x.find("d");
        x.erase("d");
        x.find("d"); // after "d" was erased
       
        // clear function
        x.clear();
        x.find("g"); // after clear function
        x.find("a"); // after clear function

        System.out.println("Is empty? " + x.empty());
        
        x.insert("a");
        x.insert("s");
        x.insert("d");
        x.insert("f");
        x.insert("g");
        // because if this line, insert function throws an exception
        x.insert("a");
       }
        catch(Exception e){
            System.out.println("Element is already in the set.");
        }
    }  
    
}

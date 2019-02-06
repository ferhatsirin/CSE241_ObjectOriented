/**
 * Iterator class for GTUSet and GTUMap
 * @author ferhat
 * @param <T> T is type of set
 */
public class GTUIterator<T> {
    
    private int cursor;
    private final int size;
    private final T[] data;
    
    /**
     * Constructor to set parameters 
     * @param d for data
     * @param s for size
     * @param c for cursor 
     */
    public GTUIterator(T[] d,int s,int c){
        data =d;
        size =s;
        cursor = c;
    }
    
    /**
     * Compare 2 class to look if they are equal
     * @param other
     * @return true if they are equal otherwise false
     */
    public boolean equals(GTUIterator other){
    
        if(other == null)
            return false;
        return ((data == other.data) && (size == other.size) && (cursor == other.cursor));
    }
    
    /**
     * To look if Iteration has more elements 
     * @return true if There are more elements otherwise false
     */
    public boolean hasNext(){
       
        return cursor < size;
    }

    /**
     * To look if Iteration has more elements in the reverse direction
     * @return true if there are more elements in the reverse direction otherwise false
     */
    public boolean hasPrevious(){
      
        return 0 < cursor;
    }
       
    /**
     * 
     * @return next element The cursor points 
     */
    public T next(){
         
        return data[cursor++];
    }

    /**
     *
     * @return previous elements The cursor points
     */
    public T previous(){
       
        return data[cursor--];
    }
    
}


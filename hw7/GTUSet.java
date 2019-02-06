import java.security.InvalidParameterException;

/**
 * Create a set whose type is T 
 * @author ferhat
 * @param <T> T is type of set
 */
public class GTUSet<T> implements GTUSetInt<T> {
    
    private final T[] data;
    private int Dsize; 
    private final int Dcapacity =100;
    
    /**
     * Constructor of GTUSet 
     */
    public GTUSet(){
        data = (T[])new Object[Dcapacity];
        Dsize =0;
    }
    
    /**
     *
     * @return true if The set is empty otherwise false.
     */
    @Override
    public boolean empty(){
        
        return Dsize == 0;
    }
    
    /**
     *
     * @return size of the Set
     */
    @Override
    public int size(){
   
        return Dsize;
    }
    
    /**
     *
     * @return maximum size that Set can have
     */
    @Override
    public int max_size(){
     
        return Dcapacity;
    }
    
    /**
     *
     * @param element which is type of T added to set 
     * @throws InvalidParameterException If element is already in set then throws exception
     */
    @Override
    public void insert(T element)throws InvalidParameterException{
    
        if(find(element).equals(end())){ // if argument does not exist then insert it
        
            if(Dsize < Dcapacity){
 
                data[Dsize] =element;
                ++Dsize;
            }
            else{
            
                System.err.println("Capacity is full!!!");
            }
        
        }
        else{
            throw new InvalidParameterException();     
        }
    }
    
    /**
     *
     * @param other set to compare with itself 
     * @return Set of intersection of itself and other set
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){
    
        GTUSetInt<T> temp;
        temp = new GTUSet<>();
        for(int i=0;i<Dsize ;++i){
        
            if(!other.find(data[i]).equals(other.end())){ // looking if element exist in both sets
            
                temp.insert(data[i]);
            }      
        }        
        return temp;
    }

    /**
     *  if element exist in the set then erase it    
     * @param element to be erased
     */
    @Override
    @SuppressWarnings("empty-statement")
    public void erase(T element){
        
        if(!find(element).equals(end())){  // if it is in the set then erase it
        
            int i=0;
            for(;!data[i].equals(element) ;++i); // looking for its index
            
            for(;i<Dsize-1;++i){
            
                data[i] =data[i+1];
            }
            --Dsize;   
        }
    
    }

    /**
     * Delete all elements in the set 
     * set Size to 0
     */
    @Override
    public void clear(){
        Dsize =0;
    }
    
    /**
     *
     * @param element that is looked
     * @return because all elements  in a set are unique   if element is in the set then return 1 otherwise 0 
     */
    @Override
    public int count(T element){
    
        if(!find(element).equals(end())){  
                                            
            return 1;
        }
        else{ 
            return 0;
        }
    }
    
    /**
     *
     * @param element to be found
     * @return Iterator if exists 
     */
    @Override
    public GTUIterator find(T element){
        int i =0;   
        for(;i<Dsize;++i){
        
            if(data[i].equals(element)){
            
                break;
            }
        }
        return new GTUIterator(data,Dsize,i);
    }

    /**
     *
     * @return Iterator for first element of set
     */
    @Override
    public GTUIterator begin(){
        return new GTUIterator(data,Dsize,0);
    }

    /**
     *
     * @return Iterator for end of the set
     */
    @Override
    public GTUIterator end(){
    
        return new GTUIterator(data,Dsize,Dsize);
    }
}


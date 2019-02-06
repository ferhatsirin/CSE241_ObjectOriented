import javafx.util.Pair;

/**
 * Make a map class
 * @author ferhat
 * @param <K> first type for Map
 * @param <V> Second type for Map
 */
public class GTUMap<K,V> extends GTUSet<Pair<K,V>> {
    
     /**
     *
     * @return value for corresponding key if exists 
     */
    V at(K k){
        
        Pair<K,V> temp =null;
        GTUIterator<Pair<K,V>> p =begin();
        while(p.hasNext()){  // looking for that element
            temp =p.next();
            if(temp.getKey() == k){        
                break;
            }
        }
        
        return temp.getValue();
    }
    
}


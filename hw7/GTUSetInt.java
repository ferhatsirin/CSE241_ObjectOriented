/**
 *
 * @author ferhat
 * @param <T>
 */
import java.security.InvalidParameterException;

public interface GTUSetInt<T> {
    boolean empty();
    int size();
    int max_size();
    void insert(T element)throws InvalidParameterException;
    GTUSetInt<T> intersection(GTUSetInt<T> other);
    void erase(T element);
    void clear();
    int count(T element);
    GTUIterator find(T element);
    GTUIterator begin();
    GTUIterator end();

}


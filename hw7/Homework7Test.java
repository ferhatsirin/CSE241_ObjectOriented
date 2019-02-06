/**
 *
 * @author ferhat
 */
import javafx.util.Pair;
import java.security.InvalidParameterException;

public class Homework7Test {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        System.out.println("GTUSet tests ");
        
        GTUSet<Integer> s1 =new GTUSet<>();
        System.out.printf("s1 size at the beginning :%d\n", s1.size());
        s1.insert(2);
        s1.insert(5);
        s1.insert(8);
        s1.insert(11);
        System.out.printf("s1 size after insertion :%d\n", s1.size());
    
        GTUIterator<Integer> setP =s1.begin();
        System.out.println("Set s1's elements :");
        while(setP.hasNext()){
        
            System.out.println(setP.next());
        }
        System.out.println();
        
        GTUSet<Integer> s2 =new GTUSet<>();
    
        s2.insert(3);
        s2.insert(5);
        s2.insert(11);
        s2.insert(34);
        s2.insert(55);
        
        System.out.printf("s2 size after insertion :%d\n", s2.size());
    
        s2.erase(34);
        
        System.out.printf("s2 size after erasing one element :%d\n", s2.size());

        setP =s2.begin();
        System.out.println("Set s2's elements :");
        while(setP.hasNext()){
        
            System.out.println(setP.next());
        }
        System.out.println();
        
        GTUSetInt<Integer> setInter =s1.intersection(s2);
        setP =setInter.begin();
        System.out.println("Intersection of s1 and s2 :");
        while(setP.hasNext()){
       
            System.out.println(setP.next());
        }
        System.out.println();
        
        System.out.println("Adding Set s1 same element '5' ");
        try{
        
            s1.insert(5);
        }
        catch(InvalidParameterException exp){
        
            System.out.println("Invalid Parameter Exception get caught!!!\n");
        }
        
        s2.clear();
        
        System.out.printf("Size of s2 after calling its clear() method :%d\n", s2.size());
        System.out.println();
        
        System.out.println("GTUMap tests");
        
        GTUMap<String,Integer> m1 =new GTUMap<>();
        
        m1.insert(new Pair<>("ABC",4));
        m1.insert(new Pair<>("GTU",7));
        m1.insert(new Pair<>("PHP",9));
        m1.insert(new Pair<>("CPP",12));
        
        GTUMap<String,Integer> m2 =new GTUMap<>();
   
        m2.insert(new Pair<>("MAP",3));
        m2.insert(new Pair<>("ABC",4));
        m2.insert(new Pair<>("GTU",9));
        m2.insert(new Pair<>("CPP",12));
        m2.insert(new Pair<>("FHT",22));
        
        System.out.printf("Map m1 size :%d\n",m1.size());
        
        GTUIterator<Pair<String,Integer> > mapP =m1.begin();
        System.out.println("Map m1's elements :");
        while(mapP.hasNext()){
        
            System.out.println(mapP.next());
        }
        System.out.println();
        
        mapP =m2.begin();
        System.out.println("Map m2's elements :");
        while(mapP.hasNext()){
        
            System.out.println(mapP.next());
        }
        System.out.println();
        
        GTUSetInt<Pair<String,Integer> > mapInter =m1.intersection(m2);
        mapP =mapInter.begin();
        while(mapP.hasNext()){
         System.out.println(mapP.next());
        }
        System.out.println();
        System.out.println("Adding Map m2 same element '(GTU,9)' ");
        try{
        
            m2.insert(new Pair<>("GTU",9));
        }
        catch(InvalidParameterException exp){
        
            System.out.println("Invalid Parameter Exception get caught!!!\n");
        }
        
        m2.erase(new Pair<>("FHT",22));
        
        System.out.printf("Map m2 size after erasing '(FHT,22)' element :%d\n", m2.size());
        
        m1.clear();
        
        System.out.printf("Size of m1 after calling its clear() method :%d\n", m1.size());
        
    }
    
}


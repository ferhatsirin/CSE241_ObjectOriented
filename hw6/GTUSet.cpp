#include "GTUSet.h"
#include<iostream>
using namespace std;
namespace GTUFerhat{
    
    template<class T>
    GTUSet<T>::GTUSet():GTUSetBase<T>(),data(new T[100],default_delete<T[]>()),Dsize(0),Dcapacity(100){
        
    }
    
    template<class T>
    bool GTUSet<T>::empty()const{
        if(Dsize == 0){
            return true;
        }
        else
            return false;
    }
    
    template<class T>
    int GTUSet<T>::size()const{
        return Dsize;
    }
    
    template<class T>
    int GTUSet<T>::max_size()const{
        return Dcapacity;  // capacity of array of shared_ptr 
    }
    
    template<class T>
    void GTUSet<T>::insert(const T& v)throw (invalid_argument){ // if argument is already in set then throw invalid _argument 
         
        if(find(v) == end()){  // if argument does not exist then insert it
          
            if(Dsize <= Dcapacity ){
                int i;
                for(i=0;i<Dsize;++i){   // to make them in order
                    if(v < data.get()[i]){
                        break;
                    }
                }
                for(int j =Dsize;i < j;--j){
                    data.get()[j] =data.get()[j-1];
                }
                data.get()[i] =v;
                ++Dsize;
            }
            else{
                cerr<<"Capacity is full\n";
            }
        }
        else{
            throw invalid_argument("The element is already in set!!!\n");
        }
    } 
    
    template<class T>
    void GTUSet<T>::erase(const T& v){
        if(find(v) != end()){ // if it is in the set then erase it
            int i;
            for(i=0;data.get()[i] !=v ;++i); // looking for its index
            
            for(;i < Dsize-1 ;++i){
              data.get()[i] = data.get()[i+1];
          }          
          --Dsize;
        }
    }
    
    template<class T>
    void GTUSet<T>::clear(){
        Dsize =0;
    }
    
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::find(const T& v){ // return type is GTUIterator 
        int i;                                                       
        for(i=0;i<Dsize;++i){
            if(data.get()[i] == v){
                break;
            }
        }
        typename GTUSetBase<T>::GTUIterator temp(&data.get()[i]);  // making temp GTUIterator obj to return
        return temp;
    }
    
    template<class T>
    int GTUSet<T>::count(const T& v){ // because all elements  in a set are unique  
        if(find(v) !=end()){          // if element is in the set then return 1 otherwise 0
            return 1;
        }
        else
            return 0;
    }
    
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::begin(){ // returning the address of first element type of GTUIterator
        
        typename GTUSetBase<T>::GTUIterator temp(&data.get()[0]);
    
        return temp;
    }
    
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::end(){ // returning the address of last+1  element type of GTUIterator
        
   
        typename GTUSetBase<T>::GTUIterator v(&data.get()[Dsize]);
        return v;
    }
    
}

#include "GTUSetBase.h"

namespace GTUFerhat{
    
    template<class T>
    GTUSetBase<T>::GTUSetBase(){
    
    }
    
    template<class T>
    GTUSetBase<T>::GTUIterator::GTUIterator(){
    
    }
    template<class T>
    GTUSetBase<T>::GTUIterator::GTUIterator(T* v):pData(v){
    
    }
    
    
    template<class T>
    T GTUSetBase<T>::GTUIterator::operator*() const{
    
        return *pData;
    }
    
    template<class T>
    T* GTUSetBase<T>::GTUIterator::operator->()const{
    
        return pData;
    }
   
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSetBase<T>::GTUIterator::operator++(){ // pre inc..
       
        ++pData;
        
        return *this; 
    }
    template<class T>
   typename GTUSetBase<T>::GTUIterator GTUSetBase<T>::GTUIterator::operator++(int ignore){ //post inc
    
        GTUIterator temp =*this;
        ++pData;
        
        return temp; 
    }
    
    template<class T>
    typename GTUSetBase<T>::GTUIterator  GTUSetBase<T>::GTUIterator::operator--(){ // pre dec..
    
        --pData;
        
        return *this;
    }
    
    template<class T>
    typename GTUSetBase<T>::GTUIterator  GTUSetBase<T>::GTUIterator::operator--(int ignore){ //post dec...
    
        GTUIterator temp =*this;
        --pData;
        return temp;
    }
    
    template<class T>
    typename GTUSetBase<T>::GTUIterator& GTUSetBase<T>::GTUIterator::operator=(const GTUIterator& obj){
    
        pData =obj.pData;
        return *this;
    }
    
    template<class T>
    bool GTUSetBase<T>::GTUIterator::operator==(const GTUIterator& obj)const{
        return pData == obj.pData;
    }
    
    template<class T>
    bool GTUSetBase<T>::GTUIterator::operator!=(const GTUIterator& obj)const{
        return !(*this == obj);
    }
}



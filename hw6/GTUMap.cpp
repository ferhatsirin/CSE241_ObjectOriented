#include "GTUMap.h"

namespace GTUFerhat{

    template<class K,class V>
    GTUMap<K,V>::GTUMap():GTUSet<pair<K,V> >(){
    
    }
    
    template<class K,class V>
    V& GTUMap<K,V>::operator[](const K& k){
        
        typename GTUMap<K,V>::GTUIterator p =this->begin(); 
        for(;p !=this->end();++p){ // looking for that element
        
            if(p->first == k){
                return p->second;
            }
        }
        this->insert(pair<K,V>(k,V())); // if k value does not exist then insert new one and return
        return p->second;
    }

}



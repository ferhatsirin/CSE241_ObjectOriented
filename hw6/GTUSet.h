#ifndef GTUSET_H
#define GTUSET_H
#include"GTUSetBase.h"
#include"GTUSetBase.cpp"
#include<memory>
using namespace std;

namespace GTUFerhat{
    template<class T>
    class GTUSet:public GTUSetBase<T> {
    public:
        
        GTUSet();
        bool empty()const;
        int size()const; 
        int max_size()const;       
        void insert(const T& v)throw(invalid_argument);    
        void erase(const T& v);
        void clear();
        typename GTUSetBase<T>::GTUIterator find(const T& v);
        int count(const T& v);
        typename GTUSetBase<T>::GTUIterator begin();
        typename GTUSetBase<T>::GTUIterator end();

    private:
        shared_ptr<T> data;
        int Dsize;
        int Dcapacity;

    };

}
#endif /* GTUSET_H */


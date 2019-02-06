#ifndef GTUSETBASE_H
#define GTUSETBASE_H
#include<memory>
using namespace std;

namespace GTUFerhat{
    template<class T>
    class GTUSetBase {
        
        public:
            GTUSetBase();
            virtual bool empty()const =0;
            virtual int size()const=0;
            virtual int max_size()const =0;
            virtual void insert(const T& v)throw(invalid_argument)=0;
            virtual void erase(const T& v)=0;
            virtual void clear()=0;
            
            class GTUIterator;
            
            virtual GTUIterator find(const T& v) =0;
            virtual int count(const T& v) =0;
            virtual GTUIterator begin() =0;
            virtual GTUIterator end() =0;
            
            class GTUIterator{
            public:
                GTUIterator();
                GTUIterator(T* v);
                T operator*()const;
                T* operator->()const;
                GTUIterator operator++(); // pre inc..
                GTUIterator operator++(int ignore); //post inc
                GTUIterator operator--(); // pre dec..
                GTUIterator operator--(int ignore); //post dec...
                GTUIterator& operator=(const GTUIterator& obj);
                bool operator==(const GTUIterator& obj)const;
                bool operator!=(const GTUIterator& obj)const;
                
            private:
                T* pData;        
            
            };
            
        private:

    };

}

#endif /* GTUSETBASE_H */


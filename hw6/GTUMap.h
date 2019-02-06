#ifndef GTUMAP_H
#define GTUMAP_H
#include"GTUSet.h"
#include"GTUSet.cpp"

namespace GTUFerhat{
    template<class K,class V>
    class GTUMap:public GTUSet<pair<K,V> > {
    public:
        GTUMap();
        V& operator[](const K& k);
   
    private:

    };

}

#endif /* GTUMAP_H */


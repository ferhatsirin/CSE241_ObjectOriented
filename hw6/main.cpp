#include<iostream>
#include<string>
#include"GTUMap.h"
#include"GTUMap.cpp"

using namespace std;
using namespace GTUFerhat;

template<class T>
shared_ptr<GTUSetBase<T> > setIntersection(GTUSetBase<T>& obj1, GTUSetBase<T>& obj2); // returns the intersection set of two set or map 

int main(void) {
    
    // GTUSet tests  
    cout<<"GTUSet tests "<<endl;
    GTUSet<int> s1;
    
    cout<<"s1 size at the beginning :"<<s1.size()<<endl;
    
    s1.insert(2);
    s1.insert(5);
    s1.insert(8);
    s1.insert(11);
    
    cout<<"s1 size after inserting :"<<s1.size()<<endl;
    
    GTUSetBase<int>::GTUIterator setP =s1.begin();
    cout<<"Set s1's elements :"<<endl;
    
    for(;setP != s1.end();++setP){ // printing s1 elements 
        cout<<*setP<<" ";
    }
    cout<<endl;
    
    GTUSet<int> s2;
    
    s2.insert(3);
    s2.insert(44);
    s2.insert(5);
    s2.insert(11);
    s2.insert(34);
    cout<<"s2 size after inserting :"<<s2.size()<<endl;
    
    s2.erase(34);
    
    cout<<"s2 size after erasing one element :"<<s2.size()<<endl;
    
    
    setP =s2.begin();
    cout<<"Set s2's elements :"<<endl;
    
    for(;setP != s2.end();++setP){ // printing s2 elements 
        cout<<*setP<<" ";
    }
    cout<<endl;
    
    shared_ptr<GTUSetBase<int> > setInter =setIntersection(s1,s2);
    cout<<"Intersection of s1 and s2 :"<<endl;
    setP =setInter->begin();
    for(;setP != setInter->end();++setP){ // printing intersection of s1 and s2 
        cout<<*setP<<" ";
    }
    cout<<endl;
    
    cout<<"Adding Set s1 same element '5' "<<endl;
    try{
        s1.insert(5);
    }
    catch(exception& excp){
        cerr<<"Exception get caught!!! \n";
        cerr<<excp.what()<<endl;
    }
    
    s2.clear();
    
    cout<<"Size of s2 after calling its clear() function :"<<s2.size()<<endl;
    
    cout<<endl;
    // GTUMap tests 
    cout<<"GTUMap tests "<<endl;
    
    GTUMap<string,int> m1; 
    
    m1.insert(pair<string,int>("ABC",4));
    m1.insert(pair<string,int>("GTU",7));
    m1.insert(pair<string,int>("PHP",9));
    m1.insert(pair<string,int>("CPP",12));
    
    GTUMap<string,int> m2;
    m2.insert(pair<string,int>("MAP",2));
    m2.insert(pair<string,int>("ABC",4));
    m2.insert(pair<string,int>("GTU",9));
    m2.insert(pair<string,int>("FHT",22));
    m2.insert(pair<string,int>("CPP",12));
    
    cout<<"Map m1 size :"<<m1.size()<<endl;
    
    GTUSetBase<pair<string,int> >::GTUIterator mapP =m1.begin();
    cout<<"Map m1's elements :"<<endl<<endl;
    for(;mapP != m1.end();++mapP){   // printing Map m1's elements 
     
        cout<<mapP->first<<" "<<mapP->second<<endl;
    }
    
    mapP =m2.begin();
    cout<<"Map m2's elements :"<<endl<<endl;
    for(;mapP != m2.end();++mapP){
     
        cout<<mapP->first<<" "<<mapP->second<<endl; // printing Map m2's elements 
    } 
    
    cout<<"Intersection of Map m1 and Map m2 's elements: "<<endl<<endl;
    shared_ptr<GTUSetBase<pair<string,int> > > intersectionMap =setIntersection(m1,m2);
    GTUSetBase<pair<string,int> >::GTUIterator iteratorMap =intersectionMap->begin();
    for(;iteratorMap != intersectionMap->end();++iteratorMap){                 // printing intersection of m1 and m2 elements 
        cout<<iteratorMap->first<< " "<<iteratorMap->second<<endl;
    }


    return 0;
}
 
template<class T>
shared_ptr<GTUSetBase<T> > setIntersection(GTUSetBase<T>& obj1, GTUSetBase<T>& obj2){
    shared_ptr<GTUSetBase<T> > temp(new GTUSet<T>());
    
    for(typename GTUSetBase<T>::GTUIterator p =obj1.begin();p !=obj1.end();++p){
        if(obj2.find(*p) != obj2.end()) {
            temp->insert(*p);        
        }
    
    }
    return temp;
}

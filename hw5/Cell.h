#ifndef CELL_H
#define CELL_H
#include<iostream>
using namespace std;

namespace GTUFerhat{
    
class Cell {
    
    public:
        Cell();
        void setPosition(char pos);
        void setRow(int row);
        void setType(char type);
        
        char getPosition()const;
        int getRow()const;
        char getType()const;
        
        bool operator==(const Cell& other)const;
        bool operator!=(const Cell& other)const;
        Cell& operator++(); //pre increment
        const Cell operator++(int ignoreMe); //post increment
        Cell& operator--(); //pre decrement
        const Cell operator--(int ignoreMe); //post decrement
        friend ostream& operator<<(ostream& outStream,const Cell& outCell);
        friend istream& operator>>(istream& inputStream,Cell& inCell);
        
    private:
        
        char position;
        int row;
        char type;

};

}

#endif /* CELL_H */



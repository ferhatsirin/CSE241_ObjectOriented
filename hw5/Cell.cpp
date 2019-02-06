#include "Cell.h"

namespace GTUFerhat{
    Cell::Cell(){
    
    }
    
    void Cell::setPosition(char pos){
         position =pos;
    } 
    void Cell::setRow(int rowNum){
         row=rowNum;
    }
    void Cell::setType(char letter){
         type =letter;
    }
    char Cell::getPosition()const{      
            return position;
    }
    int Cell::getRow()const{
        return row;
    }
      
    char Cell::getType()const{
        return type;
    }

    bool Cell::operator==(const Cell& other)const{
    
      return (row==other.row)&&(position==other.position)&&(type==other.type);
    }
    bool Cell::operator!=(const Cell& other)const{
    
       return !(*this ==other);
    }
    Cell& Cell::operator++(){ //pre increment
      if(getType()=='.')
          setType('X');
      else if(getType() =='X') // means user1
         setType('O'); //to user2
      else if(getType() =='O')
         setType('C');
      else if(getType()=='C')
         setType('.');
    
     return *this;
    }

    const Cell Cell::operator++(int ignoreMe){ //post increment
    
       Cell temp =*this;  
    
       if(getType()=='.')
          setType('X');
       else if(getType() =='X') // means user1
          setType('O'); //to user2
       else if(getType() =='O')
         setType('C');
       else if(getType()=='C')
         setType('.');
    
       return temp; //returning a copy
    }
    Cell& Cell::operator--(){ //pre decrement
    
       if(getType()=='.') //means empty
          setType('C'); // to comp.
       else if(getType() =='C') // means user1
          setType('O'); //to user2
       else if(getType() =='O')
        setType('X');
       else if(getType()=='X')
         setType('.');
    
       return *this;
    }

    const Cell Cell::operator--(int ignoreMe){ //post decrement
         Cell temp =*this;
         if(getType()=='.') //means empty
            setType('C'); // to comp.
         else if(getType() =='C') // means user1
           setType('O'); //to user2
         else if(getType() =='O')
           setType('X');
         else if(getType()=='X')
           setType('.');
    
         return temp; // returning a copy
    }
    ostream& operator<<(ostream& outStream,const Cell& outCell){ // writing stream position row and type
       outStream<<outCell.position<<outCell.row<<" "<<outCell.type<<endl;
       return outStream;
    }
    istream& operator>>(istream& inputStream,Cell& inCell){ // reading from stream position row and type
        inputStream>>inCell.position>>inCell.row>>inCell.type;
        return inputStream;
    }

}

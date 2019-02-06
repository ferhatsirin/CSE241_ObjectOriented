#include "ConnectFourPlus.h"
namespace GTUFerhat{
    
ConnectFourPlus::ConnectFourPlus():ConnectFourAbstract() {

}
ConnectFourPlus::ConnectFourPlus(int rowN,int colN):ConnectFourAbstract(rowN,colN){

}
ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& orig):ConnectFourAbstract(orig){

}

ConnectFourPlus& ConnectFourPlus::operator=(const ConnectFourPlus& other){
    ConnectFourAbstract::operator=(other);
}
ConnectFourPlus::~ConnectFourPlus(){
}

bool ConnectFourPlus::isWin(){
    
    int Brow,Bcol;                          //for last move coordinates
    Bcol = static_cast<int>(lastMove-'a');   // move-'a' refers to column number
    for(int i=0;i<getHeight();++i){
        if(gameCells[i][Bcol].getType() !='.' && gameCells[i][Bcol].getType() !=' '){
            Brow =i;
            break;
        }
    }
    
    if(ToWin <= vertical(Brow,Bcol)){         // check for vertical    
        win =1;
        return true;
    }
    
    if(ToWin <= horizontal(Brow,Bcol)){       // check for horizontal
        win =1;
        return true;
    }
    
    return false;
}

bool ConnectFourPlus::isBetter(const ConnectFourPlus& other){ // compares to obj. to find which one is better
    char letter; int max,otherMax;
    if(currentPlayer =="User1")
        letter ='X';
    else if(currentPlayer =="User2") 
        letter ='O';
    else
        letter ='C';
    
    max =0;
    for(int i=0;i<getHeight();++i){         // finding the max number to learn how much close to win 
        for(int j=0;j<getWidth();++j){
            if(gameCells[i][j].getType() ==letter ){
                if(max < vertical(i,j)){
                    max =vertical(i,j);
                }
                if(max <horizontal(i,j)){
                    max =horizontal(i,j);
                }
            }
        }
    }
    otherMax =0;
    for(int i=0;i<other.getHeight();++i){ // finding max number for opponent to learn how much close to win 
        for(int j=0;j<other.getWidth();++j){
            if(other.gameCells[i][j].getType() ==letter){
                if(otherMax <vertical(i,j)){
                    otherMax =vertical(i,j);
                }
                if(otherMax <horizontal(i,j)){
                    otherMax =horizontal(i,j);
                }
            }
        }
    }
    
    if(otherMax < max)
        return true;
    
    return false;
}

}


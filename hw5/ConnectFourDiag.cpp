#include "ConnectFourDiag.h"

namespace GTUFerhat{
    
ConnectFourDiag::ConnectFourDiag():ConnectFourAbstract() {
}

ConnectFourDiag::ConnectFourDiag(int rowN,int colN):ConnectFourAbstract(rowN,colN) {
}

ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag& obj):ConnectFourAbstract(obj){

}

ConnectFourDiag& ConnectFourDiag::operator=(const ConnectFourDiag& obj){
    ConnectFourAbstract::operator=(obj);
}

bool ConnectFourDiag::isWin(){
    int Brow,Bcol;                          //for last move coordinates
    Bcol = static_cast<int>(lastMove-'a');   // move-'a' refers to column number
    for(int i=0;i<getHeight();++i){
        if(gameCells[i][Bcol].getType() !='.' && gameCells[i][Bcol].getType() !=' '){
            Brow =i;
            break;
        }
    }
    
    if(ToWin <= diagonal(Brow,Bcol)){    //check for diagonal
        win =1;
        return true;
    }
    
    return false;

}

int ConnectFourDiag::diagonal(int Brow,int Bcol){        // check for diagonal
    int rightToLeft,leftToRight,rightUp,rightDown,leftUp,leftDown;
    int i,j;
    int ret,count;
    
    rightToLeft =1; leftToRight =1; rightUp=0; rightDown=0; leftUp =0; leftDown =0;
    
    for(i=Brow-1,j=Bcol+1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[Brow][Bcol].getType() == gameCells[i][j].getType() ;--i,++j){
            ++rightUp;     
    }
    
    for(i=Brow+1,j=Bcol+1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[Brow][Bcol].getType() == gameCells[i][j].getType() ;++i,++j){
            ++rightDown;     
    }
    
    for(i=Brow-1,j=Bcol-1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[Brow][Bcol].getType() == gameCells[i][j].getType() ;--i,--j){
            ++leftUp;     
    }
    
    for(i=Brow+1,j=Bcol-1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[Brow][Bcol].getType() == gameCells[i][j].getType() ;++i,--j){
            ++leftDown;     
    }
    
    rightToLeft +=rightUp+leftDown;
    leftToRight +=leftUp+rightDown;
    count =0;
    
    if(ToWin <= rightToLeft){                                                  // if win then make them lower case
        
        gameCells[Brow][Bcol].setType(toLower(gameCells[Brow][Bcol].getType()));
        ++count;
        for(i=1;i<=rightUp && count <ToWin; ++i,++count){
            gameCells[Brow-i][Bcol+i].setType(gameCells[Brow][Bcol].getType());
        }
        for(i=1;i<=leftDown && count <ToWin;++i,++count){
            gameCells[Brow+i][Bcol-i].setType(gameCells[Brow][Bcol].getType());
        }
        ret =rightToLeft;
    }
    
    else if(4 <= leftToRight){
        gameCells[Brow][Bcol].setType(toLower(gameCells[Brow][Bcol].getType()));
        ++count;
        for(i=1;i<=leftUp && count<ToWin;++i,++count){
            gameCells[Brow-i][Bcol-i].setType(gameCells[Brow][Bcol].getType());
        }
        for(i=1;i<=rightDown &&count <ToWin;++i,++count){
            gameCells[Brow+i][Bcol+i].setType(gameCells[Brow][Bcol].getType());
        }
        ret =leftToRight;
    }
    else
        ret =0;
    
    return ret;
}


}


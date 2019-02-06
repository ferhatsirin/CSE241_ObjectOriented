#include "ConnectFourPlusUndo.h"

namespace GTUFerhat{

ConnectFourPlusUndo::ConnectFourPlusUndo():ConnectFourPlus(),backGround(nullptr),capacityB(0),usedB(0) {
}
ConnectFourPlusUndo::ConnectFourPlusUndo(int rowN,int colN):ConnectFourPlus(rowN,colN),usedB(0){
    capacityB =rowN*colN; // max number of undo can be made is rowN*colN 
    backGround =new reserved[capacityB];
    
}
ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& orig):ConnectFourPlus(orig) { // copy const.

    capacityB =orig.capacityB; 
    usedB =orig.usedB;
    
    backGround =new reserved[capacityB];
    
    copyBackground(orig); // copying the variable of orig 
}

void ConnectFourPlusUndo::copyBackground(const ConnectFourPlusUndo& obj){ // copying data to background
   
    for(int i=0;i<usedB;++i){
        backGround[i] =obj.backGround[i];
        
    }
    for(int i=0;i<usedB;++i){                                      // allocating space for gameCellsB inside backGround
        backGround[i].gameCellsB =new Cell*[backGround[i].rowB];
        for(int j=0;j<backGround[i].rowB;++j){
            backGround[i].gameCellsB[j] =new Cell[backGround[i].colB];
        }
    }
    for(int k=0;k<usedB;++k){                       // copying gameCellsB inside backGround
        for(int i=0;i<backGround[k].rowB;++i){
            for(int j=0;j<backGround[k].colB;++j){
                backGround[k].gameCellsB[i][j] =obj.backGround[k].gameCellsB[i][j];
            }
        }
    }
}

ConnectFourPlusUndo& ConnectFourPlusUndo::operator=(const ConnectFourPlusUndo& obj){ // overloading assignment
    
    if(this == &obj) // if a=a then return same object
        return *this;
    
    free(); // deleting old data in background 
    
    ConnectFourPlus::operator=(obj); // base class assignment called
   
    capacityB =obj.capacityB;
    usedB =obj.usedB;
 
    backGround =new reserved[capacityB];
    copyBackground(obj);
}
void ConnectFourPlusUndo::free(){ // deleting backGround and gameCellsB 
    
    for(int i=0;i<usedB;++i){
        for(int j=0;j<backGround[i].rowB;++j){
            delete [] backGround[i].gameCellsB[j];
        }
        delete [] backGround[i].gameCellsB;
    }

    delete [] backGround;
    
    backGround =nullptr;
}

char ConnectFourPlusUndo::takeMove(){ // this is overrided because added UNDO attribute 
    
    bool check; string fileName, command;
    char move;
    cout<<currentPlayer<<" make your move \n";
    check =true;
    
    while(check){
        cin>>command;
        if(cin.eof()){   // when testing homework from file to see it reachs end of file 
            cerr<<"End of file!!!"<<endl;
            exit(1);
        }
        if(command == "SAVE"){
            
            cin>>fileName;
            saveGame(fileName);
            cout<<currentPlayer<<" make your move :";
        }
        else if(command =="LOAD"){
            cin>>fileName;
            backup();
            loadGame(fileName);
            printBoard();
            cout<<currentPlayer<<" make your move :";
        }
        else if(command =="UNDO"){
            undo();
            printBoard();
            if(currentPlayer =="Computer"){ // if in Computer turn then computer make move again 
                undo();
                printBoard();
            }
            cout<<currentPlayer<<" make your move :";
        }
        else if(isAvailable(tolower(command[0]))){
            move =toLower(command[0]);
            check =false;
    
        }
        else{

            cerr<<"Input is not valid \n";
            cerr<<"Enter again :";
        } 
        cin.clear();
        cin.ignore(1000,'\n');
    }
    return move;        
      
}

void ConnectFourPlusUndo::play(char move){ // this is overrided because backup() attribute added  
    
    char letter;
    if(currentPlayer == "User1")
        letter ='X';
    else if(currentPlayer =="User2")
        letter ='O';
    else
        letter ='C';
    
    backup();
    
    for(int i=getHeight()-1; 0<=i ;--i){
        if(gameCells[i][move-'a'].getType() == '.'){               // move-'a' refers to column number
            gameCells[i][move-'a'].setType(letter);
            gameCells[i][move-'a'].setRow(i);
            gameCells[i][move-'a'].setPosition(move);
            break;
        }
    }
    lastMove =move;
    ++livingCells;
    ++usedCells;
}

void ConnectFourPlusUndo::prepareBoard(){ // this is overried because needed to allocate space for backGround 
 
    cout<<"Enter the size of the board \n";
    cout<<"Enter the row number :";
    
    row =takeNumber();
    cout<<"Enter the col number :";
    col =takeNumber();
    
    makeBoard();
    
    takeStyle();
    capacityB =row*col; // max number of undo can be made is row*col
    usedB =0;
    backGround =new reserved[capacityB];
}


void ConnectFourPlusUndo::undo(){
    if(0 < usedB){
    
        --usedB;
        if(row != backGround[usedB].rowB || col != backGround[usedB].colB){ // if a file loaded then row and col could be changed  
            for(int i=0;i<row;++i){                                         // so to restore them 
                delete [] gameCells[i];
            }
            delete [] gameCells;
            gameCells =new Cell*[backGround[usedB].rowB];
            for(int i=0;i<backGround[usedB].rowB;++i)
                gameCells[i] =new Cell[backGround[usedB].colB];
        }
        currentPlayer =backGround[usedB].currentPlayerB;
        lastMove =backGround[usedB].lastMoveB;
        style =backGround[usedB].styleB;
        livingCells =backGround[usedB].livingCellsB;
        usedCells =backGround[usedB].usedCellsB;
        win =backGround[usedB].winB;
        row =backGround[usedB].rowB;
        col =backGround[usedB].colB;
        
        for(int i=0;i<row;++i){
           for(int j=0;j<col;++j){
             gameCells[i][j] =backGround[usedB].gameCellsB[i][j];
           }
        }
        for(int i=0;i<row;++i){                 // deleting backGround gameCellsB because no need them anymore 
            delete [] backGround[usedB].gameCellsB[i];
        }
        delete [] backGround[usedB].gameCellsB;

    }
    else{
        cout<<"Game can not go back because You didn't play game!!! \n";
    }
}
void ConnectFourPlusUndo::backup(){
    if(capacityB <= usedB){
        increaseCapacity();
    }
    backGround[usedB].currentPlayerB =currentPlayer;
    backGround[usedB].lastMoveB =lastMove;
    backGround[usedB].styleB =style;
    backGround[usedB].livingCellsB =livingCells;
    backGround[usedB].usedCellsB =usedCells;
    backGround[usedB].winB =win;
    backGround[usedB].rowB =row;
    backGround[usedB].colB=col;

    backGround[usedB].gameCellsB =new Cell*[row];  // allocating new space for gameCellsB to copy data 
    for(int i=0;i<row;++i){
        backGround[usedB].gameCellsB[i] =new Cell[col];
    }
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            backGround[usedB].gameCellsB[i][j] =gameCells[i][j];
        } 
    }
    ++usedB;

}
void ConnectFourPlusUndo::increaseCapacity(){
    capacityB *=2;    // increase 2 times
    reserved *temp;
    temp =new reserved[capacityB];
 
    for(int i=0;i<usedB;++i){
        temp[i] =backGround[i];
        
    }
   
    for(int i=0;i<usedB;++i){
        temp[i].gameCellsB =new Cell*[backGround[i].rowB];
        for(int j=0;j<backGround[i].rowB;++j){
            temp[i].gameCellsB[j] =new Cell[backGround[i].colB];
        }
    }
  
    for(int k=0;k<usedB;++k){
        for(int i=0;i<backGround[k].rowB;++i){
            for(int j=0;j<backGround[k].colB;++j){
                temp[k].gameCellsB[i][j] =backGround[k].gameCellsB[i][j];
            }
        }
    }
    
    free();  // deleting old space 
    
    backGround =temp;
    
}


ConnectFourPlusUndo::~ConnectFourPlusUndo() {
    free();
}

}



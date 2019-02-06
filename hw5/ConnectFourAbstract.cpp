#include "ConnectFourAbstract.h"
#include<fstream>
using namespace std;

namespace GTUFerhat{

int ConnectFourAbstract::livingCells =0;
    
ConnectFourAbstract::ConnectFourAbstract():gameCells(nullptr),currentPlayer("User1"),ToWin(4),usedCells(0),win(0),row(0),col(0){
}

ConnectFourAbstract::ConnectFourAbstract(int rowN,int colN):gameCells(nullptr),currentPlayer("User1"),ToWin(4),usedCells(0),win(0),row(rowN),col(colN){//2 parameter const.
    makeBoard();
}

ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& obj):currentPlayer(obj.currentPlayer),style(obj.style),lastMove(obj.lastMove),ToWin(obj.ToWin),
usedCells(obj.usedCells),win(obj.win),row(obj.row),col(obj.col){ // copy constructor 
    
    livingCells +=usedCells;
    
    gameCells =new Cell*[row];
    for(int i=0;i<row;++i)
        gameCells[i] =new Cell[col];
    
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j)
            gameCells[i][j] =obj.gameCells[i][j];
    }
    
}

ConnectFourAbstract::~ConnectFourAbstract() {
        
    for(int i=0;i<getHeight();++i)
        delete [] gameCells[i]; 
     
    delete [] gameCells;
    
    livingCells -=usedCells;

}

int ConnectFourAbstract::getWidth()const{
    return col;
}
int ConnectFourAbstract::getHeight()const{
    return row;
}
char ConnectFourAbstract::getStyle()const{
    return style;
}
string ConnectFourAbstract::getCurrentPlayer()const{
    return currentPlayer;
}
int ConnectFourAbstract::getLivingCells(){ //static function
    return livingCells;
}
void ConnectFourAbstract::setCurrentPlayer(string player){
    if(player =="User1" || player =="User2" || player =="Computer")
      currentPlayer =player;
    else
        cout<<"Player can only be User1 User2 or Computer \n";
}
void ConnectFourAbstract::setStyle(char type){
    type =toLower(type);
    
    if(type == 'c' || type =='p'){
        style =type;
    }
    else{
        cout<<"Game style can only be PVP (P) or PVC (C) \n";
    }
}

ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& obj){ //assignment operator overloading 
    
    if(this == &obj)
        return *this;
    
    style =obj.style;
    currentPlayer =obj.currentPlayer;
    lastMove =obj.lastMove;
    livingCells -=usedCells;
    usedCells =obj.usedCells;
    livingCells +=usedCells;
    win =obj.win;
   
    for(int i=0;i<row;++i)  // deleting previous data 
        delete [] gameCells[i];

    delete [] gameCells;
    
    row =obj.row;
    col =obj.col;
    
    gameCells =new Cell*[row];
    for(int i=0;i<row;++i)
        gameCells[i] =new Cell[col];
    
    for(int i=0;i<row;++i){  // copying data
        for(int j=0;j<col;++j)
            gameCells[i][j] =obj.gameCells[i][j];
    }
    
    return *this;
    
}

bool ConnectFourAbstract::operator==(const ConnectFourAbstract& other)const{
    if(currentPlayer !=other.currentPlayer || style !=other.style || 
            lastMove != other.lastMove || usedCells != other.usedCells ||
            win !=other.win || row != other.row || col != other.col)
        return false;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            if(gameCells[i][j] !=other.gameCells[i][j])
                return false;
        }
    }
    return true;
}
bool ConnectFourAbstract::operator!=(const ConnectFourAbstract& other)const{
     return !(*this==other);
}
    
char ConnectFourAbstract::takeMove(){
    
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
            loadGame(fileName);
            printBoard();
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

bool ConnectFourAbstract::isAvailable(char move)const{   // looking if that move is available
    if(move < 'a' || move >= static_cast<char>('a'+getWidth()))
        return false;
        
    for(int i=0;i<getHeight();++i){  //controls all column from top to down
        if(gameCells[i][move-'a'].getType() =='.') // move-'a' refers to column number.
            return true;
    }
        
    return false;
}

bool ConnectFourAbstract::isGameOver()const{
    
    if(win ==1){
        return true;
    }

    for(int i=0;i<getHeight();++i){    //looking for empty cells
        for(int j=0;j<getWidth();++j){
           if(gameCells[i][j].getType() =='.')
              return false;
        }
    }
    
    return true;
}

void ConnectFourAbstract::prepareBoard(){
 
    cout<<"Enter the size of the board \n";
    cout<<"Enter the row number :";
    
    row =takeNumber();
    cout<<"Enter the col number :";
    col =takeNumber();
    
    makeBoard();
    
    takeStyle();

}

void ConnectFourAbstract::makeBoard(){
  
    gameCells =new Cell*[row];
    for(int i=0;i<row;++i)
        gameCells[i] =new Cell[col];
    
    char position;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            position ='a'+col;
            gameCells[i][j].setRow(row);
            gameCells[i][j].setPosition(position);
            gameCells[i][j].setType('.');
        }
    }
}

int ConnectFourAbstract::takeNumber()const{ // used to take row and col number from input 
    int number;    
    while(!(cin>>number)){
        cin.clear();
        cin.ignore(1000,'\n');
        cerr<<"Input is not valid \n";
        cerr<<"Enter again :";
    }
    cin.ignore(1000,'\n');
    
    return number;
}

char ConnectFourAbstract::toLower(char letter)const{
    if( 'A' <= letter && letter <= 'Z')
        letter +='a'-'A';
    
    return letter;
}

void ConnectFourAbstract::takeStyle(){
    
    char choice;
    
    cout<<"Do you want to play against computer or player\n";
    cout<<"For player versus computer PVC (C) \n";
    cout<<"For player versus player PVP (P) \n";
    cin >>choice;
    choice =toLower(choice);
    while(cin.fail() || (choice != 'p' && choice !='c')){
        cin.clear();
        cin.ignore(1000,'\n');
        cerr<<"Input is not valid \n";
        cerr<<"Enter again PVC (C) or PVP (P) :";
        cin>>choice;
        choice =toLower(choice);
    }
    cin.clear();
    cin.ignore(1000,'\n');
    
    style =toLower(choice);
}

void ConnectFourAbstract::printBoard()const{
    
    for(int i=0;i<getWidth();++i){
        cout<<"| ";
        cout<<static_cast<char>('a'+i)<<" ";
    }
    cout<<"|"<<endl;
    
    for(int i=0;i<getHeight();++i){
        cout<<"| ";
        for(int j=0;j<getWidth();++j){
            cout<<gameCells[i][j].getType()<<" | ";
        }
        cout<<endl;
    }
    cout<<endl;

}
void ConnectFourAbstract::playGame(){

    prepareBoard();

    while(!isGameOver()){        /* game start here */

        printBoard();
        if(currentPlayer == "User1" || currentPlayer == "User2"){
            lastMove =takeMove();
            play(lastMove);
        }
        else{
            play();
        }
        cout<<"Living cells :"<<livingCells<<endl;
        if(isWin()){
            printBoard();
            cout<<currentPlayer<<" won the game \n";
            win =1;
        }
        else{         
            switchUser();
        }
    
    }
    if(!win){
        
        printBoard();
        cout<<"Board is full \n";
    }

}
void ConnectFourAbstract::play(char move){ // this is for players to play 
    
    char letter;
    if(currentPlayer == "User1")
        letter ='X';
    else if(currentPlayer =="User2")
        letter ='O';
    else
        letter ='C';
    
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
void ConnectFourAbstract::play(){    /* this is for computer to play */

    srand(time(NULL));   
    int used,max; char move;
    used =0;
    
    for(int i=0;i<getHeight() && !used;++i){           // blocking the opponent
        for(int j=0;j<getWidth() && !used;++j){
            if(gameCells[i][j].getType() == 'X'){         /* looking if there is 3 element of opponent  if there is then block it */ 
                if(ToWin -1 == vertical(i,j)){
  
                    if(0 <=(i-1) && gameCells[i-1][j].getType() == '.'){
                        move ='a'+j;
                        used =1;
                    }
                }
                if(!used && ToWin -1 == horizontal(i,j)){
                    
                    if((j+1) < getWidth() && gameCells[i][j+1].getType() =='.'){
                        move ='a'+j+1;
                        used =1;
                    }
                    if(0 <= (j-1) && gameCells[i][j-1].getType() == '.'){
                        move ='a'+j-1;
                        used =1;
                    }
                }
            }
        }
    }
    max =0;
    if(!used){                                                   //to win

       for(int i=0;i<getHeight();++i){                          // if there is 3 element of its own then try to win 
           for(int j=0;j<getWidth();++j){
              if(gameCells[i][j].getType() =='C'){
                 if(1 <= vertical(i,j) && max < vertical(i,j)){           /* for vertical */
                    if( 0<=(i-1) && gameCells[i-1][j].getType() =='.'){
                      move ='a'+j;
                      used =1;
                      max =vertical(i,j);
                    }              
                 }
               }
            }
        }
        for(int i=0;i<getHeight();++i){
          for(int j=0;j<getWidth();++j){
            if(gameCells[i][j].getType() == 'C'){
                if(1 <=horizontal(i,j) && max < horizontal(i,j)){
                   if((j+1)<getWidth() && gameCells[i][j+1].getType() == '.'){       /* if used in vertical then to be used in horizontal it must be bigger than max */
                      move ='a'+j+1;
                      used =1;
                      max =horizontal(i,j);
                    }
                      
                   if(0 <=(j-1) && gameCells[i][j-1].getType() =='.'){
                      move ='a'+j-1;
                      used =1;
                      max =horizontal(i,j);
                   }
                }
             }
           }
        }
    }
    if(!used){    // if couldn't find a logical move then make a random move 
        
        do{
        move =static_cast<char>((rand()%getWidth())+'a');
        
        }while(!isAvailable(move));
    
    }
    
    cout<<currentPlayer<<"'s move "<<move<<endl;
    play(move);
}

int ConnectFourAbstract::vertical(int Brow,int Bcol){  /* checks for vertical */
    int sum,up,down,count;
    
    sum =1; up =0; down =0;
    
    for(int i=Brow+1;i<getHeight() && gameCells[Brow][Bcol].getType() == gameCells[i][Bcol].getType() ;++i){
            ++down;     
    }
    
    for(int i=Brow-1; 0<= i && gameCells[Brow][Bcol].getType() == gameCells[i][Bcol].getType() ;--i){
            ++up;     
    }
    
    sum +=up+down;
    count =0;
    if(ToWin <= sum){
        gameCells[Brow][Bcol].setType(toLower(gameCells[Brow][Bcol].getType()));  //to lowercase 
        ++count; 
        for(int i=1;i<=up && count <ToWin;++i,++count){
            gameCells[Brow-i][Bcol].setType(gameCells[Brow][Bcol].getType());
        }
        for(int i=1; i<=down && count < ToWin ;++i,++count){
               gameCells[i+Brow][Bcol].setType(gameCells[Brow][Bcol].getType());
        }   
    }
    
    return sum;
}
int ConnectFourAbstract::horizontal(int Brow,int Bcol){   // check for horizontal
    int sum,right,left,count;
    
    sum =1; right =0; left =0;
    
    for(int i=Bcol+1; i<getWidth() && gameCells[Brow][Bcol].getType() == gameCells[Brow][i].getType() ;++i){  // for right side
            ++right;     
    }
    
    for(int i=Bcol-1; 0<= i && gameCells[Brow][Bcol].getType() == gameCells[Brow][i].getType() ;--i){  // for left side
            ++left;     
    }
    
    sum +=right+left;
    count =0;
    if(ToWin <= sum){
        gameCells[Brow][Bcol].setType(toLower(gameCells[Brow][Bcol].getType()));       // if win then make them lower case 
        ++count;
        for(int i=1; i<=right && count< ToWin ;++i,++count){
            gameCells[Brow][Bcol+i].setType(gameCells[Brow][Bcol].getType());   
        }
    
        for(int i=1; i<=left && count < ToWin ;++i,++count){
            gameCells[Brow][Bcol-i].setType(gameCells[Brow][Bcol].getType());     
        }
        
    }
    
    return sum;
}

void ConnectFourAbstract::loadGame(string fname){  // load game from a file
    
    char letter;
    ifstream fin(fname);
    while(fin.fail()){
        cerr<<fname<<" file either doesn't exist or program can't open it "<<endl;
        cerr<<"Enter another file name :"<<endl;
        cin>>fname;
        fin.open(fname);
    }
    for(int i=0;i<getHeight();++i)
        delete [] gameCells[i];
        
    delete [] gameCells;
    
    livingCells -=usedCells;    // old board used cells 
    fin>>row>>col>>currentPlayer>>style>>usedCells;
    livingCells +=usedCells;       // new board used cells
    makeBoard();
    fin.get(letter); //overthrow '\n'
    for(int i=0;i<getHeight();++i){
        for(int j=0;j<getWidth();++j){
            fin.get(letter);
            gameCells[i][j].setType(letter);
            gameCells[i][j].setPosition(j+'a');
            gameCells[i][j].setRow(i);
        }
        fin.get(letter);
    }
    fin.close();
}
void ConnectFourAbstract::saveGame(string fname)const{  // save game to a file
    
    ofstream fout(fname);
    fout<<row<<" "<<col<<" "<<currentPlayer<<" "<<style<<" "<<usedCells<<endl;
    for(int i=0;i<getHeight();++i){
        for(int j=0;j<getWidth();++j){
            fout<<gameCells[i][j].getType();
        }
        fout<<endl;
    }
    fout.close();
}
void ConnectFourAbstract::switchUser(){
                
    if(currentPlayer =="User1"){        
        if(style =='p')
            currentPlayer ="User2";
        else
            currentPlayer ="Computer";
    }
    else{
        currentPlayer ="User1";
    }

}


}


#include"ConnectFour.h"

int ConnectFour::livingCells =0;

void ConnectFour::Cell::setPosition(char pos){
    position =pos;
}
void ConnectFour::Cell::setRow(int rowNum){
    row=rowNum;
}
void ConnectFour::Cell::setType(char letter){
    type =letter;
}

void ConnectFour::setStyle(char type){
    type =toLower(type);
    
    if( type =='p' || type =='c' )
       style =type;
    else
        cerr<<"Invalid style!!!\n";
}
void ConnectFour::setCurrentPlayer(string player){
    currentPlayer =player;
}

ConnectFour::ConnectFour(int row,int col,char type){

    makeBoard(row,col);
    type =toLower(type);
    while(type != 'c' && type !='p'){
        cerr<<"Game type is not valid \n";
        exit(1);
    }
    style =type;
};

ConnectFour::ConnectFour(int row,int col){
    makeBoard(row,col);
}

ConnectFour::ConnectFour(){

}

int ConnectFour::getLivingCells(){
    return livingCells;
}

int ConnectFour::takeNumber()const{
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

char ConnectFour::toLower(char letter)const{
    if( 'A' <= letter && letter <= 'Z')
        letter +='a'-'A';
    
    return letter;
}

void ConnectFour::takeStyle(){
    
    char choice;
    
    cout<<"Do you want to play against computer or player\n";
    cout<<"For player versus computer PVC (C) \n";
    cout<<"For player versus player PVP (P) \n";
    cin >>choice;
    while(cin.fail() || (choice != 'p' && choice !='c')){
        cin.clear();
        cin.ignore(1000,'\n');
        cerr<<"Input is not valid \n";
        cerr<<"Enter again PVC (C) or PVP (P) :";
        cin>>choice;
    }
    cin.clear();
    cin.ignore(1000,'\n');
    
    style =toLower(choice);
}

void ConnectFour::play(){    /* this is for computer to play */

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
              if(gameCells[i][j].getType() =='O'){
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
            if(gameCells[i][j].getType() == 'O'){
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

void ConnectFour::play(char move){
    
    char letter;
    if(currentPlayer == "User1")
        letter ='X';
    else
        letter ='O';
    
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
bool ConnectFour::isBetter(const ConnectFour& other){
    char letter; int max,otherMax;
    if(currentPlayer =="User1")
        letter ='X';
    else
        letter ='O';
    max =0;
    for(int i=0;i<getHeight();++i){         // finding the max number in the vertical 
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
    for(int i=0;i<other.getHeight();++i){
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
bool ConnectFour::isAvailable(char move)const{
    if(move < 'a' || move >= static_cast<char>('a'+getWidth()))
        return false;
        
    if(gameCells[0][move-'a'].getType() != '.')  // move-'a' refers to column number. control the top of the column if not empty then it is full  
        return false;
    
    return true;
}

void ConnectFour::saveGame(string fname)const{  // save game to a file
    
    ofstream fout(fname);
    fout<<gameCells.size()<<" "<<gameCells[0].size()<<" "<<currentPlayer<<" "<<style<<" "<<usedCells<<endl;
    for(int i=0;i<getHeight();++i){
        for(int j=0;j<getWidth();++j){
            fout<<gameCells[i][j].getType();
        }
        fout<<endl;
    }
}
void ConnectFour::loadGame(string fname){  // load game from a file
    
    int row,col; char letter;
    ifstream fin(fname);
    while(fin.fail()){
        cerr<<fname<<" file either doesn't exist or program can't open it "<<endl;
        cerr<<"Enter another file name :"<<endl;
        cin>>fname;
        fin.open(fname);
    }
    
    livingCells -=usedCells;    // old board used cells 
    fin>>row>>col>>currentPlayer>>style>>usedCells;
    livingCells +=usedCells;       // new board used cells
    makeBoard(row,col);
    for(int i=0;i<getHeight();++i){
        for(int j=0;j<getWidth();++j){
            fin>>letter;
            gameCells[i][j].setType(letter);
            gameCells[i][j].setPosition(j+'a');
            gameCells[i][j].setRow(i);
        }
    }

}

char ConnectFour::takeMove(){
    
    bool check; string fileName, command;
    char move;
    cout<<currentPlayer<<" make your move \n";
    check =true;
    
    while(check){
        cin>>command;
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

int ConnectFour::vertical(int row,int col){  /* checks for vertical */
    int sum,up,down,count;
    
    sum =1; up =0; down =0;
    
    for(int i=row+1;i<getHeight() && gameCells[row][col].getType() == gameCells[i][col].getType() ;++i){
            ++down;     
    }
    
    for(int i=row-1; 0<= i && gameCells[row][col].getType() == gameCells[i][col].getType() ;--i){
            ++up;     
    }
    
    sum +=up+down;
    count =0;
    if(ToWin <= sum){
        gameCells[row][col].setType(toLower(gameCells[row][col].getType()));  //to lowercase 
        ++count; 
        for(int i=1;i<=up && count <ToWin;++i,++count){
            gameCells[row-i][col].setType(gameCells[row][col].getType());
        }
        for(int i=1; i<=down && count < ToWin ;++i,++count){
               gameCells[i+row][col].setType(gameCells[row][col].getType());
        }   
    }
    
    return sum;
}

int ConnectFour::horizontal(int row,int col){   // check for horizontal
    int sum,right,left,count;
    
    sum =1; right =0; left =0;
    
    for(int i=col+1; i<getWidth() && gameCells[row][col].getType() == gameCells[row][i].getType() ;++i){  // for right side
            ++right;     
    }
    
    for(int i=col-1; 0<= i && gameCells[row][col].getType() == gameCells[row][i].getType() ;--i){  // for left side
            ++left;     
    }
    
    sum +=right+left;
    count =0;
    if(ToWin <= sum){
        gameCells[row][col].setType(toLower(gameCells[row][col].getType()));       // if win then make them lower case 
        ++count;
        for(int i=1; i<=right && count< ToWin ;++i,++count){
            gameCells[row][col+i].setType(gameCells[row][col].getType());   
        }
    
        for(int i=1; i<=left && count < ToWin ;++i,++count){
            gameCells[row][col-i].setType(gameCells[row][col].getType());     
        }
        
    }
    
    return sum;
}


int ConnectFour::diagonal(int row,int col){        // check for diagonal
    int rightToLeft,leftToRight,rightUp,rightDown,leftUp,leftDown;
    int i,j;
    int ret,count;
    
    rightToLeft =1; leftToRight =1; rightUp=0; rightDown=0; leftUp =0; leftDown =0;
    
    for(i=row-1,j=col+1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[row][col].getType() == gameCells[i][j].getType() ;--i,++j){
            ++rightUp;     
    }
    
    for(i=row+1,j=col+1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[row][col].getType() == gameCells[i][j].getType() ;++i,++j){
            ++rightDown;     
    }
    
    for(i=row-1,j=col-1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[row][col].getType() == gameCells[i][j].getType() ;--i,--j){
            ++leftUp;     
    }
    
    for(i=row+1,j=col-1; 0<=i&& 0<=j && i<getHeight() && j<getWidth() && gameCells[row][col].getType() == gameCells[i][j].getType() ;++i,--j){
            ++leftDown;     
    }
    
    rightToLeft +=rightUp+leftDown;
    leftToRight +=leftUp+rightDown;
    count =0;
    
    if(ToWin <= rightToLeft){                                                  // if win then make them lower case
        
        gameCells[row][col].setType(toLower(gameCells[row][col].getType()));
        ++count;
        for(i=1;i<=rightUp && count <ToWin; ++i,++count){
            gameCells[row-i][col+i].setType(gameCells[row][col].getType());
        }
        for(i=1;i<=leftDown && count <ToWin;++i,++count){
            gameCells[row+i][col-i].setType(gameCells[row][col].getType());
        }
        ret =rightToLeft;
    }
    
    else if(4 <= leftToRight){
        gameCells[row][col].setType(toLower(gameCells[row][col].getType()));
        ++count;
        for(i=1;i<=leftUp && count<ToWin;++i,++count){
            gameCells[row-i][col-i].setType(gameCells[row][col].getType());
        }
        for(i=1;i<=rightDown &&count <ToWin;++i,++count){
            gameCells[row+i][col+i].setType(gameCells[row][col].getType());
        }
        ret =leftToRight;
    }
    else
        ret =0;
    
    return ret;
}

bool ConnectFour::isWin(){
    
    int row,col;                          //for last move coordinates
    col = static_cast<int>(lastMove-'a');   // move-'a' refers to column number
    for(int i=0;i<getHeight();++i){
        if(gameCells[i][col].getType() !='.'){
            row =i;
            break;
        }
    }
    
    if(ToWin <= vertical(row,col)){         // check for vertical    
        win =1;
        return true;
    }
    
    if(ToWin <= horizontal(row,col)){       // check for horizontal
        win =1;
        return true;
    }
    
    if(ToWin <= diagonal(row,col)){    //check for diagonal
        win =1;
        return true;
    }
    
    return false;
}
bool ConnectFour::isGameOver()const{
    
    if(win ==1){
        return true;
    }
    
    for(int i=0;i<getWidth();++i){            // looking at the top side of the board
        if(gameCells[0][i].getType() =='.')
            return false;
    }
    
    return true;
}

void ConnectFour::prepareBoard(){
    
    int row,col;
 
    cout<<"Enter the size of the board \n";
    cout<<"Enter the row number :";
    
    row =takeNumber();
    cout<<"Enter the col number :";
    col =takeNumber();
    
    makeBoard(row,col);
    
    takeStyle();

}

void ConnectFour::playGame(){
    
    prepareBoard();
 
    currentPlayer ="User1";
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
void ConnectFour::switchUser(){
                
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


void ConnectFour::makeBoard(int row,int col){
  
    gameCells.resize(row);
    for(int i=0;i<row;++i)
        gameCells[i].resize(col);
    char position;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            position ='a'+col;
            gameCells[i][j].setRow(row);
            gameCells[i][j].setPosition(position);
            gameCells[i][j].setType('.');
        }
    }
    usedCells =0;
    win =0;
}

void ConnectFour::printBoard()const{
    
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

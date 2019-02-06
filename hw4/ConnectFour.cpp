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

bool ConnectFour::Cell::operator==(const Cell& other)const{
    
    return (row==other.row)&&(position==other.position)&&(type==other.type);
}
bool ConnectFour::Cell::operator!=(const Cell& other)const{
    
    return !(*this ==other);
}
ConnectFour::Cell& ConnectFour::Cell::operator++(){ //pre increment
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

const ConnectFour::Cell ConnectFour::Cell::operator++(int ignoreMe){ //post increment
    
    ConnectFour::Cell temp =*this;  
    
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
ConnectFour::Cell& ConnectFour::Cell::operator--(){ //pre decrement
    
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

const ConnectFour::Cell ConnectFour::Cell::operator--(int ignoreMe){ //post decrement
    ConnectFour::Cell temp =*this;
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
ostream& operator<<(ostream& outStream,const ConnectFour::Cell& outCell){ // writing stream position row and type
    outStream<<outCell.position<<outCell.row<<" "<<outCell.type<<endl;
    return outStream;
}
istream& operator>>(istream& inputStream,ConnectFour::Cell& inCell){ // reading from stream position row and type
    inputStream>>inCell.position>>inCell.row>>inCell.type;
    return inputStream;
}

ConnectFour& ConnectFour::operator=(const ConnectFour& obj){ // assign operator overload
    if(this == &obj)
        return *this;
    
    style =obj.style;
    currentPlayer =obj.currentPlayer;
    lastMove =obj.lastMove;
    usedCells =obj.usedCells;
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

ConnectFour::ConnectFour(const ConnectFour& obj):currentPlayer(obj.currentPlayer),style(obj.style),lastMove(obj.lastMove),ToWin(obj.ToWin),
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

bool ConnectFour::operator==(const ConnectFour& other)const{
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
bool ConnectFour::operator!=(const ConnectFour& other)const{
    return !(*this==other);
}

void ConnectFour::setStyle(char type){
    
    type =toLower(type);
    
    if(type != 'c' && type !='p'){
        cerr<<"Game type is not valid \n";
        cerr<<"Enter type again \n";
        takeStyle();
    }
    else
        style =type;
}
void ConnectFour::setCurrentPlayer(string player){
    currentPlayer =player;
}

ConnectFour::ConnectFour(string fName):gameCells(nullptr),currentPlayer("User1"),ToWin(4),usedCells(0),win(0){
    
    learnRowAndCol(fName); //first learn row and col number
    makeBoard(); // then make board
    
    ifstream fin(fName);

    char letter;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            fin.get(letter);
            if(letter ==' ')  // when there is ' ' then change that part in the board
                gameCells[i][j].setType(letter);
        }
        fin.get(letter);
    }
    
    takeStyle();
    
    fin.close();
}

void ConnectFour::learnRowAndCol(string& fname){ // to learn how many row and col there exist in the file
    
    ifstream fin(fname);
    while(fin.fail()){
        cerr<<fname<<" file either doesn't exist or program can't open it "<<endl;
        cerr<<"Enter another file name :"<<endl;
        cin>>fname;
        fin.open(fname);
    }
    char letter;
    int i,j;
   
    fin.get(letter);
    for(i=0;!fin.eof();++i){
        for(j=0;letter !='\n' && !fin.eof();++j){
            fin.get(letter); 
        }
        fin.get(letter);
    }
    row =i;
    col =j;;
    
    fin.close();
}

ConnectFour::ConnectFour(int rowN,int colN):gameCells(nullptr),currentPlayer("User1"),ToWin(4),usedCells(0),win(0),row(rowN),col(colN){//2 parameter const.
    makeBoard();
}

ConnectFour::ConnectFour():ConnectFour(5,5){ // no parameter const.
}

int ConnectFour::getLivingCells(){
    return livingCells;
}

int ConnectFour::takeNumber()const{ // used to take row and col number from input 
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

void ConnectFour::play(char move){ // this is for players to play 
    
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
bool ConnectFour::isBetter(const ConnectFour& other){ // compares to obj. to find which one is better
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
bool ConnectFour::isAvailable(char move)const{   // looking if that move is available
    if(move < 'a' || move >= static_cast<char>('a'+getWidth()))
        return false;
        
    for(int i=0;i<getHeight();++i){  //controls all column from top to down
        if(gameCells[i][move-'a'].getType() =='.') // move-'a' refers to column number.
            return true;
    }
        
    return false;
}

void ConnectFour::saveGame(string fname)const{  // save game to a file
    
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
void ConnectFour::loadGame(string fname){  // load game from a file
    
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

char ConnectFour::takeMove(){
    
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

int ConnectFour::vertical(int Brow,int Bcol){  /* checks for vertical */
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

int ConnectFour::horizontal(int Brow,int Bcol){   // check for horizontal
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


int ConnectFour::diagonal(int Brow,int Bcol){        // check for diagonal
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

bool ConnectFour::isWin(){
    
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
    
    if(ToWin <= diagonal(Brow,Bcol)){    //check for diagonal
        win =1;
        return true;
    }
    
    return false;
}
bool ConnectFour::isGameOver()const{
    
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

void ConnectFour::prepareBoard(){
 
    for(int i=0;i<row;++i)
        delete [] gameCells[i];
        
    delete [] gameCells;
    
    livingCells -=usedCells;
    usedCells =0;
    win =0;
    currentPlayer ="User1";
    
    string fName;
    cout<<"Enter name of file that includes board :";
    cin>>fName;
    learnRowAndCol(fName);
    makeBoard();
    
    ifstream fin(fName);

    char letter;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            fin.get(letter);
            if(letter ==' ')
                gameCells[i][j].setType(letter);
        }
        fin.get(letter);
    }
    
    takeStyle();
    
    fin.close();
}

void ConnectFour::playGame(){

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


void ConnectFour::makeBoard(){
  
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

ConnectFour::~ConnectFour(){
    
    for(int i=0;i<getHeight();++i)
        delete [] gameCells[i]; 
     
    delete [] gameCells;
    
    livingCells -=usedCells;

}

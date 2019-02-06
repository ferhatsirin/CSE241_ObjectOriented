#include <iostream>
#include<string>
#include<cstdlib>   // for rand() func
#include<ctime>   // for srand(Time()) func
#include<fstream>
using namespace std;

const int TOWIN =4;  // number needed to win  

void makeBoard(char board[][20],int& size);
bool controlSize(const int& size);     // size const parameter by reference
void printBoard(char board[][20],int size =4); // if size not send then it will be accepted 4 by default 
void play(char board[][20],int size);
bool isWin(char board[][20],int size,char move);
bool isAvailable(char board[][20],int size,char& move);     //move parameter by reference
void updateBoard(char board[][20],int size,char move,string currentPlayer);
int vertical(char board[][20],int size,int row,int col);
int horizontal(char board[][20],int size,int row,int col);
int diagonal(char board[][20],int size,int row,int col);
void playWithComp(char board[][20],int size);
void makeMove(char board[][20],int size,char& move);  // move parameter by reference
char toLower(char letter);
void takeCommand(char board[][20],int& size,string& currentPlayer,char& move);
void saveGame(char board[][20],int size,string currentPlayer,string fname);
void loadGame(char board[][20],int& size,string& currentPlayer,string fname);

int main(void) {
    
    char board[20][20]; int size;
    char choice;
    
    makeBoard(board,size);
    
    cout<<"Do you want to play against computer or player\n";
    cout<<"For player versus computer PVC (C) \n";
    cout<<"For player versus player PVP (P) \n";
    
    while(!(cin>>choice) || (toLower(choice)!= 'p' && toLower(choice) != 'c')){
        cin.clear();
        cin.ignore(1000,'\n');
        cerr<<"Input is not valid \n";
        cerr<<"Enter again PVC (C) or PVP (P) :";
    }
    cin.ignore(1000,'\n');
    
    if(toLower(choice) == 'c'){
        playWithComp(board,size);
    }
    else{
        
        play(board,size);
    }

    
    return 0;
}

void makeMove(char board[][20],int size,char& move){ 
    
    srand(time(NULL));   
    int used,max;
    used =0;
    
    for(int i=0;i<size && !used;++i){           // blocking the opponent
        for(int j=0;j<size && !used;++j){
            if(board[i][j] == 'X'){
                if(TOWIN -1 == vertical(board,size,i,j)){
  
                    if(0 <=(i-1) && board[i-1][j] == '.'){
                        move ='a'+j;
                        used =1;
                    }
                }
                if(!used && TOWIN -1 == horizontal(board,size,i,j)){
                    
                    if((j+1) < size && board[i][j+1] =='.'){
                        move ='a'+j+1;
                        used =1;
                    }
                    if(0 <= (j-1) && board[i][j-1] == '.'){
                        move ='a'+j-1;
                        used =1;
                    }
                }
            }
        }
    }
    max =0;
    if(!used){     

       for(int i=0;i<size;++i){
           for(int j=0;j<size;++j){
              if(board[i][j] =='O'){
                 if(1 <= vertical(board,size,i,j) && max < vertical(board,size,i,j)){/* for vertical */
                    if( 0<=(i-1) && board[i-1][j] =='.'){
                      move ='a'+j;
                      used =1;
                      max =vertical(board,size,i,j);
                    }              
                 }
               }
            }
        }
        for(int i=0;i<size;++i){
          for(int j=0;j<size;++j){
            if(board[i][j] == 'O'){
                if(1 <=horizontal(board,size,i,j) && max < horizontal(board,size,i,j)){
                   if((j+1)<size && board[i][j+1] == '.'){       /* if used in vertical then to be used in horizontal it must be bigger than max */
                      move ='a'+j+1;
                      used =1;
                      max =horizontal(board,size,i,j);
                    }
                      
                   if(0 <=(j-1) && board[i][j-1] =='.'){
                      move ='a'+j-1;
                      used =1;
                      max =horizontal(board,size,i,j);
                   }
                }
             }
           }
        }
    }
    if(!used){    // if couldn't find a logical move then make a random move 
        
        do{
        move =static_cast<char>(rand()%size+'a');
        
        }while(!isAvailable(board,size,move));
    
    }


}

void playWithComp(char board[][20],int size){
    string currentPlayer;
    char move; 
    
    currentPlayer ="User1";   
    auto win =0;                    //usage of auto
    decltype(win) count=0;         //usage of decltype
    
    while(count < size*size && !win){ /* game can be played max size^2 if there is no winning*/
    
        printBoard(board,size);
        if(currentPlayer =="User1"){
            takeCommand(board,size,currentPlayer,move);
  
        }
        else{
            makeMove(board,size,move);
            cout<<"Computer's move '"<<move<<"'"<<endl;
            updateBoard(board,size,move,currentPlayer);
        }

        if(isWin(board,size,move)){
            printBoard(board,size);
            cout<<currentPlayer<<" won the game \n";
            win =1;
        }
        else{
            if(currentPlayer == "User1"){
                currentPlayer = "Computer";
            }
            else{
                currentPlayer ="User1";
            }
            ++count;
        }
    
    }
    if(!win){
        
        printBoard(board,size);
        cout<<"Board is full \n";
    }
    


}
void saveGame(char board[][20],int size,string currentPlayer,string fname){ // save game to a file
    ofstream fout(fname);
    fout<<size<<" "<<currentPlayer<<endl;
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            fout<<board[i][j];
        }
        fout<<endl;
    }
}
void loadGame(char board[][20],int& size,string& currentPlayer,string fname){  // load game from a file
    ifstream fin(fname);
    
    while(fin.fail()){
        cerr<<fname<<" file either doesn't exist or program can't open it "<<endl;
        cerr<<"Enter another file name :"<<endl;
        cin>>fname;
        fin.open(fname);
    }    
    
    fin>>size>>currentPlayer;
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            fin>>board[i][j];
        }
    }
}
void takeCommand(char board[][20],int& size,string& currentPlayer,char& move){
    bool check; string fileName, command;
    
    cout<<currentPlayer<<" make your move \n";
    check =true;
    
    while(check){
        cin>>command;
        if(command == "SAVE"){
            
            cin>>fileName;
            saveGame(board,size,currentPlayer,fileName);
            cout<<currentPlayer<<" make your move :";
        }
        else if(command =="LOAD"){
            cin>>fileName;
            loadGame(board,size,currentPlayer,fileName);
            printBoard(board,size);
            cout<<currentPlayer<<" make your move :";
        }
        else if(isAvailable(board,size,command[0])){
        move =command[0];
        updateBoard(board,size,move,currentPlayer);
        check =false;
    
        }
        else{
        cerr<<"Input is not valid \n";
        cerr<<"Enter again :";
     
        }         
    }
}

void play(char board[][20],int size){

    string currentPlayer;  char move; 
    
    currentPlayer ="User1";
    auto win =0;                       // usage of auto
    decltype(win) count =0;            //usage of decltype
    
    while(count < size*size && !win){ /* game can be played max size^2 if there is no winning*/
    
        printBoard(board,size);

        takeCommand(board,size,currentPlayer,move);
        
        if(isWin(board,size,move)){
            printBoard(board,size);
            cout<<currentPlayer<<" won the game \n";
            win =1;
        }
        else{
            if(currentPlayer == "User1"){
                currentPlayer = "User2";
            }
            else{
                currentPlayer ="User1";
            }
            ++count;
        }
    
    }
    if(!win){
        
        printBoard(board,size);
        cout<<"Board is full \n";
    }
    
}

void updateBoard(char board[][20],int size,char move,string currentPlayer){
    char letter;
    if(currentPlayer == "User1")
        letter ='X';
    else
        letter ='O';
    
    for(int i=size-1; 0<=i ;--i){
        if(board[i][move-'a'] == '.'){               // move-'a' refers to column number
            board[i][move-'a'] =letter;
            break;
        }
    }

}

bool isWin(char board[][20],int size,char move){  // check if game is over 
    int row,col;
    col = static_cast<int>(move-'a');   // move-'a' refers to column number
    for(int i=0;i<size;++i){
        if(board[i][col] !='.'){
            row =i;
            break;
        }
    }
    
    if(TOWIN <= vertical(board,size,row,col))           
        return true;
    
    if(TOWIN <= horizontal(board,size,row,col))      
        return true;
    
    if(TOWIN <= diagonal(board,size,row,col))
        return true;
    
 
    return false;
}

int diagonal(char board[20][20],int size,int row,int col){        // check for diagonal
    int rightToLeft,leftToRight,rightUp,rightDown,leftUp,leftDown;
    int i,j,ret,count;
    
    rightToLeft =1; leftToRight =1; rightUp=0; rightDown=0; leftUp =0; leftDown =0;
    
    for(i=row-1,j=col+1; 0<=i&& 0<=j && i<size && j<size && board[row][col] == board[i][j] ;--i,++j){
            ++rightUp;     
    }
    
    for(i=row+1,j=col+1; 0<=i&& 0<=j && i<size && j<size && board[row][col] == board[i][j] ;++i,++j){
            ++rightDown;     
    }
    
    for(i=row-1,j=col-1; 0<=i&& 0<=j && i<size && j<size && board[row][col] == board[i][j] ;--i,--j){
            ++leftUp;     
    }
    
    for(i=row+1,j=col-1; 0<=i&& 0<=j && i<size && j<size && board[row][col] == board[i][j] ;++i,--j){
            ++leftDown;     
    }
    
    rightToLeft +=rightUp+leftDown;
    leftToRight +=leftUp+rightDown;
    count =0;
    
    if(TOWIN <= rightToLeft){
        
        board[row][col] = toLower(board[row][col]);
        ++count;
        for(i=1;i<=rightUp && count <TOWIN;++i,++count){
            board[row-i][col+i] =board[row][col];
        }
        for(i=1;i<=leftDown && count <TOWIN;++i,++count){
            board[row+i][col-i] =board[row][col];
        }
        ret =rightToLeft;
    }
    
    else if(TOWIN <= leftToRight){
        board[row][col] = toLower(board[row][col]);
        ++count;
        for(i=1;i<=leftUp && count<TOWIN;++i,++count){
            board[row-i][col-i] =board[row][col];
        }
        for(i=1;i<=rightDown &&count <TOWIN;++i,++count){
            board[row+i][col+i] =board[row][col];
        }
        ret =leftToRight;
    }
    else
        ret =0;
    
    return ret;


}


int horizontal(char board[][20],int size,int row,int col){   // check for horizontal
    int sum,right,left,count;
    
    sum =1; right =0; left =0;
    
    for(int i=col+1; i<size && board[row][col] == board[row][i] ;++i){
            ++right;     
    }
    
    for(int i=col-1; 0<= i && board[row][col] == board[row][i] ;--i){
            ++left;     
    }
    
    sum +=right+left;
    count =0;
    if(TOWIN <= sum){
        board[row][col] = toLower(board[row][col]);  
        ++count;
        for(int i=1; i<=right && count< TOWIN ;++i,++count){
            board[row][col+i] =board[row][col];   
        }
    
        for(int i=1; i<=left && count < TOWIN ;++i,++count){
            board[row][col-i] =board[row][col];     
        }
        
    }
    
    return sum;
}

int vertical(char board[][20],int size,int row,int col){  /* checks for vertical */
    int sum,up,down,count;
    
    sum =1; up =0; down =0;
    
    for(int i=row+1;i<size && board[row][col] == board[i][col] ;++i){
            ++down;     
    }
    
    for(int i=row-1;0<= i && board[row][col] == board[i][col] ;--i){
            ++up;     
    }
    
    sum +=up+down;
    count =0;
    if(TOWIN <= sum){
        board[row][col] = toLower(board[row][col]);  // to lowercase
        ++count; 

        for(int i=1; i<=down && count < TOWIN  ;++i,++count){
               board[i+row][col] =board[row][col]; 
        } 
        
    }
    
    return sum;
}

bool isAvailable(char board[][20],int size,char& move){
    
    move =toLower(move);
    if(move < 'a' || move >= 'a'+size)
        return false;
    
    if(board[0][move-'a'] != '.')  // move-'a' refers to column number. control the top of the column if not empty then it is full  
        return false;
    
    return true;
}

char toLower(char letter){
    if( 'A' <= letter && letter <= 'Z')
        letter +='a'-'A';
    
    return letter;
}

void makeBoard(char board[][20],int& size){
    
    cout<<"Board size can be 4x4 6x6 ... 20x20 \n";
    cout<<"Enter the size of the board :";
    
    while(!(cin>>size) || !controlSize(size)){
        cin.clear();
        cin.ignore(1000,'\n');
        cerr<<"Input is not valid \n";
        cerr<<"Enter again :";
    }
    cin.ignore(1000,'\n');
    
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
          board[i][j] = '.';
        }
    }
    
    
}

bool controlSize(const int& size){

    if(4 <= size && size <=20 && size%2==0 )
        return true;
    
    return false;
}


void printBoard(char board[][20],int size){

    
    for(int i=0;i<size;++i){
        cout<<"| ";
        cout<<static_cast<char>('a'+i)<<" ";
    }
    cout<<"|"<<endl;
    
    for(int i=0;i<size;++i){
        cout<<"| ";
        for(int j=0;j<size;++j){
            cout<<board[i][j]<<" | ";
        }
        cout<<endl;
    }
    cout<<endl;
}

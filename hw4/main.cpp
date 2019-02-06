#include <iostream>
#include<string>
#include"ConnectFour.h"
using namespace std;

char takeMod();
char toLower(char letter);
void run(ConnectFour &game);
int whichGame();

int main(void) {
    char mod;
    string fName;
    
    cout<<"Choose the mod of game  \n";
    cout<<"For Single (S) For Multiple (M) :";
    mod =takeMod();
    
    if(mod =='s'){
        ConnectFour singleGame;
        singleGame.playGame();
    }
    else{
        cout<<"Game1:"<<endl;
        cout<<"Enter name of file that includes board :";
        cin>>fName;
        ConnectFour game1(fName);
        cout<<endl;
        cout<<"Game2:"<<endl;
        cout<<"Enter name of file that includes board :";
        cin>>fName;
        ConnectFour game2(fName);
        cout<<endl;
        cout<<"Game3:"<<endl;
        cout<<"Enter name of file that includes board :";
        cin>>fName;
        ConnectFour game3(fName);
        cout<<endl;
        cout<<"Game4:"<<endl;
        cout<<"Enter name of file that includes board :";
        cin>>fName;
        ConnectFour game4(fName);
        cout<<endl;
        cout<<"Game5:"<<endl;
        cout<<"Enter name of file that includes board :";
        cin>>fName;
        ConnectFour game5(fName);
        cout<<endl;
        
        int game; ConnectFour currentObj,previousObj;
        previousObj =game1; // for start
        while(!game1.isGameOver() ||    // if all of them is over then game is over 
                !game2.isGameOver() ||
                !game3.isGameOver() ||
                !game4.isGameOver() ||
                !game5.isGameOver()){
            
            game =whichGame();
            if(game ==1){
                run(game1);
                currentObj =game1;
            }
            else if(game ==2){
                run(game2);
                currentObj =game2;
            }
            else if(game ==3){
                run(game3);
                currentObj =game3;
            }
            else if(game ==4){
                run(game4);
                currentObj =game4;
            }
            else{
                run(game5);
                currentObj =game5;
            }
            cout<<"Current object == Previous object :"<<(currentObj == previousObj)<<endl;;
            previousObj =currentObj;
        }
        cout<<"All game is over!!! \n";
    }
    
    
    return 0;
}
char toLower(char letter){
    if( 'A' <= letter && letter <= 'Z')
        letter +='a'-'A';
    
    return letter;
}

int whichGame(){
    int game;
    cout<<"Which game do you want to play \n";
    cout<<"For Game1 (1) For Game2 (2) For Game3 (3) For Game4 (4) For Game5 (5) :";
    cin>>game;
    while(cin.fail() || game < 1 || 5 < game){
        cerr<<"Invalid input \n";
        cerr<<"You have only these games \n";
        cerr<<"Game1 (1) Game2 (2) Game3 (3) Game4 (4) Game5 (5) \n";
        cerr<<"Choice one of them :";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>game;
    }
    cin.clear();
    cin.ignore(1000,'\n');
    
    return game;
}


char takeMod(){

    char mod;
    cin>>mod;
    while(cin.fail() ||(toLower(mod) !='s' && toLower(mod) !='m')){
        cerr<<"Input is not valid \n";
        cerr<<"Enter again Single (S) or Multiple (M) :";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cin.clear();
    cin.ignore(1000,'\n');
    
    return toLower(mod);
}

void run(ConnectFour &game){

    if(game.isGameOver()){
        game.printBoard();
        cout<<"Game is over! \n";
    }
    else{
        int count =0;
        char move;
        game.setCurrentPlayer("User1");
        while (count<2 && !game.isGameOver()){
            
            game.printBoard();
            if(game.getCurrentPlayer() == "User1" || game.getCurrentPlayer() == "User2"){
                move =game.takeMove();
                game.play(move);
            }
            else{
                game.play();
            }
            if(game.isWin()){
               game.printBoard();
               cout<<game.getCurrentPlayer()<<" won the game \n";
            }
            else{
                game.switchUser();
                ++count;
            }
        }
        game.printBoard();
        cout<<"Living cells :"<<game.getLivingCells()<<endl;
    }

}


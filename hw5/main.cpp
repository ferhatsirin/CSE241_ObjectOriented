#include<iostream>
#include"ConnectFourPlus.h"
#include"ConnectFourPlusUndo.h"
#include"ConnectFourDiag.h"
using namespace std;
using namespace GTUFerhat;

char toLower(char letter);

int main(void) {

    char choice;
    
    cout<<"Which game do you want to play \n";
    cout<<"PLUS (P) DIAG (D) or UNDO (U) :";
    
    cin>>choice;
    choice =toLower(choice);
    while(cin.fail() || (choice != 'p' && choice !='d' && choice !='u')){
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Input is not valid \n";
        cout<<"Enter again PLUS (P) DIAG (D) or UNDO (U) :";
        cin>>choice;
        choice =toLower(choice);
    }
    cin.clear();
    cin.ignore(1000,'\n');
    
    if(choice =='p'){
        ConnectFourPlus obj;
        obj.playGame();
    }
    else if(choice =='d'){
        ConnectFourDiag obj;
        obj.playGame();
    }
    else{
        ConnectFourPlusUndo obj;
        obj.playGame();
    }
    
    return 0;
}

char toLower(char letter){
    if( 'A' <= letter && letter <= 'Z')
        letter +='a'-'A';
    
    return letter;
}



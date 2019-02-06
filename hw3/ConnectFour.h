#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>   // for rand() func
#include<ctime>   // for srand(Time()) func
using namespace std;

class ConnectFour{
public:
    
    ConnectFour();
    ConnectFour(int row,int col);
    ConnectFour(int row,int col,char type);
    void printBoard()const;
    void playGame();
    int takeNumber()const;
    char toLower(char letter)const;
    void takeStyle();
    void makeBoard(int row,int col);
    void play();
    void play(char move);
    int getWidth()const{                            // for inline
        return static_cast<int>(gameCells[0].size());
    }
    int getHeight()const{
        return static_cast<int>(gameCells.size());
    }
    char getStyle()const{
        return style;
    }
    string getCurrentPlayer(){
        return currentPlayer;
    }
    void setCurrentPlayer(string player);
    void setStyle(char type);
    void switchUser();
    char takeMove();
    bool isAvailable(char move)const;
    bool isWin();
    int vertical(int row,int col);
    int horizontal(int row,int col);
    int diagonal(int row,int col);
    void saveGame(string fname)const;
    void loadGame(string fname);
    bool isGameOver()const;
    void prepareBoard();
    static int getLivingCells();
    bool isBetter(const ConnectFour& other);
    
private:
    
    class Cell{
        
    public:
        
        void setPosition(char pos);
        void setRow(int row);
        void setType(char type);
        
        char getPosition()const{         // for inline
            return position;
        }
        int getRow()const{
           return row;
        }
        char getType()const{
            return type;
        }
        
    private:
        
        char position;
        int row;
        char type;
    
    };
    
    vector<vector<Cell>> gameCells;
    string currentPlayer;
    char style;
    char lastMove;
    const int ToWin =4;
    static int livingCells;
    int usedCells;
    int win;
};

#endif /* CONNECTFOUR_H */



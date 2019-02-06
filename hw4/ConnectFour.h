#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>   // for rand() func
#include<ctime>   // for srand(Time()) func
using namespace std;

class ConnectFour{
public:
    
    ConnectFour();
    ConnectFour(int row,int col);
    ConnectFour(string fName);
    ConnectFour(const ConnectFour& obj);
    void printBoard()const;
    void playGame();
    void play();
    void play(char move);
    int getWidth()const{           // for inline
        return col;
    }
    int getHeight()const{
        return row;
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
    bool isGameOver()const;
    void prepareBoard();
    static int getLivingCells();
    bool isBetter(const ConnectFour& other);
    ConnectFour& operator=(const ConnectFour& obj);
    bool operator==(const ConnectFour& other)const;
    bool operator!=(const ConnectFour& other)const;
    ~ConnectFour();
    
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
        bool operator==(const Cell& other)const;
        bool operator!=(const Cell& other)const;
        Cell& operator++(); //pre increment
        const Cell operator++(int ignoreMe); //post increment
        Cell& operator--(); //pre decrement
        const Cell operator--(int ignoreMe); //post decrement
        friend ostream& operator<<(ostream& outStream,const Cell& outCell);
        friend istream& operator>>(istream& inputStream,Cell& inCell);
    private:
        
        char position;
        int row;
        char type;
    
    };
    friend ostream& operator<<(ostream& outStream,const Cell& outCell);
    friend istream& operator>>(istream& inputStream,Cell& inCell);
   
    Cell **gameCells;
    string currentPlayer;
    char style;
    char lastMove; 
    const int ToWin; 
    static int livingCells;
    int usedCells;
    int win;
    int row;
    int col;
    
    void saveGame(string fname)const;  // save to file
    void loadGame(string fname);  // load from file
    int vertical(int row,int col);  // looking for vertical check
    int horizontal(int row,int col); // for horizontal check
    int diagonal(int row,int col);  // for diagonal check
    void learnRowAndCol(string& fname); // to find out how many row an col will be
    char toLower(char letter)const; 
    int takeNumber()const; // taking one int number
    void takeStyle();  
    void makeBoard();  // making board with empty cells
};

#endif /* CONNECTFOUR_H */



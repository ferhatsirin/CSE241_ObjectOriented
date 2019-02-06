#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
#include<string>
#include"Cell.h"
using std::string;

namespace GTUFerhat{
    
class ConnectFourAbstract {
    
public:
    ConnectFourAbstract();
    ConnectFourAbstract(int rowN,int colN);
    ConnectFourAbstract(const ConnectFourAbstract& orig); //copy const.
   
    virtual bool isWin() =0;  // pure virtual function. this makes this class abstract
    virtual  void prepareBoard();
    virtual char takeMove();
    virtual void play(char move);
    void printBoard()const;
    void playGame();
    void play();
    int getWidth()const;
    int getHeight()const;
    char getStyle()const;
    string getCurrentPlayer()const;
    void setCurrentPlayer(string player);
    void setStyle(char type);
    void switchUser();
    bool isAvailable(char move)const;
    bool isGameOver()const;
    static int getLivingCells();
    ConnectFourAbstract& operator=(const ConnectFourAbstract& obj); //assignment operator overloading
    bool operator==(const ConnectFourAbstract& other)const;
    bool operator!=(const ConnectFourAbstract& other)const;    
    virtual ~ConnectFourAbstract();
    
protected:
    Cell **gameCells;
    string currentPlayer;
    char style;
    char lastMove; 
    const int ToWin=4; 
    static int livingCells;
    int usedCells;
    int win;
    int row;
    int col;
    
    void saveGame(string fname)const;  // save to file
    void loadGame(string fname);  // load from file
    int vertical(int row,int col);  // looking for vertical check
    int horizontal(int row,int col); // for horizontal check
    void makeBoard();  // making board with empty cells
    char toLower(char letter)const; 
    int takeNumber()const; // taking one int number
    void takeStyle();

};

}

#endif /* CONNECTFOURABSTRACT_H */



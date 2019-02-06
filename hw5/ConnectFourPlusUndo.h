#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H
#include"ConnectFourPlus.h"

namespace GTUFerhat{

    class ConnectFourPlusUndo:public ConnectFourPlus {

    public:
    
        ConnectFourPlusUndo();
        ConnectFourPlusUndo(int rowN,int colN);
        ConnectFourPlusUndo(const ConnectFourPlusUndo& orig); // copy const.
    
        ConnectFourPlusUndo& operator=(const ConnectFourPlusUndo& obj); // overloading assignment
        char takeMove()override;   // this is overrided because added UNDO attribute 
        void undo();
        void backup();
        void play(char move)override; // this is overrided because backup() attribute added  
        void prepareBoard()override; // this is overried because needed to allocate space for backGround 
        
        ~ConnectFourPlusUndo();

    private:

        struct reserved{           // all variable that must be backup
                Cell **gameCellsB;
                string currentPlayerB;
                char styleB;
                char lastMoveB;  
                int livingCellsB;
                int usedCellsB;
                int winB;
                int rowB;
                int colB;
        };
        reserved *backGround;
        int capacityB;
        int usedB;
        
        void copyBackground(const ConnectFourPlusUndo& obj); // to copy the backGround variable of obj
        void increaseCapacity(); 
        void free(); // delete the backGround 
        
};

}
#endif /* CONNECTFOURPLUSUNDO_H */



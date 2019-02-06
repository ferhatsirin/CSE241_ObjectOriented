#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H
#include"ConnectFourAbstract.h"

namespace GTUFerhat{

    class ConnectFourDiag:public ConnectFourAbstract {

    public:
    
        ConnectFourDiag();
        ConnectFourDiag(int rowN,int colN);
        ConnectFourDiag(const ConnectFourDiag& obj);
        ConnectFourDiag& operator=(const ConnectFourDiag& obj);
        bool isWin() override; //check for diagonal win
        
    private:
        int diagonal(int Brow,int Bcol); //check for diagonal
};

}

#endif /* CONNECTFOURDIAG_H */



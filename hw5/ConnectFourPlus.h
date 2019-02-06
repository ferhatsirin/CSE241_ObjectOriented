#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include"ConnectFourAbstract.h"
namespace GTUFerhat{

    class ConnectFourPlus:public ConnectFourAbstract {
     public:
    
          ConnectFourPlus();
          ConnectFourPlus(int rowN,int colN);
          ConnectFourPlus(const ConnectFourPlus& orig);
          
          ConnectFourPlus& operator=(const ConnectFourPlus& other);
          bool isWin() override ; // checks for vertical and horizontal 
          bool isBetter(const ConnectFourPlus& other); // compares the objects to find which one is better for vertical or horizontal win
          ~ConnectFourPlus();
    private:

};

}

#endif /* CONNECTFOURPLUS_H */



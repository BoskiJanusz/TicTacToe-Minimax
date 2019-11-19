#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

class Board
{
private:
    char field[3][3];
    char player, computer;
    int rowParam, columnParam;
    bool flag = 1, flagToStopLoop = 0;
    int counter = 9;
    std::array<int, 3> parameters;
    
  
   
    public : 
    Board();
    ~Board();
    int minmax(char[3][3], int, bool);
    int checkField(char[3][3]);
    bool isMovesLeft(char[3][3]);
    void findBestMove(char[3][3]);
    void setX(int, int);
    void setO(int, int);
    void PlayervsComputer();
};

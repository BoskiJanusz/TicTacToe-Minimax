#include "board.h"
#include <algorithm>
Board::Board()
{
    player = 'X';
    computer = 'O';
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            field[i][j] = ' ';
        }
    }

}

Board::~Board(){};

void Board::setX(int a, int b)
{ 
    field[a][b] = 'X';
    flag = 0;
    counter--;
}

void Board::setO(int a, int b)
{ 
    field[a][b] = 'O';
    flag = 1;
    counter--;
}



bool Board::isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int Board::checkField(char field[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (field[row][0] == field[row][1] && 
            field[row][1] == field[row][2])
        {
            if (field[row][0] == computer)
            {
                parameters[0] = 90;
                parameters[1] = 450;
                parameters[2] = 150 + 300 * row;
                return +10;
            }
            else if (field[row][0] == player)
            {
                
                parameters[0] = 90;
                parameters[1] = 450;
                parameters[2] = 150 + 300 * row;
                return -10;
            }
        }
    }

    for (int column = 0; column < 3; column++)
    {
        if (field[0][column] == field[1][column] &&
            field[1][column] == field[2][column])
        {
            if (field[0][column] == computer)
            {

                parameters[0] = 0;
                parameters[1] = 150 + 300 * column;
                parameters[2] = 450;
                return +10;
            }

            else if (field[0][column] == player)
            {
                parameters[0] = 0;
                parameters[1] = 150 + 300 * column;
                parameters[2] = 450;
                return -10;
            }
        }
    }
    if (field[0][0] == field[1][1] && field[1][1] == field[2][2])
    {
        if (field[0][0] == computer)
        {
         
            parameters[0] = 45;
            parameters[1] = 450;
            parameters[2] = 450;
            return +10;
        }
        else if (field[0][0] == player)
        {
          
            parameters[0] = 45;
            parameters[1] = 450;
            parameters[2] = 450;
            return -10;
        }
    }

    if (field[0][2] == field[1][1] && field[1][1] == field[2][0])
    {
        if (field[0][2] == computer)
        {
            parameters[0] = 135;
            parameters[1] = 450;
            parameters[2] = 450;
            return +10;
        }
        else if (field[0][2] == player)
        {
            parameters[0] = 135;
            parameters[1] = 450;
            parameters[2] = 450;
            return -10;
        }
    }

    return 0;
}

int Board::minmax(char field[3][3], int depth, bool isMax)
{
    int score = checkField(field);

    if (score == 10)
        return score ;

    if (score == -10)
        return score ;

    if (isMovesLeft(field) == false)
    {
        return 0;

    }

        if(isMax)
        {
            int best = -1000;



            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if(field[i][j] == ' ')
                    {
                        field[i][j] = computer;
                        best = std::max(best, minmax(field, depth + 1, !isMax));
                        field[i][j] = ' ';
                    }
                }
            }
            return best ;
        }
        else
        {
            int best = 1000;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                 
                    if (field[i][j] == ' ')
                    {
                       
                        field[i][j] = player;
                        best = std::min(best,
                                   minmax(field, depth + 1, !isMax));

                        
                        field[i][j] = ' ';
                    }
                }
            }
            return best ;
        }
        
        
}


void Board::findBestMove(char field[3][3])
{
    int bestMove = -1000;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (field[i][j] == ' ')
            {
                field[i][j] = computer;
 
                int tempMove = minmax(field, 0, false);

                field[i][j] = ' ';

                if (tempMove > bestMove)
                {
                    bestMove = tempMove;
                    rowParam = i;
                    columnParam = j;
                   
                }
            }
        }
    }
  
    setO(rowParam, columnParam);
}


void Board::PlayervsComputer()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "TicTacToe");
    window.clear(sf::Color(239, 235, 134));
    window.setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4;
    sf::RectangleShape line(sf::Vector2f(1300, 10));
    line.setFillColor(sf::Color::Black);
    line.setOrigin(650, 0);

    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/X.png");
    t3.loadFromFile("images/O.png");

    sf::Sprite background(t1), X(t2), O(t3);




        while (window.isOpen())
        {
            sf::Event event;
            sf::Vector2i pos = sf::Mouse::getPosition(window);

            int x = pos.x / 300;
            int y = pos.y / 300;

            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (checkField(field) == -10 || checkField(field) == 10)
                {
                    if (flagToStopLoop == 0)
                    {
                        line.rotate(parameters[0]);
                        flagToStopLoop = 1;
                    }

                    line.setPosition(parameters[1], parameters[2]);
                    window.draw(line);
                    break;
                }

        

                if (field[x][y] == ' ' && flag == 1 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    setX(x, y);
                    X.setPosition(x * 300 + 30, y * 300 + 25);
                    window.draw(X);
                }
                

                if(flag == 0)
                {
                    findBestMove(field);
                    O.setPosition(rowParam*300 + 30, columnParam*300 + 30);
                    window.draw(O);
                }
                window.draw(background);
            }
            window.display();
        }
    }

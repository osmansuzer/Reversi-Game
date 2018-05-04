// main.cpp
//
// Created on 05/10/2015 by Osman_Suzer

#include "reversi.h"
#include <iostream>

using namespace std;

int main()
{
    int dimension;
    char game_board[20][20];
    
    //Take dimension of game board from user 
    dimension = Take_Dimension();
    
    //Make first board  
    MakefirstTable(game_board, dimension);
    
    //Print game board to consol
    PrintTheGame(game_board, dimension);
    
    //In general; functions are in this function
    //Supplies continuousness of the game
    TheGame(game_board, dimension);
    
    //Print score to consol when the game ended.
    ScoreOfGame(game_board, dimension, COMPUTER, USER);

    return 0;

}

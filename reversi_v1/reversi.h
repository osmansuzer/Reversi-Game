// reversi.h
//
// Created on 05/10/2015 by Osman_Suzer

//constant characters for computer and user
const char COMPUTER = 'X';
const char USER = 'O';

//takes dimension of game's board from user
int Take_Dimension();

//print the board of game to console
void PrintTheGame(char array[20][20], int n);

//make first board
void MakefirstTable(char array[20][20], int n);


//check the attack on columnpoint and linepoint for competitor
//keep the taken stones from rival for competitor -numberofstones-
bool ControlOfAttack(const char array[20][20], int dimension, 
                     int columnpoint, int linepoint, 
                     char competitor, char rival, 
                     int *numberofstone);


//realizes attack on columnpoint and linepoint for competitor
void RealizeAttack(char array[20][20], int dimension, 
                     int columnpoint, int linepoint, 
                     char competitor, char rival);


//constitute coordinate to computer -According to max taken stone-
void ComputerAttack(int *columnpoint, int *linepoint, 
                    int dimension, const char array[20][20], 
                    char computer, char user);


//checks continuity for competitor
bool IsContinuous(const char array[20][20], int dimension, 
                  char competitor, char rival);


//declares victorious and scores
void ScoreOfGame(const char array[20][20], int dimension, 
                 char computer, char user);


//checks spelling of coordinate array
bool IsCoordinateCorrect(const char array[4]);


//converts string coordinate to integer coordinates 
void MakeCoordinate(const char array[4], int *columnpoint, int *linepoint);


//In general; functions are in this function
//Supplies continuousness of the game
void TheGame(char array[20][20], int dimension);

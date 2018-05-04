// HW05_131044051_Osman_SUZER
// reversi.h
//
// Created on 29/11/2015 by Osman_SUZER

#include <vector>
#include <string>

using namespace std;

class Cell
{
public:
    Cell();
    Cell(int Y, int X, char C);
    Cell(int Y, int X);
    
    int Get_Y() const {return y;}    
    int Get_X() const {return x;}
    char Get_Char() const {return CellChar;}
    
    void Set_Y(const int NewY);    
    void Set_X(const int NewX);
    void Set_Char(const char NewChar);
    
    /////////////////////for homework 5 /////////////////////////
    
    bool operator <(Cell secondCell);
    bool operator >(Cell secondCell);
    bool operator <=(Cell secondCell);
    bool operator >=(Cell secondCell);
    bool operator ==(Cell secondCell);
    bool operator !=(Cell secondCell);
    
    Cell operator ++();
    Cell operator ++(int);
    Cell operator --();
    Cell operator --(int);
    
    friend ostream &operator<<(ostream &output,const Cell &cell);
    
    friend istream &operator>>(istream  &input, Cell &cell);

    ///////////////////////////////////////////////////////////
    
private:
    
    int y;
    int x;
    char CellChar;
};

class Reversi
{
public:
    Reversi(); 
    Reversi(const int NewDimension); // (NewDimension x NewDimension)
    Reversi(const int NewHeight, const int NewWidth); //(newHeigth x NewWeigth)
    
    int Get_Height() const {return height;}
    int Get_Width() const {return width;}
    int Get_CountAttack() const {return CountAttack;}
    
    
    void Set_Height(const int NewHeight);
    void Set_Width(const int NewWidth);
    void Set_CountAttack(const int NewCount);
    
    //////////////for homework 5 //////////////////
    
    Cell operator [](string coordinate);
    Cell operator ()(string coordinateY, string coordinateX);
    
    Reversi operator ++();
    Reversi operator ++(int);
    
    void RecordAttackToBoard();   //records every attack 
    Reversi operator --();      
    Reversi operator --(int);
    
    Reversi operator +=(Cell cell);
    
    friend ostream &operator<<(ostream &output,const Reversi &theGame);
    
    //////////////////////////////////////////////////
    
    void PrintToScreen()const;
    void PrintScore()const;
    
    bool IsEnd()const;

    
    void playGame();
    
    static int NumberOfLivingCell() {return LivingCell;}
    static void AddLivingCell() {LivingCell += 1;}
    
    bool CompareGames(const Reversi OtherGame)const;

    void GamersScores(int &UserScore, int &ComputerScore)const;

    
    void WriteToFile(const char *FileName) const;
    void ReadFromFile(const char *FileName);
    
private:
    
    int height;    
    int width; 

    vector< vector<Cell> > gameCells;
    
    vector< vector <vector<Cell> > > RecordAttack;  //vector is to record attack
    int CountAttack;                    // number of attack
    
    
    static int LivingCell;

    static const char USER = 'O';
    static const char COMPUTER = 'X';
    static const char EMPTY = '.';

    void ComputerAttack();
    void UserAttack(const int posY, const int posX);
    
    bool ControlAttack(const int posY, const int posX,
                       const char competitor, const char rival,
                       int& TakenCells)const;
    void RealizeAttack(const int posY, const int posX, 
                       const char competitor, const char rival);

    void MakeFirstBoard();
    void MakeCoordinate(string coordinate, int &posY, int &posX);

    bool IsEndUser()const;
    bool IsEndComputer() const;

};

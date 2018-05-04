// HW05_131044051_Osman_SUZER
// reversi.h
//
// Created on 10/12/2015 by Osman_SUZER

#ifndef REVERSI_H
#define REVERSI_H

#include <vector>
#include <string>

using namespace std;

namespace TheGameSpace
{
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
        Reversi(const Reversi& CpyReversi);
        
        int Get_Height() const {return height;}
        int Get_Width() const {return width;}
        int Get_Dimension() const {return dimension;}
    
        void Set_Height(const int NewHeight);
        void Set_Width(const int NewWidth);
        void Set_Dimension(const int NewDimension);

    
        void Resize_Height(const int NewHeight);
        void Resize_Width(const int NewWidth);
        void Resize_Dimension(const int NewHeight, const int NewWidth);
    
        Reversi operator ++();
        Reversi operator ++(int);
    
        friend ostream &operator<<(ostream &output,const Reversi &theGame);
    
        void PrintToScreen()const;
        void PrintScore()const;
        void GamersScores(int &UserScore, int &ComputerScore)const;
        
        bool IsEnd()const;

        void playGame();
   
        static int NumberOfLivingReversi() {return LivingReversi;}
        static void AddLivingReversi() {LivingReversi += 1;}
        static void ReduceLivingReversi() {LivingReversi -= 1;}
    
        bool CompareGames(const Reversi OtherGame)const;

        ~Reversi();
    
    private:
    
        int height;
        int width;

        Cell * gameCells;
        int dimension;

        static int LivingReversi;

        static const char USER = 'O';
        static const char COMPUTER = 'X';
        static const char EMPTY = '.';

        int FindIndexOfCell(const int posY, const int posX)const;
        
        void ComputerAttack();
        void UserAttack(const int posY, const int posX);
    
        bool ControlAttack(const int posY, const int posX,
                       const char competitor, const char rival,
                       int& TakenCells)const;
        
        void RealizeAttack(const int posY, const int posX, 
                       const char competitor, const char rival);

        void MakeFirstBoard();
        void MakeCoordinate(const char* coordinate, int &posY, int &posX);

        bool IsEndUser()const;
        bool IsEndComputer() const;

    };
    

}

#endif /* REVERSI_H */
// reversi.cpp
//
// Created on 24/11/2015 by Osman_SUZER

#include "reversi.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

Cell::Cell(int Y, int X, char C)
{
    y = Y;
    x = X;
    CellChar = C;
}

void Cell::Set_Y(const int NewY)
{
    y = NewY;
}

void Cell::Set_X(const int NewX)
{
    x = NewX;
}

void Cell::Set_Char(const char NewChar)
{
    CellChar = NewChar;
}

Reversi::Reversi()
{
    height = -1;
    width = -1;
}

Reversi::Reversi(const int NewDimension)
{
    if(NewDimension<4)
    {    
        cout<< "Width or Height can not be less than 4.";
        exit(1);
    }
    height = NewDimension;
    width = NewDimension;
    
    MakeFirstBoard();
}

Reversi::Reversi(const int NewHeight,const int NewWidth)
{

    if(NewHeight<4 || NewWidth<4)
    {    
        cout<< "Width or Height can not be less than 4.";
        exit(1);
    }
    
    height = NewHeight;
    width = NewWidth; 
    
    MakeFirstBoard();
}

void Reversi::Set_Height(const int NewHeight)
{
    height = NewHeight;
}

void Reversi::Set_Width(const int NewWidth)
{
    width = NewWidth;
}

void Reversi::MakeFirstBoard()
{
    gameCells.reserve(Get_Height()+10);
    for(int i=0; i<Get_Height(); ++i)
    {
        gameCells[i].reserve(Get_Width()+10);
        for(int j=0; j<Get_Width(); ++j)
        {   
            gameCells[i][j].Set_Y(i);
            gameCells[i][j].Set_X(j);
            gameCells[i][j].Set_Char(EMPTY);  
                        
            if((i+1==(Get_Height())/2 && j+1==(Get_Width())/2) ||
               (i==(Get_Height())/2 && j==(Get_Width())/2))
            {
                gameCells[i][j].Set_Y(i);
                gameCells[i][j].Set_X(j);
                gameCells[i][j].Set_Char(COMPUTER);

                AddLivingCell();
            }
            if((i==(Get_Height())/2 && j+1==(Get_Width())/2) ||
               (i+1==(Get_Height())/2 && j==(Get_Width())/2))
            {
                gameCells[i][j].Set_Y(i);
                gameCells[i][j].Set_X(j);
                gameCells[i][j].Set_Char(USER);

                AddLivingCell();
            }
        }
    }   
}

void Reversi::PrintToScreen() const
{   
    cout << "   ";
    for(char i='a'; i<=96+Get_Width(); ++i)
        {cout << i << " ";}

    cout << endl;
    for(int i=1; i<=Get_Height(); ++i)
        {
        if(i<10)
            {
            cout << " " << i << " ";
            for(int j=0; j<Get_Width(); ++j)
                {cout << gameCells[i-1][j].Get_Char() << " ";}
            cout << "\n";
            }
        if(i>=10)
            {
            cout << i << " ";
            for(int j=0; j<Get_Width(); ++j)
                {cout << gameCells[i-1][j].Get_Char() << " ";}
            cout << "\n";
            }
        }
}

void Reversi::ComputerAttack()
{
    int TakenCells=0;
    int MaxTakenCells=0;
    int SizeOf_SC=0;
    vector<Cell>StrongCells;
    
    for(int i=0; i<Get_Height(); ++i)
    {
        for(int j=0; j<Get_Width(); ++j)
        {
            if(ControlAttack(i, j, COMPUTER, USER, TakenCells)==true)
            {
                
                if(TakenCells > MaxTakenCells)
                {
                    StrongCells.clear();
                    MaxTakenCells = TakenCells;
                    StrongCells.push_back(gameCells[i][j]);
                    SizeOf_SC=1;

                }
                if(MaxTakenCells == TakenCells)
                {
                    StrongCells.push_back(gameCells[i][j]);
                    SizeOf_SC +=1;     
                }
            }       
        }
    }
    
    if(SizeOf_SC>0)
    {
        int RandomIndex;
        srand (time(NULL));
        RandomIndex = rand() % SizeOf_SC;
    
    
        int PositionY = StrongCells[RandomIndex].Get_Y();    
        int PositionX = StrongCells[RandomIndex].Get_X();

        RealizeAttack(PositionY, PositionX, COMPUTER, USER);
    }
}

void Reversi::UserAttack(const int posY, const int posX)
{
    RealizeAttack(posY, posX, USER, COMPUTER);
}

bool Reversi::ControlAttack(const int posY, const int posX, 
                            const char competitor, const char rival, 
                            int& TakenCells) const
{
    bool result;
    TakenCells = 0;
    
    if(gameCells[posY][posX].Get_Char() != EMPTY ||
       posY>= Get_Height() || posX>= Get_Width() ||
       posY<0 || posX <0)
    {   
        result = false;
    }
    
    else
    {
        
        //for line -left-
        if(posX-1>=0 && gameCells[posY][posX-1].Get_Char() == rival)
            {
            for(int i=1; posX-i >= 0 && 
                         gameCells[posY][posX-i].Get_Char() == rival; ++i)
                {
                if(posX-i-1 >= 0 &&
                   gameCells[posY][posX-i-1].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }

        //for line -right-
        if(posX+1<Get_Width() && gameCells[posY][posX+1].Get_Char() == rival)
            {
            for(int i=1; posX+i < Get_Width() &&
                         gameCells[posY][posX+i].Get_Char() == rival; ++i)
                {
                if(posX+i+1 < Get_Width() &&
                   gameCells[posY][posX+i+1].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }
        
        //for column -up-
        if(posY-1>=0 && gameCells[posY-1][posX].Get_Char() == rival)
            {
            for(int i=1; posY-i >= 0 &&
                         gameCells[posY-i][posX].Get_Char() == rival; ++i)
                {
                if(posY-i-1>=0 && 
                   gameCells[posY-i-1][posX].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }
        
        //for column -down-
        if(posY+1<Get_Height() 
           && gameCells[posY+1][posX].Get_Char() == rival)
            {
            for(int i=1; posY+i < Get_Height() &&
                         (gameCells[posY+i][posX].Get_Char() == rival); ++i)
                {
                if(posY+i+1 < Get_Height() && 
                   gameCells[posY+i+1][posX].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }

        //for crosswise -left-up-
        if(posY-1>=0 && posX-1>=0 && 
           gameCells[posY-1][posX-1].Get_Char() == rival)
            {
            for(int i=1; posY-i >= 0 &&
                        posX-i >= 0 &&
                        gameCells[posY-i][posX-i].Get_Char() == rival; ++i)
                {
                if(posY-i-1>=0 && posX-i-1>=0 && 
                   gameCells[posY-i-1][posX-i-1].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }

        //for crosswise -left-down-
        if(posY+1<Get_Height() && posX-1>=0 && 
           gameCells[posY+1][posX-1].Get_Char() == rival)
            {
            for(int i=1; posY+i < Get_Height() &&
                        posX-i >= 0 &&
                        gameCells[posY+i][posX-i].Get_Char() == rival; ++i)
                {
                if(posX-i-1>=0 && posY+i+1 < Get_Height() && 
                   gameCells[posY+i+1][posX-i-1].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }

        //for crosswise -right-down-
        if(posY+1<Get_Height() && posX+1<Get_Width() && 
           gameCells[posY+1][posX+1].Get_Char() == rival)
            {
            for(int i=1; posY+i < Get_Height() &&
                        posX+i < Get_Width() &&
                        gameCells[posY+i][posX+i].Get_Char() == rival; ++i)
                {
                if(posY+i+1<Get_Height() && posX+i+1<Get_Width() && 
                   gameCells[posY+i+1][posX+i+1].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
   
                }
            }

        //for crosswise -right-up-
        if(posY-1>=0 && posX+1<Get_Width() && 
           gameCells[posY-1][posX+1].Get_Char() == rival)
            {
            for(int i=1; posY-i >= 0 &&
                        posX+i < Get_Width() &&
                        gameCells[posY-i][posX+i].Get_Char() == rival; ++i)
                {
                if(posY-i-1 >=0 &&  posX+i+1< Get_Width() && 
                   gameCells[posY-i-1][posX+i+1].Get_Char() == competitor)
                    {TakenCells = TakenCells+i;}
                }
            }
    
    if(TakenCells == 0)
        result = false;

    else 
        result = true;
    
    return result;
    
    }

    return result;
}



//realizes attack on columnpoint and linepoint for competitor
void Reversi::RealizeAttack(const int posY, const int posX, 
                            const char competitor, const char rival)
{
    
        //for line -left-
        if(posX-1>=0 && 
           gameCells[posY][posX-1].Get_Char() == rival)
            {
            for(int i=1; posX-i >= 0 &&
                         gameCells[posY][posX-i].Get_Char() == rival; ++i)
                {
                if(posX-i-1 >= 0 && 
                   gameCells[posY][posX-i-1].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY][posX-j].Set_Char(competitor);}              
                    }
                }
            }

        //for line -right-
        if(posX+1< Get_Width() && 
           gameCells[posY][posX+1].Get_Char() == rival)
            {
            for(int i=1; posX+i < Get_Width() &&
                         gameCells[posY][posX+i].Get_Char() == rival; ++i)
                {
                if(posX+i+1 < Get_Width() &&
                   gameCells[posY][posX+i+1].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY][posX+j].Set_Char(competitor);}
                    }
                }
            }

        //for column -up-
        if(posY-1>=0 && 
           gameCells[posY-1][posX].Get_Char() == rival)
            {
            for(int i=1; posY-i >= 0 &&
                         gameCells[posY-i][posX].Get_Char() == rival; ++i)
                {
                if(posY-i-1 >= 0 &&
                   gameCells[posY-i-1][posX].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i+1; ++j)
                        {gameCells[posY-j][posX].Set_Char(competitor);}                 
                    }
                }
            }

        //for column -down-
        if(posY+1<Get_Height() && 
           gameCells[posY+1][posX].Get_Char() == rival)
            {
            for(int i=1; posY+i < Get_Height() &&
                         gameCells[posY+i][posX].Get_Char() == rival; ++i)
                {
                if(posY+i+1 < Get_Height() &&
                   gameCells[posY+i+1][posX].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY+j][posX].Set_Char(competitor);}        
                    }
                }
            }

        //for crosswise -left-up-
        if(posY-1>=0 && posX-1>=0 &&
           gameCells[posY-1][posX-1].Get_Char() == rival)
            {
            for(int i=1; posY-i >= 0 &&
                        posX-i >= 0 &&
                        gameCells[posY-i][posX-i].Get_Char() == rival; ++i)
                {
                if(posY-i-1>=0 && posX-i-1>=0 &&
                   gameCells[posY-i-1][posX-i-1].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY-j][posX-j].Set_Char(competitor);}                         
                    }
                }
            }

        //for crosswise -left-down-
        if(posY+1<Get_Height() && posX-1>=0 && 
           gameCells[posY+1][posX-1].Get_Char() == rival)
            {
            for(int i=1; posY+i < Get_Height() &&
                        posX-i >= 0 &&
                        gameCells[posY+i][posX-i].Get_Char() == rival; ++i)
                {
                if(posX-i-1>=0 && posY+i+1<Get_Height() &&
                   gameCells[posY+i+1][posX-i-1].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY+j][posX-j].Set_Char(competitor);}                     
                    }
                }
            }

        //for crosswise -right-down-
        if(posY+1<Get_Height() && posX+1<Get_Width() &&
           gameCells[posY+1][posX+1].Get_Char() == rival)
            {
            for(int i=1; posY+i < Get_Height() &&
                        posX+i < Get_Width() &&
                        gameCells[posY+i][posX+i].Get_Char() == rival; ++i)
                {
                if(posY+i+1<Get_Height() && posX+i+1<Get_Width() &&
                   gameCells[posY+i+1][posX+i+1].Get_Char() == competitor)
                    {              
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY+j][posX+j].Set_Char(competitor);}                      
                    }
                }
            }

        //for crosswise -right-up-
        if(posY-1>=0 && posX+1<Get_Width() &&
           gameCells[posY-1][posX+1].Get_Char() == rival)
            {
            for(int i=1; posY-i >= 0 &&
                        posX+i < Get_Width() &&
                        gameCells[posY-i][posX+i].Get_Char() == rival; ++i)
                {
                if(posX+i+1<Get_Width() && posY-i-1>=0 &&
                   gameCells[posY-i-1][posX+i+1].Get_Char() == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {gameCells[posY-j][posX+j].Set_Char(competitor);}
                    }
                }
            }
        
}

bool Reversi::IsEnd() const
{
    if(Get_Height()==-1 && Get_Width()==-1)  //boyutlandırılmamıs oyun;
        return false;
    
    if(IsEndUser() == true && IsEndComputer() == true)
        return true;
    else
        return false;
}


bool Reversi::IsEndUser() const
{
    int TakenCells;
    
    for(int i=0; i<Get_Height(); ++i)   
        for(int j=0; j<Get_Width(); ++j)
            if(ControlAttack(i, j, USER, COMPUTER, TakenCells) == true )
                return false;

    return true;
}

bool Reversi::IsEndComputer() const
{
    int TakenCells;
    
    for(int i=0; i<Get_Height(); ++i)   
        for(int j=0; j<Get_Width(); ++j)
            if(ControlAttack(i, j, COMPUTER, USER, TakenCells) == true )
                return false;

    return true;
}


void Reversi::playGame()
{
    
    if(height == -1 && width == -1)
    {
        int y, x;
        do{
            cout << "Enter an integer (bigger than 3) for --Height-- of board size > ";
            cin >> y;
        }while(y<4);
        Set_Height(y);
    
        do{
            cout << "Enter an integer (bigger than 3) for --Width-- of board size > ";
            cin >> x;        
        }while(x<4);
        Set_Width(x);
        
        MakeFirstBoard();
    }
    
    PrintToScreen();
    
    
    int posY, posX, TakenCells;
    
    
        if(IsEnd()!=true && IsEndUser()!=true)
        {
            string str;
            cout << "\n::User Attack::\nEnter coordinate of your attack (ex: 1a)> ";
            cin >> str;
            MakeCoordinate(str, posY, posX);
            
            while(posY<0 || posX<0 || 
                   posY>=Get_Height() || posX>=Get_Width() || 
                   ControlAttack(posY, posX, USER, COMPUTER, TakenCells)!=true)
            {
                cout << "Wrong coordinate!\n"
                     << "Please Enter again coordinate of your attack > ";
                cin >> str;
                MakeCoordinate(str, posY, posX);
                
            }
            RealizeAttack(posY, posX, USER, COMPUTER);
            AddLivingCell();
            PrintToScreen();
        }
        
        else if(IsEnd()!=true && IsEndUser()==true)
        {
            cout << "\nYou do not have any cell to play:(\n";
        }
        
        
        if(IsEnd()!=true && IsEndComputer()!=true)    
        {
            cout << "\n::Computer Attack::\n";
            ComputerAttack();
            AddLivingCell();
            PrintToScreen();
        }
        
        else if(IsEnd()!=true && IsEndComputer()==true)
        {
            cout << "\nComputer does not have any cell to play!\n";
        }
    
        if(IsEnd()==true)
        {
            cout << "\nThis game is ended!\n";  
            PrintScore(); 
        }
    
}

void Reversi::PrintScore()const
{
    
    int UserScore;
    int ComputerScore;
    
    GamersScores(UserScore, ComputerScore);
    
    if(UserScore > ComputerScore)
        {cout << "\nCONGRATULATIONS! You won the game!\n";}
    else if(UserScore < ComputerScore)
        {cout << "\nGAME OVER!\n";}
    else
        {"\nDRAW\n";}

    cout << "Score of user : " << UserScore << endl
         << "Score of computer : " << ComputerScore << endl;
}

bool Reversi::CompareGames(const Reversi OtherGame)const
{
    int firstUserScore;
    int firstComputerScore;
    
    GamersScores(firstUserScore, firstComputerScore);
    
    int secondUserScore;
    int secondComputerScore;
    
    OtherGame.GamersScores(secondUserScore, secondComputerScore);
    
    if(firstUserScore-firstComputerScore > secondUserScore-secondComputerScore)
        return true;
    else
        return false;
}

void Reversi::GamersScores(int &UserScore, int &ComputerScore)const
{
    UserScore = 0;
    ComputerScore = 0;
    
    for(int i=0; i<Get_Height(); ++i)
    {
        for(int j=0; j<Get_Width(); ++j)
        {
            if(gameCells[i][j].Get_Char() == USER)
                UserScore +=1;
            
            else if(gameCells[i][j].Get_Char() == COMPUTER)
                ComputerScore +=1;
        }
    }
}

void Reversi::WriteToFile(const char *FileName) const
{
    ofstream OutputFile;
    
    OutputFile.open(FileName);
       
    for(int i=0; i<Get_Height(); ++i)
    {
        for(int j=0; j<Get_Width(); ++j)
            OutputFile << gameCells[i][j].Get_Char();
        OutputFile <<endl;
    }
    
    OutputFile.close();
    
}

void Reversi::ReadFromFile(const char *FileName)
{    
    gameCells.clear();
    
    ifstream InputFile;
    InputFile.open(FileName);
    
    string temp;
    int i=0;
    int j=0;
    
    gameCells.resize(i+1);
    
    do{
        getline(InputFile, temp);
        for(j=0; j<temp.length(); ++j)
            {
            gameCells[i].push_back(Cell(i, j, temp[j]));
            }
        if(temp.length() > 0)
            Set_Width(temp.length()); 
        
        i=i+1;
        gameCells.resize(i+1);        
    }while(InputFile.eof()==false);
    
   
    Set_Height(i-1);

    
    InputFile.close();
}

void Reversi::MakeCoordinate(string coordinate, int &posY, int &posX) 
{
    if(coordinate[0]<='9' && coordinate[0]>'0')
        {
        if(coordinate[1]<='9' && coordinate[1]>='0')
            {
             posY = ((int)(coordinate[0]-48)*10) + ((int)coordinate[1]-48) -1;
            if(coordinate[2]<='z' && coordinate[2]>='a')
                {
                posX = (int(coordinate[2])-97);
                }
            }
        else if(coordinate[1]<='z' && coordinate[1]>='a')
            {
            posY = (int)coordinate[0]-49;
            posX = (int(coordinate[1])-97);
            }
        }
}
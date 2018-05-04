// reversi.cpp
//
// Created on 05/10/2015 by Osman_Suzer

#include"reversi.h" 
#include<iostream>

using namespace std;

//In general; functions are in this function
//Supplies continuousness of the game
void TheGame(char array[20][20], int dimension)
{

    int numberofstone;
    int columnpoint, linepoint;
    char CoordinateArray[4];

    while(IsContinuous(array, dimension, COMPUTER, USER)!=false ||
          IsContinuous(array, dimension, USER, COMPUTER)!=false)
        {
        cout << "Enter your coordinate > ";
        cin >> CoordinateArray;

        while(IsCoordinateCorrect(CoordinateArray) != true)
            {
            cout << "Wrong choise!\nPlease enter again coordinate > ";
            cin >> CoordinateArray;
            }
        
        if(IsCoordinateCorrect(CoordinateArray) == true)
            {
            MakeCoordinate(CoordinateArray, &columnpoint, &linepoint);
            }
        
        while(IsContinuous(array, dimension, USER, COMPUTER) == true &&
              (ControlOfAttack(array, dimension, columnpoint, linepoint, 
                                     USER, COMPUTER, &numberofstone) == false ||
               IsCoordinateCorrect(CoordinateArray) == false))
            {
            cout << "Wrong choise!\nPlease enter again coordinate > ";
            cin >> CoordinateArray;
            if(IsCoordinateCorrect(CoordinateArray) == true && 
               IsContinuous(array, dimension, USER, COMPUTER) == true)
                {
                MakeCoordinate(CoordinateArray, &columnpoint, &linepoint);
                }
            }

        if(ControlOfAttack(array, dimension, columnpoint, linepoint, 
                                          USER, COMPUTER, &numberofstone)==true)
            {
            cout << ":::::::::::::::::::   USER   ::::::::::::::::::::::::::\n";
            RealizeAttack(array, dimension, columnpoint, linepoint, 
                                                                USER, COMPUTER);
            PrintTheGame(array, dimension);
            }
        else
            {cout << "USER : You don't have anywhere to play!\n";}


        if(IsContinuous(array, dimension, COMPUTER, USER) == true)
            {
            cout << "::::::::::::::::::: COMPUTER ::::::::::::::::::::::::::\n";
            ComputerAttack(&columnpoint, &linepoint, dimension, array, 
                                                                COMPUTER, USER);
            RealizeAttack(array, dimension, columnpoint, linepoint, 
                                                                COMPUTER, USER);
            PrintTheGame(array, dimension);
            }
        else
            {cout << "COMPUTER : It doesn't have anywhere to play!\n";}

        }
}

//takes dimension of game's board 
int Take_Dimension()
{
    int dimension;
    
    cout << "Enter an even (4-20) for table of the game > ";
    cin >> dimension;
    
    while(dimension<4 || dimension>20 || dimension%2!=0)
        {
        cout << "Mistake choosing! Please enter again an even (4-20) >";
        cin >> dimension;
        }
    
    return dimension;
}


//make first board
void MakefirstTable(char array[20][20], int dimension)
{
    for(int i=0; i<dimension; ++i)
        {
        for(int j=0; j<dimension; ++j)
            {
            array[i][j] = '.';
            if(i+1==dimension/2 && j+1==dimension/2 ||
               i+1==(dimension/2+1) && j+1==(dimension/2+1))
                {array[i][j] = COMPUTER;}
            else if(i+1==dimension/2 && j+1==(dimension/2+1) ||
                    i+1==(dimension/2+1) && j+1==dimension/2)
                {array[i][j] = USER;}
            }
        }
}

//print the board of game to console
void PrintTheGame(char array[20][20], int dimension)
{
    cout << "   ";
    for(char i='a'; i<=96+dimension; ++i)
        {cout << i << " ";}

    cout << endl;
    for(int i=1; i<=dimension; ++i)
        {
        if(i<10)
            {
            cout << " " << i << " ";
            for(int j=0; j<dimension; ++j)
                {cout << array[i-1][j] << " ";}
            cout << "\n";
            }
        if(i>=10)
            {
            cout << i << " ";
            for(int j=0; j<dimension; ++j)
                {cout << array[i-1][j] << " ";}
            cout << "\n";
            }
        }
    
}

//check the attack on columnpoint and linepoint for competitor
//keep the taken stones from rival for competitor -numberofstones-
bool ControlOfAttack(const char array[20][20], int dimension, 
                     int columnpoint, int linepoint, 
                     char competitor, char rival, 
                     int *numberofstone)
{
    *numberofstone=0;
    bool result;
    
    if(array[columnpoint][linepoint] != '.' || 
       linepoint>dimension-1 || 
       columnpoint>dimension-1 ||
       linepoint < 0 ||
       columnpoint < 0)
            {result = false;}
    
    else
        {
        //for line -left-
        if(array[columnpoint][linepoint-1] == rival)
            {
            for(int i=1; linepoint-i >= 0 &&
                         array[columnpoint][linepoint-i] == rival; ++i)
                {
                if(array[columnpoint][linepoint-i-1] == competitor)
                    {*numberofstone = *numberofstone+i;}
                }
            }

        //for line -right-
        if(array[columnpoint][linepoint+1] == rival)
            {
            for(int i=1; linepoint+i < dimension &&
                         array[columnpoint][linepoint+i] == rival; ++i)
                {
                if(array[columnpoint][linepoint+i+1] == competitor)
                    {*numberofstone = *numberofstone+i;}
                }
            }
        
        //for column -up-
        if(array[columnpoint-1][linepoint] == rival)
            {
            for(int i=1; columnpoint-i >= 0 &&
                         array[columnpoint-i][linepoint] == rival; ++i)
                {
                if(array[columnpoint-i-1][linepoint] == competitor)
                    {*numberofstone = *numberofstone+i;}
                }
            }
        
        //for column -down-
        if(array[columnpoint+1][linepoint] == rival)
            {
            for(int i=1; columnpoint+i < dimension &&
                         (array[columnpoint+i][linepoint] == rival); ++i)
                {
                if(array[columnpoint+i+1][linepoint] == competitor)
                    {*numberofstone = *numberofstone+i;}
                }
            }

        //for crosswise -left-up-
        if(array[columnpoint-1][linepoint-1] == rival)
            {
            for(int i=1; columnpoint-i >= 0 &&
                        linepoint-i >= 0 &&
                        array[columnpoint-i][linepoint-i] == rival; ++i)
                {
                if(array[columnpoint-i-1][linepoint-i-1] == competitor)
                    {*numberofstone = *numberofstone+i;}
                }
            }

        //for crosswise -left-down-
        if(array[columnpoint+1][linepoint-1] == rival)
            {
            for(int i=1; columnpoint+i <= dimension-1 &&
                        linepoint-i >= 0 &&
                        array[columnpoint+i][linepoint-i] == rival; ++i)
                {
                if(array[columnpoint+i+1][linepoint-i-1] == competitor)
                    {*numberofstone = *numberofstone+i;}

                }
            }

        //for crosswise -right-down-
        if(array[columnpoint+1][linepoint+1] == rival)
            {
            for(int i=1; columnpoint+i <= dimension-1 &&
                        linepoint+i <= dimension-1 &&
                        array[columnpoint+i][linepoint+i] == rival; ++i)
                {
                if(array[columnpoint+i+1][linepoint+i+1] == competitor)
                    {*numberofstone = *numberofstone+i;}
   
                }
            }

        //for crosswise -right-up-
        if(array[columnpoint-1][linepoint+1] == rival)
            {
            for(int i=1; columnpoint-i >= 0 &&
                        linepoint+i <= dimension-1 &&
                        array[columnpoint-i][linepoint+i] == rival; ++i)
                {
                if(array[columnpoint-i-1][linepoint+i+1] == competitor)
                    {*numberofstone = *numberofstone+i;}
                }
            }
        
        }
    
    if(*numberofstone== 0)
        result = false;

    else 
        result = true;
    
    return result;

}

//realizes attack on columnpoint and linepoint for competitor
void RealizeAttack(char array[20][20], int dimension, 
                     int columnpoint, int linepoint, 
                     char competitor, char rival)
{
        //for line -left-
        if(array[columnpoint][linepoint-1] == rival)
            {
            for(int i=1; linepoint-i >= 0 &&
                         array[columnpoint][linepoint-i] == rival; ++i)
                {
                if(array[columnpoint][linepoint-i-1] == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint][linepoint-j] = competitor;}              
                    }
                }
            }

        //for line -right-
        if(array[columnpoint][linepoint+1] == rival)
            {
            for(int i=1; linepoint+i < dimension &&
                         array[columnpoint][linepoint+i] == rival; ++i)
                {
                if(array[columnpoint][linepoint+i+1] == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint][linepoint+j] = competitor;}
                    }
                }
            }

        //for column -up-
        if(array[columnpoint-1][linepoint] == rival)
            {
            for(int i=1; columnpoint-i >= 0 &&
                         array[columnpoint-i][linepoint] == rival; ++i)
                {
                if(array[columnpoint-i-1][linepoint] == competitor)
                    {
                    for(int j=0; j<=i+1; ++j)
                        {array[columnpoint-j][linepoint] = competitor;}                 
                    }
                }
            }

        //for column -down-
        if(array[columnpoint+1][linepoint] == rival)
            {
            for(int i=1; columnpoint+i < dimension &&
                         array[columnpoint+i][linepoint] == rival; ++i)
                {
                if(array[columnpoint+i+1][linepoint] == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint+j][linepoint] = competitor;}        
                    }
                }
            }

        //for crosswise -left-up-
        if(array[columnpoint-1][linepoint-1] == rival)
            {
            for(int i=1; columnpoint-i >= 0 &&
                        linepoint-i >= 0 &&
                        array[columnpoint-i][linepoint-i] == rival; ++i)
                {
                if(array[columnpoint-i-1][linepoint-i-1] == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint-j][linepoint-j] = competitor;}                         
                    }
                }
            }

        //for crosswise -left-down-
        if(array[columnpoint+1][linepoint-1] == rival)
            {
            for(int i=1; columnpoint+i <= dimension-1 &&
                        linepoint-i >= 0 &&
                        array[columnpoint+i][linepoint-i] == rival; ++i)
                {
                if(array[columnpoint+i+1][linepoint-i-1] == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint+j][linepoint-j] = competitor;}                     
                    }
                }
            }

        //for crosswise -right-down-
        if(array[columnpoint+1][linepoint+1] == rival)
            {
            for(int i=1; columnpoint+i <= dimension-1 &&
                        linepoint+i <= dimension-1 &&
                        array[columnpoint+i][linepoint+i] == rival; ++i)
                {
                if(array[columnpoint+i+1][linepoint+i+1] == competitor)
                    {              
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint+j][linepoint+j] = competitor;}                      
                    }
                }
            }

        //for crosswise -right-up-
        if(array[columnpoint-1][linepoint+1] == rival)
            {
            for(int i=1; columnpoint-i >= 0 &&
                        linepoint+i <= dimension-1 &&
                        array[columnpoint-i][linepoint+i] == rival; ++i)
                {
                if(array[columnpoint-i-1][linepoint+i+1] == competitor)
                    {
                    for(int j=0; j<=i; ++j)
                        {array[columnpoint-j][linepoint+j] = competitor;}
                    }
                }
            }
        
}

//constitute coordinate to computer -According to max taken stone-
void ComputerAttack(int *columnpoint, int *linepoint, 
                    int dimension, const char array[20][20], 
                    char computer, char user)
{
    int numberofstone, maxstone=0;
    
    for(int i=0; i<dimension; ++i)
        {
        for(int j=0; j<dimension; ++j)
            {
            if(ControlOfAttack(array, dimension, i, j, 
                                          computer, user, &numberofstone)==true)
                {
                if(numberofstone>maxstone)
                    {
                    maxstone=numberofstone;
                    *columnpoint = i;
                    *linepoint = j;
                    }
                //it is to increase randomness...
                if(numberofstone>0 && numberofstone==maxstone)
                    {
                    if(maxstone % 2 ==0)
                        {*columnpoint = i;
                         *linepoint = j;}
                    }
                }
            }
        }

}

//checks continuity for competitor
bool IsContinuous(const char array[20][20], int dimension, 
                  char competitor, char rival)
{
    int k =0;
    int numberofstone;
    
    for(int i=0; i<dimension; ++i)
        {
        for(int j=0; j<dimension; ++j)
            {
            if(ControlOfAttack(array, dimension, i, j, 
                                       competitor, rival, &numberofstone)==true)
                {k=k+1;}
            }
        }
    
    if(k>0)
        return true;
    else
        return false;
}

//declares victorious and scores
void ScoreOfGame(const char array[20][20], int dimension, 
                                                       char computer, char user)
{
    int score_of_computer=0;
    int score_of_user=0;

    for(int i=0; i<dimension; ++i)
        {
        for(int j=0; j<dimension; ++j)
            {
            if(array[i][j]==computer)
                {
                score_of_computer += 1;
                }
            if(array[i][j]==user)
                {
                score_of_user += 1;    
                }
            }
        }

    if(score_of_user > score_of_computer)
        {
        cout << "\nCONGRATULATIONS! You won the game!\n";
        }

    else if(score_of_user < score_of_computer)
        {
        cout << "\nGAME OVER!\n";
        }

    else
        {
        "\nDRAW\n";
        }

    cout << "Score of user : " << score_of_user << endl
         << "Score of computer : " << score_of_computer << endl;
}

//converts string coordinate to integer coordinates 
void MakeCoordinate(const char array[4], int *columnpoint, int *linepoint)
{
    if(array[0]<='9' && array[0]>'0')
        {
        if(array[1]<='9' && array[1]>='0')
            {
             *columnpoint = ((int)(array[0]-48)*10) + ((int)array[1]-48) -1;
            if(array[2]<='z' && array[2]>='a')
                {
                *linepoint = (int(array[2])-97);
                }
            }
        else if(array[1]<='z' && array[1]>='a')
            {
            *columnpoint = (int)array[0]-49;
            *linepoint = (int(array[1])-97);
            }
        }
}

//checks spelling of coordinate array
bool IsCoordinateCorrect(const char array[4])
{
    bool result;
    
    if(array[0]<='9' && array[0]>'0')
        {
        if(array[1]<='9' && array[1]>='0')
            {
            if(array[2]<='z' && array[2]>='a')
                {result = true;}
            else
                {result = false;} 
            }
        else if(array[1]<='z' && array[1]>='a')
            {result = true;}
        else
            {result = false;}
        }
     else 
        {result = false;} 

    return result;
}

// HW05_131044051_Osman_SUZER
// main.cpp
//
// Created on 10/12/2015 by Osman_SUZER

#include "reversi.h"
#include <iostream>

using namespace std;
using namespace TheGameSpace;


int main(int argc, char** argv) {
    
    Reversi Game2(8);
    Reversi Game1;        

    
    char command1;
    int command;
    do
    {
        cout << "a: to play Game1.\n"
             << "b: to play Game2.\n" //board dimension == 8x8 // used constructor 
             << "------------------------------\n"
             << "Please choose a command > ";
        cin >> command1;
        if(command1 == 'a' || command1 == 'A')
            Game1.playGame();
        else if(command1 == 'b' || command1 == 'B')
            Game2.playGame();
        else
            cout << "Wrong choise!\n";
        
            do{          
                cout << "\n----------------------------\n"
                     << "0: CONTINUE THE GAME.\n"
                     << "1: COMPUTER ATTACK for Game1 (with ++Game1).\n"
                     << "2: COMPUTER ATTACK for Game2 (with Game2++).\n"
                     << "3: PRINT Game1 (with cout <<).\n"
                     << "4: PRINT Game2 (with cout <<).\n"
                     << "5: PRINT SCORE for Game1.\n"
                     << "6: PRINT SCORE for Game2.\n"
                     << "7: RESIZE BOARD for Game1.\n"
                     << "8: RESIZE BOARD for Game2.\n"
                     << "9: COMPARE Games.\n"
                     << "10:COPY a new Game to Game1.\n"
                     << "11:COMPLETE THE GAME.\n"
                     << "------------------------------\n"
                        
                     << "Please choose a command > ";
                cin >> command;
                cout << endl;
                
                if(command == 1)  //  ++Reversi
                {
                    ++Game1;
                    cout << Game1;
                }
                else if(command == 2)  //  ++Reversi
                {
                    Game2++;
                    cout << Game2;
                }
                
                else if(command == 3)  //cout << Reversi
                {
                    cout << Game1;
                }
                else if(command == 4)  //cout << Reversi
                {
                    cout << Game2;
                }
                
                else if(command == 5)
                {
                    int user, computer;
                    Game1.GamersScores(user, computer);
                    cout << "USER     : " << user << endl
                         << "COMPUTER : " << computer << endl;
                    
                }
                else if(command == 6)
                {
                    int user, computer;
                    Game2.GamersScores(user, computer);
                    cout << "USER     : " << user << endl
                         << "COMPUTER : " << computer << endl;
                }
                
                else if(command == 7)
                {   
                    int y, x;
                    
                    do{
                        cout << "Enter an integer (bigger than 3) for --Height-- of board size > ";
                        cin >> y;
                    }while(y<4);
                
    
                    do{
                        cout << "Enter an integer (bigger than 3) for --Width-- of board size > ";
                        cin >> x;        
                    }while(x<4);
                    
                    Game1.Resize_Dimension(y, x);
                }
                
                else if(command == 8)
                {
                    int y, x;
                    
                    do{
                        cout << "Enter an integer (bigger than 3) for --Height-- of board size > ";
                        cin >> y;
                    }while(y<4);
                
    
                    do{
                        cout << "Enter an integer (bigger than 3) for --Width-- of board size > ";
                        cin >> x;        
                    }while(x<4);
                    
                    Game2.Resize_Dimension(y, x);
                }   
                
                else if(command == 9)
                {
                    if(Game1.CompareGames(Game2))
                        cout << "Game1 is better than Game2.\n";
                    else if(Game2.CompareGames(Game1))
                        cout << "Game2 is better than Game1.\n";
                    else
                        cout << "SCORELESS!\n";
                }                
                else if(command == 10)
                {
                    Reversi Game(Game1);        // copy constructor
                    
                    cout << "Original Reversi > \n" << Game1 << endl;
                    cout << "Copy Reversi > \n" << Game;
                
                }
                
                else if(command != 11)
                {
                cout << "Wrong choise! Please try again.\n";
                }
                
            }while(command != 0 && command != 11);
            
    }while(command == 0 && (Game1.IsEnd()!=true || Game2.IsEnd()!=true));
    
    cout << "For Game1: \n";
    Game1.PrintScore();
    
    cout << "For Game2: \n";
    Game2.PrintScore();
    

    cout << "\n---------GOODBYE!-----------\n";
    
    return 0;
}
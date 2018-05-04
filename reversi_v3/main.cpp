// HW05_131044051_Osman_SUZER
// main.cpp
//
// Created on 29/11/2015 by Osman_SUZER

#include <iostream>
#include "reversi.h"
#include <vector>
#include <string>

using namespace std;

int Reversi::LivingCell = 0;

int main(int argc, char** argv) {
    
    Reversi Game1;        
          
    char command;
    
    do
    {
        Game1.playGame();

            do{          
                cout << "\n----------------------------\n"
                     << "0: CONTINUE THE GAME.\n"
                     << "1: UNDO (with --).\n"
                     << "2: USER ATTACK (with +=).\n"
                     << "3: COMPUTER ATTACK (with ++).\n"
                     << "4: PRINT A CELL (with cell[] and cout <<).\n"
                     << "5: PRINT A CELL (with cell() and cout <<).\n"
                     << "6: PRINT THE GAME (with cout <<).\n"
                     << "7: COMPLETE THE GAME.\n"
                     << "------------------------------\n"
                        
                     << "Please choose a command > ";
                cin >> command;
                cout << endl;
                
                if(command == '1')    // --Reversi 
                {
                    --Game1;
                    cout << Game1;    // <<Reversi
                }
                
                else if(command == '2')     // += Cell
                {   
                    int Y , X;
                    cout << Game1;
                    cout << "Enter an integer for y coordinate : ";
                    cin >> Y;
                    cout << "\nEnter an integer for x coordinate : ";
                    cin >> X;
                    Game1 += Cell(Y,X);
                    cout << Game1;
                }
                
                else if(command == '3')  //  ++Reversi
                {
                    ++Game1;
                    cout << Game1;
                }
                else if(command == '4')  // Reversi["str"]
                {
                    string str;
                    cout << "Enter a string for coordinate (for example '1a') > ";
                    cin >> str;
                    Cell excell = Game1[str];
                    cout << excell;
                }
                else if(command == '5')  //Reversi("str","str")
                {   
                    string strY, strX;
                    cout << "Enter an integer for y-coordinate > ";
                    cin >> strY;
                    cout << "\n Enter a string for x-coordinate > ";
                    cin >> strX;
                    
                    Cell excell = Game1(strY, strX);
                    cout << excell;
                }
                
                else if(command == '6')  //cout << Reversi
                {
                    cout << Game1;
                }
                else if(command != '7')
                {
                cout << "Wrong choise! Please try again.\n";
                }
                
            }while(command != '0' && command != '7');
            
    }while(command == '0' && Game1.IsEnd()!=true);
    
    Game1.PrintScore();
    
    Cell cell1;
    Cell cell2;

    cout << "Enter two integer and a character for your first Cell > ";
    cin >> cell1;                           // >> Cell
    
    cout << "\nYour first cell : \n";   
    cout << cell1;                          // << Cell

    cout << "Enter two integer and a character for your second Cell > ";
    cin >> cell2;                           // >> Cell

    cout << "\nYour second cell : \n";   
    cout << cell2;                          // << Cell
    
    
    if(cell1 != cell2)                              // Cell != Cell
        cout << "First Cell != Second Cell\n";    
    
    if(cell1 == cell2)                              // Cell == Cell
        cout << "First Cell = Second Cell\n";

    else if(cell1 < cell2)                              // Cell < Cell
        cout << "First Cell < Second Cell\n";
    
    else if(cell1 > cell2)                              // Cell > Cell
        cout << "First Cell > Second Cell\n";
    
    if(cell1 <= cell2)                              // Cell <= Cell
        cout << "First Cell <= Second Cell\n";

    else if(cell1 >= cell2)                              // Cell >= Cell
        cout << "First Cell >= Second Cell\n";
    
    cout << "\n:::::::First Cell:::::\n";
    cout << cell1;        
    cout << "Cell++ for first cell :\n";
    cout << cell1++;                                  // Cell++
    
    cout << "\n:::::::First Cell:::::\n";
    cout << cell1;
    cout << "++Cell for first cell :\n";
    cout << ++cell1;                                  // ++Cell

    cout << "\n\n:::::::Second Cell:::::\n";
    cout << cell2;
    cout << "Cell-- for first cell :\n";
    cout << cell2--;                                  // Cell--
    
    cout << "\n:::::::Second Cell:::::\n";
    cout << cell2; 
    cout << "--Cell for second cell :\n";
    cout << --cell2;                                  // --Cell
    
    return 0;
}

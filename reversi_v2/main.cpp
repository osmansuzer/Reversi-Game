// main.cpp
//
// Created on 24/11/2015 by Osman_SUZER

#include <iostream>
#include "reversi.h"
#include <vector>
#include <string>
using namespace std;

int Reversi::LivingCell = 0;

int main(int argc, char** argv) {

    Reversi Game1;        //user enter dimension 
    Reversi Game2;	  //user enter dimension and write to file
    Reversi Game3(8);	  //one parameter  
    Reversi Game4(6,8);	  //two parameter
    Reversi Game5;	  //it is read from file

    do{
        int ChosenGame;
        cout << "Choose a game (1, 2, 3, 4 or 5) >> ";
        cin >> ChosenGame;
        
        // :::::::::::::::::GAME 1::::::::::::::::::::
        if(ChosenGame == 1)
        {   
            cout << "\n::::::::::::::::::::::::Game1::::::::::::::::\n" << endl;  
            Game1.playGame();
        }   

        
        // :::::::::::::::::GAME 2::::::::::::::::::::      
        else if(ChosenGame == 2)
        {   
            cout << "\n::::::::::::::::::::::::Game2::::::::::::::::\n" << endl;
            cout << ">>>>>>> THis Game is writen to file Game2.txt <<<<<<< \n";
            Game2.playGame();
            Game2.WriteToFile("Game2.txt");
        }

        
        // :::::::::::::::::GAME 3::::::::::::::::::::    
        else if(ChosenGame == 3)
        {   
            cout << "\n::::::::::::::::::::::::Game3::::::::::::::::\n" << endl;
            cout << ">>>>> One value as contructor parameter is"
                 << " given to this Object (Game3(8))<<<<<<\n";          
            Game3.playGame();
        }

        
        // :::::::::::::::::GAME 4::::::::::::::::::::
        else if(ChosenGame == 4)
        {   
            cout << "\n::::::::::::::::::::::::Game4::::::::::::::::\n" << endl;
            cout << ">>>>> Two values as contructor parameters are"
                 << " given to this Object (Game4(6,8))<<<<<<\n" ;
            Game4.playGame();        
            
            
            cout<< "\n=====In this section,Game4 and Game5 are compared==== \n";
            cout<< "(Note:Game5 is read from file Game5.txt)\n";
            if(Game4.CompareGames(Game5)==true)
                cout << "Game4 is better than Game5\n" ;
            else
                cout << "Game4 is not better than Game5\n" ;
        }

    
        // :::::::::::::::::GAME 5::::::::::::::::::::
        else if(ChosenGame == 5)
        {   
            cout << "\n::::::::::::::::::::::::Game5::::::::::::::::\n" << endl;
            cout << ">>>>>>> THis Game is read from file Game5.txt <<<<<<<\n";
            Game5.ReadFromFile("Game5.txt");
            Game5.playGame();
        }  
        
        else
        {
            cout << "\nWrong choise! Try again.\n";
        }
             
    cout << "\nNuber of living cell: " << Reversi::NumberOfLivingCell() << endl;            
    
    }while(Game1.IsEnd()!=true || Game2.IsEnd()!=true ||
           Game3.IsEnd()!=true || Game4.IsEnd()!=true || 
           Game5.IsEnd()!=true);
   
    return 0;
}

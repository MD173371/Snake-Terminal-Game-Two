/* FILE: gameplay.h
AUTHOR: Michael Durkan
PURPOSE: Provide function prototypes for functions within gameplay.c
LAST MOD: May 19 2024  */

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gamestate.h"
#include "linkedlist.h"

void updateState( GameState* pState, int* playerPos, int* snakePos );
int userInput( char** gameBoard, int* playerPos, int numRow, int numCol );
void updatePos( LinkedList* pList, int* playerPos, int* snakePos );
void moveSnake( int numRow, int numCol, int* snakePos );                 
int checkWin( int* playerPos, int* foodPos ); 
int checkLoss( int* playerPos, int* snakePos, char** gameBoard );     
void printResult( int win );

#endif

/*FILE: gameboard.h
AUTHOR: Michael Durkan
PURPOSE: Provide function prototypes for functions within gameboard.c
LAST MOD: May 19 2024  */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

void initDim( int* numRow, int* numCol, FILE* fptr );
int** readFile( int numRow, int numCol, FILE* fptr, int** fileArray );
void setPositions( int numRow, int numCol, int* playerPos, int* snakePos, 
                   int* foodPos, int** fileArray );
char** fillGameBoard( int numRow, int numCol, char** gameBoard, int* playerPos,  
                     int* snakePos, int* foodPos );                              
void printGameBoard( int numRow, int numCol, char** gameBoard ); 

#endif

/*FILE: memory.h
AUTHOR: Michael Durkan
PURPOSE: Provide function prototypes for the functions within memory.c
LAST MOD: May 15 2024  */

#ifndef MEMORY_H
#define MEMORY_H

char** initBoardMem( int numRow , int numCol );
int** initFileArrMem( int numRow, int numCol );
void freeBoardMem( int numRow, char*** gameBoard );
void freeFileArrMem( int numRow, int*** fileArray );

#endif

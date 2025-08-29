/* FILE: gameboard.c
AUTHOR: Michael Durkan
StudentID: 17378383
UNIT: COMP1000
PURPOSE: Gameboard set and printing functions for terminal based snake game.
LAST MOD: May 19 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"
#include "gameboard.h"
#include "random.h"
#include "newsleep.h"

/*
NAME: initDim
PURPOSE: Initialize dimensions, number of row and column variables from
         first line in the map file, adding 2 to account for game border.
IMPORTS: numRow, numCol, fptr - the number of rows, columns variables and 
         pointer to file holding map.
EXPORTS: none.
*/
void initDim( int* numRow, int* numCol, FILE* fptr )
{

    /* Scan in first two integers for board dimensions into row and column 
       variables. */
    fscanf(fptr, "%d %d", numRow, numCol);

    /* Increase row and columns by two to account for borders */
    *numRow = *numRow + 2;
    *numCol = *numCol + 2; 
}

/*
NAME: readFile
PURPOSE: Read the contents of the map file and write contents into fileArray 
IMPORTS: numRow, numCol, fptr, fileArray - the number of rows, columns
         variables, pointer to file holding map and 2d array of int.
EXPORTS: fileArray - 2d array of int.
*/
int** readFile( int numRow, int numCol, FILE* fptr, int** fileArray )
{
    int i, j;

    /* Scan through each element of the file and store each integer in 
       the file array */
    for ( i = 0; i < numRow - 2; i++ )
    {
        for ( j = 0; j < numCol - 2; j++ )
        {
            fscanf(fptr, "%d ", &( fileArray[i][j] ));
        }
    }

    return fileArray;
}


/*
NAME: setPositons
PURPOSE: Set initial position of player and snake.
IMPORTS: numRow, numCol, playerPos, snakePos - number of rows and columns for 
         gameboard and the position coordinates arrays for the player and snake.
EXPORTS: none.
*/
void setPositions( int numRow, int numCol, int* playerPos, int* snakePos, 
                   int* foodPos, int** fileArray)
{
    /* Position array follows format: playerPos[<Row Number>][<Column Number>]
       and playerPos[<Row Number>][<Column Number>] (starting at row/column
       number 0) */
    int i, j;

    /* Scan through every element of the array and set character positions when
       there equivelant integer is found */
    for ( i = 0; i < numRow - 2; i++ )
    {
        for ( j = 0; j < numCol - 2; j++ )
        {
            /* Player position */
            if ( fileArray[i][j] == 1 )
            {
                playerPos[0] = i + 1;
                playerPos[1] = j + 1;
            }
            /* Food position */
            else if ( fileArray[i][j] == 2 )
            {
                foodPos[0] = i + 1;
                foodPos[1] = j + 1;
            }
            /* Snake position */
            else if ( fileArray[i][j] == 3 )
            {
                snakePos[0] = i + 1;
                snakePos[1] = j + 1;
            }
        }
    }
}

/*
NAME: fillGameboard
PURPOSE: Update the gameboard array with the position arrays of the game 
         characters
IMPORTS: numRow, numCol, gameboard, playerPos, snakePos, foodPos - number of 
         rows and columns for gameboard, gameboard 2d array of char, 
         and the position coordinates arrays for the player, snake and food.
EXPORTS: gameboard - the 2d char array once updated with the positions.
*/
char** fillGameBoard( int numRow, int numCol, char** gameBoard, int* playerPos,
                     int* snakePos, int* foodPos )
{
    int i, j;

    /* Fill the board with white space characters */
    for ( i = 0; i < numRow; i++ )
    {
        for ( j = 0; j < numCol; j++ )
        {
            gameBoard[i][j] = ' ';
        }
    }
    /* Fill the top and bottom borders with '*' characters */
    for ( j = 0; j < numCol; j++ )
    {
        gameBoard[0][j] = '*';
        gameBoard[numRow - 1][j] = '*';
    }
    /* Fill the left and right borders with '*' characters */
    for ( i = 0; i < numRow; i++ )
    {
        gameBoard[i][0] = '*';
        gameBoard[i][numCol - 1] = '*';
    }
    /* Place the food character on the board */
    gameBoard[foodPos[0]][foodPos[1]] = '@';

    /* Place the player character on the board */
    gameBoard[playerPos[0]][playerPos[1]] = 'P';

    /* Place the snake character on the board */
    gameBoard[snakePos[0]][snakePos[1]] = '~';

    return gameBoard;
}

/*
NAME: printGameBoard
PURPOSE: Print the game board in the terminal.
IMPORTS: numRow, numcol, gameBoard - the number of rows and columns of the
         gameboard, and the gameboard array.
EXPORTS: none.
*/
void printGameBoard( int numRow, int numCol, char** gameBoard )
{
    int i, j;

    /* Set cursor at start of the terminal so it overwrites previous board */
    system("tput cup 0 0");
    
    /* Print the 2d array for game board */
    for ( i = 0; i < numRow; i++ )
    {
        for ( j = 0; j < numCol; j++ )
        {
            printf( "%c", gameBoard[i][j] );
        }
        printf("\n");

    }

    /* Print the input movement controls, including room for incorrect input
       dialog */
    printf("Press 'w' key to move up   \n");
    printf("Press 's' key to move down \n");
    printf("Press 'a' key to move left \n");
    printf("Press 'd' key to move right\n");
    printf("Press 'u' key to undo      \n");
    printf("                           \n");

    /* Smooth animation with a sleep command */
    newSleep(0.003);
}

/* FILE: gameplay.c
AUTHOR: Michael Durkan
PURPOSE: Gameplay functions for terminal based snake game.
LAST MOD: May 19 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "macros.h"
#include "random.h"
#include "terminal.h"
#include "linkedlist.h"
#include "gamestate.h"

/*
NAME: updateState
PURPOSE: Update the struct position variables with the position arrays of the 
         player and snake.
IMPORTS: pState, playerPos, snakePos - GameState struct holding player and 
         snake positions, player position array and snake position array
EXPORTS: none.
*/
void updateState( GameState* pState, int* playerPos, int* snakePos )
{
    /* Update player state */
    pState->playerRowPos = playerPos[0];
    pState->playerColPos = playerPos[1];
    
    /* Update snake state */
    pState->snakeRowPos = snakePos[0];
    pState->snakeColPos = snakePos[1]; 
}

/*
NAME: userInput
PURPOSE: Accept a user input and move the character accordingly, or return
         boolean for u being pressed.
IMPORTS: gameBoard, playerPos, numRow, numCol - 2d array of chars for the game 
         board before user input, player position array, integer for number of 
         rows and integer for number of columns.
EXPORTS: pressU - int as boolean for 'u' being pressed or not.
*/
int userInput( char** gameBoard, int* playerPos, int numRow, int numCol )
{
    char dirInput;
    int invalidKey, pressU;

    invalidKey = TRUE;
    
    /* Loop for input if leading into border, or the wrong key input */
    while ( invalidKey )
    {   
        /* Accept user input without requiring the enter key by disabling 
           buffer */
        disableBuffer();
        scanf(" %c", &dirInput);
        enableBuffer();

        pressU = FALSE;
        
        /* Incerement player position in corresponding direction of input */
        /* Move up */
        if ( dirInput == 'w' )
        {
            playerPos[0] -= 1;
            invalidKey = FALSE;
        }
        /* Move left */
        else if ( dirInput == 'a' )
        {
            playerPos[1] -= 1;
            invalidKey = FALSE;
        }
        /* Move down */
        else if ( dirInput == 's' )
        {
            playerPos[0] += 1;
            invalidKey = FALSE;
        }
        /* Move right */
        else if ( dirInput == 'd' )
        {
            playerPos[1] += 1;
            invalidKey = FALSE;
        }
        /* Undo moves */
        else if ( dirInput == 'u' )
        {
            pressU = TRUE;
            invalidKey = FALSE;
        }
        else
        {
            /* Print invalid input in lowest point of screen */
            char command[20];
            sprintf(command, "tput cup %d 0", numRow + 5);
            system(command);
            printf("Invalid key input\n");
        }
    }

    /* Adjust the player position when its position is greater or less than the
       gameboard size */
    /* Vertical wrap around */
    if ( playerPos[0] > ( numRow - 2 ) )
    { 
        playerPos[0] = ( playerPos[0] + 1 ) % ( numRow - 1 );
    }
    else if ( playerPos[0] < 1 )
    {
        playerPos[0] = playerPos[0] + numRow - 2;
    }
    
    /* Horizontal wrap around */
    if ( playerPos[1] > ( numCol - 2 ) )
    {
        playerPos[1] = ( playerPos[1] + 1 ) % ( numCol - 1 );
    }
    else if ( playerPos[1] < 1 )
    {   
        playerPos[1] = playerPos[1] + numCol - 2;
    }

    return pressU;
}

/*
NAME: updatePos
PURPOSE: Update position arrays of snake and player with those stored in the 
         linkedlist head.
IMPORTS: pList, playerPos, snakePos - Linked list holding move states, 
         player position array and snake position array.
EXPORTS: none.
*/
void updatePos( LinkedList* pList, int* playerPos, int* snakePos )
{
    /* Update player position */
    playerPos[0] = ( ( GameState* )( pList->head->data ) )->playerRowPos;
    playerPos[1] = ( ( GameState* )( pList->head->data ) )->playerColPos;
    
    /* Update snake position */
    snakePos[0] = ( ( GameState* )( pList->head->data ) )->snakeRowPos;
    snakePos[1] = ( ( GameState* )( pList->head->data ) )->snakeColPos;
}

/*
NAME: moveSnake
PURPOSE: Randomly move the snake into aligning element space.
IMPORTS: numRow, numCol, snakePos - number of row and columns for board, and 
         snake position array.
EXPORTS: none.
*/
void moveSnake( int numRow, int numCol, int* snakePos )
{
    int rowMov, colMov;

    /* Set amounts to move rows and columns to zero */
    rowMov = 0;
    colMov = 0;

    /* Loop if random values equate to zero movement in any direction */
    while ( ( rowMov == 0 ) && ( colMov == 0 ) )
    {
        /* Get a random x and y movement for snake from -1 to 1 */
        rowMov = randomUCP(-1, 1);
        colMov = randomUCP(-1, 1);
    }

    /* Apply random movements to temp snake position array */
    snakePos[0] += rowMov;
    snakePos[1] += colMov;

    /* Adjust the snake position if it is greater or less than the gameboard
       size so that it loops around */
    if ( snakePos[0] > numRow - 2 )
    { 
        snakePos[0] = ( snakePos[0] + 1 ) % ( numRow - 1 );
    }
    if ( snakePos[1] > numCol - 2 )
    {
        snakePos[1] = ( snakePos[1] + 1 ) % ( numCol - 1 );
    }
    if ( snakePos[0] < 1 )
    {
        snakePos[0] = snakePos[0] + numRow - 2;
    }
    if ( snakePos[1] < 1 )
    {   
        snakePos[1] = snakePos[1] + numCol - 2;
    }
}

/*
NAME: checkWin
PURPOSE: Check if player position equals food position and return outWin true 
         if so.
IMPORTS: playerPos, foodPos - position vectors for player and food position.
EXPORTS: outWin - boolean int for determining win or not.
*/

int checkWin( int* playerPos, int* foodPos )
{
    int outWin;

    outWin = FALSE;

    if ( ( playerPos[0] == foodPos[0] ) && ( playerPos[1] == foodPos[1] ) )
    {
        outWin = TRUE;
    }

    return outWin;
}

/*
NAME: checkLoss
PURPOSE: Check the player distance from the snake to determine if a loss.
IMPORTS: playerPos, snakePos, gameBoard - the position arrays of the player
         and snake, and the 2d array game board.
EXPORTS: outLose - TRUE or FALSE int for if loss.
*/
int checkLoss( int* playerPos, int* snakePos, char** gameBoard )
{
    int outLose = FALSE;

    /* If distance between player and snake on x and y is < 1 update gameBoard
       and return true for outLose */
    if ( ( abs(playerPos[0] - snakePos[0]) <= 1 ) && 
         ( abs (playerPos[1] - snakePos[1]) <= 1 ) )
    {
        gameBoard[playerPos[0]][playerPos[1]] = '~';
        gameBoard[snakePos[0]][snakePos[1]] = ' ';
        
        outLose = TRUE;
    }

    return outLose;
}

/*
NAME: printResult
PURPOSE: Print win or lose message to terminal
IMPORTS: win - integer boolean for whether player has won or not
EXPORTS: none.
*/
void printResult( int win )
{
    if ( win ) 
    {
        printf("You win!\n");
    }
    else
    {
        printf("You lose!\n"); 
    }
}

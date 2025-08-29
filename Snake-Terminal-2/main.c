/* FILE: main.c
AUTHOR: Michael Durkan
PURPOSE: Terminal based snake game application main file.
LAST MOD: May 19 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "gameboard.h"
#include "gameplay.h"
#include "random.h"
#include "terminal.h"
#include "newsleep.h"
#include "macros.h"
#include "linkedlist.h"
#include "gamestate.h"

int main( int argc, char** argv )
{ 
    int numRow, numCol, pressU, win, lose;
    
    /* Position array follows format: ___Pos[<Row Number>][<Column Number>] 
       (starting at row/colum number 0) */
    int foodPos[2], snakePos[2], playerPos[2];
    
    char** gameBoard;
    int** fileArray;

    /* Initialise random number generator function */
    initRandom();

    /* Print error message if incorrect number of command arguments input */
    if ( argc != 2 )
    {
        printf("Error: Incorrect number of arguments\n");
        printf("Usage: ./eat <map_file_name>\n");
    }
    else
    {
        /* Open file pointer to first agument file */
        FILE* fptr = fopen(argv[1], "r");

        /* Check for null file pointer, if so print error and close program */
        if ( fptr == NULL )
        {
            perror("Could not open file");
        }
        else
        {
            /* Initialise dimensions of gameboard from first line in file */
            initDim(&numRow, &numCol, fptr);
           
            /* Initialise memory for array to hold file contents and store file
               integers in it */
            fileArray = initFileArrMem(numRow, numCol);
            fileArray = readFile(numRow, numCol, fptr, fileArray);

            /* Check for error reading FILE* stream and close program safely 
               if so, closing file pointer and freeing file array memory */
            if( ferror( fptr ) )
            {
                perror("Error reading from file");
                fclose(fptr);
                fptr = NULL;
                freeFileArrMem(numRow, &fileArray);
            }
            else
            {
                /* Create linked list to hold positions every move */
                LinkedList* moveList = createLinkedList();
                
                /* Allocate memory for struct holding initial game positions */ 
                GameState* firstState = malloc(sizeof(GameState));
                
                /* Close file pointer and set to NULL */
                fclose(fptr);
                fptr = NULL;
                
                /* Set inital game position arrays from file Array and free
                   file array memory */
                setPositions(numRow, numCol, playerPos, snakePos, foodPos, 
                             fileArray);
                freeFileArrMem(numRow, &fileArray);
                
                /* Set the struct for inital game state with position arrays
                   and insert as first node of linked list */
                updateState(firstState, playerPos, snakePos);
                insertStart(moveList, firstState);

                /* Allocate memory for gameboard, place characters on it and 
                   print on fresh terminal */
                gameBoard = initBoardMem(numRow, numCol);
                gameBoard = fillGameBoard(numRow, numCol, gameBoard, 
                            playerPos, snakePos, foodPos);    
                system("clear");
                printGameBoard(numRow, numCol, gameBoard);

                win = FALSE;
                lose = FALSE;                

                while ( !( win || lose ) )
                {
                    /* Get movement or undo input from user */
                    pressU = userInput(gameBoard, playerPos, numRow, numCol);
                    
                    if ( pressU )
                    {
                        /* Remove the start of the linked list and update
                           game position arrays */
                        removeStart(moveList);
                        updatePos(moveList, playerPos, snakePos);
                        
                        /* Update gameboard array and print */
                        gameBoard = fillGameBoard(numRow, numCol, gameBoard, 
                                playerPos, snakePos, foodPos);
                        printGameBoard(numRow, numCol, gameBoard);
                    }
                    else
                    {
                        /* Allocate memory for the following game state struct */
                        GameState* newState = malloc(sizeof(GameState)); 
                        
                        /* Update gameboard array with player position after
                           movement */
                        gameBoard = fillGameBoard(numRow, numCol, gameBoard, 
                                                playerPos, snakePos, foodPos);

                        /* Check distance from snake to determine if player 
                           has lost */
                        lose = checkLoss(playerPos, snakePos, gameBoard);

                        if ( !lose && !pressU )
                        {
                            /* Move snake to random aligning position 
                               and update board */
                            moveSnake(numRow, numCol, snakePos);
                            gameBoard = fillGameBoard(numRow, numCol, gameBoard,
                                        playerPos, snakePos, foodPos);

                            /* Check players distance to food to see if a win */
                            win = checkWin(playerPos, foodPos);
                        }
                        /* Clear terminal and print game board */
                        printGameBoard(numRow, numCol, gameBoard);

                        /* Set positions in latest struct with character 
                           positions after turn and add to move linked list */
                        updateState(newState, playerPos, snakePos);
                        insertStart(moveList, newState);
                    }
                }

                /* Free memory allocated by malloc for 2d array */
                freeBoardMem(numRow, &gameBoard);

                /* Free memoty allocated for the linked list */
                freeLinkedList(moveList);
                
                /* Print to terminal if player won or lost */
                printResult(win); 
            }
        }    
    }

    return 0;

}

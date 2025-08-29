/*FILE: gamestate.h
AUTHOR: Michael Durkan
PURPOSE: Provide game state struct functionality
LAST MOD: May 18 2024  */

#ifndef GAMESTATE_H
#define GAMESTATE_H

typedef struct
{
    int playerRowPos;
    int playerColPos;
    int snakeRowPos;
    int snakeColPos;
} GameState;

#endif

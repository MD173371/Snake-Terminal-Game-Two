# Snake-Terminal-Game-Two
Terminal based snake game written in C89 with extra features
FILE: README.txt
AUTHOR: Michael Durkan
PURPOSE: Provide documentation for terminal base snake game
LAST MOD: 18 May 2024

Overal design: Created a simple game for the linux terminal, where a player
               tries to eat food before the snake bites them. Uses a 2d array
               of characters to present the game board and position variables to 
               keep track of where the player, snake and food are. The map is read
               from a map file into the game, the snake and player wrap around
               when intersecting with the board edge, and a linkedlist is utilized
               to allow for an undo feature.
               Random.c terminal.c and newsleep.c functions where provided 
               by the course for use.
 
               Program should be run as such: ./eat <map_file_name>

               Decided to utilize the system("tput cup 0 )" command to make the
               gameplay not flicker.

               No known bugs.

               

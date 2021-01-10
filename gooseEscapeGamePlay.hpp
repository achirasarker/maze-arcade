
//File: gooseEscapeGamePlay.hpp

#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

/*This file is all about the game world.  You will modify this to add
    constants and function prototypes.  Modify gooseGamePlay.cpp to
	actually add functionality.
*/

/*
    Declare constants to indicate various game world features in the board
    array.  Modify them to fit what you would like to do in the game.  You can
    change the type if you choose to store your game board as something other
    than intengers.
*/	
// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int POWERUP = 3;

const int WIDTH = 80;
const int HEIGHT = 21;

const int PLAY_START_X = 9;
const int PLAY_START_Y = 9;
const int PLAY_INIT_SPEED = 3;
const int PLAY_NEW_SPEED = 6;

const int GOOSE_START_X = 70;
const int GOOSE_START_Y = 20;
const int GOOSE_INIT_SPEED = 2;
const int GOOSE_NEW_SPEED = 1;

const int SAFE_X = 39;
const int SAFE_Y = 9;

const int WALL_ROW = 11;
const int WALL_START_COL = 35;
const int VERT_COL_ONE = 20;
const int VERT_COL_TWO = 60;
const int LENGTH_WALL = 12;

const int NUM_GOOSE_STEP = 1;
const int NO_STEP = 0;
const int MAX_POW_STEPS = 10;

/*
    A few examples of characters both for actors and for the game board
    itself are shown.
*/	
//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%'); 
const int POWERUP_CHAR = int('P');

/*
    Game play function prototypes are give below.
*/

// print the game board function protype
void printBoard(int game_board[HEIGHT][WIDTH]);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

//add prototype for captured func
bool captured(Actor const & player, Actor const & monster);

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
*/

//fix prototype for movePlayer func
void movePlayer(int key, Actor & player, int game_board[HEIGHT][WIDTH]);

/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/

//add a prototype for moveMonster func
void moveMonster(Actor & monster, Actor & player, int game_board[HEIGHT][WIDTH]);

//add a prototype for win func
bool won(Actor const & player, Actor const & safe);

//prototype for custom random number generator
int generate_random_num(int min, int max);

//prototype for placing the power-ups on the game board
void place_powerups(int game_board[HEIGHT][WIDTH]);

//prototype for detecting collision between player and the power-ups
bool is_at_powerup(Actor & player, int game_board[HEIGHT][WIDTH]);

#endif


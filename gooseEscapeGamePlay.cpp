
//File: gooseEscapeGamePlay.cpp

#include <iostream>
#include<cstdlib>
#include<ctime>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/

// print the game board function
void printBoard(int game_board[HEIGHT][WIDTH])
{		 
    int printChar = 0;
	for (int row = 0; row < HEIGHT; row++)
	{	
		for (int col = 0; col < WIDTH; col++)
		{	
			if( game_board[row][col] != EMPTY)
			{	
				//print safe char onto game board
				if (game_board[row][col] == WINNER)
					printChar = WIN_CHAR;
				//print wall onto game board
				else if (game_board[row][col] == SHALL_NOT_PASS)
					printChar = WALL_CHAR;
				 //print powerups onto game board
				else if (game_board[row][col] == POWERUP)
					printChar = POWERUP_CHAR;
				
				terminal_put(col, row, printChar);
			}
					
		}
	}
}

//this func determines how goose moves relative to player's location
void moveMonster(Actor & monster, Actor & player, int game_board[HEIGHT][WIDTH])
{	
	int player_x = player.get_x();
	int player_y = player.get_y();
	
	int monster_x = monster.get_x();
	int monster_y = monster.get_y();
	
	int moveX = 0, moveY = 0;
	
	//if player left of goose
	if (player_x < monster_x)
	{	
		//if player above goose
		if (player_y < monster_y)
		{
			moveX = -NUM_GOOSE_STEP;
			moveY = -NUM_GOOSE_STEP;
		}
		//if player below goose
		else if (player_y > monster_y)
		{	
			moveX = -NUM_GOOSE_STEP;
			moveY = NUM_GOOSE_STEP;
		}
		//if goose on same row as player
		else 
		{
			moveX = -NUM_GOOSE_STEP;
			moveY = NO_STEP;
		}
	}
	
	//if player right of goose
	else if (player_x > monster_x)
	{	
		//if player above goose
		if (player_y < monster_y)
		{
			moveX = NUM_GOOSE_STEP;
			moveY = -NUM_GOOSE_STEP;
		}
		//if player below goose
		else if (player_y > monster_y)
		{	
			moveX = NUM_GOOSE_STEP;
			moveY = NUM_GOOSE_STEP;
		}
		//if goose on same row as player
		else 
		{
			moveX = NUM_GOOSE_STEP;
			moveY = NO_STEP;
		}
	}
	
	//if player and goose in same column
	else 
	{	
		moveX = NO_STEP;
		//if player above goose
		if (player_y < monster_y)
			moveY = -NUM_GOOSE_STEP;
		//if player below goose
		else 
			moveY = NUM_GOOSE_STEP;
	}
	
	//multiply step by speed multiplier
	moveX *= monster.get_speed();
	moveY *= monster.get_speed();
	
	//if monster can move, then update its location
	if (monster.can_move(moveX, moveY) 
	&& game_board[monster.get_y() + moveY][monster.get_x() + moveX] != WINNER
	&& game_board[monster.get_y() + moveY][monster.get_x() + moveX] != POWERUP)
      	monster.update_location(moveX, moveY);
}

//this func checks if goose location = player location
bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() &&
            player.get_y() == monster.get_y());
}

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/

//this func moves player around game board based on keys pressed
void movePlayer(int key, Actor & player, int game_board[HEIGHT][WIDTH])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
    
    //multiply step by speed multiplier
    yMove *=  player.get_speed();
    xMove *=  player.get_speed();
    
    //if player can move, then update its location
    if (player.can_move(xMove, yMove) &&
        game_board[player.get_y() + yMove][player.get_x() + xMove] !=
		SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

//this func checks if player reached the safe spot 
bool won(Actor const & player, Actor const & safe)
{
    return (player.get_x() == safe.get_x() &&
            player.get_y() == safe.get_y());
}

//this func generates a random number between a min and max 
int generate_random_num(int min, int max)
{
	srand(time(NULL));
	return rand() % max + min;
}

//this func places one power-up at a random location on the board
void place_powerups(int game_board[HEIGHT][WIDTH])
{	
	//generate random x,y location for powerup
	int x_powerup = generate_random_num(0, WIDTH);
	int y_powerup = generate_random_num(0, HEIGHT);
	
	//if spot is empty, then powerup can be placed at that location
	if (game_board[y_powerup][x_powerup] == EMPTY)
		game_board[y_powerup][x_powerup] = POWERUP;
}

//this func checks if a player is at a powerup location
bool is_at_powerup(Actor & player, int game_board[HEIGHT][WIDTH])
{
	return game_board[player.get_y()][player.get_x()] == POWERUP;
}



/*
Henchel Santillan and Achira Sarker
*/

/*
  For the generate_random_num function in gooseEscapeGamePlay.cpp, we 
  referred to C++.com to learn about the rand() function 
  Link: https://www.cplusplus.com/reference/cstdlib/rand/
*/

//File: gooseEscapeMain.cpp

#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/
    //make the player
	Actor player(PLAYER_CHAR, PLAY_START_X, PLAY_START_Y, false, 
			     PLAY_INIT_SPEED); 
	
	//make the monster
	Actor monster(MONSTER_CHAR, GOOSE_START_X, GOOSE_START_Y, false, 
				  GOOSE_INIT_SPEED); 
	
	//make the safe zone
	Actor safe(WIN_CHAR, SAFE_X, SAFE_Y, false, 0);
	
	//set game board array
    int game_board[HEIGHT][WIDTH] = {0};
  	
/*
    Initiallize locations in the game board to have game features.  What if you
    have many things to add to the game board?  Should you use a loop?  Does it
    make sense to store this information in a file?  Should this code be a
    function as well?
*/	
	//print the horizontal wall
	for (int count = 0; count < LENGTH_WALL; count++)
		game_board[WALL_ROW][WALL_START_COL + count] = SHALL_NOT_PASS;
	
	//print the two vertical walls
	for (int count = 0; count < LENGTH_WALL; count++)
	{
		game_board[count][VERT_COL_ONE] = SHALL_NOT_PASS;
		game_board[count][VERT_COL_TWO] = SHALL_NOT_PASS;
	}
	
	//place the win char
    game_board[SAFE_Y][SAFE_X] = WINNER;
    
	//place powerups onto board
	place_powerups(game_board);
  	
    // Call function to print the game board
    printBoard(game_board);
  	
	// Print instructions to console
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  
    
    int pow_counter = 0;
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
                    && !captured(player,monster) && !won(player, safe))
	{
	    // get player key press
	    keyEntered = terminal_read();
		
		//keep a count of number of steps player takes with powerup
		if (player.get_powerup_status())
		{
			pow_counter++;
		}
		
        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
        	if (pow_counter > MAX_POW_STEPS && player.get_powerup_status())
        	{	
        		//if player takes over 10 steps with powerup, then reset
        		//initial conditions and update powerup status
        		out.writeLine("Power-up expired!");
        		player.set_speed(PLAY_INIT_SPEED);
        		monster.set_speed(GOOSE_INIT_SPEED);
        		pow_counter = 0;
        		player.set_powerup_status(false);
			}
            // move the player, you can modify this function
    	    movePlayer(keyEntered,player, game_board);
    	    
    	    if (is_at_powerup(player, game_board))
    	    {
    	    	if (!player.get_powerup_status())
    	    	{	
    	    		//if player doesn't already have powerup, then update 
    	    		//powerup status and change player&goose speeds
    	    		player.set_powerup_status(true);
    	    		game_board[player.get_y()][player.get_x()] = EMPTY;
    	    		out.writeLine("Player got a power-up!");
    	    		player.set_speed(PLAY_NEW_SPEED);
    	    		monster.set_speed(GOOSE_NEW_SPEED);
				}
			}
            // call the goose's chase function
            moveMonster(monster, player, game_board);	    
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
        //if player reaches safe spot, player wins and game done
        if (won(player, safe))
        	out.writeLine("Congrats, player won!");
        //if player captured by goose, player loses and game done
        if (captured(player,monster))
        	out.writeLine("Oh no, player was captured!");
        //if player hits escape, send msg that player exited terminal
        if (keyEntered == TK_ESCAPE)
        	out.writeLine("Player exited terminal!");
        //once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}


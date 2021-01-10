
//File: gooseEscapeActors.hpp

#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

/*
    Modify this class to contain more characteristics of the "actor".  Add
    functions that will be useful for playing the game that are specific to
    the Actor.
*/

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;
    bool hasPowerUp;	//New data member indicating whether actor has power-up
    int speed;			//New data member for player speed

  public:
  	//New data members are initialized to default values in both constructors
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        put_actor();
        hasPowerUp = false;		//new data member for powerup status
        speed = DEFAULT_SPEED;	//new data member for speed
    }	

    Actor(char initPlayerChar, int x0, int y0, bool powerStat, int theSpeed)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        update_location(x0,y0);
        hasPowerUp = powerStat;		//new data member for powerup status
        speed = theSpeed;			//new data member for speed
    }
    
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    //Accessor func for getting powerup status
    bool get_powerup_status() const
    {
    	return hasPowerUp;
	}
	
	//Mutator func for changing powerup status
	void set_powerup_status(bool new_status)
	{
		hasPowerUp = new_status;
	}
	
	//Accessor func for getting speed
	int get_speed() const
	{
		return speed;
	}
	
	//Mutator func for changing speed
	void set_speed(int new_speed)
	{
		speed = new_speed;
	}
    
    string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
          && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
};
#endif

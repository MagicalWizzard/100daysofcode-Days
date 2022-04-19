#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

#define WIDTH 203
#define HEIGHT 53 

void print_menu(WINDOW *menu_win);
void print_world(WINDOW *world_win);

int main()
{	WINDOW *menu_win;
 	WINDOW *world_win;
	int key;
    int wS = 51; // worldSize
    struct snake{int length = 3;int x [900];int y [900];};
    struct food{int x = 0; int y = 0;};
    struct food fd;
 	struct snake s;
 	for(int i = 0; i < 900; i++) {s.x[i] = s.y[i] = 0;} //null out the x and y
    srand(time(0)); // rand() generates the same number when we run the program, so this sets a different seed
    int randNum = rand() % wS;
    for(int i = 0; i < s.length; i++){
	s.x[i] = s.y[i] = randNum; // generate random position of the snake
    }
    fd.x = (rand() % wS);
    fd.y = (rand() % wS);
    
 
	initscr();
	clear();
	noecho(); //no echoing of the terminal when typing
	cbreak();	/* Line buffering disabled. pass on everything */

	menu_win = newwin(HEIGHT, WIDTH, 0, 0); // those zeroes are starting possition for the menu window
 	world_win = newwin(wS, wS, 1, 1);
	keypad(world_win, TRUE);
	//mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win);
 	print_world(world_win);
    
    int key_left, key_right, key_down, key_up;
    
    std::string str;//char const* is string 
    int fuck = 1;
	while(fuck)
	{   
    key = wgetch(world_win);
    key_left  = (key == KEY_LEFT ) ? 1 : 0;
    key_right = (key == KEY_RIGHT) ? 1 : 0;
    key_down  = (key == KEY_DOWN ) ? 1 : 0;
    key_up    = (key == KEY_UP   ) ? 1 : 0;
    
    s.length += (key == 43) ? 1 : (key == 45) ? -1 : 0;
    
    s.x[0] += key_right - key_left;
    s.y[0] += key_down  - key_up;
    
    s.x[0] = (s.x[0] < 1) ? 49 : s.x[0] = (s.x[0] > 49) ? 1 : s.x[0]; // this is fun
    s.y[0] = (s.y[0] < 1) ? 49 : s.y[0] = (s.y[0] > 49) ? 1 : s.y[0]; // logic for snake out of bounds
    
    if(s.x[0] == fd.x && s.y[0] == fd.y){
        for(int i = 0; s.x[i] == fd.x && s.y[i] == fd.y 
                                      || fd.x < 1 || fd.y < 1
                                      || fd.x > 49 || fd.y > 49 
                                      || i <= s.length; i++) {
        fd.x = rand() % wS;
        fd.y = rand() % wS;       

        } 
        s.length++;
    }
    for(int i = s.length-1; i > 0; i--) {
        s.y[i] = s.y[i-1]; // shifts index values of two arrays x[], y[] to the right
        s.x[i] = s.x[i-1];
	}
    /*if(foodPos == s.y[0]) {
	for(int i = 0; foodPos == s.x[0] && i <= s.length; i++) {
		foodPos = rand() % wS;
		}
		s.length++;
	}*/
    wclear(world_win);box(world_win, 0, 0);
    for(int i = 0; i < s.length; i++){
    mvwprintw(world_win,s.y[i],s.x[i],"x");
    }
    mvwprintw(world_win,fd.y,fd.x,"A");
    str = "Score: ";
    str.append(std::to_string(s.length));
    mvwprintw(world_win,0,10,str.c_str());
    wrefresh(menu_win);
     //usleep(50000);wrefresh(world_win);
	}	
	clrtoeol();
	refresh();
	endwin();
	return 0;
}
void print_menu(WINDOW *menu_win)
{
	box(menu_win, 0, 0);
	wrefresh(menu_win);
}
void print_world(WINDOW *world_win)
{
	box(world_win, 0, 0);
	wrefresh(world_win);
}

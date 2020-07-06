/* Console based snake game using WASD */

#include <iostream>
#include <curses.h>  // console input-output
using namespace std;

bool gameOver;
// window dimensions
const int width = 20;
const int height = 20;

// head + fruit dimensions
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
WINDOW * win;

void setup() 
{
    //win = newwin(height, width, 0, 0);
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw() 
{
    system("clear");
    for (int i = 0; i < width; i++) 
    {
        for (int j = 0; j < height; j++) 
        {
            if (i == 0 || i == width-1 || j == 0 || j == width-1) 
            {
                printw('#');
            } else 
            {
                printw(' ');
            }            
        }
        printw('\n');
    }
}

void input() 
{
    switch(getchar()) 
    {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
    }
}

void logic() 
{
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
}


int main() 
{

    
    initscr();  // init curses
    cbreak();  // one char
    noecho();  // don't spit out char
    
    setup();
    while (!gameOver) {
        draw();
        //input();
        //logic();
    }

    endwin();  // exit curses
    return 0;
}
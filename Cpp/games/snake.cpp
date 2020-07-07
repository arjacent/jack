/* Console based snake game using WASD */

#include <iostream>
#include <curses.h>  // console input-output
using namespace std;

bool gameOver;
// window dimensions
const int width = 50;
const int height = 20;

// head + fruit dimensions
int snakeX, snakeY, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int tailX[100], tailY[100];
int tailSize;
int frame;


void fruit()
{
    fruitX = 1 + rand() % (width-1);
    fruitY = 1 + rand() % (height-1);
}

void setup() 
{
    //win = newwin(height, width, 0, 0);
    gameOver = false;
    dir = STOP;
    snakeX = width / 2;
    snakeY = height / 2;
    fruit();
    score = 0;
    tailSize = 0;
}

void draw() 
{
    clear();
    printw("Score: %d\n", score);
    printw("fruitX: %d   fruitY: %d    frame: %d\n\n", fruitX, fruitY, frame);
    
    for (int y = 0; y < height; y++) 
    {
        int index = 0;
        for (int x = 0; x < width; x++) 
        {
            if (y == 0 || y == height-1 || x == 0 || x == width-1) 
            {
                printw("#");
            } 
            else if (x == snakeX && y == snakeY)
            {
                printw("O");  // snake head
            }
            else if (x == fruitX && y == fruitY)
            {
                printw("F");
            }
            else 
            {
                int k;
                for (k = 0; k < tailSize; k++) {
                    if (tailX[k] == x && tailY[k] == y)
                    {
                        printw("o");
                        break;
                    }
                }
                if (k == tailSize)  // failed to print tail
                {
                    printw(" ");
                }
            }            
        }
        printw("\n");
    }
    refresh();
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
        default:
            break;
    }
}

void logic() 
{
    // update tail position (shift array elements right)
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < tailSize; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case LEFT:
            snakeX--;
            break;
        case RIGHT:
            snakeX++;
            break;
        case UP:
            snakeY--;
            break;
        case DOWN:
            snakeY++;
            break;
    }
    // collided with wall, end game
    if (snakeX <= 0 || snakeX >= width-1 || snakeY <= 0 || snakeY >= height-1)
    {
        gameOver = true;
    }
    // eat fruit
    if (snakeX == fruitX && snakeY == fruitY)
    {
        score += 10;
        tailSize++;
        fruit();
    } 
    else 
    {
        for (int k = 0; k < tailSize; k++)
        {
            if (snakeX == tailX[k] && snakeY == tailY[k])  // you hit tail
            {
                gameOver = true;
                break;
            }
            else if (fruitX == tailX[k] && fruitY == tailY[k])  // tail ate fruit
            {  
                score += 10;
                tailSize++;
                fruit();
                break;
            }
        }
    }
}


int main() 
{

    
    initscr();  // init curses
    //cbreak();  // one char
    noecho();  // don't spit out char    
    setup();
    frame = 0;

    while (!gameOver) {
        frame++;
        draw();
        input();
        logic();
    }

    endwin();  // exit curses
    return 0;
}
#include<iostream>
#include <bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
using namespace std;
bool gameover;//global bool variable represents true for game over, false for game not over
const int width =25;//global constants
const int length =25;
char map[width][length];
int x,y,gx,gy,fruitx,fruity,score;//global variables for all functions
int tailX[100], tailY[100];//arrays for storing the axis of tail segments
int nTail;//tail length counter
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};//constants
eDirection dir;//a direction directory from where we can call all the constants
void gotoxy(short x, short y)           //definition of gotoxy function                                              
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setup()//general game setup function
{
	gameover=false;
	dir=STOP; //this makes the snake stop at one position when game starts untill the user clicks a key
	x=width/2;//determining the position of snake head
	y=length/2;
	gx=width/4;
	gy=width/4;
	fruitx= rand() % width;//laying fruits at random axis using rand()
	fruity= rand() % length;
	score=0;
}
void draw()
{
	char map[width][length];
	system("cls");
	gotoxy(3,3);
/*	for(int i=0;i<=length;i++)//printing the bottom wall
	{
		map[width][i]=35;
	}
	for(int i=0;i<=width;i++)//printing the bottom wall
	{
		map[i][length]=35;
	}*/
	for(int i=0;i<width;i++)//this loop continuosly updates and prints the inner body of the map
	{
		for(int j=0;j<length;j++)
		{
			if(j==0)//printing side wall
			{
				map[i][j]=35;
			}
			if(i==0)
			{
				map[i][j]=35;
			}
			if(i==y && j==x)//printing the snake's head
			{
				map[i][j]=79;
			}
			else if(i==gx && j==gy)//printing the ghost
		    {
		    	map[i][j]=71;
			}
			else if(i==fruity && j==fruitx)//printing the fruit
			{
				map[i][j]=70;
			}
			else//printing the tail of snake
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						map[i][j]=111;
						print = true;
					}
				}
            	if(!print)//prints blank space after the snake has passed by an axis
		   	    	{
		   		     map[i][j]=32;
					}
		    }
			if(j==length-1)//printing side wall
			{
				map[i][j]=35;
			}
			if(i==width-1)
			{
				map[i][j]=35;
			}
		}
    }
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<length;j++)
		{
			cout<<map[i][j];
		}
		cout<<endl;
	}
	cout<<"Score: "<<score;//printing score
}
void logic()//the logic of how everything works
{
	int prevX = tailX[0];//arrays that store the x and y coordinates of the tail of snake
	int prevY = tailY[0];
	int prev2X, prev2Y;//variables to hold the previous axis of the snake tail segments
	tailX[0] = x;//initializing the first index of array with the axis of snake's head
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)//this loop continuosly stores the previous axis of snake's head and the segments follow
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch(dir)//this switch statement defines the controls through arrow keys that move the snake's head
	{
		case RIGHT:
			x++;
       		break;
       	case LEFT:
       		x--;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
	}	
	//these two if else statements are used to make the snakes pass through the walls 
	if (x >= width) 
	    {
		x = 0;
	    }
	else if (x < 0) 
	    {
		x = width - 1;
	    }
	if (y >= length)
	    {
		y = 0; 
		}
	else if (y < 0)
	    {
		y = length - 1; 
		}
	//the same condition for the ghost	
    if (gx >= width) 
	    {
		gx = 0;
	    }
	else if (gx < 0) 
	    {
	    gx = width - 1;
	    }
	if (gy >= length)
	    {
	    gy = 0;
		}
	else if (gy < 0)
	    {
	    gy= length - 1;
		}  		
	//this loop ends the game when the snake head hits its own tail or turns directly to the direction of its tail  
	for (int i = 0; i < nTail; i++)
		{
		if (tailX[i] == x && tailY[i] == y)
		    {
			gameover = true;
			}
	    }
    //this condition increases the score when a fruit is eaten and prints a new fruit at a random axis
	if (x == fruitx && y == fruity)
		{
			score += 10;
			fruitx = rand() % width;
			fruity = rand() % length;
			nTail++;
		}	
	//these 4 if else statements below determine the automatic movements of the ghost(this is the module where we make the ghost dumber or wiser)	
	if(x>gx)
   	{
   		gx++;
	}
	else if(x<gx)
	{
		gx--;
	}
   	if(y>gy)
   	{
   		gy--;
	}
	else if(y<gy)
	{
		gy--;
	}	
	//THIS IF STATEMENT IS THE PROBLEM THAT I WILL DISCUSS TOMORROW
	if(gx==x && gy==y)
	{
		//gameover=true;
    }	
}
void input()//this function deals with the user's input
{
	if(_kbhit())//key board hit function is used to detect whenever the user uses a key from the keyboard
	{
        switch(_getch())//get character takes the key that user entered and exhibits the function it is supposed to perform
        {
        	case 77:
        		dir=RIGHT;
        		break;
        	case 75:
			    dir=LEFT;
				break;
			case 72:
			    dir=UP;
				break;
			case 80:
			    dir=DOWN;
			    break;
			case 'x':
			    gameover=true;			
		}
    }
}
int main()
{
	setup();
	while(gameover==false)
	{ 
		draw();
		input();
		logic();
		Sleep(150);
	}
}

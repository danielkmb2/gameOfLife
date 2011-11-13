#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#define X 30
#define Y 30

void generateBoard(char v[X][Y])
{
	/*
	0|\/|G H4x0R!!!!!!1111
	  
	     j-1  j  j+1
	    +---+---+---
	 i-1|   | # |   |
	    +-----------	
	 i  | # |   |   |
            +-----------
	 i+1| # | # | # |
	    +-----------
	*/
	int i,j;
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			v[i][j] = 0;
		}
	}
	v[14][15] = 1;
	v[15][14] = 1;
	v[16][14] = 1;
	v[16][15] = 1;
	v[16][16] = 1;
}

void updateBoard (char v[X][Y], char v1[X][Y])
{
	int i, j;
	char neighbourCounter = 0;
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			//some better ways but...
			neighbourCounter = 0;
			if (v[(i-1)%X][(j-1)%Y] == 1)	neighbourCounter += 1;
			if (v[(i-1)%X][j%Y] == 1) 	neighbourCounter += 1;
			if (v[(i-1)%X][(j+1)%Y] == 1)	neighbourCounter += 1;
			if (v[(i)%X][(j-1)%Y] == 1)	neighbourCounter += 1;
			if (v[(i)%X][(j+1)%Y] == 1)	neighbourCounter += 1;
			if (v[(i+1)%X][(j-1)%Y] == 1)	neighbourCounter += 1;
			if (v[(i+1)%X][j%Y] == 1)	neighbourCounter += 1;
			if (v[(i+1)%X][(j+1)%Y] == 1)	neighbourCounter += 1;
		
			if (v[i%X][j%Y] == 1)
			{
				if ((neighbourCounter == 2)||(neighbourCounter == 3))
				{
					v1[i%X][j%Y] = 1;		//unnecesary output
				} else if ((neighbourCounter < 2)||(neighbourCounter > 3))
				{
					v1[i%X][j%Y] = 0;
					mvaddstr(i%X, j%Y, " ");	//output
				}
			} else if ((v[i%X][j%Y] == 0)&&(neighbourCounter == 3))
			{
				v1[i%X][j%Y] = 1;
				mvaddstr(i%X, j%Y, "O");		//output
			} else
			{
				v1[i%X][j%Y] = v[i%X][j%Y];	
			}
			refresh();
		}
	}
}

void initializeScreen()
{
	WINDOW * mainwin;
	if ( (mainwin = initscr()) == NULL ) 
	{
		fprintf(stderr, "Derp while initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}
}

int main()
{
	char board[X][Y];
	char auxBoard[X][Y];
	char derp=1;
	initializeScreen();		//useless but cool
	generateBoard(board);		//with multiple functions using arguments coming soon
	while (1)
	{
		usleep(1000);
		if (derp==1)
			updateBoard(board,auxBoard);
		if (derp==-1)
			updateBoard(auxBoard,board);
		derp= derp * (-1);
	}				//not exit method implemented yed (V)(;,,;)(V)
	return 0;
}

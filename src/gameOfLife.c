#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#define X 30
#define Y 30

struct cell
{
	char neighbours;
	char alive;	//0 muerta - 1 viva
};

void generateBoard(struct cell v[X][Y])
{
	//inicializar el struct cell con neighbours = 0!
	int i, j;
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			v[i][j].neighbours = 0;
		}
	}
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
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			v[i][j].alive = 0;
		}
	}
	v[14][15].alive = 1;
	v[15][14].alive = 1;
	v[16][14].alive = 1;
	v[16][15].alive = 1;
	v[16][16].alive = 1;
}

void updateBoard (struct cell v[X][Y])
{
	int i, j;
	char neighbourCounter = 0;
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)		
		{
			//some better ways but...
			neighbourCounter = 0;
			if (v[(i-1)%X][(j-1)%Y].alive == 1)	neighbourCounter += 1;
			if (v[(i-1)%X][j%Y].alive == 1) 	neighbourCounter += 1;
			if (v[(i-1)%X][(j+1)%Y].alive == 1)	neighbourCounter += 1;
			if (v[(i)%X][(j-1)%Y].alive == 1)	neighbourCounter += 1;
			if (v[(i)%X][(j+1)%Y].alive == 1)	neighbourCounter += 1;
			if (v[(i+1)%X][(j-1)%Y].alive == 1)	neighbourCounter += 1;
			if (v[(i+1)%X][j%Y].alive == 1)		neighbourCounter += 1;
			if (v[(i+1)%X][(j+1)%Y].alive == 1)	neighbourCounter += 1;
			v[i][j].neighbours = neighbourCounter;
		}
	}
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			if (v[i%X][j%Y].alive == 1)
			{
				if ((v[i%X][j%Y].neighbours == 2)||(v[i%X][j%Y].neighbours == 3))
				{
					v[i%X][j%Y].alive = 1;	//yeeeeeeeeeeeeeaahhhhh
				} else if ((v[i%X][j%Y].neighbours < 2)||(v[i%X][j%Y].neighbours > 3))
				{
					v[i%X][j%Y].alive = 0;
					mvaddstr(i, j, " ");
				}
			} else if ((v[i%X][j%Y].alive == 0)&&(v[i%X][j%Y].neighbours == 3))
			{
				v[i%X][j%Y].alive = 1;
				mvaddstr(i, j, "O");
			}
			//DUNNO reinicializar neighbours de paso...
			v[i][j].neighbours=0;
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
	struct cell board[X][Y];
	initializeScreen();		//useless but cool
	generateBoard(board);		//with multiple functions using arguments coming soon
	while (1)
	{
		updateBoard(board);
		usleep(1000);		//or pressing a button 4 debugging
	}				//not implemented yed (V)(;,,;)(V)
	return 0;
}

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
			v[i][j].alive = 0;
			v[i][j].neighbours = 0;
		}
	}
	v[14][15].alive = 1;
	v[15][14].alive = 1;
	v[16][14].alive = 1;
	v[16][15].alive = 1;
	v[16][16].alive = 1;
}

void updateBoard (struct cell v[X][Y], struct cell v1[X][Y])
{
	int i, j;
	char neighbourCounter = 0;
	struct cell auxCell;
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
			v[i%X][j%Y].neighbours = neighbourCounter;
		

			auxCell = v[i%X][j%Y];
			if (auxCell.alive == 1)
			{
				if ((auxCell.neighbours == 2)||(auxCell.neighbours == 3))
				{
					v1[i%X][j%Y].alive = 1;		//yeeeeeeeeeeeeeaahhhhh
				} else if ((auxCell.neighbours < 2)||(auxCell.neighbours > 3))
				{
					v1[i%X][j%Y].alive = 0;
					mvaddstr(i%X, j%Y, " ");	//output
				}
			} else if ((auxCell.alive == 0)&&(auxCell.neighbours == 3))
			{
				v1[i%X][j%Y].alive = 1;
				mvaddstr(i%X, j%Y, "O");		//output
			} else
			{
				v1[i%X][j%Y].alive = v[i%X][j%Y].alive;	
			}
			refresh();
		}
	}
	/*
		operamos con v cada recorrido de la matriz, la nueva condición de viva o muerta se guardará en v1, 
		al acabar cada recorrido v y v1 se intercambian de la forma más ineficiente posible....

		en v1 tendremos la posicion actualizada de todas las celulas, si están vivas o muertas, 
		y sobre v se hacen todas las operaciones para no liarla
	*/
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
	struct cell auxBoard[X][Y];
	int derp=1;
	initializeScreen();		//useless but cool
	generateBoard(board);		//with multiple functions using arguments coming soon
	while (1)
	{
		usleep(100000);
		if (derp==1)
			updateBoard(board,auxBoard);
		if (derp==-1)
			updateBoard(auxBoard,board);
		derp= derp * (-1);
					//or pressing a button 4 debugging
	}				//not implemented yed (V)(;,,;)(V)
	return 0;
}

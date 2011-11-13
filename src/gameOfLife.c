#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#define X 30
#define Y 30

typedef struct cell
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
			v[X][Y].neighbours = 0;
		}
	}
	//generar el tablero aleatoriamente, o de algún otro modo alucinante	
	
	//hurdur testing flying hacker logo
	/*   j-1  j  j+1
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
	/*
		buscar todas las posiciones del vector y mirar que hay en sus vecinos
		para cada posición de board, mirar cuántos vecinos hay en la matrix 3x3 que la rodea
		if cell=0 && vecinos == 3 then cell = 1
		if cell=1 && vecinos == 2 || vecinos == 3 then cell = 1
		if cell=1 && vecinos > 3 || vecinos < 2 then cell = 0
		OPERAR %X%Y!!!!!!!!!!!
	*/
	int i, j;
	char neighbourCounter = 0;
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			neighbourCounter = 0;
			//0|\/|G H4x0R!!!!!!1111
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
	//y recorremos de nuevo toda la matriz FTW... actualizamos el estado esta vez
	//aqui no uso el módulo verdad?
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			if (v[i%X][j%Y].alive == 1)
			{
				if ((v[i%X][j%Y].neighbours == 2)||(v[i%X][j%Y].neighbours == 3))
				{
					v[i%X][j%Y].alive = 1;
				} else
				if ((v[i%X][j%Y].neighbours < 2)||(v[i%X][j%Y].neighbours > 3))
				{
					v[i%X][j%Y].alive = 0;
				}
			} else
			if ((v[i%X][j%Y].alive == 0)&&(v[i%X][j%Y].neighbours == 3))
			{
				v[i%X][j%Y].alive = 1;
			}

			//DUNNO reinicializar neighbours
			v[i][j].neighbours=0;
		}
	}
}

void printBoard (struct cell v[X][Y])
{
	//brozear la pantalla
	int i,j;
	for (i=0;i<X;i++)
	{
		for (j=0;j<Y;j++)
		{
			if (v[i][j].alive == 1)
			{
				mvaddstr(i, j, "O");
			} else
			{
				mvaddstr(i, j, ".");
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
void endPrinting()
{
	WINDOW * mainwin;
	delwin(mainwin);
	endwin();
	refresh();
}

int main()
{
	struct cell board[X][Y];
	initializeScreen();
	generateBoard(board);
	while (1)
	{
		printBoard(board);
		updateBoard(board);
		usleep(1000);		//or pressing a button 4 debugging
					//not implemented yed (V)(;,,;)(V)
	}
	endPrinting();			//tiene gracia porque esto no se va a ejecutar nunca
	return 0;
}

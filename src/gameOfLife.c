#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define X 30
#define Y 120

#ifndef CURSES
#define CURSES 1
#endif

#if CURSES
#include <ncurses.h>
WINDOW *mainwin;
#endif

void generateBoard(char v[X][Y])
{
	/*
	0|\/|G H4><0|2!!!!!!1111	  
	     j-1  j  j+1
	    +---+---+---+
	 i-1|   | # |   |
	    +---+---+---+	
	 i  | # |   |   |
            +---+---+---+
	 i+1| # | # | # |
	    +---+---+---+
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
			if (v[(((i-1)%X)+X)%X][(((j-1)%Y)+Y)%Y] == 1)	neighbourCounter += 1;
			if (v[(((i-1)%X)+X)%X][((j%Y)+Y)%Y] == 1) 	neighbourCounter += 1;
			if (v[(((i-1)%X)+X)%X][(((j+1)%Y)+Y)%Y] == 1)	neighbourCounter += 1;
			if (v[(((i)%X)+X)%X][(((j-1)%Y)+Y)%Y] == 1)	neighbourCounter += 1;
			if (v[(((i)%X)+X)%X][(((j+1)%Y)+Y)%Y] == 1)	neighbourCounter += 1;
			if (v[(((i+1)%X)+X)%X][(((j-1)%Y)+Y)%Y] == 1)	neighbourCounter += 1;
			if (v[(((i+1)%X)+X)%X][((j%Y)+Y)%Y] == 1)	neighbourCounter += 1;
			if (v[(((i+1)%X)+X)%X][(((j+1)%Y)+Y)%Y] == 1)	neighbourCounter += 1;
		
			if (v[i%X][j%Y] == 1)
			{
				if ((neighbourCounter == 2)||(neighbourCounter == 3))
				{
					v1[i%X][j%Y] = 1;		//unnecesary output
				} else if ((neighbourCounter < 2)||(neighbourCounter > 3))
				{
					v1[i%X][j%Y] = 0;
#if CURSES
					mvaddstr(i,j," ");
#else
					fprintf(stderr,"\033[%d;%dH",i,j);
					printf(" \n");
#endif
				}
			} else if ((v[i%X][j%Y] == 0)&&(neighbourCounter == 3))
			{
				v1[i%X][j%Y] = 1;
				#if CURSES
				mvaddstr(i,j,"0");
				#else
				fprintf(stderr,"\033[%d;%dH",i%X,j%Y);
				printf("0\n");
				#endif
			} else
			{
				v1[i%X][j%Y] = v[i%X][j%Y];	
			}
		}
	}
	#if CURSES
	wrefresh(mainwin);
	#endif
}

#if CURSES
void initializeScreen()
{
	if (!(mainwin = initscr()))
	{
		fprintf(stderr, "Curses herp\n");
		exit(1);
	}
	curs_set(0);
	cbreak();
	noecho();
	nodelay(mainwin,1);
	werase(mainwin);
}
void endScreen()
{
	erase();
	endwin();
}
#else
void initializeScreen()
{
	fprintf(stderr, "\033[2J");
}

void endScreen()
{
	//not exit method implemented yed (V)(;,,;)(V)
}
#endif

int main()
{
	char board[X][Y];
	char auxBoard[X][Y];
	char derp=1;
	char c=49;
	int n=1;
	initializeScreen();		
	generateBoard(board);		//with multiple functions using arguments coming soon
#if CURSES
	while (c!='q')
#else
	while (1)
#endif
	{
		usleep(100000/n);
		if (derp==1)
			updateBoard(board,auxBoard);
		if (derp==-1)
			updateBoard(auxBoard,board);
		derp= derp * (-1);
#if CURSES
		c=wgetch(mainwin);
		if( (c> 48) && (c<58) )
			n = c-48;
#endif
	}			
	endScreen();
	return 0;
}

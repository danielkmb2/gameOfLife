#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define X 39
#define Y 146


#ifdef NCURSES
#include <ncurses.h>
WINDOW *mainwin;
#endif

void generateBoard(char v[X][Y],int mode)
/*
	modes:
		1- glider
		2- random board
*/
{

	switch (mode)
	{
		case 0:
		{
			printf("if u are stupid, dont use this program for your security\n");	
			endwin();
			exit(1);
		}break;

		case 1:
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
		}break;

		case 2:			//RANDOM BOARD
		{

        		srand(time(NULL));
        		int i,j;
        		for (i=0;i<X;i++)
        	        	for (j=0;j<Y; j++)	
					v[i][j] = (rand() % 2);
		}break;
			//implement fucking glider gun... zzZzZZZzzzZzzzZzzzzZz
		case 3:
		{
			
		}break;
	}
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
#ifdef NCURSES
					mvaddstr(i,j," ");
#else
					fprintf(stderr,"\033[%d;%dH",i,j);
					printf(" \n");
#endif
				}
			} else if ((v[i%X][j%Y] == 0)&&(neighbourCounter == 3))
			{
				v1[i%X][j%Y] = 1;
				#ifdef NCURSES
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
	#ifdef NCURSES
	wrefresh(mainwin);
	#endif
}

#ifdef NCURSES
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
	//in fact, not necesary because herpaponga derpa
}
#endif

int main(int argc, char* argv[])
{
	char board[X][Y];
	char auxBoard[X][Y];
	char derp=1;
	char c=49;
	int n=1;
	int mode=0;
	if (argc == 2) 
		{
			initializeScreen();		
			mode = atoi(argv[1]);
		}
	else
		mode = 0;

	generateBoard(board,mode);		//with multiple functions using arguments coming soon
#ifdef NCURSES
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
#ifdef NCURSES
		c=wgetch(mainwin);
		if( (c> 48) && (c<58) )
			n = c-48;
#endif
	}			
	endScreen();
	return 0;
}

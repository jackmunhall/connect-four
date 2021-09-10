// John Munhall
// CSE 20311
// project.c
// This program creates a simple connect four game for two users to play. Hit the '1'  key to place a piece in the first column, the '2'  key to place a piece in the second column and so forth.
#include "gfx2.h"
#include <stdbool.h>

void drawBoard(int x, int y, int board[][7]);
int updateBoard(int c, int currentplayer, int board[][7]);
int checkDown(int i, int c, int board[][7]);
int checkRight(int i, int c, int board[][7]);
int checkLeft(int i, int c, int board[][7]);
int checkRightUp(int i, int c, int board[][7]);
int checkLeftDown(int i, int c, int board[][7]);
int checkLeftUp(int i, int c, int board[][7]);
int checkRightDown(int i, int c, int board[][7]);

struct Message {
	char *font;
	char *text;
};

int main() {
	int width = 1000, height = 1000, mrgn = 100, i, j, currentplayer = 1;
	bool loop = true, over = false;
	char c = 0;
	struct Message winner;
	winner.font = "-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1";
	gfx_open(width, height, "Connect Four");
	gfx_changefont(winner.font);

	int board[6][7];
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			board[i][j] = 0;
		}
	}
	
	drawBoard(width-mrgn, height-mrgn, board);

	while (loop) {
		c = gfx_wait();
		i = updateBoard(c-48, currentplayer, board);
		drawBoard(width-mrgn, height-mrgn, board);
		if (checkDown(i, c-48, board) == 3) {
			over = true;
		}
		if (checkRight(i, c-48, board) + checkLeft(i, c-48, board) == 3) {
			over = true;
		}
		if (checkRightUp(i, c-48, board) + checkLeftDown(i, c-48, board) == 3) {
			over = true;
		}
		if (checkLeftUp(i, c-48, board) + checkRightDown(i, c-48, board) == 3) {
			over = true;
		}
		if (over == true) {
			if (currentplayer % 2 == 1) {
				gfx_text(500, 50, "Red wins");
			}
			if (currentplayer % 2 == 0) {
				gfx_text(500, 50, "Blue wins");
			}
		}
		if (c == 'q') {
			loop = false;
		}
		currentplayer++;
	}
		
	return 0;
}

// draws connect four board
void drawBoard(int xmax, int ymax, int board[][7])
{
	gfx_color(255, 255, 255);	

	int x = xmax/7;
	int y = ymax/6;
	int i = 0, j = 0;

	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			if (board[i][j] == 0) {
				gfx_color(255, 255, 255); // if no piece has been placed, color should be white
				gfx_fill_circle(x*(j+1), y*(i+1), 50);
			}
			if (board[i][j] == 1) {
				gfx_color(255, 0, 0); // if player 1's piece has been placed, color should be red
				gfx_fill_circle(x*(j+1), y*(i+1), 50);
			}
			if (board[i][j] == 2) {
				gfx_color(0, 0, 255); // if player 2's piece has been placed, color should be blue
				gfx_fill_circle(x*(j+1), y*(i+1), 50);
			}
		}
	} 
}	

// updates board array depending on user input and returns row of current piece
int updateBoard(int c, int currentplayer, int board[][7])
{
	int i;

	for (i = 5; i >=  0; i--) {
		if (board[i][c] == 0 && currentplayer % 2 == 0) { // if current spot is empty and current player is 2
			board[i][c] = 2;
			return i;
		}
		if (board[i][c] == 0 && currentplayer % 2 == 1) { // if current spot is empty and current player is 1
			board[i][c] = 1;
			return i;
		}
	}
}

// check the 3 locations below the current piece
int checkDown(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (i + count < 6)	{
			if (board[i][c] == board[i+count][c]) num++;
		}
	}
	
	return num;
}

// check the 3 locations to the right of the current piece
int checkRight(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (c + count < 7)	{
			if (board[i][c] == board[i][c+count]) num++;
		}
	}
	
	return num;
}

// check the 3 locations to the left of the current piece
int checkLeft(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (c - count > -1)	{
			if (board[i][c] == board[i][c-count]) num++;
		}
	}
	
	return num;
}

// check the 3 locations diagonally up and to the right of the current piece
int checkRightUp(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (i - count > -1 && c + count < 7) {
			if (board[i][c] == board[i-count][c+count]) num++;
		}
	}
	
	return num;
}

// check the 3 locations diagonally down and the left of the current piece
int checkLeftDown(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (i + count < 6 && c - count > -1) {
			if (board[i][c] == board[i+count][c-count]) num++;
		}
	}
	
	return num;
}

// check the 3 locations diagonally up and to the left of the current piece
int checkLeftUp(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (i - count > -1 && c - count > -1) {
			if (board[i][c] == board[i-count][c-count]) num++;
		}
	}
	
	return num;
}

// check the 3 locations diagonally down and to the right of the current piece
int checkRightDown(int i, int c, int board[][7])
{
	int count, num = 0;

	for (count = 1; count < 4; count++) {
		if (i + count < 6 && c + count < 7) {
			if (board[i][c] == board[i+count][c+count]) num++;
		}
	}
	
	return num;
}

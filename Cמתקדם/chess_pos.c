#include "chess_pos.h"
#include <stdio.h>
#include <stdlib.h>
/*
students:Raanan Harpak and Lir Mimrod
*/


int validCoord(int x, int y)/*check validation of location bo board*/
{
	return x >= 0 && x < BOARD_SIZE&& y >= 0 && y < BOARD_SIZE;
}

chessPos* chessPosByCoord(int x, int y)
{
	chessPos* cp = (chessPos*)malloc(sizeof(chessPos));

	if (cp == NULL)
	{
		printf("Failed to allocate memory!\nProgram will now exit...");
		exit(1);
	}

	(*cp)[0] = 'A' + x;
	(*cp)[1] = '1' + y;
	return cp;
}/*make new array of chesposs by the cordinate*/

void coordByChessPos(chessPos pos, int* x, int* y)//change the type
{
	*x = pos[0] - 'A';
	*y = pos[1] - '1';
}

chessPosArray* vkmArrayByCoord(int x, int y)/*check the valid moves of specific loaction*/
{
	chessPosArray* cpa = (chessPosArray*)malloc(sizeof(chessPosArray));

	if (cpa == NULL)/*if mermory alloaction failed*/
	{
		printf("Failed to allocate memory!\nProgram will now exit...");
		exit(1);
	}

	cpa->positions = (chessPos*)malloc(sizeof(chessPos) * BOARD_SIZE);/*create new array*/

	if (cpa->positions == NULL)
	{
		printf("Failed to allocate memory!\nProgram will now exit...");
		exit(1);
	}

	cpa->size = 0;

	int index = 0, currX, currY, i;
	int possiblePositions[8][2] = { {x - 1, y - 2},{x - 2, y - 1},{x - 2, y + 1},{x - 1, y + 2},{x + 1, y + 2},{x + 2, y + 1},{x + 2, y - 1},{x + 1, y - 2} };
	/*complete all cases by valid location*/
	for (i = 0; i < 8; i++)/*check valid loaction by automatic(loop)*/
	{

		currX = possiblePositions[i][0];
		currY = possiblePositions[i][1];
		if (validCoord(currX, currY))/*it this location is valid*/
		{
			(cpa->size)++;
			(cpa->positions)[index][0] = 'A' + currX;
			(cpa->positions)[index][1] = '1' + currY;
			index++;
		}
	}

	chessPosArray* temp = cpa->positions;
	temp = (chessPos*)realloc(cpa->positions, sizeof(chessPos) * cpa->size);

	if (temp == NULL)
	{
		printf("Failed to allocate memory!\nProgram will now exit...");
		exit(1);
	}

	cpa->positions = temp;


	return cpa;
}
/*------------------------------------------Question 1---------------------*/

chessPosArray*** validKnightMoves()
{
	int k;
	chessPosArray*** vkm = (chessPosArray***)malloc(sizeof(chessPosArray**) * BOARD_SIZE);

	if (vkm == NULL)/*if memory allocation failed*/
	{
		printf("Failed to allocate memory!\nProgram will now exit...");
		exit(1);
	}

	for (k = 0; k < BOARD_SIZE; k++)/*check allocation for every cell in the array-every cell is array*/
	{
		vkm[k] = (chessPosArray**)malloc(sizeof(chessPosArray*) * BOARD_SIZE);

		if (vkm[k] == NULL)
		{
			printf("Failed to allocate memory!\nProgram will now exit...");
			exit(1);
		}
	}

	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)/*iff memory allocation is ok*/
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			vkm[i][j] = vkmArrayByCoord(i, j);/*check the valid moves for every location and get into new array*/
		}
	}

	return vkm;
}



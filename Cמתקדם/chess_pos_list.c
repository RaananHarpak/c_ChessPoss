#include "chess_pos_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
students:Raanan Harpak and Lir Mimrod
*/

chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next)
{
	chessPosCell* cpc = (chessPosCell*)malloc(sizeof(chessPosCell));

	if (cpc == NULL)
	{
		printf("Failed to allocate memory!\nProgram will now exit...");
		exit(1);
	}

	cpc->position[0] = position[0];
	cpc->position[1] = position[1];
	cpc->next = next;
	return cpc;
}

void removeChessPosCell(chessPosCell* previous)
{
	chessPosCell* remove = previous->next;
	previous->next = remove->next;
	free(remove);
}

/*------------------------------------------Question 2---------------------*/
void display(chessPosList* lst)
{
	int x, y;
	bool dupArray[BOARD_SIZE][BOARD_SIZE] = { false };
	chessPosCell* curr = lst->head;
	chessPosCell* previous = NULL;

	while (curr != NULL)
	{
		x = curr->position[0] - 'A';
		y = curr->position[1] - '1';
		
		if (!dupArray[x][y])
			dupArray[x][y] = true;

		else
		{
			removeChessPosCell(previous);
			curr = previous;
		}

		previous = curr;
		curr = curr->next;
	}
	printBoard(lst);
}

void printBoard(chessPosList* lst)/*print the board*/
{
	int i, j, x, y, count = 1;
	int boardArr[BOARD_SIZE][BOARD_SIZE] = { 0 };
	chessPosCell* curr = lst->head;
	while (curr != NULL)
	{
		x = (int)curr->position[0] - 'A';
		y = (int)curr->position[1] - '1';
		boardArr[x][y] = count;
		count++;
		curr = curr->next;
	}

	for (i = 0; i < 8; i++)
	{
		if (i == 0)/*print the top line*/
		{
			printf("|---|---|---|---|---|---|---|---|---|\n");
			printf("| + | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
			printf("|---|---|---|---|---|---|---|---|---|\n");

		}

		printf("| %c |", 'A' + i);
		for (j = 0; j < 8; j++)
		{
			if (boardArr[i][j] == 0)
				printf("   |");
			else
				printf(" %d |", boardArr[i][j]);
		}
		printf("\n");
		printf("|---|---|---|---|---|---|---|---|---|\n");
	}

}
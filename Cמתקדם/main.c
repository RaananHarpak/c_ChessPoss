#include "knight_api.h"
#include "chess_pos.h"
#include "chess_pos_list.h"
#include "path_tree.h"
#include "tests.h"
/*
students:Raanan Harpak and Lir Mimrod
*/

void main()
{

	/*Test for Question 1----------------------------------*/
	
	chessPosArray*** whatever;
	whatever = validKnightMoves();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("For spot %c%d: [", i + 'A', j + 1);
			for (int k = 0; k < whatever[i][j]->size; k++)
			{
				printf("%c%c", whatever[i][j]->positions[k][0], whatever[i][j]->positions[k][1]);
				if (k != whatever[i][j]->size - 1)
					printf(", ");
			}
			printf("]\n");
		}

	}

	/*Test for Qustion 2--------------------------------------*/
	/*
	chessPosList cpl;
	chessPos cp1 = { 'A', '4' };
	chessPos cp2 = { 'H', '5' };
	chessPos cp3 = { 'D', '8' };
	chessPos cp4 = { 'H', '5' };
	chessPos cp5 = { 'A', '4' };
	chessPos cp6 = { 'E', '1' };

	chessPosCell* cpc6 = createNewChessPosCell(cp6, NULL);
	chessPosCell* cpc5 = createNewChessPosCell(cp5, cpc6);
	chessPosCell* cpc4 = createNewChessPosCell(cp4, cpc5);
	chessPosCell* cpc3 = createNewChessPosCell(cp3, cpc4);
	chessPosCell* cpc2 = createNewChessPosCell(cp2, cpc3);
	chessPosCell* cpc1 = createNewChessPosCell(cp1, cpc2);
	cpl.head = cpc1;
	cpl.tail = cpc6;
	display(&cpl);
	*/
	/*Test for Question 3-----------------------------------*/
	/*
	chessPos cp1 = { 'A','2' };
	pathTree Boy = findAllPossibleKnightPaths(cp1);
	*/
	/*Test for Question 4-----------------------------------*/
	/*
	TestQuestion4();
	*/
	/*Test for Question 5+6-----------------------------------*/
	/*
	TestQuestion5();
	*/
	/*Test for Question 7-----------------------------------*/



}
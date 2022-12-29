#include "path_tree.h"


/*for tests change the board_size to 3 3*/
/*#define BOARDSIZE 3*/
/*
students:Raanan Harpak and Lir Mimrod
*/



treeNode* createNewTreeNode(chessPos position, treeNodeListCell* next_possible_positions)
{
	treeNode* res = malloc(sizeof(*res));

	if (res == NULL)
	{
		printf("Error allocation memory!");
		exit(1);
	}

	(res->position)[0] = position[0];
	(res->position)[1] = position[1];
	res->next_possible_positions = next_possible_positions;
	return res;
}

treeNodeListCell* createNewTreeNodeListCell(treeNode* node, treeNodeListCell* next)
{
	treeNodeListCell* res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	res->node = node;
	res->next = next;
	return res;
}

bool checkIfPossiblePosition(chessPos pos, bool trackingArray[BOARDSIZE][BOARDSIZE])
{
	int x, y;
	coordByChessPos(pos, &x, &y);
	return !trackingArray[x][y];
}

/*------------------------------------------Question 3---------------------*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{	
	pathTree tree;
	chessPosArray*** validmovesarr = validKnightMoves();
	
	bool trackingArray[BOARDSIZE][BOARDSIZE] = { false };
	tree.root = findAllPossibleKnightPathsRec(*startingPosition, validmovesarr, trackingArray);/*recursive function check all validmoves*/
	return tree;
}

bool checkIfNowhereToGo(chessPos pos, chessPosArray*** validmovesarr, bool trackingArray[BOARDSIZE][BOARDSIZE])
{
	int x, y, i, currX, currY;

	coordByChessPos(pos, &x, &y);

	for (i = 0; i < (validmovesarr[x][y]->size); i++)
	{
		coordByChessPos(validmovesarr[x][y]->positions[i], &currX, &currY);/*check if there is no more option to play*/
		if (trackingArray[currX][currY] == false)
			return false;
	}

	return true;
}

treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition, chessPosArray*** validmovesarr, bool trackingArray[BOARDSIZE][BOARDSIZE])
{
	treeNode* res = createNewTreeNode(startingPosition, NULL);
	int x=0, y=0, i;
	treeNodeListCell* nextListCell = NULL;
	treeNodeListCell* currListCell = NULL;
	treeNode* currTreeNode;

	if (checkIfNowhereToGo(startingPosition, validmovesarr, trackingArray))
	{
		printf("\n");
		return res;
	}

	else
	{
		coordByChessPos(startingPosition, &x, &y);
		trackingArray[x][y] = true;


		
		for (i = 0; i < (validmovesarr[x][y]->size); i++)
		{
			if (checkIfPossiblePosition((validmovesarr[x][y]->positions[i]), trackingArray))
			{
				currTreeNode = findAllPossibleKnightPathsRec(validmovesarr[x][y]->positions[i], validmovesarr, trackingArray);
				currListCell = createNewTreeNodeListCell(currTreeNode, nextListCell);
				printf("%c %c \n", currListCell->node->position[0], currListCell->node->position[1]);
				nextListCell = currListCell;
			}
		}
		res->next_possible_positions = currListCell;
	}

	trackingArray[x][y] = false;
	return res;
}

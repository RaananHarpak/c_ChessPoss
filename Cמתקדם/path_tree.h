#ifndef PATH_TREE_H
#define PATH_TREE_H
#define _CRT_SECURE_NO_WARNINGS
#include "chess_pos.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define BOARDSIZE 3


struct _treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	struct _treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
} pathTree;

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* createNewTreeNode(chessPos position, treeNodeListCell* next_possible_positions);
treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition, chessPosArray*** vkm, bool trackingArray[BOARDSIZE][BOARDSIZE]);
treeNodeListCell* createNewTreeNodeListCell(treeNode* node, treeNodeListCell* next);
bool checkIfNowhereToGo(chessPos pos, chessPosArray*** vkm, bool trackingArray[BOARDSIZE][BOARDSIZE]);
bool checkIfPossiblePosition(chessPos pos, bool trackingArray[BOARDSIZE][BOARDSIZE]);

#endif
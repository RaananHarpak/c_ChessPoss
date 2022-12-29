#ifndef CHESS_POS_LIST_H
#define CHESS_POS_LIST_H
#include "chess_pos.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

void display(chessPosList* lst);
void removeChessPosCell(chessPosCell* previous);
void printBoard(chessPosList* lst);
chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next);

#endif
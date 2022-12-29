#ifndef CHESS_POS_H
#define CHESS_POS_H
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8

typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

int validCoord(int x, int y);
chessPos* chessPosByCoord(int x, int y);
chessPosArray* vkmArrayByCoord(int x, int y);
chessPosArray*** validKnightMoves();
void coordByChessPos(chessPos pos, int* x, int* y);

#endif

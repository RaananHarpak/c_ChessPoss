#include "knight_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
/*
students:Raanan Harpak and Lir Mimrod
*/

#define BYTE char

#define N 8
#define M 8

#define ROW_START 'A'
#define COL_START '1'

#define INIT 0
#define VISITED 1

#define POS_BITS 6

#define FILE_DOES_NOT_EXIST -1
#define NO_LEGAL_PATH 1
#define NOT_ALL_BOARD_COVERED 2
#define ALL_BOARD_COVERED 3

/* q4  - internal declarations */
int isPathFound(treeNode *node, chessPosList* lst, int board[N][M]);
int isBoardCovered(int board[N][M]);
void addToHeadOfList(treeNode *node, chessPosList* lst);

/* q5 - internal declarations */
void compressPositions(chessPos* positions, short int positionsSize, FILE* fp);
BYTE split(char data, BYTE write, int cr, int* offset, int* full, FILE* f);
BYTE nosplit(char data, int cr, int offset, int* full);
short int getSize(chessPosList* lst);
void turnListToArray(chessPosList* lst, chessPos* arr);

/* q6 - internal declarations */
chessPos* decodeData(FILE* fp, double numOfPos);
char merg(BYTE part1, BYTE part2, int* left);
char nomerg(int* left, char read);
void turnArrayIntoList(chessPos* positions, int positionsSize, chessPosList* lst);
int isPathLegal(chessPosList* lst);
int isPosInNextMoves(chessPosArray* nextMoves, chessPos pos);
int isAllBoardCovered(chessPosList* lst);
void freeList(chessPosList* lst);

/* q7 - internal declarations */
void getStartingPos(chessPos* pos);
void createAllPossibleKnightPaths(chessPos pos, pathTree* path);
void findPathCoveringAllBoard(chessPos pos, pathTree* path);
void savePathCoveringAllBoardToFile(chessPos pos, pathTree* path);
void loadAndDisplayPathFromFile();

/* q7 - external api */
void handleCmds()
{
	char* menu = "1. Enter a knight's starting position\n"
				"2. Create all possible knight paths\n"
				"3. Find a knight path covering all board\n"
				"4. Save knight path covering all board to file\n"
				"5. Load and display path from file\n"
				"6. Exit\n";

	int cmd = 0;
	chessPos pos = { 0 , 0 };
	pathTree path = { .root = NULL };
	printf("%s", menu);
	printf("Please enter next command number according to menu above:\n");
	scanf("%d", &cmd);
	while (cmd != 6)
	{
		switch (cmd) {
			case 1: getStartingPos(&pos); break;
			case 2: createAllPossibleKnightPaths(pos, &path); break;
			case 3: findPathCoveringAllBoard(pos, &path); break;
			case 4: savePathCoveringAllBoardToFile(pos, &path); break;
			case 5: loadAndDisplayPathFromFile(); break;
			case 6: break;
		}
		printf("Please enter next command number according to menu above:\n");
		scanf("%d", &cmd);
	}
}

/* q6 - external api */
int checkAndDisplayPathFromFile(char *file_name)
{
	chessPosList* pos_list = malloc(sizeof(*pos_list));
	chessPos* positions;
	short int numOfPos = 0;
	FILE *fp = fopen(file_name, "rb");
	if (fp == NULL)
		return FILE_DOES_NOT_EXIST;

	pos_list->head = NULL;
	pos_list->tail = NULL;

	fread(&numOfPos, sizeof(short int), 1, fp);

	positions = decodeData(fp, numOfPos);

	fclose(fp);

	turnArrayIntoList(positions, numOfPos, pos_list);

	if (!isPathLegal(pos_list)) {
		freeList(pos_list);
		return NO_LEGAL_PATH;
	}

	display(pos_list);

	int allBoardCovered = isAllBoardCovered(pos_list);
	freeList(pos_list);

	if (allBoardCovered == 1)
		return ALL_BOARD_COVERED;

	return NOT_ALL_BOARD_COVERED;
}


/* q5 - external api */
void saveListToBinFile(char* file_name, chessPosList *pos_list)/*save the bits*/
{
	FILE* fp = fopen(file_name, "wb");
	assert(fp);
	short int numOfPos = getSize(pos_list);

	chessPos* positions = calloc(numOfPos, sizeof(chessPos));
	assert(positions);
	turnListToArray(pos_list, positions);
	compressPositions(positions, numOfPos, fp);

	fclose(fp);
	free(positions);
}

/* q4  - external api */
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree)
{
	int pathCoveringAllBoard = 0;

	// Init empty board
	int board[N][M];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			board[i][j] = INIT;
		}
	}

	// Create empty list
	chessPosList* lst = malloc(sizeof(*lst));
	lst->head = NULL;
	lst->tail = NULL;

	// Find path
	pathCoveringAllBoard = isPathFound(path_tree->root, lst, board);
	if (pathCoveringAllBoard) {
		return lst;
	}
	freeList(lst);
	return NULL;
}


/* q7 - internal api */
void getStartingPos(chessPos* pos)
{
	char r, c;
	printf("Please enter knight's starting position:\n");
	scanf(" %c %c", &r, &c);
	if (r < 'A' || r > 'H' || c < '1' || c > '8') {
		printf("You entered invalid position. Please try again\n");
		return;
	}
	(*pos)[0] = r;
	(*pos)[1] = c;
}

void createAllPossibleKnightPaths(chessPos pos, pathTree* path)
{
	if (pos[0] == 0 && pos[1] == 0) {
		printf("Starting position wasn't entered. Please try again\n");
		return;
	}
	*path = findAllPossibleKnightPaths(&pos);
}

void findPathCoveringAllBoard(chessPos pos, pathTree* path)
{
	if (path->root == NULL)
		createAllPossibleKnightPaths(pos, path);

	chessPosList* lst = findKnightPathCoveringAllBoard(path);
	if (lst == NULL) {
		printf("No path covering all board found.\n");
		return;
	}
	display(lst);
	freeList(lst);
}

void savePathCoveringAllBoardToFile(chessPos pos, pathTree* path)
{
	if (path->root == NULL)
		createAllPossibleKnightPaths(pos, path);

	char file_name[100];
	printf("Please enter file name:\n");
	scanf("%s", file_name);

	chessPosList* lst = findKnightPathCoveringAllBoard(path);
	if (lst == NULL) {
		printf("No path covering all board found.\n");
		return;
	}
	saveListToBinFile(file_name, lst);
	freeList(lst);
}

void loadAndDisplayPathFromFile()
{
	char file_name[100];
	printf("Please enter file name:\n");
	scanf("%s", file_name);
	int res = checkAndDisplayPathFromFile(file_name);
	printf("Result: %d\n", res);
}

/* q6 - internal api */
chessPos* decodeData(FILE* fp, double numOfPos)
{
	int left = 3, i = 0, readsize = (int)ceil((numOfPos * 6) / 8);
	BYTE* read = malloc(sizeof(BYTE) * readsize);
	assert(read);

	fread(read, sizeof(BYTE), readsize, fp);
	chessPos* arr = malloc(sizeof(chessPos) * (size_t)numOfPos);
	assert(arr);

	for (int t = 0; t < numOfPos; ) {

		if (left <= 8)
			arr[t][0] = nomerg(&left, read[i]) + ROW_START;
		else
			arr[t][0] = merg(read[i++], read[i], &left) + ROW_START;

		if (left <= 8)
			arr[t++][1] = nomerg(&left, read[i]) + COL_START;
		else
			arr[t++][1] = merg(read[i++], read[i], &left) + COL_START;
	}

	free(read);
	return arr;
}

char merg(BYTE part1, BYTE part2, int* left)
{

	BYTE cell = (part1 << ((*left) - 3));
	cell = cell >> 5;
	cell |= (part2 >> (16 - (*left)));

	(*left) = 3 - (8 - (*left));

	return cell;
}

char nomerg(int* left, char read)
{

	BYTE temp = ((read >> (8 - (*left))) & 0x7);
	(*left) += 3;
	return temp;
}

void turnArrayIntoList(chessPos* positions, int positionsSize, chessPosList* lst)
{
	for (int i = 0; i < positionsSize; i++) {
		chessPosCell* node = malloc(sizeof(*node));
		node->position[0] = positions[i][0];
		node->position[1] = positions[i][1];
		node->next = NULL;
		if (lst->head == NULL) {
			lst->head = node;
			lst->tail = node;
		} else {
			lst->tail->next = node;
			lst->tail = node;
		}
	}
}

int isPathLegal(chessPosList* lst)
{
	chessPosArray *** validMoves = validKnightMoves();

	chessPosCell *node = lst->head;

	while (node && node->next) {
		int r = node->position[0] - ROW_START;
		int c = node->position[1] - COL_START;
		chessPosArray* nextMoves = validMoves[r][c];
		if (isPosInNextMoves(nextMoves, node->next->position) == 0) {
			return 0;
		}
	}
	return 1;
}

int isPosInNextMoves(chessPosArray* nextMoves, chessPos pos)
{
	for (int i = 0; i < nextMoves->size; i++) {
		chessPos nextPos;
		nextPos[0] = nextMoves->positions[i][0];
		nextPos[1] = nextMoves->positions[i][1];
		if (nextPos[0] == pos[0] && nextPos[1] == pos[1]) {
			return 1;
		}
	}
	return 0;
}

int isAllBoardCovered(chessPosList* lst)
{
	short int lstSize = getSize(lst);
	short int boardSize = N * M;

	if (lstSize == boardSize)
		return 1;
	return 0;
}

void freeList(chessPosList* lst)
{
	chessPosCell* node = lst->head;
	while (node) {
		chessPosCell *tmp = node;
		node = node->next;
		free(tmp);
	}
	free(lst);
}

/* q5 - internal api */
void compressPositions(chessPos* positions, short int positionsSize, FILE* fp)
{
	const int cell_size = 3;
	int t = 8, cr = 0, full = 0;
	BYTE write = 0;
	fwrite(&positionsSize, sizeof(short int), 1, fp);

	for (unsigned int i = 0; i < positionsSize; ) {

		t -= cell_size;

		if (t > 0 && full < 6)
			write |= nosplit(positions[i][cr % 2], cr, t, &full);

		else
			write = split(positions[i][cr % 2], write, cr, &t, &full, fp);
		cr++;
		if (cr % 2 == 0 && cr > 0)
			i++;
	}
	if (positionsSize % 4)
		fwrite(&write, sizeof(char), 1, fp);
}

BYTE split(char data, BYTE write, int cr, int* offset, int* full, FILE* f)
{
	BYTE mask = 0;
	if (cr % 2 == 0)
		mask = data - ROW_START;
	else
		mask = data - COL_START;

	write |= (mask >> (3 - (8 - (*full))));
	(*offset) = 8 - (3 - (8 - (*full)));
	(*full) = 3 - (8 - (*full));

	fwrite(&write, sizeof(char), 1, f);
	return (mask << (*offset));
}


BYTE nosplit(char data, int cr, int offset, int* full)
{
	(*full) += 3;

	if (cr % 2 == 0)
		return (data - ROW_START) << offset;
	else
		return (data - COL_START) << offset;
}

short int getSize(chessPosList* lst)
{
	if (!lst)
		return 0;
	chessPosCell *node = lst->head;
	short int cnt = 0;
	while (node) {
		cnt++;
		node = node->next;
	}
	return cnt;
}

void turnListToArray(chessPosList* lst, chessPos* arr)
{
	chessPosCell *node = lst->head;
	int idx = 0;
	while (node) {
		arr[idx][0] = node->position[0];
		arr[idx][1] = node->position[1];
		idx++;
		node = node->next;
	}
}

/* q4  - internal api */
int isPathFound(treeNode *node, chessPosList* lst, int board[N][M])
{
	int row = node->position[0] - ROW_START;
	int col = node->position[1] - COL_START;
	board[row][col] = VISITED;
	int boardCovered = isBoardCovered(board);

	treeNodeListCell* next_pos = node->next_possible_positions;

	while (next_pos && boardCovered == 0) {
		if (next_pos->node)
			boardCovered = isPathFound(next_pos->node, lst, board);
		next_pos = next_pos->next;
	}

	if (boardCovered) {
		addToHeadOfList(node, lst);
		return 1;
	}
	board[row][col] = INIT;
	return 0;
}

int isBoardCovered(int board[N][M])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == INIT)
				return 0;
		}
	}
	return 1;
}

void addToHeadOfList(treeNode *node, chessPosList* lst)
{
	chessPosCell *newHead = malloc(sizeof(*newHead));
	newHead->position[0] = node->position[0];
	newHead->position[1] = node->position[1];

	if (!lst) {
		lst->head = newHead;
		lst->head->next = NULL;
		lst->tail = newHead;
		return;
	}

	newHead->next = lst->head;
	lst->head = newHead;
}

#include "knight_api.h"
#include <stdlib.h>
/*
students:Raanan Harpak and Lir Mimrod
*/


void printList(chessPosList* lst)
{
	chessPosCell* node = lst->head;
	while (node) {
		printf("Pos: %c %c\n", node->position[0], node->position[1]);
		node = node->next;
	}
}

void TestQuestion4()
{
	// Init path tree that covers all board (when board is 2 x 2
	pathTree p;
	p.root = (treeNode*)malloc(sizeof(treeNode));
	p.root->position[0] = 'A';
	p.root->position[1] = '1';
	p.root->next_possible_positions = malloc(sizeof(treeNodeListCell) * 3);
	p.root->next_possible_positions[0].node = malloc(sizeof(treeNode));
	p.root->next_possible_positions[0].node->position[0] = 'A';
	p.root->next_possible_positions[0].node->position[1] = '2';
	p.root->next_possible_positions[0].node->next_possible_positions = NULL;
	p.root->next_possible_positions[0].next = NULL;

	chessPosList *lst = findKnightPathCoveringAllBoard(&p);
	if (lst == NULL) {
		printf("List is null\n");
	} else {
		printf("Expected: ");
		printList(lst);
	}

	//Init path that doesn't cover all board
	pathTree p2;
	p2.root = (treeNode*)malloc(sizeof(treeNode));
	p2.root->position[0] = 'A';
	p2.root->position[1] = '1';
	p2.root->next_possible_positions = malloc(sizeof(treeNodeListCell) * 1);
	p2.root->next_possible_positions[0].node = malloc(sizeof(treeNode));
	p2.root->next_possible_positions[0].node->position[0] = 'A';
	p2.root->next_possible_positions[0].node->position[1] = '2';
	p2.root->next_possible_positions[0].node->next_possible_positions = NULL;
	p2.root->next_possible_positions[0].next = NULL;

	lst = findKnightPathCoveringAllBoard(&p);
	if (lst == NULL) {
		printf("List is null\n");
	} else {
		printf("Expected: ");
		printList(lst);
	}
}

void print_binary(char c)
{
	int i, mask;
	for (i = 7; i >= 0; i--)
	{
		mask = 1 << i;
		putchar((c & mask) ? '1' : '0');
		if (i % 4 == 0)
			putchar(' ');
	}
}

void printListToBinFileInBinary(char* file_name)
{
	short int size,i;
	char byte;
	FILE* fp = fopen(file_name, "rb");

	fread(&size, sizeof(short int), 1, fp);
	size *= 6;
	if(size%8==0)
		size /= 8;
	else
	{
		size /= 8;
		size++;
	}

	printf("Size: %d\n", size);

	for (i = 0; i < (size); i++)
	{
		fread(&byte, sizeof(char), 1, fp);
		print_binary(byte);
		printf(" ");
	}

	fclose(fp);
}

void TestQuestion5()
{
	chessPosList* lst = malloc(sizeof(*lst));
	lst->head = malloc(sizeof(*lst->head));
	lst->head->position[0] = 'A';
	lst->head->position[1] = '1';
	lst->head->next = NULL;

	chessPosCell *node = malloc(sizeof(*node));
	node->position[0] = 'E';
	node->position[1] = '2';
	node->next = NULL;

	lst->head->next = node;

	lst->tail = lst->head;
	char* file_name = "binFile";
	saveListToBinFile(file_name, lst);
	printListToBinFileInBinary(file_name);
	checkAndDisplayPathFromFile(file_name);
}

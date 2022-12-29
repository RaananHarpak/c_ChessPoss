#ifndef KNIGHT_API_H_
#define KNIGHT_API_H_
#define _CRT_SECURE_NO_WARNINGS
#include "chess_pos_list.h"
#include "chess_pos.h"
#include "path_tree.h"

/* q4 */
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree);

/* q5 */
void saveListToBinFile(char* file_name, chessPosList *pos_list);

/* q6 */
int checkAndDisplayPathFromFile(char *file_name);

/* q7 */
void handleCmds();

#endif /* KNIGHT_API_H_ */

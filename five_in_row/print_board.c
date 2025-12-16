#include "gomoku.h"

void print_board(void) // 打印棋盘
{
    printf("    ");
    for (int i = 0; i < size; i++)
    {
        printf(" %2d ", i);
    }
    printf(" y\n\n");
    for (int i = 0; i < size; i++)
    {
        printf(" %2d  ", i);
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 1)
                printf(" X  ");
            else if (board[i][j] == 2)
                printf(" O  ");
            else
                printf(" .  ");
        }
        printf("\n\n");
    }
    printf(" x\n\n");
}
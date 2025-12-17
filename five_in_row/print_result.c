#include "gomoku.h"

void print_result(int result) // 打印棋局最终结果
{
    if (result == 2)
    {
        printf("YOU WIN！\n");
    }
    else if (result == -1)
    {
        printf("DRAW！\n");
    }
    else if (result == 1)
    {
        printf("YOU LOSE！\n");
    }
}
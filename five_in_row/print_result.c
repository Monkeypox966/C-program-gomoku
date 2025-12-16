#include "gomoku.h"

void print_result(int result) // 打印棋局最终结果
{
    if (result == 2)
    {
        printf("你赢了！\n");
    }
    else if (result == -1)
    {
        printf("平局！\n");
    }
    else if (result == 1)
    {
        printf("你输了！\n");
    }
}
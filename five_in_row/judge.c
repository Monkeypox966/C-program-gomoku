#include "gomoku.h"

int judge(void) // 判断游戏是否结束，返回0表示未结束，2表示人赢，1表示AI赢，-1表示平局
{
    // 遍历棋盘上的每一个点
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // 如果当前位置是空的，就跳过，不需要检查
            if (board[i][j] == 0)
                continue;

            int p = board[i][j]; // 获取当前是谁的子，人是2，AI是1

            // 检查横向
            if (j + 4 < size)
            {
                if (board[i][j + 1] == p && board[i][j + 2] == p && board[i][j + 3] == p && board[i][j + 4] == p)
                    return p;
            }

            // 检查纵向
            if (i + 4 < size)
            {
                if (board[i + 1][j] == p && board[i + 2][j] == p && board[i + 3][j] == p && board[i + 4][j] == p)
                    return p;
            }

            // 检查主对角线
            if (i + 4 < size && j + 4 < size)
            {
                if (board[i + 1][j + 1] == p && board[i + 2][j + 2] == p && board[i + 3][j + 3] == p && board[i + 4][j + 4] == p)
                    return p;
            }

            // 检查反对角线
            if (i + 4 < size && j - 4 >= 0)
            {
                if (board[i + 1][j - 1] == p && board[i + 2][j - 2] == p && board[i + 3][j - 3] == p && board[i + 4][j - 4] == p)
                    return p;
            }
        }
    }

    // 检查是否平局
    int full = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 0)
            {
                full = 0;
                break; // 只要发现一个空位，就没满
            }
        }
        if (!full)
            break;
    }

    if (full)
        return -1; // 平局

    return 0; // 游戏未结束
}
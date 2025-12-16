#include "gomoku.h"

int limit(int x, int y);

struct move ai_move(int a, int b, int turn, int deep) // 递归实现minimax和alpha-beta剪枝算法
{
    struct move option;
    option.x = 0;
    option.y = 0;
    int result = judge();
    if (result != 0 || deep == 0) // 游戏结束了或递归层数到了
    {
        switch (result)
        {
        case 1:
            option.score = 1000000000;
            break;
        case 2:
            option.score = -1000000000;
            break;
        case -1:
            option.score = 0;
            break;
        default:
            option.score = score(turn);
            break;
        }
    }
    else if (turn) // minimax中AI的回合
    {
        option.score = -1000000000;
        int flag = 1; // 是否剪枝的标志
        for (int i = 0; i < size && flag; i++)
        {
            for (int j = 0; j < size && flag; j++)
            {
                if (board[i][j] == 0 && limit(i, j)) // 该位置为空
                {
                    board[i][j] = 1;                               // AI下在该位置
                    struct move temp = ai_move(a, b, 0, deep - 1); // minimax递归
                    board[i][j] = 0;                               // 恢复该位置
                    if (temp.score > option.score)                // 得分更高，下法对AI更有利
                    {
                        option.score = temp.score; // 更新得分和位置
                        option.x = i;
                        option.y = j;
                        a = option.score > a ? option.score : a; // 更新最大值alpha
                        if (a >= b)
                            flag = 0; // 剪枝
                    }
                }
            }
        }
    }
    else // minimax中人的回合
    {
        option.score = 1000000000;
        int flag = 1; // 是否剪枝的标志
        for (int i = 0; i < size && flag; i++)
        {
            for (int j = 0; j < size && flag; j++)
            {
                if (board[i][j] == 0 && limit(i, j)) // 该位置为空
                {
                    board[i][j] = 2;                               // 人下在该位置
                    struct move temp = ai_move(a, b, 1, deep - 1); // minimax递归
                    board[i][j] = 0;                               // 恢复该位置
                    if (temp.score < option.score)                // 得分更低，下法对人更有利
                    {
                        option.score = temp.score; // 更新得分和位置
                        option.x = i;
                        option.y = j;
                        b = option.score < b ? option.score : b; // 更新最小值beta
                        if (b <= a)
                            flag = 0; // 剪枝
                    }
                }
            }
        }
    }
    return option; // 返回最佳落子位置和得分
}

int limit(int x, int y)
{
    int flag = 0;
    for (int i = x - 1; i <= x + 1 && i >= 0 && i < size; i++)
    {
        for (int j = y - 1; j <= y + 1 && j >= 0 && j < size; j++)
        {
            if (i == x && j == y)
                continue;
            else if (board[i][j])
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}
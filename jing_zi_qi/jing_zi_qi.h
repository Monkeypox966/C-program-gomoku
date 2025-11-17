
/* -------------------------------------------------------------------------- */
/*  运用minimax和alpha-beta剪枝算法实现的井字棋AI                               */
/*  人下记为-1，AI下记为1，空位记为0                                            */
/*  人用O表示，AI用X表示，空位用.表示                                           */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

extern int board[3][3];
struct move // 结构体存储最佳落子位置和分数
{
    int score;
    int x, y;
};

void print_board(void);                      // 打印棋盘
int judge(void);                             // 判断游戏是否结束，返回2表示未结束，-1表示人赢，1表示AI赢，0表示平局
void print_the_result(void);                 // 打印棋局最终结果
struct move ai_move(int a, int b, int turn); // 递归实现minimax和alpha-beta剪枝算法
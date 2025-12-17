/* -------------------------------------------------------------------------- */
/*  运用minimax和alpha-beta剪枝算法实现的井字棋AI                               */
/*  人下记为2，AI下记为1，空位记为0                                             */
/*  人用O表示，AI用X表示，空位用.表示                                           */
/*  判断游戏是否结束，返回0表示未结束，2表示人赢，1表示AI赢，-1表示平局            */
/*  递归深度depth控制难度                                                      */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define size 15 // 棋盘大小
#define depth 3 // 递归深度，可控制难度,但对后期速度影响极大,不建议超过5

extern int board[size][size];
struct move // 结构体存储最佳落子位置和分数
{
    int score;
    int x, y;
};

void print_board(void);                                // 打印棋盘
int judge(void);                                       // 判断游戏是否结束，返回0表示未结束，2表示人赢，1表示AI赢，-1表示平局
int score(void);                                       // 棋盘估分
void print_result(int result);                         // 打印棋局最终结果
struct move ai_move(int a, int b, int turn, int deep); // 递归实现minimax和alpha-beta剪枝算法
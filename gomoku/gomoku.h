#include "raylib.h"
#include <math.h>
#include <stdlib.h>


#define CELL_SIZE 50       // 格子大小
#define PADDING 60   // 棋盘边缘留白
#define SIZE 15       // 棋盘大小
#define Info_W 400
#define Window_W  ((SIZE - 1) * CELL_SIZE + PADDING * 2 + Info_W)
#define Window_H ((SIZE - 1) * CELL_SIZE + PADDING * 2) 
#define Color_back (Color){ 222, 184, 135, 255 }
#define Color_line (Color) { 80, 50, 20, 255 }

typedef struct {
    int x, y;
} Move;
extern Move MOVE[SIZE * SIZE];
extern int step;
extern int board[SIZE][SIZE] ;
extern int direct[4][2];
extern int dif;

int valid(int x, int y) ;
int init_board() ;
int check_win() ;
int PVP();
int PVE();
int get_best_move(int *x, int *y);
int choose_dif();

//*branch-yu*//








#include <stdio.h>
#include <string.h>

#define size 15 // 棋盘大小
struct move // 结构体存储最佳落子位置和分数
{
    int score;
    int x, y;
};

                             // 打印棋盘
int judge(void);                                       // 判断游戏是否结束，返回0表示未结束，2表示人赢，1表示AI赢，-1表示平局
int score(void);                                       // 棋盘估分                     // 打印棋局最终结果
struct move ai_move(int a, int b, int turn, int deep); // 递归实现minimax和alpha-beta剪枝算法


//*ma  second*//





























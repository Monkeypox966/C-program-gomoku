#include "raylib.h"


#define CELL_SIZE 50       // 格子大小
#define BOARD_PADDING 60   // 棋盘边缘留白
#define BOARD_SIZE 8       // 棋盘大小
#define SCREEN_WIDTH  ((BOARD_SIZE - 1) * CELL_SIZE + BOARD_PADDING * 2)
#define SCREEN_HEIGHT ((BOARD_SIZE - 1) * CELL_SIZE + BOARD_PADDING * 2 + 50) 
#define COLOR_BOARD (Color){ 222, 184, 135, 255 }
#define COLOR_LINE (Color) { 80, 50, 20, 255 }

int board[BOARD_SIZE][BOARD_SIZE] ;
int directions[4][2] = {{1, 1}, {1, -1}, {1, 0}, {0, 1}} ;

int valid(int x, int y) {
    return (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT);
}

int init_board() {
    for (int i = 0 ; i < BOARD_SIZE; i++)
        for (int j =0; j < BOARD_SIZE; j++) board[i][j] = 0;
}

int check_win() ;
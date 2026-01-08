#include "gomoku.h"

void print_board(void) // 打印棋盘
{
    for (int i = 0; i < SIZE; i++) {    //画棋盘
                DrawLine(PADDING, PADDING + i*CELL_SIZE,
                            Window_W - PADDING - Info_W, PADDING + i*CELL_SIZE, Color_line); //横线
                DrawLine(PADDING + i*CELL_SIZE, PADDING,
                            PADDING + i*CELL_SIZE, Window_H - PADDING, Color_line); //竖线       
            }
            DrawCircle(PADDING + CELL_SIZE * 7, PADDING + CELL_SIZE * 7, 4, BLACK); //天元
            DrawCircle(PADDING + CELL_SIZE * 3, PADDING + CELL_SIZE * 3, 4, BLACK); //星位
            DrawCircle(PADDING + CELL_SIZE * 3, PADDING + CELL_SIZE * 11, 4, BLACK);
            DrawCircle(PADDING + CELL_SIZE * 11, PADDING + CELL_SIZE * 3, 4, BLACK);
            DrawCircle(PADDING + CELL_SIZE * 11, PADDING + CELL_SIZE * 11, 4, BLACK);
}
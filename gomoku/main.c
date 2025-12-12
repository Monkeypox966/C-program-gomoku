#include "gomoku.h"

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gomoku - Player VS AI");   // 初始化窗口
    SetTargetFPS(60); // 锁定60帧

    int current_player = 1;
    while ( !WindowShouldClose()) {
        if (!check_win()) {
            //1.处理鼠标点击
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 MousePos = GetMousePosition();
                int col = (int) round((MousePos.x - BOARD_PADDING) / CELL_SIZE);
                int row = (int) round((MousePos.y - BOARD_PADDING) / CELL_SIZE);
                    
                if (valid(row, col) && board[row][col] == 0) {
                    if (current_player == 1) {board[row][col] = 1;    current_player = -current_player;}
                    else {board[row][col] = -1;    current_player = -current_player;}
                }
                
            }    
        }

        if (IsKeyPressed(KEY_R)) {
            current_player = 1;
            init_board();
        }
        

        //2.开始绘图
        BeginDrawing();     

            ClearBackground(COLOR_BOARD);

            //画网格线
            for (int i = 0; i < BOARD_SIZE; i++) {
                DrawLine(BOARD_PADDING, BOARD_PADDING + i*CELL_SIZE,
                            SCREEN_WIDTH - BOARD_PADDING, BOARD_PADDING + i*CELL_SIZE, COLOR_LINE); //横线
                DrawLine(BOARD_PADDING + i*CELL_SIZE, BOARD_PADDING,
                            BOARD_PADDING + i*CELL_SIZE, SCREEN_WIDTH - BOARD_PADDING, COLOR_LINE); //竖线       
            }
            //画棋子
            for (int i = 0; i < BOARD_SIZE; i++)
                for (int j = 0; j < BOARD_SIZE; j++) {
                    int x = BOARD_PADDING + j * CELL_SIZE;
                    int y = BOARD_PADDING + i * CELL_SIZE;
                    if (board[i][j] == 1) DrawCircle(x, y, CELL_SIZE / 2 -10, BLACK);
                    if (board[i][j] == -1) DrawCircle(x, y, CELL_SIZE / 2 -10, WHITE);

                }
            //画游戏结束
            if (check_win()) {
                if (check_win() == 1) DrawText("YOU WIN! Press R to Restart", 20, SCREEN_HEIGHT - 40, 20, DARKGREEN);
                else DrawText("AI WIN! Press R to Restart", 20, SCREEN_HEIGHT - 40, 20, RED);
            }
                          
        EndDrawing();       

    }


    CloseWindow();
    return 0;
}

int check_win() {
    int flag = 0;
    for (int i = 0; i < BOARD_SIZE && !flag; i++) 
        for (int j = 0; j < BOARD_SIZE && !flag; j++)
            if (board[i][j] != 0) {
                for (int k = 0; k < 4; k++) {
                    int x = i, y = j;
                    int count = 0;
                    while (valid(x, y) && board[x][y] == board[i][j] && count < 5) {
                        count++;
                        x += directions[k][0]; y += directions[k][1];
                    }
                    if (count == 5) flag = board[i][j];
                }
            }

    
    return flag;
}
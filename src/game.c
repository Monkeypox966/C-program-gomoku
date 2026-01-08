#include "gomoku.h"

int board[SIZE][SIZE];
int direct[4][2] = {{1, 1}, {1, -1}, {1, 0}, {0, 1}} ;

int dif;
Move MOVE[SIZE*SIZE];
int step;

int valid(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}
int init_board() {
    for (int i = 0 ; i < SIZE; i++)
        for (int j =0; j < SIZE; j++) board[i][j] = 0;
}
int check_win() {
    int flag = 0;
    for (int i = 0; i < SIZE && !flag; i++) 
        for (int j = 0; j < SIZE && !flag; j++)
            if (board[i][j] != 0) {
                for (int k = 0; k < 4; k++) {
                    int x = i, y = j;
                    int count = 0;
                    while (valid(x, y) && board[x][y] == board[i][j] && count < 5) {
                        count++;
                        x += direct[k][0]; y += direct[k][1];
                    }
                    if (count == 5) flag = board[i][j];
                }
            }

    
    return flag;
}
int choose_dif() {
    while(!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) { dif = 1; break;}      //选择难度，存入dif，递归时调用
        if (IsKeyPressed(KEY_TWO)) { dif = 2; break;}
        if (IsKeyPressed(KEY_THREE)) { dif = 3; break;}
        
        BeginDrawing();
            ClearBackground(Color_back);
            DrawText("Choose AI difficulty!!", Window_W - Info_W, 300, 30, RAYWHITE);
            DrawText("Press button 1/2/3...", Window_W - Info_W, 400, 27, RAYWHITE);

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

        EndDrawing();
    }
    PVE();
}

int PVP() {

    Sound knock = LoadSound("../resources/knock.wav");
    Sound cheers = LoadSound("../resources/cheers.wav");

    int player = 2;
    while ( !WindowShouldClose()) {
        if (!check_win()) {
            //1.处理鼠标点击
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 MousePos = GetMousePosition();
                int col = (int) round((MousePos.x - PADDING) / CELL_SIZE);
                int row = (int) round((MousePos.y - PADDING) / CELL_SIZE);
                    
                if (valid(row, col) && board[row][col] == 0) {
                    step++; MOVE[step].x = row; MOVE[step].y = col;
                    board[row][col] = player;    player = 3 -player;

                    PlaySound(knock);
                    if (check_win()) PlaySound(cheers);
                }
                
            }    
        }

        Vector2 MousePos = GetMousePosition();      //控制面板按钮
        Rectangle regret = {Window_W - Info_W + 50, 650, 130, 60}, restart = {Window_W - Info_W + 230, 650, 135, 60};
        Color btn_color1 = CheckCollisionPointRec(MousePos, regret) ? SKYBLUE : BLUE;
        Color btn_color2 = CheckCollisionPointRec(MousePos, restart) ? SKYBLUE : BLUE;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(MousePos, regret)) {
                board[MOVE[step].x][MOVE[step].y] = 0;
                step = (step > 0)? step - 1 : 0;
                player = 3 -player;
            }
            if (CheckCollisionPointRec(MousePos, restart)) {
                player = 2;
                step = 0;
                init_board();
            }
        }

        char step_ch[10] = {'\0'};
        itoa(step, step_ch, 10);
        //2.开始绘图
        BeginDrawing();     

            ClearBackground(Color_back);

            //画网格线
            for (int i = 0; i < SIZE; i++) {
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
            //画棋子
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++) {
                    int x = PADDING + j * CELL_SIZE;
                    int y = PADDING + i * CELL_SIZE;
                    if (board[i][j] == 2) {
                        DrawCircle(x + 3, y + 3, CELL_SIZE / 2 -4, Fade(BLACK, 0.3f));
                        DrawCircleGradient(x, y, CELL_SIZE / 2 -4, DARKGRAY, BLACK);
                    }
                    if (board[i][j] == 1) {
                        DrawCircle(x + 3, y + 3, CELL_SIZE / 2 -4, Fade(BLACK, 0.3f));
                        DrawCircleGradient(x, y, CELL_SIZE / 2 -4, RAYWHITE, LIGHTGRAY);
                        DrawCircleLines(x, y, CELL_SIZE / 2 -4, Fade(BLACK, 0.1f));
                    }

                }
            //画面板
            DrawText("Current step:", Window_W - Info_W, 500, 40, DARKBROWN);
            DrawText(step_ch, Window_W - Info_W + 300, 500, 40, DARKBROWN);
            DrawRectangleRounded(regret, 0.3f, 10, btn_color1);  //画两个按钮
            DrawText("Regret", Window_W - Info_W + 60, 670, 30, RAYWHITE);
            DrawRectangleRounded(restart, 0.3f, 10, btn_color2);
            DrawText("Restart", Window_W - Info_W + 240, 670, 30, RAYWHITE);

            //画游戏结束
            if (check_win()) {
                if (check_win() == 2) {
                    DrawCircleGradient(Window_W - Info_W + 200, 350, 100, DARKGRAY, BLACK);
                    DrawText("Black Win !!!", Window_W - Info_W, 150, 40, DARKBROWN);
                    DrawText("Close the window or restart ...", Window_W - Info_W, 200, 25, DARKBROWN);
                }
                else {
                    DrawCircleGradient(Window_W - Info_W + 200, 350, 100, RAYWHITE, LIGHTGRAY);
                    DrawText("White Win !!!", Window_W - Info_W, 150, 40, DARKBROWN);
                    DrawText("Close the window or restart ...", Window_W - Info_W, 200, 25, DARKBROWN);
                }
            }
            else {
                DrawText("Current player:", Window_W - Info_W +35, 150, 40, DARKBROWN); 
                if (player == 2) DrawCircleGradient(Window_W - Info_W + 200, 350, 100, DARKGRAY, BLACK);
                else DrawCircleGradient(Window_W - Info_W + 200, 350, 100, RAYWHITE, LIGHTGRAY);
            }
                          
        EndDrawing();       

    }

    CloseWindow();

    UnloadSound(knock);
    UnloadSound(cheers);
    return 0;
}

int PVE() {
    int player = 2;

    Sound knock = LoadSound("../resources/knock.wav");
    Sound cheers = LoadSound("../resources/cheers.wav");

    while ( !WindowShouldClose()) {
        if (!check_win()) {
            if (player == 2) {      //玩家执子
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 MousePos = GetMousePosition();
                    int col = (int) round((MousePos.x - PADDING) / CELL_SIZE);
                    int row = (int) round((MousePos.y - PADDING) / CELL_SIZE);
                        
                    if (valid(row, col) && board[row][col] == 0) {
                        step++; MOVE[step].x = row; MOVE[step].y = col;
                        board[row][col] = 2;    player = 3 -player; 
                        PlaySound(knock);
                        if (check_win()) PlaySound(cheers);
                    }
                }
            }
            else if (player == 1) {    //AI执子
                int col, row;
                get_best_move(&row, &col);
                step++; MOVE[step].x = row; MOVE[step].y = col;
                board[row][col] = 1;    player = 3 -player;
                PlaySound(knock);
                if (check_win()) PlaySound(cheers);
            }
                
        }

        Vector2 MousePos = GetMousePosition();      //控制面板按钮
        Rectangle regret = {Window_W - Info_W + 50, 650, 130, 60}, restart = {Window_W - Info_W + 230, 650, 135, 60};
        Color btn_color1 = CheckCollisionPointRec(MousePos, regret) ? SKYBLUE : BLUE;
        Color btn_color2 = CheckCollisionPointRec(MousePos, restart) ? SKYBLUE : BLUE;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(MousePos, regret)) {
                board[MOVE[step].x][MOVE[step].y] = 0;  step = (step > 0)? step - 1 : 0;
                board[MOVE[step].x][MOVE[step].y] = 0;  step = (step > 0)? step - 1 : 0;
            }
            if (CheckCollisionPointRec(MousePos, restart)) {
                player = 2;
                init_board();
                step = 0;
            }
        }

        char step_ch[10] = {'\0'};
        itoa(step, step_ch, 10);

        //2.开始绘图
        BeginDrawing();     
            ClearBackground(Color_back);

            //画网格线
            for (int i = 0; i < SIZE; i++) {
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
            //画棋子
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++) {
                    int x = PADDING + j * CELL_SIZE;
                    int y = PADDING + i * CELL_SIZE;
                    if (board[i][j] == 2) {
                        DrawCircle(x + 3, y + 3, CELL_SIZE / 2 -4, Fade(BLACK, 0.3f));
                        DrawCircleGradient(x, y, CELL_SIZE / 2 -4, DARKGRAY, BLACK);
                    }
                    if (board[i][j] == 1) {
                        DrawCircle(x + 3, y + 3, CELL_SIZE / 2 -4, Fade(BLACK, 0.3f));
                        DrawCircleGradient(x, y, CELL_SIZE / 2 -4, RAYWHITE, LIGHTGRAY);
                        DrawCircleLines(x, y, CELL_SIZE / 2 -4, Fade(BLACK, 0.1f));
                    }

                }
            //画面板
            DrawText("Current step:", Window_W - Info_W, 500, 40, DARKBROWN);
            DrawText(step_ch, Window_W - Info_W + 300, 500, 40, DARKBROWN);
            DrawRectangleRounded(regret, 0.3f, 10, btn_color1); 
            DrawText("Regret", Window_W - Info_W + 60, 670, 30, RAYWHITE);
            DrawRectangleRounded(restart, 0.3f, 10, btn_color2);
            DrawText("Restart", Window_W - Info_W + 240, 670, 30, RAYWHITE);

            //画游戏结束
            if (check_win()) {
                if (check_win() == 2) {
                    DrawCircleGradient(Window_W - Info_W + 200, 350, 100, DARKGRAY, BLACK);
                    DrawText("You Win !!!", Window_W - Info_W, 150, 40, DARKBROWN);
                    DrawText("Close the window or restart ...", Window_W - Info_W, 200, 25, DARKBROWN);
                }
                else {
                    DrawCircleGradient(Window_W - Info_W + 200, 350, 100, RAYWHITE, LIGHTGRAY);
                    DrawText("AI Win !!!", Window_W - Info_W, 150, 40, DARKBROWN);
                    DrawText("Close the window or restart ...", Window_W - Info_W, 200, 25, DARKBROWN);
                }
            }
            else {
                if (player == 2) {
                    DrawCircleGradient(Window_W - Info_W + 200, 350, 100, DARKGRAY, BLACK);
                    DrawText("Your turn ...", Window_W - Info_W +40, 150, 40, DARKBROWN); 
                }
                else {
                    DrawCircleGradient(Window_W - Info_W + 200, 350, 100, RAYWHITE, LIGHTGRAY);
                    DrawText("AI is thinking ...", Window_W - Info_W +30, 150, 40, DARKBROWN); 
                }
            }
                          
        EndDrawing();       
    }
}

int get_best_move(int *x, int * y) {    //测试用，接入后删除
    
    struct move option = ai_move(-1000000000, 1000000000, 1, dif); // AI计算最佳落子点
	*x = option.x; *y = option.y;
}
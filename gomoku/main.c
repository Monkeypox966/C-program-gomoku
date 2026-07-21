#include "gomoku.h"

int main() {
    InitWindow(Window_W, Window_H, "Welcome");
    SetTargetFPS(60);

    InitAudioDevice();      //音频开关

    int gamemode = 0;
    Rectangle pvp = {Window_W - Info_W + 60, 480, 100, 60}, pve = {Window_W - Info_W + 240, 480, 100, 60};

    while (!WindowShouldClose() && !gamemode) {
        Vector2 MousePos = GetMousePosition();      //选择人机or人人对战
        Color btn_color1 = CheckCollisionPointRec(MousePos, pvp) ? SKYBLUE : BLUE;
        Color btn_color2 = CheckCollisionPointRec(MousePos, pve) ? SKYBLUE : BLUE;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(MousePos, pvp)) gamemode = 1;
            if (CheckCollisionPointRec(MousePos, pve)) gamemode = -1;
        }

        BeginDrawing();
            ClearBackground(Color_back);
            DrawText("Choose your gamemode!!", Window_W - Info_W , 300, 30, RAYWHITE);

            DrawRectangleRounded(pvp, 0.3f, 10, btn_color1);  //画两个按钮
            DrawText("PVP", Window_W - Info_W + 75, 500, 30, RAYWHITE);
            DrawRectangleRounded(pve, 0.3f, 10, btn_color2);
            DrawText("PVE", Window_W - Info_W + 255, 500, 30, RAYWHITE);

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

    if (gamemode == 1) PVP();
    if (gamemode == -1) choose_dif();

    CloseAudioDevice();
    return 0;
}

//*YU.MAIN*//







/*
int board[size][size] = {0}; // 存储棋盘
int main(void)
{
    int x, y, temp;
    print_board();
    while (1)
    {
        // 人下
        printf("Enter the position for your move(x y)："); // 必须用空格隔开
        scanf("%d %d", &x, &y);
        board[x][y] = 2;
        print_board();
        temp = judge();
        if (temp != 0) // 游戏结束
        {
            print_result(temp);
            system("pause"); // 防止程序直接退出
            return 0;
        }
        // AI下
        printf("AI is thinking:\n");
        struct move option = ai_move(-1000000000, 1000000000, 1, dif); // AI计算最佳落子点
        board[option.x][option.y] = 1;                                   // AI落子
        print_board();
        temp = judge();
        if (temp != 0) // 游戏结束
        {
            print_result(temp);
            system("pause");
            return 0;
        }
    }
}




*/









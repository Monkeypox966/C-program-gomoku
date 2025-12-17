#include "gomoku.h"

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
        struct move option = ai_move(-1000000000, 1000000000, 1, depth); // AI计算最佳落子点
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
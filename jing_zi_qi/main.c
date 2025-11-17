#include <stdio.h>
#include <stdlib.h>
#include "jing_zi_qi.h"

int main()
{
    int x, y;
    print_board();
    while (1)
    {
        printf("请输入你要下的位置(x y)："); // 必须用空格隔开
        scanf("%d %d", &x, &y);
        board[x][y] = -1;
        print_board();
        if (judge() != 2) // 游戏结束
        {
            print_the_result();
            system("pause"); // 防止程序直接退出
            return 0;
        }
        printf("AI落子:\n");
        struct move option = ai_move(-1000, 1000, 1); // AI计算最佳落子点
        board[option.x][option.y] = 1;                // AI落子
        print_board();
        if (judge() != 2) // 游戏结束
        {
            print_the_result();
            system("pause");
            return 0;
        }
    }
}
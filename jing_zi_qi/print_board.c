void print_board() // 打印棋盘
{
    printf("\n    0   1   2   y\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf(" %d ", i);
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 1)
                printf(" X  ");
            else if (board[i][j] == -1)
                printf(" O  ");
            else
                printf(" .  ");
        }
        printf("\n\n");
    }
    printf(" x\n\n");
}
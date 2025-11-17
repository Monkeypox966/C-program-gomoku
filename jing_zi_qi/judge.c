int judge() // 判断游戏是否结束，返回2表示未结束，-1表示人赢，1表示AI赢，0表示平局
{
    for (int i = 0; i < 3; i++) // 检查每行
    {
        if (board[i][0] == -1 && board[i][1] == -1 && board[i][2] == -1)
            return -1;
        if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1)
            return 1;
    }
    for (int j = 0; j < 3; j++) // 检查每列
    {
        if (board[0][j] == -1 && board[1][j] == -1 && board[2][j] == -1)
            return -1;
        if (board[0][j] == 1 && board[1][j] == 1 && board[2][j] == 1)
            return 1;
    }
    if (board[0][0] == -1 && board[1][1] == -1 && board[2][2] == -1)
        return -1; // 检查主对角线
    if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1)
        return 1;
    if (board[0][2] == -1 && board[1][1] == -1 && board[2][0] == -1)
        return -1; // 检查反对角线
    if (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)
        return 1;
    int full = 1; // 检查是否下满
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                full = 0;
        }
    }
    if (full)
        return 0;
    return 2;
}
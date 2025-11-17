void print_the_result() // 打印棋局最终结果
{
    int result = judge();
    if (result == -1)
    {
        printf("你赢了！\n");
    }
    else if (result == 0)
    {
        printf("平局！\n");
    }
    else if (result == 1)
    {
        printf("你输了！\n");
    }
}
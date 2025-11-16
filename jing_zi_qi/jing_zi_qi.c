//运用minimax和alpha-beta剪枝算法实现的井字棋AI
//人下记为-1，AI下记为1，空位记为0
//人用O表示，AI用X表示，空位用.表示

#include<stdio.h>
#include <stdlib.h>


int board[3][3]={0}; //存储棋盘
struct move //结构体存储最佳落子位置和分数
{
    int score;
    int x,y;
};


void print_board(); //打印棋盘
int judge(); //判断游戏是否结束，返回2表示未结束，-1表示人赢，1表示AI赢，0表示平局
void print_the_result(); //打印棋局最终结果
struct move ai_move(int a,int b,int turn); //递归实现minimax和alpha-beta剪枝算法

int main()
{
    int x,y;
    print_board();
    while(1)
    {
        printf("请输入你要下的位置(x y)："); //必须用空格隔开
        scanf("%d %d",&x,&y);
        board[x][y]=-1;
        print_board();
        if(judge()!=2) //游戏结束
        {
            print_the_result();
            system("pause"); //防止程序直接退出
            return 0;
        }
        printf("AI落子:\n");
        struct move option=ai_move(-1000,1000,1); //AI计算最佳落子点
        board[option.x][option.y]=1; //AI落子
        print_board();
        if(judge()!=2) //游戏结束
        {
            print_the_result();
            system("pause");
            return 0;
        }
    }
}

void print_board() //打印棋盘
{
    printf("\n    0   1   2   y\n\n");
    for(int i=0;i<3;i++)
    {
        printf(" %d ",i);
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==1) printf(" X  ");
            else if(board[i][j]==-1) printf(" O  ");
            else printf(" .  ");
        }
        printf("\n\n");
    }
    printf(" x\n\n");
}

int judge() //判断游戏是否结束，返回2表示未结束，-1表示人赢，1表示AI赢，0表示平局
{
    for(int i=0;i<3;i++) //检查每行
    {
        if(board[i][0]==-1 && board[i][1]==-1 && board[i][2]==-1) return -1;
        if(board[i][0]==1 && board[i][1]==1 && board[i][2]==1) return 1;
    }
    for(int j=0;j<3;j++) //检查每列
    {
        if(board[0][j]==-1 && board[1][j]==-1 && board[2][j]==-1) return -1;
        if(board[0][j]==1 && board[1][j]==1 && board[2][j]==1) return 1;
    }
    if(board[0][0]==-1 && board[1][1]==-1 && board[2][2]==-1) return -1; //检查主对角线
    if(board[0][0]==1 && board[1][1]==1 && board[2][2]==1) return 1;
    if(board[0][2]==-1 && board[1][1]==-1 && board[2][0]==-1) return -1; //检查反对角线
    if(board[0][2]==1 && board[1][1]==1 && board[2][0]==1) return 1;
    int full=1; //检查是否下满
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==0) full=0;
        }
    }
    if(full) return 0;
    return 2;
}

void print_the_result() //打印棋局最终结果
{
    int result=judge();
    if(result==-1)
    {
        printf("你赢了！\n");
    }
    else if(result==0)
    {
        printf("平局！\n");
    }
    else if(result==1)
    {
        printf("你输了！\n");
    }
}

struct move ai_move(int a,int b,int turn) //递归实现minimax和alpha-beta剪枝算法
{
    struct move option;
    if(judge()!=2) //游戏结束了
    {
        option.score=judge();
        option.x=0;
        option.y=0;
    }
    else if(turn) //minimax中AI的回合
    {
        option.score=-1000;
        int flag=1; //是否剪枝的标志
        for(int i=0;i<3&flag;i++)
        {
            for(int j=0;j<3&flag;j++)
            {
                if(board[i][j]==0) //该位置为空
                {
                    board[i][j]=1; //AI下在该位置
                    struct move temp=ai_move(a,b,0); //minimax递归
                    board[i][j]=0; //恢复该位置
                    if(temp.score>option.score) //得分更高，下法对AI更有利
                    {
                        option.score=temp.score; //更新得分和位置
                        option.x=i;
                        option.y=j;
                        a=option.score>a?option.score:a; //更新最大值alpha
                        if(a>=b) flag=0; //剪枝
                    }
                }
            }
        }
    }
    else //minimax中人的回合
    {
        option.score=1000;
        int flag=1; //是否剪枝的标志
        for(int i=0;i<3&flag;i++)
        {
            for(int j=0;j<3&flag;j++)
            {
                if(board[i][j]==0) //该位置为空
                {
                    board[i][j]=-1; //人下在该位置
                    struct move temp=ai_move(a,b,1); //minimax递归
                    board[i][j]=0; //恢复该位置
                    if(temp.score<option.score) //得分更低，下法对人更有利
                    {
                        option.score=temp.score; //更新得分和位置
                        option.x=i;
                        option.y=j;
                        b=option.score<b?option.score:b; //更新最小值beta
                        if(b<=a) flag=0; //剪枝
                    }
                }
            }
        }
    }
    return option; //返回最佳落子位置和得分
}
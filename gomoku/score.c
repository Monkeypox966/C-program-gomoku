#include "gomoku.h"

// 分值梯度
const int s1 = 50000;
const int s2 = 8000;
const int s3 = 10;
const int s4 = 1;

int table[243] = {0}; // 哈希表存储分数，五个位置一共有3^5=243种可能
static int flag = 0;  // 防止多次重复构建table

int hash(int p[5]);              // 返回棋形对应的哈希值
void grade(int p[5], int score); // 对棋形进行打分
void build_table(void);          // 构建哈希表

int score(void)
{
    build_table();
    int total = 0;
    int dx[4] = {1, 0, 1, 1}; // 步长
    int dy[4] = {0, 1, 1, -1};
    // 遍历棋盘
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int x = i + 4 * dx[k];
                int y = j + 4 * dy[k];
                if (x < 0 || x >= size || y < 0 || y >= size) // 保证边界条件
                    continue;

                int a0 = board[i + 0 * dx[k]][j + 0 * dy[k]];
                int a1 = board[i + 1 * dx[k]][j + 1 * dy[k]];
                int a2 = board[i + 2 * dx[k]][j + 2 * dy[k]];
                int a3 = board[i + 3 * dx[k]][j + 3 * dy[k]];
                int a4 = board[i + 4 * dx[k]][j + 4 * dy[k]];
                int sum = a0 + a1 * 3 + a2 * 9 + a3 * 27 + a4 * 81; // 计算哈希值
                total += table[sum];                                // 分别计算棋形对ai和人的分数
            }
        }
    }
    return total;
}

int hash(int p[5]) // 计算哈希值
{
    return p[0] + p[1] * 3 + p[2] * 9 + p[3] * 27 + p[4] * 81;
}

void grade(int p[5], int score) // 给哈希表赋值
{
    int ai = hash(p);
    table[ai] = score;
    int p1[5];
    for (int i = 0; i < 5; i++)
    {
        p1[i] = (p[i]) ? 3 - p[i] : 0; // 下面只列举了ai情况，1和2反转以下能列举人的情况
    }
    int human = hash(p1);
    table[human] = -(int)(1.2 * score); // 1.2为防守系数，可以更改
}

void build_table(void) // 构建哈希表
{
    if (flag)
        return;
    int p4a[5] = {0, 1, 1, 1, 1};
    grade(p4a, s1);
    int p4b[5] = {1, 1, 1, 1, 0};
    grade(p4b, s1);
    int p4c[5] = {1, 0, 1, 1, 1};
    grade(p4c, s1);
    int p4d[5] = {1, 1, 0, 1, 1};
    grade(p4d, s1);
    int p4e[5] = {1, 1, 1, 0, 1};
    grade(p4e, s1);
    int p3a[5] = {0, 1, 1, 1, 0};
    grade(p3a, s2);
    int p3b[5] = {0, 1, 0, 1, 1};
    grade(p3b, s2);
    int p3c[5] = {1, 1, 0, 1, 0};
    grade(p3c, s2);
    int p3d[5] = {0, 1, 1, 0, 1};
    grade(p3d, s2);
    int p3e[5] = {1, 0, 1, 1, 0};
    grade(p3e, s2);
    int p3f[5] = {2, 1, 1, 1, 0};
    grade(p3f, s3);
    int p3g[5] = {0, 1, 1, 1, 2};
    grade(p3g, s3);
    int p2a[5] = {0, 0, 1, 1, 0};
    grade(p2a, s4);
    int p2b[5] = {0, 1, 1, 0, 0};
    grade(p2b, s4);
    int p2c[5] = {0, 1, 0, 1, 0};
    grade(p2c, s4);
    flag = 1;
}
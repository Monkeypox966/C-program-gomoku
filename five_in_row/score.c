#include "gomoku.h"

const int s1 = 50000;
const int s2 = 8000;
const int s3 = 10;
const int s4 = 1;

int table[243][2] = {0};
static int flag = 0;

int hash(int p[5]);
void grade(int p[5], int score);
void build_table(void);

int score(int turn)
{
    build_table();
    int score_ai = 0;
    int score_human = 0;
    int dx[4] = {1, 0, 1, 1};
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
                if (x < 0 || x >= size || y < 0 || y >= size)
                    continue;

                int a0 = board[i + 0 * dx[k]][j + 0 * dy[k]];
                int a1 = board[i + 1 * dx[k]][j + 1 * dy[k]];
                int a2 = board[i + 2 * dx[k]][j + 2 * dy[k]];
                int a3 = board[i + 3 * dx[k]][j + 3 * dy[k]];
                int a4 = board[i + 4 * dx[k]][j + 4 * dy[k]];
                int sum = a0 + a1 * 3 + a2 * 9 + a3 * 27 + a4 * 81;
                score_ai += table[sum][0];
                score_human += table[sum][1];
            }
        }
    }
    if (turn)
        return (score_human - 1.2 * score_ai);
    else
        return (score_ai - 1.2 * score_human);
}

int hash(int p[5])
{
    return p[0] + p[1] * 3 + p[2] * 9 + p[3] * 27 + p[4] * 81;
}

void grade(int p[5], int score)
{
    int ai = hash(p);
    table[ai][0] = score;
    int p1[5];
    for (int i = 0; i < 5; i++)
    {
        if (p[i] == 1)
            p1[i] = 2;
        else if (p[i] == 2)
            p1[i] = 1;
        else
            p1[i] = 0;
    }
    int human = hash(p1);
    table[human][1] = score;
}

void build_table(void)
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
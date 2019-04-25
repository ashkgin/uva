/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/19
Problem: uva p11906

Algo   : DFS

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_R                   100
#define MAX_C                   100

#define MAX_NODES               30

#define WHITE                   0
#define GRAY                    1
#define BLACK                   2

#define NE                      0
#define NW                      1
#define ES                      2
#define WS                      3
#define JUMP_DIR_MAX            4


int rows, cols;

typedef struct NODE {
    int x;
    int y;
    int even;
    int evenCnt;
    int oddCnt;
    int isBomb;
    int color;
}tNODE;

tNODE nodes[MAX_C][MAX_R];
int cords[8][2];
int distinctJump;

int cordExist(int sx, int sy, int ex, int ey)
{
    int result = 0;
    int x, y;

    x = sx + ex;
    y = sy + ey;

    if ((x < cols) && (y < rows) && (x >= 0) && (y >= 0) && (nodes[y][x].isBomb==0))
    {
        result = 1;
    }

    return result;
}

int cordExistNew(int x, int y)
{
    int result = 0;

    if ((x < cols) && (y < rows) && (x >= 0) && (y >= 0) && (nodes[y][x].isBomb == 0))
    {
        result = 1;
    }

    return result;
}

void jumpAndSearch(int x, int y, int (*cords)[2])
{
    int cnt, i;
    int xNew, yNew;

    if (nodes[y][x].color != WHITE)
    {
        return 0;
    }

    nodes[y][x].color = GRAY;

    cnt = 0;

    for (i = 0; i < distinctJump; i++)
    {
        xNew = x + cords[i][0];
        yNew = y + cords[i][1];
        if (cordExistNew(xNew, yNew))
        {
            cnt++;
            if (nodes[yNew][xNew].color == WHITE)
            {
                jumpAndSearch(xNew, yNew, cords);
                nodes[y][x].evenCnt += nodes[yNew][xNew].evenCnt;
                nodes[y][x].oddCnt += nodes[yNew][xNew].oddCnt;
            }
        }
    }

    if (cnt % 2)
    {
        nodes[y][x].even = 0;
        nodes[y][x].oddCnt++;
    }
    else
    {
        nodes[y][x].even = 1;
        nodes[y][x].evenCnt++;
    }

    nodes[y][x].color = BLACK;

}

int main()
{
    int i, j, x, y, xNew, yNew;
    tNODE *pT;
    int isBomb;

    int tCnt, testCases;
    int cJump, rJump;       //knight max jump size in number of columns and rows
    int wGrids;             //water grid counts
    int wCnt;               //water grid counter
    int cnt;
    int caseID;

#ifndef ONLINE_JUDGE
    freopen("input_p11906.txt", "r", stdin);
#endif
    scanf("%d", &testCases);

    caseID = 0;

    for (tCnt = 0; tCnt < testCases; tCnt++)
    {
        scanf("%d", &cols);
        scanf("%d", &rows);

        scanf("%d", &cJump);
        scanf("%d", &rJump);

        scanf("%d", &wGrids);

        //init
        for (y = 0; y < rows; y++)
        {
            for (x = 0; x < cols; x++)
            {
                nodes[y][x].y = y;
                nodes[y][x].x = x;
                nodes[y][x].isBomb = 0;
                nodes[y][x].even = -1;
                nodes[y][x].evenCnt = 0;
                nodes[y][x].oddCnt = 0;
                nodes[y][x].color = WHITE;
            }
        }

        //read water grids
        for (wCnt = 0; wCnt < wGrids; wCnt++)
        {
            scanf("%d", &x);
            scanf("%d", &y);
            nodes[y][x].isBomb = 1;
        }

        if (rJump!=cJump && rJump!=0 && cJump!=0)
        {
            distinctJump = 8;
            cords[0][0] = rJump;
            cords[0][1] = cJump;

            cords[1][0] = rJump;
            cords[1][1] = -cJump;

            cords[2][0] = cJump;
            cords[2][1] = rJump;

            cords[3][0] = cJump;
            cords[3][1] = -rJump;

            cords[4][0] = -rJump;
            cords[4][1] = cJump;

            cords[5][0] = -rJump;
            cords[5][1] = -cJump;

            cords[6][0] = -cJump;
            cords[6][1] = rJump;

            cords[7][0] = -cJump;
            cords[7][1] = -rJump;
        }
        else if (rJump == cJump)
        {
            distinctJump = 4;
            cords[0][0] = rJump;
            cords[0][1] = cJump;

            cords[1][0] = rJump;
            cords[1][1] = -cJump;

            cords[2][0] = -rJump;
            cords[2][1] = cJump;

            cords[3][0] = -rJump;
            cords[3][1] = -cJump;
        }
        else if (rJump == 0)
        {
            distinctJump = 4;
            cords[0][0] = rJump;
            cords[0][1] = cJump;

            cords[1][0] = rJump;
            cords[1][1] = -cJump;

            cords[2][0] = cJump;
            cords[2][1] = rJump;

            cords[3][0] = -cJump;
            cords[3][1] = rJump;
        }
        else
        {
            distinctJump = 4;
            cords[0][0] = rJump;
            cords[0][1] = cJump;

            cords[1][0] = -rJump;
            cords[1][1] = cJump;

            cords[2][0] = cJump;
            cords[2][1] = rJump;

            cords[3][0] = cJump;
            cords[3][1] = -rJump;
        }



        cnt = 0;
        x = 0;
        y = 0;
        nodes[y][x].color = GRAY;
        for (i = 0; i < distinctJump; i++)
        {
            xNew = x + cords[i][0];
            yNew = y + cords[i][1];
            if (cordExistNew(xNew, yNew))
            {
                cnt++;
                if (nodes[yNew][xNew].color == WHITE)
                {
                    jumpAndSearch(xNew, yNew, cords);
                    nodes[y][x].evenCnt += nodes[yNew][xNew].evenCnt;
                    nodes[y][x].oddCnt += nodes[yNew][xNew].oddCnt;
                }
            }
        }

        if (cnt % 2)
        {
            nodes[y][x].even = 0;
            nodes[y][x].oddCnt++;
        }
        else
        {
            nodes[y][x].even = 1;
            nodes[y][x].evenCnt++;
        }



        nodes[y][x].color = BLACK;

        caseID++;

        printf("Case %d: %d %d\n", caseID, nodes[0][0].evenCnt, nodes[0][0].oddCnt);
    }

    return 0;
}

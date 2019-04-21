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

int main()
{
    int i, j, x, y, sx, sy;
    tNODE *pT;
    int isBomb;

    int tCnt, testCases;
    int cJump, rJump;       //knight max jump size in number of columns and rows
    int wGrids;             //water grid counts
    int wCnt;               //water grid counter

#ifndef ONLINE_JUDGE
    freopen("input_p314.txt", "r", stdin);
#endif
    scanf("%d", &testCases);

    for (tCnt = 1; tCnt < testCases; tCnt++)
    {
        scanf("%d", &rows);
        scanf("%d", &cols);

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

        for (i = 0; i < 8; i++)
        {

        }


        printf("%d\n", nodes[0][0].evenCnt, nodes[0][0].oddCnt);
    }

    return 0;
}

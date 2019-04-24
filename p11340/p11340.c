/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/22
Problem: uva p11340
Algo   : HASH

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define N_MAX                   5
#define K_MAX                   100
#define M_MAX                   150000
#define LINE_MAX                10000

#define MAX_NODES               30

#define WHITE                   0
#define GRAY                    1
#define BLACK                   2

int rows, cols;


typedef struct NODE {
    int x;
    int y;
    int depth;
    int dir;
    int isBomb;
    int color;
}tNODE;

tNODE nodes[MAX_C][MAX_R][4];
tNODE *que[MAX_C*MAX_R*4];

tNODE **pQR, **pQW;

void initQ()
{
    pQR = &que[0];
    pQW = &que[0];
}

void pushQ(int depth, tNODE *pEle)
{
    if (pEle->color == WHITE)
    {
        pEle->color = GRAY;
        pEle->depth = depth;
        *pQW = pEle;
        pQW++;
    }
}

tNODE *popQ()
{
    tNODE *pRes = 0;

    if (pQR < pQW)
    {
        pRes = *pQR;
        pQR++;
        pRes->color = BLACK;
    }

    return pRes;
}

int main()
{
    int i, j, x, y, sx, sy, ex, ey, dirCnt, dirNum;
    int nBombRows, nBombs, finalDepth;
    int done = 0;
    int curNodeCnt;
    tNODE *pT;
    int isBomb;


    int tCnt, testCases, k;
    int   numPaidChars;
    int  paidChars[256];
    char tChar, line[LINE_MAX];
    int mLines;


#ifndef ONLINE_JUDGE
    freopen("input_p314.txt", "r", stdin);
#endif
    scanf("%d", &testCases);

    for (tCnt = 1; tCnt < testCases; tCnt++)
    {
        //init 
        for (i = 0; i < 256; i++)
        {
            paidChars[i] = 0;
        }

        scanf("%d", &numPaidChars);

        for (k = 0; k < numPaidChars; k++)
        {
            scanf("%c", &tChar);
            scanf("%d", &mLines);
        }

        scanf("%d", &paidChars[tChar]);






        K_MAX

    while (1)
    {
        finalDepth = -1;
        scanf("%d", &rows);
        scanf("%d", &cols);

        if (rows == 0 && cols == 0)
            break;

        //reset connections
        for (y = 0; y < rows; y++)
        {
            for (x = 0; x < cols; x++)
            {
                scanf("%d", &isBomb);
                for (dirCnt = 0; dirCnt < 4; dirCnt++)
                {
                    nodes[y][x][dirCnt].dir = dirCnt;
                    nodes[y][x][dirCnt].y = y;
                    nodes[y][x][dirCnt].x = x;
                    nodes[y][x][dirCnt].isBomb = isBomb;
                    nodes[y][x][dirCnt].depth = 0;
                    nodes[y][x][dirCnt].color = WHITE;
                }
            }
        }

        curNodeCnt = 0;

        scanf("%d", &sy);                   //start row
        scanf("%d", &sx);                   //start col

        scanf("%d", &ey);                   //end row
        scanf("%d", &ex);                   //end col

        scanf("%s", &dir);

        if (dir[0] == 'e')
            dirNum = EAST;

        if (dir[0] == 'w')
            dirNum = WEST;


        if (dir[0] == 'n')
            dirNum = NORTH;


        if (dir[0] == 's')
            dirNum = SOUTH;


        initQ();

        pushQ(nodes[sy][sx][dirNum].depth, &nodes[sy][sx][dirNum]);

        while ((pT = popQ()) != 0)
        {
            if ((pT->x == ex) && (pT->y == ey))
            {
                finalDepth = pT->depth;
                break;
            }
            else
            {
                turn(&nodes[pT->y][pT->x][pT->dir]);
                go(&nodes[pT->y][pT->x][pT->dir]);
            }

        }

        printf("%d\n", finalDepth);
    }

    return 0;
}

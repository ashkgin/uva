/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/18
Problem: uva p10653
Algo   : BFS

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_R                   1000
#define MAX_C                   1000

#define MAX_NODES               30

#define WHITE                   0
#define GRAY                    1
#define BLACK                   2

typedef struct NODE {
    int id;
    int depth;
    int isBomb;
    int color;
}tNODE;

tNODE nodes[MAX_C][MAX_R];
tNODE *que[MAX_C*MAX_R];

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
    int i, j, x, y, sx, sy, ex, ey, nID;
    int rows, cols, nBombRows, nBombs, finalDepth;
    int done = 0;
    int curNodeCnt;
    tNODE *pT;
    int caseID = 1;

#ifndef ONLINE_JUDGE
    freopen("input_p10653.txt", "r", stdin);
#endif
    while (1)
    {
        finalDepth = 0;
        scanf("%d", &rows);
        scanf("%d", &cols);

        if (rows == 0 && cols == 0)
            break;

        //reset connections
        for (y = 0; y < rows; y++)
        {
            for (x = 0; x < cols; x++)
            {
                nodes[y][x].id = y * cols + x;
                nodes[y][x].isBomb = 0;
                nodes[y][x].depth = 0;
                nodes[y][x].color = WHITE;
            }
        }

        curNodeCnt = 0;

        scanf("%d", &nBombRows);

        //read connections
        for (i = 0; i < nBombRows; i++)
        {
            scanf("%d", &y);
            scanf("%d", &nBombs);

            for (j = 0; j < nBombs; j++)
            {
                scanf("%d", &x);
                nodes[y][x].isBomb = 1;
            }
        }

        scanf("%d", &sy);                   //start row
        scanf("%d", &sx);                   //start col

        scanf("%d", &ey);                   //end row
        scanf("%d", &ex);                   //end col

        nID = sy * cols + sx;

        initQ();
        pushQ(nodes[sy][sx].depth, &nodes[sy][sx]);
        while ((pT = popQ()) != 0)
        {
            int tx, ty;

            ty = pT->id / cols;
            tx = pT->id % cols;

            if ((tx == ex) && (ty == ey))
            {
                finalDepth = nodes[ty][tx].depth;
                break;
            }
            else
            {
                //right
                if((tx+1 < cols) && (ty<rows) && (nodes[ty][tx+1].color == WHITE) &&(nodes[ty][tx + 1].isBomb==0))
                    pushQ(pT->depth + 1, &nodes[ty][tx+1]);

                //left
                if ((tx - 1 >= 0) && (ty<rows) && (nodes[ty][tx - 1].color == WHITE) && (nodes[ty][tx - 1].isBomb == 0))
                    pushQ(pT->depth + 1, &nodes[ty][tx - 1]);

                //down
                if ((tx < cols) && (ty+1<rows) && (nodes[ty+1][tx ].color == WHITE) && (nodes[ty+1][tx].isBomb == 0))
                    pushQ(pT->depth + 1, &nodes[ty+1][tx]);

                //up
                if ((tx < cols) && (ty-1>=0) && (nodes[ty-1][tx].color == WHITE) && (nodes[ty-1][tx ].isBomb == 0))
                    pushQ(pT->depth + 1, &nodes[ty-1][tx]);
            }

        }

        printf("%d\n", finalDepth);
        caseID++;
    }

    return 0;
}

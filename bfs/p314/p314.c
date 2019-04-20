/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/19
Problem: uva p314

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_R                   50
#define MAX_C                   50

#define MAX_NODES               30

#define WHITE                   0
#define GREY                    1
#define BLACK                   2

#define EAST                    0
#define WEST                    1
#define NORTH                   2
#define SOUTH                   3

#define LEFT                    0
#define RIGHT                   1
#define OPPOSITE                2

#define ONE                     1
#define TWO                     2
#define THREE                   3

int rows, cols;

int direction[4][3] = {
    { NORTH, SOUTH, WEST},                       //EAST FACING
    {SOUTH, NORTH, EAST},                       //WEST FACING
    {WEST, EAST, SOUTH},                         //NORTH FACING
    { EAST, WEST, NORTH }                         //SOUTH FACING
};

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
        pEle->color = GREY;
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

void turn(tNODE *pNode)
{
    int newDir, curDirNum;
    int x, y;

    x = pNode->x;
    y = pNode->y;

    //turn left if possible
    curDirNum = pNode->dir;
    newDir = direction[curDirNum][LEFT];
    if (nodes[y][x][newDir].color == WHITE)
    {
        pushQ(pNode->depth + 1, &nodes[y][x][newDir]);
    }

    newDir = direction[curDirNum][RIGHT];
    if (nodes[y][x][newDir].color == WHITE)
    {
        pushQ(pNode->depth + 1, &nodes[y][x][newDir]);
    }

}

void go_west(tNODE *pNode, int x, int y, int curDirNum, int step)
{
    if (step > 3)
    {
        return;
    }

    if (x - (step+1) >= 0)
    {
        if ((nodes[y][x - (step + 1)][curDirNum].isBomb != 1) && (nodes[y - 1][x - (step + 1)][curDirNum].isBomb != 1))
        {
            pushQ(pNode->depth + 1, &nodes[y][x - step][curDirNum]);
            //check if forward to next step is possible
            go_west(pNode, x, y, curDirNum, step + 1);
        }
    }
}

void go_east(tNODE *pNode, int x, int y, int curDirNum, int step)
{
    if (step > 3)
    {
        return;
    }

    if (x + step < cols)
    {
        if ((nodes[y][x +step][curDirNum].isBomb != 1) && (nodes[y - 1][x +step][curDirNum].isBomb != 1))
        {
            pushQ(pNode->depth + 1, &nodes[y][x + step][curDirNum]);
            //check if forward to next step is possible
            go_east(pNode, x, y, curDirNum, step + 1);
        }
    }
}

void go_north(tNODE *pNode, int x, int y, int curDirNum, int step)
{
    if (step > 3)
    {
        return;
    }

    if (y - (step + 1) >= 0)
    {
        if ((nodes[y - (step + 1)][x][curDirNum].isBomb != 1) && (nodes[y - (step + 1)][x - 1][curDirNum].isBomb != 1))
        {
            pushQ(pNode->depth + 1, &nodes[y - step][x][curDirNum]);
            //check if forward to next step is possible
            go_north(pNode, x, y, curDirNum, step + 1);
        }
    }
}

void go_south(tNODE *pNode, int x, int y, int curDirNum, int step)
{
    if (step > 3)
    {
        return;
    }

    if (y + step < rows)
    {
        if ((nodes[y + step][x][curDirNum].isBomb != 1) && (nodes[y + step][x -1][curDirNum].isBomb != 1))
        {
            pushQ(pNode->depth + 1, &nodes[y + step][x][curDirNum]);
            //check if forward to next step is possible
            go_south(pNode, x, y, curDirNum, step + 1);
        }
    }
}

void go(tNODE *pNode)
{
    tNODE* pRes = 0;
    int curDirNum;
    int x, y;

    x = pNode->x;
    y = pNode->y;

    curDirNum = pNode->dir;

    //check if forward to one step is possible
    if (curDirNum == EAST)
    {
        go_east(pNode, x, y, curDirNum, 1);
    }
    else if (curDirNum == WEST)
    {
        go_west(pNode, x, y, curDirNum, 1);
    }
    else if (curDirNum == NORTH)
    {
        go_north(pNode, x, y, curDirNum, 1);
    }
    else
    {
        go_south(pNode, x, y, curDirNum, 1);
    }
}


int main()
{
    int i, j, x, y, sx, sy, ex, ey, dirCnt, dirNum;
    int nBombRows, nBombs, finalDepth;
    int done = 0;
    int curNodeCnt;
    tNODE *pT;
    int isBomb;
    char  dir[6];

#ifndef ONLINE_JUDGE
    freopen("input_p314.txt", "r", stdin);
#endif
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

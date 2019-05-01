/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/29
Problem: uva p957
Algo   : Binary Tree Search + Complete Search

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_NODES               (2 * 1000000)

typedef struct NODE {
    int popNum;
    int YLEx;
    int YREx;
    struct NODE *pL;
    struct NODE *pR;
}tNODE;

tNODE nodes[MAX_NODES];
int depth;
tNODE *pRoot=0;
int nodeCntMax;

//find node with year yTemp
int findNode(int yTemp, int idx)
{
    int i;
    int nodeIdx;

    for (i = 1; i <= depth; i++)
    {
        nodeIdx = idx >> i;
        if (pRoot[nodeIdx].YLEx <= yTemp)
        {
            break;
        }
    }

    for (; i > 0; --i)
    {
        if (yTemp < pRoot[(nodeIdx << 1) + 1].YLEx)
        {
            nodeIdx = (nodeIdx << 1);
        }
        else
        {
            nodeIdx = (nodeIdx << 1)+1;
        }
    }

    return nodeIdx;
}

int main()
{
    int res = 0;
    int nYears, nPopes, year, yMax, yTemp;
    int i, j, idx, nodeCnt;
    int temp1, temp2;
    tNODE *pMid, *pTemp;
    int layerIdx;
    int maxPopes, startYear, endYear;

#ifndef ONLINE_JUDGE
    freopen("input_p957.txt", "r", stdin);
#endif

    pMid = &nodes[MAX_NODES / 2];

    while (1)
    {
        res = scanf("%d", &nYears);
        if (res < 0)
        {
            break;
        }

        scanf("%d", &nPopes);

        //init
        pTemp = pMid;
        nodeCnt = 0;

        scanf("%d", &year);
        pTemp->YLEx = year;
        pTemp->popNum = 1;
        nodeCnt++;


        for (i = 2; i <= nPopes; i++)
        {
            scanf("%d", &year);
            if (pTemp->YLEx != year)
            {
                pTemp++;
                nodeCnt++;
                pTemp->YLEx = year;
            }
            pTemp->popNum = i;
        }

        yMax = year;

        //for sake of completion of tree
        if (nodeCnt % 2)
        {
            pTemp++;
            nodeCnt++;
            pTemp->popNum = nPopes;
            pTemp->YLEx = year;
        }

        for (i = 1; i <= 32; i++)
        {
            if ((nPopes >> i) == 0)
            {
                break;
            }
        }

        depth = i;
        nodeCntMax = 1 << depth;
        pRoot = pMid - (1 << depth);

        //set first parent level
        temp1 = nodeCnt >> 1;
        temp2 = nodeCntMax >> 1;
        for (i = 0; i < temp1; i++)
        {
            pRoot[temp2 + i].YLEx = pRoot[nodeCntMax + 2 * i].YLEx;
            pRoot[temp2 + i].YREx = pRoot[nodeCntMax + 2 * i + 1].YLEx;
        }

        //set rest of the tree
        for (i = 2; i <= depth; i++)
        {
            layerIdx = nodeCntMax >> i;
            for (j = 0; j < (nodeCntMax >> i); j++)
            {
                pRoot[layerIdx + j].YLEx = pRoot[2 * (layerIdx + j)].YLEx;
                pRoot[layerIdx + j].YREx = pRoot[2 * (layerIdx + j) + 1].YREx;
            }
        }

        //first search

        for (i = 0; i < nodeCnt; i++)
        {
            if (pMid[i].YLEx > nYears)
            {
                break;
            }
        }
        i--;
        maxPopes = pMid[i].popNum;
        startYear = pMid[0].YLEx;
        endYear = pMid[i].YLEx;

            //complete search
            for (; i < nodeCnt; i++)
            {
                yTemp = pMid[i].YLEx - nYears;
                idx = findNode(yTemp, nodeCntMax + i);

                //check max
                if (maxPopes < (pMid[i].popNum - pRoot[idx].popNum))
                {
                    maxPopes = (pMid[i].popNum - pRoot[idx].popNum);
                    startYear = pRoot[idx+1].YLEx;
                    endYear = pMid[i].YLEx;
                }
            }

        printf("%d %d %d\n", maxPopes, startYear, endYear);
    }

    return 0;
}

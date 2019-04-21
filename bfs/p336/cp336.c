/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/19
Problem: uva p336
Algo   : BFS

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_NODES               30

#define WHITE                   0
#define GRAY                    1
#define BLACK                   2

typedef struct NODE {
    int id;
    int ticks;
    int color;
    int cntLink;
    struct NODE *links[MAX_NODES];
}tNODE;

tNODE nodes[MAX_NODES];
tNODE *que[MAX_NODES];

tNODE **pQR, **pQW;

tNODE *pRoot;

void initQ()
{
    int i;

    //reset connections
    for (i = 0; i < MAX_NODES; i++)
    {
        nodes[i].ticks = -1;
        nodes[i].color = WHITE;
    }

    pQR = &que[0];
    pQW = &que[0];
}

void pushQ(int ticks, tNODE *pEle)
{
    if (pEle->color == WHITE)
    {
        pEle->color = GRAY;
        pEle->ticks = ticks;
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

tNODE *searchNode(int id)
{
    tNODE *pRes = 0;
    int i = 0;

    while (nodes[i].id != -1)
    {
        if (nodes[i].id == id)
        {
            break;
        }
        i++;
    }
    nodes[i].id = id;

    pRes = &nodes[i];

    return pRes;
}

tNODE *searchNodeForPush(int id)
{
    tNODE *pRes = 0;
    int i = 0;

    while (nodes[i].id != -1)
    {
        if (nodes[i].id == id)
        {
            pRes = &nodes[i];
            break;
        }
        i++;
    }

    return pRes;
}

int main()
{
    int i, j;
    int done = 0;
    int nodeCnt, node1, node2;
    int NC;
    int curNodeCnt;
    tNODE *pT, *pT1, *pT2;
    int temp;
    int nodeNum;
    int unReachNodes;
    int caseID = 1;

#ifndef ONLINE_JUDGE
    freopen("input_p336.txt", "r", stdin);
#endif

    while (1)
    {
        //reset connections
        for (i = 0; i < MAX_NODES; i++)
        {
            nodes[i].id = -1;
            nodes[i].cntLink = 0;
        }

        curNodeCnt = 0;

        scanf("%d", &NC);

        if (NC == 0)
            break;

        //read connections
        for (i = 0; i < NC; i++)
        {
            scanf("%d", &node1);
            scanf("%d", &node2);

            //register first node
            pT = searchNode(node1);
            pT->links[pT->cntLink] = searchNode(node2);
            pT->cntLink++;

            //register second node
            pT = searchNode(node2);
            pT->links[pT->cntLink] = searchNode(node1);
            pT->cntLink++;
        }

        while (1)
        {

            int nID, tCnt;

            scanf("%d", &nID);
            scanf("%d", &tCnt);

            if ((nID == 0) && (tCnt == 0))
            {
                break;
            }

            initQ();
            if (searchNodeForPush(nID))
                pushQ(tCnt, searchNodeForPush(nID));
            while ((pT = popQ()) != 0)
            {
                if (pT->ticks > 0)
                {
                    for (j = 0; j < pT->cntLink; j++)
                    {
                        pushQ(pT->ticks - 1, searchNodeForPush(pT->links[j]->id));
                    }
                }
            }

            //count nodes not reachable
            unReachNodes = 0;
            i = 0;
            while ((nodes[i].id != -1) && (i < MAX_NODES))
            {
                if (nodes[i].ticks < 0)
                {
                    unReachNodes++;
                }
                i++;
            }

            printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", caseID, unReachNodes, nID, tCnt);
            caseID++;
        }
    }

    return 0;
}

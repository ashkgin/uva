/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/19
Problem: uva p336
Algo   : BFS + HASH Table

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_NODES               100

#define WHITE                   -1
#define GRAY                    1
#define PRIME                   31

int curNodeCnt;

typedef struct NODE {
    int id;
    int color;
    int cntLink;
    struct NODE *links[MAX_NODES];
    struct NODE *hashNext;
}tNODE;

tNODE nodes[MAX_NODES];
tNODE *que[MAX_NODES];

tNODE *searchQue[PRIME];

tNODE **pQR, **pQW;

static void initQ()
{
    int i;

    //reset connections
    for (i = 0; i < curNodeCnt; i++)
    {
        nodes[i].color = WHITE;
    }

    pQR = &que[0];
    pQW = &que[0];
}

static void pushQ(int ticks, tNODE *pEle)
{
        pEle->color = ticks;
        *pQW = pEle;
        pQW++;
}

static tNODE *popQ()
{
    tNODE *pRes = 0;

    if (pQR < pQW)
    {
        pRes = *pQR;
        pQR++;
    }

    return pRes;
}

static tNODE *searchNode(int id)
{
    tNODE *pRes = 0;
    tNODE *pT;
    int rem;

    rem = id % PRIME;

    if (searchQue[rem] == 0)
    {
        pT = &nodes[curNodeCnt++];
        pT->id = id;
        pT->cntLink = 0;
        pT->hashNext = 0;
        searchQue[rem] = pT;
        return pT;
    }
    else
    {
        pT = searchQue[rem];
        while (pT->id != id)
        {
            if (pT->hashNext == 0)
            {
                pT->hashNext = &nodes[curNodeCnt++];
                pT = pT->hashNext;
                pT->id = id;
                pT->cntLink = 0;
                pT->hashNext = 0;
                return pT;
            }
            else
            {
                pT = pT->hashNext;
            }
        }

        return pT;

    }


    return pRes;
}

static tNODE *searchNodeForPush(int id)
{
    tNODE *pRes = 0;
    tNODE *pT;
    int rem;

    rem = id % PRIME;

        pT = searchQue[rem];
        while (pT && pT->id != id)
        {
            if (pT->hashNext == 0)
            {
                return pRes;
            }
            else
            {
                pT = pT->hashNext;
            }
        }

        return pT;
}

tNODE *pRoot;

int main()
{
    int i, j;
    int nodeCnt, node1, node2;
    int NC;
    tNODE *pT, *pT1, *pT2;
    int nodeNum;
    int unReachNodes;
    int caseID = 1;
    int reachNodes;
    int rem;
#ifndef ONLINE_JUDGE
    int setCnt;
#endif

#ifndef ONLINE_JUDGE
    freopen("input_p336.txt", "r", stdin);
#endif

#ifndef ONLINE_JUDGE
    setCnt = 0;
#endif

    pRoot = &nodes[0];
    while (1)
    {

        //reset connections
        curNodeCnt = 0;

        for (i = 0; i < PRIME; i++)
        {
            searchQue[i] = 0;
        }

        scanf("%d", &NC);

        if (NC == 0)
            break;

        scanf("%d", &node1);
        rem = node1 % PRIME;
        pT1 = &nodes[0];
        pT1->id = node1;
        pT1->cntLink = 0;
        pT1->hashNext = 0;
        curNodeCnt++;
        searchQue[rem] = pT1;

        scanf("%d", &node2);

        if (node1 != node2)
        {
            pT2 = &nodes[1];
            pT2->id = node2;
            pT2->hashNext = 0;
            curNodeCnt++;

            rem = node2 % PRIME;
            searchQue[rem] = pT2;

            pT1->links[0] = pT2;
            pT1->cntLink = 1;

            //register second node
            pT2->links[0] = pT1;
            pT2->cntLink = 1;
        }

        //read connections
        for (i = 1; i < NC; i++)
        {
            scanf("%d", &node1);
            scanf("%d", &node2);

            if (node1 != node2)
            {
                //register first node
                pT1 = searchNode(node1);
                pT2 = searchNode(node2);
                pT1->links[pT1->cntLink] = pT2;
                pT1->cntLink++;

                //register second node
                pT2->links[pT2->cntLink] = pT1;
                pT2->cntLink++;
            }
            else
            {
                pT1 = searchNode(node1);
            }
        }

        while (1)
        {
            int nID, tCnt;

            reachNodes = 0;

            scanf("%d", &nID);
            scanf("%d", &tCnt);

            if ((nID == 0) && (tCnt == 0))
            {
                break;
            }

            initQ();
            if (pT = searchNodeForPush(nID))
            {
                reachNodes++;
                pT->color = tCnt;
                *pQW = pT;
                pQW++;
            }
            while (pT = popQ())
            {
                if (pT->color > 0)
                {
                    for (j = 0; j < pT->cntLink; j++)
                    {
                        pT1 = searchNodeForPush(pT->links[j]->id);
                        if (pT1->color == WHITE)
                        {
                            reachNodes++;
                            pT1->color = pT->color - 1;
                            *pQW = pT1;
                            pQW++;
                        }
                    }
                }
                else
                {
                    break;
                }
            }

            //count nodes not reachable
            unReachNodes = curNodeCnt - reachNodes;

            printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", caseID, unReachNodes, nID, tCnt);
            caseID++;
        }
#ifndef ONLINE_JUDGE
        setCnt++;
#endif
    }

    return 0;
}

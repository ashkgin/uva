/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/19
Problem: uva p383
Algo   : BFS

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_NODES				100         //with 30 submission is not accepted at uva

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
    int i, j, m;
    int done = 0;
    int nodeCnt, node1, node2;
    int NC, numHouseM, numLegN, numReqP;
    int curNodeCnt;
    tNODE *pT, *pT1, *pT2;
    int temp;
    int nodeNum;
    int unReachNodes;
    int caseID = 1;
    int legCnt;

#ifndef ONLINE_JUDGE
    freopen("input_p383.txt", "r", stdin);
#endif

    printf("SHIPPING ROUTES OUTPUT\n\n");


    curNodeCnt = 0;

    scanf("%d", &NC);       //number of cases

    //read data sets
    for (i = 0; i < NC; i++)
    {
        printf("DATA SET  %d\n\n", i+1);

        scanf("%d", &numHouseM);
        scanf("%d", &numLegN);
        scanf("%d", &numReqP);

        //reset connections
        for (j = 0; j < MAX_NODES; j++)
        {
            nodes[j].id = -1;
            nodes[j].cntLink = 0;
        }

        //read houses
        for (m = 0; m < numHouseM; m++)
        {
            char hName[3];
            int node;
            scanf("%s", &hName);

            node = (((int)hName[0]) << 8) + ((int)hName[1]);

            //register node
            pT = searchNode(node);
        }

        //read legs
        for (m = 0; m < numLegN; m++)
        {
            char hName1[3], hName2[3];
            int node1, node2;
            scanf("%s", &hName1);
            node1 = (((int)hName1[0]) << 8) + ((int)hName1[1]);

            scanf("%s", &hName2);
            node2 = (((int)hName2[0]) << 8) + ((int)hName2[1]);

            //register node
            pT1 = searchNodeForPush(node1);
            pT2 = searchNodeForPush(node2);

            //register first node
            pT1->links[pT1->cntLink] = pT2;
            pT1->cntLink++;

            //register second node
            pT2->links[pT2->cntLink] = pT1;
            pT2->cntLink++;
        }

        for (m = 0; m < numReqP; m++)
        {
            char hName1[3], hName2[3];
            int node1, node2, size;

            scanf("%d", &size);

            scanf("%s", &hName1);
            node1 = (((int)hName1[0]) << 8) + ((int)hName1[1]);

            scanf("%s", &hName2);
            node2 = (((int)hName2[0]) << 8) + ((int)hName2[1]);

            legCnt = 0;
            initQ();
            if (searchNodeForPush(node1))
                pushQ(legCnt, searchNodeForPush(node1));

            while ((pT = popQ()) != 0)
            {
                if (pT->id == node2)
                {
                    break;
                }
                for (j = 0; j < pT->cntLink; j++)
                {
                    pushQ(pT->ticks + 1, searchNodeForPush(pT->links[j]->id));
                }

            }

            if (pT == 0)
            {
                printf("NO SHIPMENT POSSIBLE\n");
            }
            else
            {
                printf("$%d\n", size*pT->ticks * 100);
            }
        }
        printf("\n");
    }
    printf("END OF OUTPUT\n");
    return 0;
}


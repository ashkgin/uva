/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/26
Problem: uva p12356
Algo   : Linked List

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES               100000
#define MAX_PASSWORD_SIZE       10
#define PRIME                   1031

typedef struct NODE {
    int id;
    struct NODE *pL;
    struct NODE *pR;
}tNODE;

tNODE nodes[MAX_NODES];

void removeNodes(int s1, int s2, int *res)
{
    tNODE* pL, *pLL, *pLR;
    tNODE* pR, *pRL, *pRR;

    pL = &nodes[s1];
    pR = &nodes[s2];

    if (pL->pL != 0)
    {
        res[0] = pL->pL->id;
    }
    else
    {
        res[0] = -1;
    }

    if (pR->pR != 0)
    {
        res[1] = pR->pR->id;
    }
    else
    {
        res[1] = -1;
    }

    pLL = pL->pL;
    pLR = pL->pR;
    pRL = pR->pL;
    pRR = pR->pR;

    //remove pL
    if (pLL != 0)
    {
        pLL->pR = pRR;
    }

    if (pRR != 0)
    {
        pRR->pL = pLL;
    }
}

int main()
{
    int i;
    int sMen, rCnt;
    int s1, s2;
    int res[2];

#ifndef ONLINE_JUDGE
    freopen("input_p12356.txt", "r", stdin);
#endif

    while (1)
    {
        scanf("%d %d", &sMen, &rCnt);

        if ((sMen == 0) && (rCnt==0))
            break;

        //init list
        i = 1;
        nodes[i].id = i;
        nodes[i].pL = 0;
        if(sMen > i)
            nodes[i].pR = &nodes[i+1];

        for (i = 2; i <= sMen-1; i++)
        {
            nodes[i].id = i;
            nodes[i].pL = &nodes[i - 1];
            nodes[i].pR = &nodes[i + 1];
        }

        nodes[i].id = i;
        nodes[i].pL = &nodes[i - 1];
        nodes[i].pR = 0;

        for (i = 0; i < rCnt; i++)
        {
            scanf("%d %d", &s1, &s2);
            removeNodes(s1, s2, res);

            if (res[0] == -1)
            {
                printf("%c ", '*');
            }
            else
            {
                printf("%d ", res[0]);
            }

            if (res[1] == -1)
            {
                printf("%c\n", '*');
            }
            else
            {
                printf("%d\n", res[1]);
            }
        }

        printf("-\n");

    }

    return 0;
}

/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/24
Problem: uva p11849
Algo   : HASH Table

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRIME                   1000003
#define N_MAX                   1000000
#define M_MAX                   1000000


int curNodeCnt;

typedef struct NODE {
    int id;
    struct NODE *hashNext;
}tNODE;

tNODE nodes[N_MAX];
tNODE *searchQue[PRIME];

int main()
{
    int i, j, NNum, MNum, catNum;
    int NC;
    tNODE *pT;
    int caseID = 1;
    int rem;
    int commonCat;

#ifndef ONLINE_JUDGE
    freopen("input_p11849.txt", "r", stdin);
#endif

    while (1)
    {
        scanf("%d", &NNum);
        scanf("%d", &MNum);

        if (NNum == 0  && MNum == 0)
            break;

        //reset connections
        curNodeCnt = 0;
        commonCat = 0;

        for (i = 0; i < PRIME; i++)
        {
            searchQue[i] = 0;
        }

        for (i = 0; i < NNum; i++)
        {
            scanf("%d", &catNum);
            rem = catNum % PRIME;

            if (searchQue[rem] == 0)
            {
                pT = &nodes[curNodeCnt++];
                pT->id = catNum;
                pT->hashNext = 0;
                searchQue[rem] = pT;
            }
            else
            {
                pT = searchQue[rem];
                while (pT != 0)
                {
                    if (pT->hashNext == 0)
                    {
                        pT->hashNext = &nodes[curNodeCnt++];
                        pT = pT->hashNext;
                        pT->id = catNum;
                        pT->hashNext = 0;
                        break;
                    }
                    else
                    {
                        pT = pT->hashNext;
                    }
                }
            }
        }

        for (i = 0; i < MNum; i++)
        {
            scanf("%d", &catNum);
            rem = catNum % PRIME;

            if (searchQue[rem] != 0)
            {
                pT = searchQue[rem];
                while (pT != 0)
                {
                    if (pT->id == catNum)
                    {
                        commonCat++;
                        break;
                    }
                    else
                    {
                        if (pT->hashNext == 0)
                        {
                            break;
                        }
                        else
                        {
                            pT = pT->hashNext;
                        }
                    }
                }
            }
        }

        printf("%d\n", commonCat);
        caseID++;
    }

    return 0;
}

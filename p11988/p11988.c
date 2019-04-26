/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/26
Problem: uva p11988
Algo   : Linked List

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES               100000

typedef struct NODE {
    char ch;
    struct NODE *pL;
    struct NODE *pR;
}tNODE;

tNODE nodes[MAX_NODES];
int curNodeCnt;

void insertNode(tNODE** pCur, tNODE** pHome, tNODE** pEnd, char cTemp)
{
    if (curNodeCnt == 0)
    {
        nodes[curNodeCnt].ch = cTemp;
        nodes[curNodeCnt].pR = 0;
        nodes[curNodeCnt].pL = 0;
        *pCur = &nodes[curNodeCnt];
        *pHome = &nodes[curNodeCnt];
        *pEnd = &nodes[curNodeCnt];
        curNodeCnt++;
    }
    else if (*pCur == *pEnd)
    {
        nodes[curNodeCnt].ch = cTemp;
        nodes[curNodeCnt].pR = 0;
        nodes[curNodeCnt].pL = *pCur;
        (*pCur)->pR = &nodes[curNodeCnt];
        *pCur = &nodes[curNodeCnt];
        *pEnd = *pCur;
        curNodeCnt++;
    }
    else if (*pCur == 0)
    {
        nodes[curNodeCnt].ch = cTemp;
        nodes[curNodeCnt].pR = *pHome;
        nodes[curNodeCnt].pL = 0;
        *pCur = &nodes[curNodeCnt];
        *pHome = *pCur;
        curNodeCnt++;
    }
    else
    {
        nodes[curNodeCnt].ch = cTemp;
        nodes[curNodeCnt].pR = (*pCur)->pR;
        nodes[curNodeCnt].pL = *pCur;
        (*pCur)->pR = &nodes[curNodeCnt];
        *pCur = &nodes[curNodeCnt];
        curNodeCnt++;
    }
}

int main()
{
    int i, res;
    char str[MAX_NODES], cTemp;
    int strSize;
    tNODE *pCur, *pHome, *pEnd;


#ifndef ONLINE_JUDGE
    freopen("input_p11988.txt", "r", stdin);
#endif

    while (1)
    {
        curNodeCnt = 0;
        res = scanf("%s", &str);

        if (res < 0)
            break;


        //init list

        pCur = 0;
        pHome = 0;
        pEnd = 0;

       strSize = 0;
        while ((cTemp=str[strSize]) != '\0')
        {
            if (cTemp == '[')
            {
                pCur = 0;
            }
            else if (cTemp == ']')
            {
                pCur = pEnd;
            }
            else
            {
                insertNode(&pCur, &pHome, &pEnd, cTemp);
            }
            strSize++;
        }

        for (i = 0; i < curNodeCnt; i++)
        {
            printf("%c", pHome->ch);
            pHome = pHome->pR;
        }

        printf("\n");

    }

    return 0;
}

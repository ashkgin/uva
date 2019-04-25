/******************************************************************

Author : Ashwani Kumar Gupta
Date   : 2019/04/25
Problem: uva p902
Algo   : HASH Table

******************************************************************/

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_STRING_SIZE         1024
#define MAX_PASSWORD_SIZE       10
#define PRIME                   1031

int curNodeCnt;

typedef struct NODE {
    char *pWord;
    int cnt;
    struct NODE *hashNext;
}tNODE;

tNODE nodes[MAX_STRING_SIZE];
tNODE *searchQue[PRIME];
int curNodeCnt;

unsigned int hashf(unsigned char *str, int size)
{
    unsigned int hash = 5381;
    int c, i;

    for (i = 0; i < size; i++)
    {
        c = *str++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

int myStrCmp(unsigned char *str1, unsigned char *str2, int size)
{
    int res=1;        //str match
    int i;

    for (i = 0; i < size; i++)
    {
        if (str1[i] != str2[i])
        {
            res = 0;
            break;
        }
    }
    return res;
}

int main()
{
    int i;
    tNODE *pT;
    int caseID = 1;
    int rem;
    int pwSize;
    unsigned char str[MAX_STRING_SIZE];
    int res;
    int strSize;
    unsigned int hashVal;
    int maxCnt;
    unsigned char *pMax;

#ifndef ONLINE_JUDGE
    freopen("input_p902.txt", "r", stdin);
#endif

    while (1)
    {
        maxCnt = 1;
        res=scanf("%d", &pwSize);

        if (res < 0)
            break;

        scanf("%s", &str);

        strSize = 0;
        while (str[strSize] != '\0')
        {
            strSize++;
        }

        //reset connections
        curNodeCnt = 0;

        for (i = 0; i < PRIME; i++)
        {
            searchQue[i] = 0;
        }

        for (i = 0; i <= strSize-pwSize; i++)
        {
                hashVal = hashf(&str[i], pwSize);
                rem = hashVal % PRIME;

                if (searchQue[rem] == 0)
                {
                    pT = &nodes[curNodeCnt++];
                    pT->pWord = &str[i];
                    pT->hashNext = 0;
                    searchQue[rem] = pT;
                    pT->cnt=1;
                }
                else
                {
                    pT = searchQue[rem];
                    while (pT != 0)
                    {
                        if (myStrCmp(pT->pWord, &str[i], pwSize))
                        {
                            pT->cnt++;
                            if (pT->cnt > maxCnt)
                            {
                                pMax = &str[i];
                                maxCnt = pT->cnt;
                            }
                            break;
                        }
                        else
                        {
                            if (pT->hashNext == 0)
                            {
                                pT->hashNext = &nodes[curNodeCnt++];
                                pT = &nodes[curNodeCnt++];
                                pT->pWord = &str[i];
                                pT->hashNext = 0;
                                searchQue[rem] = pT;
                                pT->cnt = 1;
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
        for (i = 0; i < pwSize; i++)
        {
            printf("%c", pMax[i]);
        }
        printf("\n");
        caseID++;
    }

    return 0;
}

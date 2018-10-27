/*
 *  [PRI] Project 2
 *  Generates magic squares.
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

void printTab(int n, int *tab)
{
    for (int i = 0; i < n * n; ++i)
    {
        printf("%d ", tab[i]);
        if ((i + 1) % n == 0)
        {
            printf("\n");
        }
    }

    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool isMagic(int n, int *tab)
{
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int sum4 = 0;

    for (int i = 0; i < n; ++i)
    {
        sum1 += tab[(n + 1) * i];
        sum2 += tab[(n - 1) * (i + 1)];
 
        for (int j = 0; j < n; ++j)
        {
            sum3 += tab[i*n + j];
            sum4 += tab[j*n + i];

            if ((j + 1) % n == 0)
            {
                if (sum3 == n*(n*n + 1)/2 && sum4 == n*(n*n + 1)/2)
                {
                    sum3 = 0;
                    sum4 = 0;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    
    if (sum1 != n*(n*n + 1)/2 || sum2 != n*(n*n + 1)/2)
    {
        return false;
    }

    return true;
}

void func(int n, int *tab, int index, int *counter)
{
    if (n != 3 && *counter == 5)
    {
        return;
    }

    if (index >= n * n)
    {
        if (isMagic(n, tab))
        {
            printTab(n, tab);
            ++(*counter);
        }
    }
    else
    {
        for (int i = index; i < n * n; ++i)
        {
            swap(tab + i, tab + index);
            func(n, tab, index + 1, counter);
            swap(tab + i, tab + index);
        }
    }
}

int main()
{
    printf("3x3 magic squares:\n");
    int tab3x3[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    int counter3x3 = 0;
    func(3, tab3x3, 0, &counter3x3);

    printf("4x4 magic squares:\n");
    int tab4x4[] = {
        1, 15, 14, 4,
        12, 6, 7, 9,
        8, 10, 11, 5,
        13, 3, 2, 16
    };
    int counter4x4 = 0;
    func(4, tab4x4, 0, &counter4x4);

    printf("5x5 magic squares:\n");
    int tab5x5[] = {
        3, 7, 14, 16, 25,
        11, 20, 23, 2, 9,
        22, 4, 6, 15, 18,
        10, 13, 17, 24, 1,
        19, 21, 5, 8, 12
    };
    int counter5x5 = 0;
    func(5, tab5x5, 0, &counter5x5);

    return 0;
}


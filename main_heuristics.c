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
    int sumRow = 0;
    int sumCol = 0;

    for (int i = 0; i < n; ++i)
    {
        sum1 += tab[(n + 1) * i];
        sum2 += tab[(n - 1) * (i + 1)];
 
        for (int j = 0; j < n; ++j)
        {
            sumRow += tab[i*n + j];
            sumCol += tab[j*n + i];

            if ((j + 1) % n == 0)
            {
                if (sumRow == n*(n*n + 1)/2 && sumCol == n*(n*n + 1)/2)
                {
                    sumRow = 0;
                    sumCol = 0;
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

void permutate(int size, int *tab, int index, void (*callback)(int, int*, int*), int *data)
{
    if (index == size)
    {
        callback(size, tab, data);
    }
    else
    {
        for (int i = index; i < size; ++i)
        {
            swap(tab + i, tab + index);
            permutate(size, tab, index + 1, callback, data);
            swap(tab + i, tab + index);
        }
    }
}

void createSquare(int size, int *x, int *X)
{
    int magic[] = {
        X[0] + x[0], X[1] + x[1], X[2] + x[2], X[3] + x[3],
        X[2] + x[3], X[3] + x[2], X[0] + x[1], X[1] + x[0],
        X[3] + x[1], X[2] + x[0], X[1] + x[3], X[0] + x[2],
        X[1] + x[2], X[0] + x[3], X[3] + x[0], X[2] + x[1]
    };

    printTab(size, magic);
}

void innerPerm(int size, int *tab, int *data)
{
    permutate(size, data, 0, createSquare, tab);
}

// TODO: 3x3, 4x4, 5x5, maybe 6x6, code cleanup

int main()
{
    int X[] = { 0, 4, 8, 12 };
    int x[] = { 1, 2, 3, 4 };

    permutate(4, X, 0, innerPerm, x);

    return 0;
}


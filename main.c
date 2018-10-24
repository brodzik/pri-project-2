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
    int sum = 0;
    for (int i = 0; i < n * n; ++i)
    {
        sum += tab[i];

        if ((i + 1) % n == 0)
        {
            if (sum == n*(n*n + 1)/2)
            {
                sum = 0;
            }
            else
            {
                return false;
            }
        }
    }

    sum = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            sum += tab[j*n + i];

            if ((j + 1) % n == 0)
            {
                if (sum == n*(n*n + 1)/2)
                {
                    sum = 0;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < n; ++i)
    {
        sum1 += tab[(n + 1) * i];
        sum2 += tab[(n - 1) * (i + 1)];
    }

    if (sum1 != n*(n*n + 1)/2 || sum2 != n*(n*n + 1)/2)
    {
        return false;
    }

    return true;
}

void func(int n, int *tab, int index, int *counter)
{
    if (*counter == 5)
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
    int n;
    scanf("%d", &n);

    int *tab = malloc(n*n*sizeof(int));

    for (int i = 0; i < n*n; ++i)
    {
        tab[i] = i + 1;
    }

    int counter = 0;
    func(n, tab, 0, &counter);
    printf("Found: %d\n", counter);

    free(tab);

    return 0;
}

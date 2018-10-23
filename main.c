/*
 *  [PRI] Project 2
 *  Generates magic squares.
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_N 10

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
}

bool isMagicSquare(int n, int *tab)
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

void func(int n, int *tab, bool *used, int index)
{
    if (index == n * n)
    {
        if (isMagicSquare(n, tab))
        {
            printTab(n, tab);
            printf("\n");
        }
    }
    else
    {
        for (int i = 1; i <= n * n; ++i)
        {
            if (!used[i])
            {
                used[i] = true;
                tab[index] = i;

                func(n, tab, used, index + 1);

                used[i] = false;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int tab[MAX_N] = { 0 };
    bool used[MAX_N * MAX_N + 1] = { false };

    func(n, tab, used, 0);

    return 0;
}

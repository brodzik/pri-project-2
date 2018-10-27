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

// Swaps two values
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Prints a square matrix
void printSquare(int n, int *tab)
{
    for (int i = 0; i < n*n; ++i)
    {
        printf("%d ", tab[i]);

        if ((i + 1) % n == 0)
        {
            printf("\n");
        }
    }

    printf("\n");
}

// Checks if the square matrix is a magic square
bool isMagicSquare(int n, int *tab)
{
    // Source: https://en.wikipedia.org/wiki/Magic_constant
    int magicConst = n*(n*n + 1)/2;

    int sumDiag1 = 0;
    int sumDiag2 = 0;

    // Calculate diagonal sums
    for (int i = 0; i < n; ++i)
    {
        sumDiag1 += tab[(n + 1) * i];
        sumDiag2 += tab[(n - 1) * (i + 1)];
    }

    // Check diagonal sums
    if (sumDiag1 != magicConst || sumDiag2 != magicConst)
    {
        return false;
    }

    int sumRow = 0;
    int sumCol = 0;

    // Calculate row/column sums
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            sumRow += tab[i*n + j];
            sumCol += tab[j*n + i];

            // For each row/column
            if ((j + 1) % n == 0)
            {
                // Check row/column sums
                if (sumRow == magicConst && sumCol == magicConst)
                {
                    // Reset the sums
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

    return true;
}

// Generates all possible permutations of a square matrix
void bruteForcePermutations(int n, int *tab, int index)
{
    if (index == n*n)
    {
        if (isMagicSquare(n, tab))
        {
            printSquare(n, tab);
        }
    }
    else
    {
        for (int i = index; i < n*n; ++i)
        {
            swap(tab + i, tab + index);
            bruteForcePermutations(n, tab, index + 1);
            swap(tab + i, tab + index);
        }
    }
}

int main()
{
    // n = 3
    int tab3x3[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    bruteForcePermutations(3, tab3x3, 0);

    return 0;
}


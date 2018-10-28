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
        printf("%d\t", tab[i]);

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
// Source: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
void permutate(int n, int *tab, int index)
{
    // Finish recursion
    if (index == n*n)
    {
        if (isMagicSquare(n, tab))
        {
            printSquare(n, tab);
        }
    }
    // Continue recursion
    else
    {
        // Permutate non-fixed characters
        for (int i = index; i < n*n; ++i)
        {
            swap(tab + i, tab + index);
            permutate(n, tab, index + 1);
            swap(tab + i, tab + index);
        }
    }
}

// Generates all permutations of 'tab' and calls 'callback' after each permutation,
// 'data' variable is used to pass extra information to the 'callback' function,
// 'callback' arguments: size, tab, data, counter
void advancedPermutate(int size, int *tab, int *data, int index, void (*callback)(int, int*, int*, int*), int *counter)
{
    // Limit magic square output
    if (*counter == 5)
    {
        return;
    }

    // Finish recursion
    if (index == size)
    {
        callback(size, tab, data, counter);
    }
    // Continue recursion
    else
    {
        // Permutate non-fixed characters
        for (int i = index; i < size; ++i)
        {
            swap(tab + i, tab + index);
            advancedPermutate(size, tab, data, index + 1, callback, counter);
            swap(tab + i, tab + index);
        }
    }
}

// Creates a 4x4 magic square
// Source: http://www.magic-squares.net/pandiag5.htm
void create4x4(int size, int *x, int *X, int *counter)
{
    int magic[] = {
        X[0] + x[0], X[1] + x[1], X[2] + x[2], X[3] + x[3],
        X[2] + x[3], X[3] + x[2], X[0] + x[1], X[1] + x[0],
        X[3] + x[1], X[2] + x[0], X[1] + x[3], X[0] + x[2],
        X[1] + x[2], X[0] + x[3], X[3] + x[0], X[2] + x[1]
    };

    printSquare(size, magic);

    ++(*counter);
}

// Creates a 5x5 magic square
// Source: http://www.magic-squares.net/pandiag5.htm
void create5x5(int size, int *x, int *X, int *counter)
{
    int magic[] = {
        X[0] + x[0], X[1] + x[1], X[2] + x[2], X[3] + x[3], X[4] + x[4],
        X[2] + x[3], X[3] + x[4], X[4] + x[0], X[0] + x[1], X[1] + x[2],
        X[4] + x[1], X[0] + x[2], X[1] + x[3], X[2] + x[4], X[3] + x[0],
        X[1] + x[4], X[2] + x[0], X[3] + x[1], X[4] + x[2], X[0] + x[3],
        X[3] + x[2], X[4] + x[3], X[0] + x[4], X[1] + x[0], X[2] + x[1]
    };

    printSquare(size, magic);

    ++(*counter);
}

// Used as a 'callback' function for 'advancedPermutate' to permutate 'data'
void innerPermutation(int size, int *tab, int *data, int *counter)
{
    if (size == 4)
    {
        advancedPermutate(size, data, tab, 0, create4x4, counter);
    }
    else if (size == 5)
    {
        advancedPermutate(size, data, tab, 0, create5x5, counter);
    }
    else
    {
        printf("Size must be equal to 4 or 5.\n");
        exit(-1);
    }
}

int main()
{
    printf("---------- n = 3 ----------\n\n");

    int tab3x3[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    permutate(3, tab3x3, 0);

    printf("---------- n = 4 ----------\n\n");

    int tab4x4_1[] = { 0, 4, 8, 12 };
    int tab4x4_2[] = { 1, 2, 3, 4 };
    int counter4x4 = 0;

    advancedPermutate(4, tab4x4_1, tab4x4_2, 0, innerPermutation, &counter4x4);

    printf("---------- n = 5 ----------\n\n");

    int tab5x5_1[] = { 0, 5, 10, 15, 20 };
    int tab5x5_2[] = { 1, 2, 3, 4, 5 };
    int counter5x5 = 0;

    advancedPermutate(5, tab5x5_1, tab5x5_2, 0, innerPermutation, &counter5x5);

    return 0;
}


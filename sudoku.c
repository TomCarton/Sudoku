// Sudoku.c
// --------
//
// Sudoku solver
//
// Created by Thomas CARTON
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <locale.h>
#include <wchar.h>


#define S L"╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n"
#define C L"║ x │ x │ x ║ x │ x │ x ║ x │ x │ x ║\n"
#define L L"╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n"
#define M L"╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣\n"
#define E L"╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝\n"

#define Grid S C L C L C M C L C L C M C L C L C E

void printGrid(int *t)
{
    for(int i = 0; i < 38 * 38 / 2; ++i)
    {
        wprintf(L"%lc", Grid[i] == 'x' ? *t++ ? '0' + t[-1] : ' ' : Grid[i]);
    }
}


bool isValid(int *T, int x, int y, int n)
{
    int sx = (x / 3) * 3;
    int sy = (y / 3) * 3;

    int x1 = (x + 2) % 3;
    int x2 = (x + 4) % 3;
    int y1 = (y + 2) % 3;
    int y2 = (y + 4) % 3;

    if (T[9 * (sy + y1) + (sx + x1)] == n) return false;
    if (T[9 * (sy + y2) + (sx + x1)] == n) return false;
    if (T[9 * (sy + y1) + (sx + x2)] == n) return false;
    if (T[9 * (sy + y2) + (sx + x2)] == n) return false;

    for (unsigned int i = 0; i < 9; ++i)
    {
        if (T[9 * y + i] == n) return false;
        if (T[9 * i + x] == n) return false;
    }

    return true;
}

bool findEmpty(int *T, int *x, int *y)
{
    for (*y = 0; *y < 9; (*y)++)
    {
        for (*x = 0; *x < 9; (*x)++)
        {
            if (T[9 * *y + *x] == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool solve(int *T)
{
    int x, y;

    if (findEmpty(T, &x, &y))
    {
        for (int n = 1; n <= 9; ++n)
        {
            if (isValid(T, x, y, n))
            {
                T[9 * y + x] = n;

                if (solve(T))
                {
                    return true;
                }

                T[9 * y + x] = 0;
            }
        }

        return false;
    }

    return true;
}

int main()
{
    int easy[] =
    {
        8, 4, 1,  0, 0, 0,  5, 0, 2,
        0, 5, 0,  2, 4, 0,  0, 0, 0,
        0, 0, 9,  0, 0, 8,  1, 0, 6,

        4, 0, 0,  0, 3, 6,  7, 9, 0,
        0, 0, 0,  0, 0, 0,  0, 0, 0,
        0, 1, 5,  0, 2, 0,  3, 0, 0,

        0, 0, 0,  8, 9, 2,  4, 0, 0,
        0, 0, 8,  0, 0, 3,  0, 2, 0,
        1, 0, 0,  6, 0, 0,  9, 8, 3,
    };

    int hard[] =
    {
        0, 0, 0,  5, 0, 0,  0, 8, 0,
        7, 0, 0,  4, 8, 0,  0, 3, 0,
        1, 0, 0,  0, 2, 0,  0, 0, 5,

        0, 0, 6,  9, 0, 0,  0, 7, 0,
        8, 0, 3,  0, 0, 0,  5, 0, 9,
        0, 2, 0,  0, 0, 8,  4, 0, 0,

        2, 0, 0,  0, 4, 0,  0, 0, 1,
        0, 3, 0,  0, 6, 7,  0, 0, 8,
        0, 8, 0,  0, 0, 3,  0, 0, 0,
    };


    setlocale(LC_ALL,"");
    printf("\033[H\033[J");

    printGrid(easy);
    solve(easy);
    printGrid(easy);

//    printGrid(hard);
//    solve(hard);
//    printGrid(hard);

    return 0;
}

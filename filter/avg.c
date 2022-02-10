#include <stdio.h>

int tl_corner(int h, int w, int ary[h][w], int avg_ary[h][w]);
int tr_corner(int h, int w, int ary[h][w], int avg_ary[h][w]);
int bl_corner(int h, int w, int ary[h][w], int avg_ary[h][w]);
int br_corner(int h, int w, int ary[h][w], int avg_ary[h][w]);
int top_edge(int h, int w, int ary[h][w], int avg_ary[h][w]);
int bottom_edge(int h, int w, int ary[h][w], int avg_ary[h][w]);
int left_edge(int h, int w, int ary[h][w], int avg_ary[h][w]);
int right_edge(int h, int w, int ary[h][w], int avg_ary[h][w]);
int middle(int h, int w, int ary[h][w], int avg_ary[h][w]);

int main(void)
{

    int height = 4;
    int width = 4;
    int ary[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int avg_ary[4][4] = {0};

    for (int i = 0; i < height; i++)
    {
        printf("row %i: ", i);
        for (int j = 0; j < width; j++)
        {
            printf("%i ", ary[i][j]);
        }
        printf("\n");
    }

    int ans = tl_corner(height, width, ary, avg_ary);
    ans = tr_corner(height, width, ary, avg_ary);
    ans = bl_corner(height, width, ary, avg_ary);
    ans = br_corner(height, width, ary, avg_ary);

    ans = top_edge(height, width, ary, avg_ary);
    ans = bottom_edge(height, width, ary, avg_ary);
    ans = left_edge(height, width, ary, avg_ary);
    ans = right_edge(height, width, ary, avg_ary);

    ans = middle(height, width, ary, avg_ary);

    for (int i = 0; i < height; i++)
    {
        printf("row %i: ", i);
        for (int j = 0; j < width; j++)
        {
            printf("%i ", avg_ary[i][j]);
        }
        printf("\n");
    }

    return 0;
}




int tl_corner(int h, int w, int ary[h][w], int avg_ary[h][w])  // top left [0][0], 4 points
{
    int avg = (ary[0][0] + ary[0][1] + ary[1][0] + ary[1][1]) / 4;
    avg_ary[0][0] = avg;
    printf("Top left corner average: %i\n", avg);

    return 0;
}

int tr_corner(int h, int w, int ary[h][w], int avg_ary[h][w]) // top right [0][width - 1], 4 points
{
    int avg = (ary[0][w - 2] + ary[0][w - 1] + ary[1][w - 2] + ary[1][w - 1]) / 4;
    avg_ary[0][w - 1] = avg;
    printf("Top right corner average: %i\n", avg);

    return 0;
}

int bl_corner(int h, int w, int ary[h][w], int avg_ary[h][w]) // bottom left [height - 1][0], 4 points
{
    int avg = (ary[h - 1][0] + ary[h - 1][1] + ary[h - 2][0] + ary[h - 2][1]) / 4;
    avg_ary[h - 1][0] = avg;
    printf("Bottom left corner average: %i\n", avg);

    return 0;
}

int br_corner(int h, int w, int ary[h][w], int avg_ary[h][w]) // bottom right [height - 1][width - 1], 4 points
{
    int avg = (ary[h - 1][w - 1] + ary[h - 1][w - 2] + ary[h - 2][w - 1] + ary[h - 2][w - 2]) / 4;
    avg_ary[h - 1][w - 1] = avg;
    printf("Bottom right corner average: %i\n", avg);

    return 0;
}

int top_edge(int h, int w, int ary[h][w], int avg_ary[h][w]) // top edge [0][1] -> [0][width - 2], 6 points
{
    int avg;

    for(int i = 0; i < w - 2; i++)
    {
        avg = (ary[0][i] + ary[0][i + 1] + ary[0][i + 2] + ary[1][i] + ary[1][i + 1] + ary[1][i + 2]) / 6;
        avg_ary[0][i + 1] = avg;
        printf("Top edge %i: %i\n", i, avg);
    }

    return 0;
}

int bottom_edge(int h, int w, int ary[h][w], int avg_ary[h][w]) // bottom edge [h-1][1] -> [h-1][width - 2], 6 points
{
    int avg;

    for(int i = 0; i < w - 2; i++)
    {
        avg = (ary[h - 1][i] + ary[h - 1][i + 1] + ary[h - 1][i + 2] + ary[h - 2][i] + ary[h - 2][i + 1] + ary[h - 2][i + 2]) / 6;
        avg_ary[h - 1][i + 1] = avg;
        printf("Bottom edge %i: %i\n", i, avg);
    }

    return 0;
}

int left_edge(int h, int w, int ary[h][w], int avg_ary[h][w]) // left edge [1][0] -> [h-2][0], 6 points
{
    int avg;

    for(int i = 0; i < h - 2; i++)
    {
        avg = (ary[i][0] + ary[i + 1][0] + ary[i + 2][0] + ary[i][1] + ary[i + 1][1] + ary[i + 2][1]) / 6;
        avg_ary[i + 1][0] = avg;
        printf("Left edge %i: %i\n", i, avg);
    }

    return 0;
}

int right_edge(int h, int w, int ary[h][w], int avg_ary[h][w]) // right edge [1][w - 1] -> [h-2][w - 1], 6 points
{
    int avg;

    for(int i = 0; i < h - 2; i++)
    {
        avg = (ary[i][w - 1] + ary[i + 1][w - 1] + ary[i + 2][w - 1] + ary[i][w - 2] + ary[i + 1][w - 2] + ary[i + 2][w - 2]) / 6;
        avg_ary[i + 1][w - 1] = avg;
        printf("Right edge %i: %i\n", i, avg);
    }

    return 0;
}

int middle(int h, int w, int ary[h][w], int avg_ary[h][w]) // middle points [1][1] -> [1][w - 2] ... [h - 2][1] -> [h - 2][w - 2], 9 points
{
    int avg;

    for(int i = 0; i < h - 2; i++)
    {
        for(int j = 0; j < w - 2; j++)
        {
            avg = (ary[i][j] + ary[i][j + 1] + ary[i][j + 2] + \
                  ary[i + 1][j] + ary[i + 1][j + 1] + ary[i + 1][j + 2] + \
                  ary[i + 2][j] + ary[i + 2][j + 1] + ary[i + 2][j + 2]) / 9;
            avg_ary[i + 1][j + 1] = avg;
            printf("Middle point (%i, %i): %i\n", i + 1, j + 1, avg);
        }
    }

    return 0;
}
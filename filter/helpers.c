#include "helpers.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// functions for blurring image
void top_left_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void top_right_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void bottom_left_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void bottom_right_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void top_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void bottom_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void left_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void right_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);
void middle(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]);


// Convert image to grayscale by taking the average of
// the red, green, and blue pixel values
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float pixel;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            pixel = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0;
            image[h][w].rgbtRed = (int) round(pixel);
            image[h][w].rgbtGreen = (int) round(pixel);
            image[h][w].rgbtBlue = (int) round(pixel);
        }
    }
    return;
}

// Convert image to sepia using formula.
// Any value greater than 255 is set to 255
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            sepiaRed = (0.393 * image[h][w].rgbtRed) + (0.769 * image[h][w].rgbtGreen) + (0.189 * image[h][w].rgbtBlue);
            sepiaGreen = (0.349 * image[h][w].rgbtRed) + (0.686 * image[h][w].rgbtGreen) + (0.168 * image[h][w].rgbtBlue);
            sepiaBlue = (0.272 * image[h][w].rgbtRed) + (0.534 * image[h][w].rgbtGreen) + (0.131 * image[h][w].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[h][w].rgbtRed = (int) round(sepiaRed);
            image[h][w].rgbtGreen = (int) round(sepiaGreen);
            image[h][w].rgbtBlue = (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            temp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for image
    RGBTRIPLE(*blurred)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (blurred == NULL)
    {
        fprintf(stderr, "Not enough memory to store image.\n");
        return;
    }

    // corners: average pixel + 3 surrounding pixels (4 points)
    top_left_corner(height, width, image, blurred);
    top_right_corner(height, width, image, blurred);
    bottom_left_corner(height, width, image, blurred);
    bottom_right_corner(height, width, image, blurred);

    // edges: average pixel + 5 surrounding pixels (6 points)
    top_edge(height, width, image, blurred);
    bottom_edge(height, width, image, blurred);
    left_edge(height, width, image, blurred);
    right_edge(height, width, image, blurred);

    // middle: average pixel + 8 surrounding pixels (9 points)
    middle(height, width, image, blurred);

    // write blurred image to original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }

    free(blurred);

    return;
}


// Calculates the average of four points in the top left corner
void top_left_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]) // top left [0][0], 4 points
{
    avg_ary[0][0].rgbtRed = (int) round((ary[0][0].rgbtRed + ary[0][1].rgbtRed + ary[1][0].rgbtRed +
                                         ary[1][1].rgbtRed) / 4.0);

    avg_ary[0][0].rgbtGreen = (int) round((ary[0][0].rgbtGreen + ary[0][1].rgbtGreen + ary[1][0].rgbtGreen +
                                           ary[1][1].rgbtGreen) / 4.0);

    avg_ary[0][0].rgbtBlue = (int) round((ary[0][0].rgbtBlue + ary[0][1].rgbtBlue + ary[1][0].rgbtBlue +
                                          ary[1][1].rgbtBlue) / 4.0);

    return;
}

// Calculates the average of four points in the top right corner
void top_right_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]) // top right [0][width - 1], 4 points
{
    avg_ary[0][w - 1].rgbtRed = (int) round((ary[0][w - 2].rgbtRed + ary[0][w - 1].rgbtRed + ary[1][w - 2].rgbtRed +
                                            ary[1][w - 1].rgbtRed) / 4.0);

    avg_ary[0][w - 1].rgbtGreen = (int) round((ary[0][w - 2].rgbtGreen + ary[0][w - 1].rgbtGreen + ary[1][w - 2].rgbtGreen +
                                  ary[1][w - 1].rgbtGreen) / 4.0);

    avg_ary[0][w - 1].rgbtBlue = (int) round((ary[0][w - 2].rgbtBlue + ary[0][w - 1].rgbtBlue + ary[1][w - 2].rgbtBlue +
                                 ary[1][w - 1].rgbtBlue) / 4.0);

    return;
}

// Calculates the average of four points in the bottom left corner
void bottom_left_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w]) // bottom left [height - 1][0], 4 points
{
    avg_ary[h - 1][0].rgbtRed = (int) round((ary[h - 1][0].rgbtRed + ary[h - 1][1].rgbtRed +
                                            ary[h - 2][0].rgbtRed + ary[h - 2][1].rgbtRed) / 4.0);

    avg_ary[h - 1][0].rgbtGreen = (int) round((ary[h - 1][0].rgbtGreen + ary[h - 1][1].rgbtGreen +
                                  ary[h - 2][0].rgbtGreen + ary[h - 2][1].rgbtGreen) / 4.0);

    avg_ary[h - 1][0].rgbtBlue = (int) round((ary[h - 1][0].rgbtBlue + ary[h - 1][1].rgbtBlue +
                                 ary[h - 2][0].rgbtBlue + ary[h - 2][1].rgbtBlue) / 4.0);

    return;
}

// Calculates the average of four points in the bottom right corner
void bottom_right_corner(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w])
{
    avg_ary[h - 1][w - 1].rgbtRed = (int) round((ary[h - 1][w - 1].rgbtRed + ary[h - 1][w - 2].rgbtRed +
                                    ary[h - 2][w - 1].rgbtRed + ary[h - 2][w - 2].rgbtRed) / 4.0);

    avg_ary[h - 1][w - 1].rgbtGreen = (int) round((ary[h - 1][w - 1].rgbtGreen + ary[h - 1][w - 2].rgbtGreen +
                                      ary[h - 2][w - 1].rgbtGreen + ary[h - 2][w - 2].rgbtGreen) / 4.0);

    avg_ary[h - 1][w - 1].rgbtBlue = (int) round((ary[h - 1][w - 1].rgbtBlue + ary[h - 1][w - 2].rgbtBlue +
                                     ary[h - 2][w - 1].rgbtBlue + ary[h - 2][w - 2].rgbtBlue) / 4.0);

    return;
}

// Calculates the average of 6 points for each point along the top edge
void top_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w])
{
    for (int i = 0; i < w - 2; i++)
    {
        avg_ary[0][i + 1].rgbtRed = (int) round((ary[0][i].rgbtRed + ary[0][i + 1].rgbtRed + ary[0][i + 2].rgbtRed +
                                                ary[1][i].rgbtRed + ary[1][i + 1].rgbtRed + ary[1][i + 2].rgbtRed) / 6.0);

        avg_ary[0][i + 1].rgbtGreen = (int) round((ary[0][i].rgbtGreen + ary[0][i + 1].rgbtGreen + ary[0][i + 2].rgbtGreen +
                                      ary[1][i].rgbtGreen + ary[1][i + 1].rgbtGreen + ary[1][i + 2].rgbtGreen) / 6.0);

        avg_ary[0][i + 1].rgbtBlue = (int) round((ary[0][i].rgbtBlue + ary[0][i + 1].rgbtBlue + ary[0][i + 2].rgbtBlue +
                                     ary[1][i].rgbtBlue + ary[1][i + 1].rgbtBlue + ary[1][i + 2].rgbtBlue) / 6.0);
    }

    return;
}

// Calculates the average of 6 points for each point along the bottom edge
void bottom_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w])
{
    for (int i = 0; i < w - 2; i++)
    {
        avg_ary[h - 1][i + 1].rgbtRed = (int) round((ary[h - 1][i].rgbtRed + ary[h - 1][i + 1].rgbtRed +
                                        ary[h - 1][i + 2].rgbtRed + ary[h - 2][i].rgbtRed + ary[h - 2][i + 1].rgbtRed +
                                        ary[h - 2][i + 2].rgbtRed) / 6.0);

        avg_ary[h - 1][i + 1].rgbtGreen = (int) round((ary[h - 1][i].rgbtGreen + ary[h - 1][i + 1].rgbtGreen +
                                          ary[h - 1][i + 2].rgbtGreen + ary[h - 2][i].rgbtGreen + ary[h - 2][i + 1].rgbtGreen +
                                          ary[h - 2][i + 2].rgbtGreen) / 6.0);

        avg_ary[h - 1][i + 1].rgbtBlue = (int) round((ary[h - 1][i].rgbtBlue + ary[h - 1][i + 1].rgbtBlue +
                                         ary[h - 1][i + 2].rgbtBlue + ary[h - 2][i].rgbtBlue + ary[h - 2][i + 1].rgbtBlue +
                                         ary[h - 2][i + 2].rgbtBlue) / 6.0);
    }

    return;
}

// Calculates the average of 6 points for each point along the left edge
void left_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w])
{
    for (int i = 0; i < h - 2; i++)
    {
        avg_ary[i + 1][0].rgbtRed = (int) round((ary[i][0].rgbtRed + ary[i + 1][0].rgbtRed + ary[i + 2][0].rgbtRed +
                                                ary[i][1].rgbtRed + ary[i + 1][1].rgbtRed + ary[i + 2][1].rgbtRed) / 6.0);

        avg_ary[i + 1][0].rgbtGreen = (int) round((ary[i][0].rgbtGreen + ary[i + 1][0].rgbtGreen + ary[i + 2][0].rgbtGreen +
                                      ary[i][1].rgbtGreen + ary[i + 1][1].rgbtGreen + ary[i + 2][1].rgbtGreen) / 6.0);

        avg_ary[i + 1][0].rgbtBlue = (int) round((ary[i][0].rgbtBlue + ary[i + 1][0].rgbtBlue + ary[i + 2][0].rgbtBlue +
                                     ary[i][1].rgbtBlue + ary[i + 1][1].rgbtBlue + ary[i + 2][1].rgbtBlue) / 6.0);
    }

    return;
}

// Calculates the average of 6 points for each point along the right edge
void right_edge(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w])
{
    for (int i = 0; i < h - 2; i++)
    {
        avg_ary[i + 1][w - 1].rgbtRed = (int) round((ary[i][w - 1].rgbtRed + ary[i + 1][w - 1].rgbtRed +
                                        ary[i + 2][w - 1].rgbtRed + ary[i][w - 2].rgbtRed + ary[i + 1][w - 2].rgbtRed +
                                        ary[i + 2][w - 2].rgbtRed) / 6.0);

        avg_ary[i + 1][w - 1].rgbtGreen = (int) round((ary[i][w - 1].rgbtGreen + ary[i + 1][w - 1].rgbtGreen +
                                          ary[i + 2][w - 1].rgbtGreen + ary[i][w - 2].rgbtGreen + ary[i + 1][w - 2].rgbtGreen +
                                          ary[i + 2][w - 2].rgbtGreen) / 6.0);

        avg_ary[i + 1][w - 1].rgbtBlue = (int) round((ary[i][w - 1].rgbtBlue + ary[i + 1][w - 1].rgbtBlue +
                                         ary[i + 2][w - 1].rgbtBlue + ary[i][w - 2].rgbtBlue + ary[i + 1][w - 2].rgbtBlue +
                                         ary[i + 2][w - 2].rgbtBlue) / 6.0);
    }

    return;
}

// Calculates the average of 9 points for each of the middle points
void middle(int h, int w, RGBTRIPLE ary[h][w], RGBTRIPLE avg_ary[h][w])
{
    for (int i = 0; i < h - 2; i++)
    {
        for (int j = 0; j < w - 2; j++)
        {
            avg_ary[i + 1][j + 1].rgbtRed = (int) round((ary[i][j].rgbtRed + ary[i][j + 1].rgbtRed + ary[i][j + 2].rgbtRed +
                                            ary[i + 1][j].rgbtRed + ary[i + 1][j + 1].rgbtRed + ary[i + 1][j + 2].rgbtRed +
                                            ary[i + 2][j].rgbtRed + ary[i + 2][j + 1].rgbtRed + ary[i + 2][j + 2].rgbtRed) / 9.0);

            avg_ary[i + 1][j + 1].rgbtGreen = (int) round((ary[i][j].rgbtGreen + ary[i][j + 1].rgbtGreen + ary[i][j + 2].rgbtGreen +
                                              ary[i + 1][j].rgbtGreen + ary[i + 1][j + 1].rgbtGreen + ary[i + 1][j + 2].rgbtGreen +
                                              ary[i + 2][j].rgbtGreen + ary[i + 2][j + 1].rgbtGreen + ary[i + 2][j + 2].rgbtGreen) / 9.0);

            avg_ary[i + 1][j + 1].rgbtBlue = (int) round((ary[i][j].rgbtBlue + ary[i][j + 1].rgbtBlue + ary[i][j + 2].rgbtBlue +
                                             ary[i + 1][j].rgbtBlue + ary[i + 1][j + 1].rgbtBlue + ary[i + 1][j + 2].rgbtBlue +
                                             ary[i + 2][j].rgbtBlue + ary[i + 2][j + 1].rgbtBlue + ary[i + 2][j + 2].rgbtBlue) / 9.0);
        }
    }

    return;
}
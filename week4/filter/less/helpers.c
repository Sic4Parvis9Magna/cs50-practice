#include <math.h>
#include <stdio.h>
#include "helpers.h"
#include <stdlib.h>

int capped(int init_val);
int aling_top(int value, int limit);
int aling_down(int value, int limit);
void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE image_copy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *next_pixel = &image[i][j];
            BYTE new_val = round((next_pixel->rgbtRed + next_pixel->rgbtGreen + next_pixel->rgbtBlue) / (float)3);
            next_pixel->rgbtBlue = new_val;
            next_pixel->rgbtGreen = new_val;
            next_pixel->rgbtRed = new_val;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *next_pixel = &image[i][j];

            BYTE red = next_pixel->rgbtRed;
            BYTE green = next_pixel->rgbtGreen;
            BYTE blue = next_pixel->rgbtBlue;

            int new_red = round(.393 * red + .769 * green + .189 * blue);
            int new_green = round(.349 * red + .686 * green + .168 * blue);
            int new_blue = round(.272 * red + .534 * green + .131 * blue);

            new_red = capped(new_red);
            new_green = capped(new_green);
            new_blue = capped(new_blue);

            next_pixel->rgbtRed = new_red;
            next_pixel->rgbtGreen = new_green;
            next_pixel->rgbtBlue = new_blue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width / 2; j++, k--)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for image
    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    copy_image(height, width, image, image_copy);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE result;
            int tot_red = 0, tot_green = 0, tot_blue = 0;
            int x_min = aling_down(i - 1, 0);
            int x_max = aling_top(i + 2, height);
            int y_min = aling_down(j - 1, 0);
            int y_max = aling_top(j + 2, width);
            int divider = 0;
            // int mark = 0;

            for (int k = x_min; k < x_max; k++)
            {
                for (int l = y_min; l < y_max; l++)
                {
                    RGBTRIPLE *next_pixel = &image_copy[k][l];
                    tot_red += next_pixel->rgbtRed;
                    tot_green += next_pixel->rgbtGreen;
                    tot_blue += next_pixel->rgbtBlue;
                    divider++;

                }

            }

            result.rgbtRed = round(tot_red / (float)divider);
            result.rgbtGreen = round(tot_green / (float)divider);
            result.rgbtBlue = round(tot_blue / (float)divider);

            RGBTRIPLE *next_pixel = &image[i][j];
            next_pixel->rgbtRed = result.rgbtRed;
            next_pixel->rgbtGreen = result.rgbtGreen;
            next_pixel->rgbtBlue = result.rgbtBlue;

        }
    }

    free(image_copy);
    return;
}


int capped(int init_val)
{
    if (init_val > 255)
    {
        return 255;
    }

    return init_val;
}

int aling_top(int value, int limit)
{
    if (value > limit)
    {
        return limit;
    }

    return value;
}

int aling_down(int value, int limit)
{
    if (value < limit)
    {
        return limit;
    }

    return value;
}

void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE image_copy[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            RGBTRIPLE *pixel_copy = &image_copy[i][j];

            pixel_copy->rgbtRed = pixel->rgbtRed;
            pixel_copy->rgbtGreen = pixel->rgbtGreen;
            pixel_copy->rgbtBlue = pixel->rgbtBlue;
        }

    }

}
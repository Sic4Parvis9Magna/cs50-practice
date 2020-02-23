#include <cs50.h>
#include <stdio.h>

void print_points(int);
void print_spaces(int);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (!(height > 0 && height < 9));

    int spaces, points;

    for (int i = 0; i < height; i++)
    {
        spaces = height - i - 1;
        points = i + 1;
        print_spaces(spaces);
        print_points(points);
        print_spaces(2);
        print_points(points);
        printf("\n");
    }
}


void print_points(int points)
{
    for (int i = 0; i < points; i++)
    {
        printf("#");
    }
}

void print_spaces(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
}

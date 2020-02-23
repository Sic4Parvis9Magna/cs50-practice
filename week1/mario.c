#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
     height = get_int("Height: ");
    } while (!(height > 0 && height < 9));

    int spaces, points;

    for (int i = 0; i < height; i++) {
        spaces = height - i - 1;
        points = i + 1;
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        for (int k = 0; k < points; k++) {
            printf("#");
        }
        printf("\n");
    }


}
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float cash;
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash < 0.00F);

    int coins[] = {25, 10, 5, 1};
    int num_coins = 0;
    int cutted_val = round(cash * 100);
    int cursor = 0;
    while (cutted_val > 0)
    { 
        for (int index = cursor; index < 4; index++)
        { 
            if ( cutted_val >= coins[index])
            {
                cursor = index;
                cutted_val -= coins[index];
                num_coins++;
                break;
            }
        }
    }
    printf("%i\n", num_coins);
}
#include <cs50.h>
#include <stdio.h>

int main(void) {
    int number = get_int("n: ");
    if (number % 2 == 0 ) {
        printf("%i is an even number!\n", number);
    } else
    {
        printf("%i is an odd number!\n", number);
    }
    
}
#include <stdio.h>
#include "cs50.h"

int main(void) {
    // char name[20]; 
    // printf("What is your name? Write here: ");
    // scanf("%s", name);
    // printf("Hello, %s!!\n", name);
    string answer = get_string("What is your name? Write here: ");
    printf("Hello, %s!!\n", answer);
}


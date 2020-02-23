#include <cs50.h>
#include <stdio.h>

int main(void) {
    int age = get_int("How old are you ? \nWrite here: ");
    printf("You are %i years old! Wow!\n", age);
}
#include <stdio.h>

void caugh(int);

int main(void) {
    caugh(3);
}


void caugh(int times) {
    for(int i = 0; i < times; i++) {
        printf("Caugh!\n");
    }
}
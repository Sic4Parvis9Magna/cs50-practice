#include <stdio.h>

int main(void)
{
    float var1 = 0.01F;
    
    float var2 = 0.010000;
    printf("var1-var2=%f\n", var2-var1);
    printf("var1-var2=%i\n", 0.000000==0.00F);
    printf("0.010000*100=%i\n", (int)(0.010000*100) > 0);
}
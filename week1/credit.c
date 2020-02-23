#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool verify_card(int *);
void print_card_type(int *);
int * split_to_digits(long);

int main(void)
{
    long number;
    long low_limit = pow(10, 13); 
    long upper_limit = pow(10, 16); 
        
    number = get_long("Number: ");
       
    if (!(number > low_limit && number < upper_limit))
    {
        printf("INVALID\n");
        return 0;
    }

    int *p = split_to_digits(number);
    if (verify_card(p))
    {
        print_card_type(p);
    } else
    {
        printf("INVALID\n");
    }    
}

bool verify_card(int * array)
{
    int first_part  = 0;
    for(int i = 16-2; i >= 0; i = i - 2)
    {
        int temp_val = *(array + i);
        temp_val *=2;

        if (temp_val > 0)
        {
            if(temp_val < 10){
                first_part += temp_val;
            }else
            {
                first_part++;
                first_part += temp_val % 10; 
            }
            
        }
        
    }

    int second_part = first_part;
    for(int i = 16-1; i >= 0; i = i - 2)
    {
        int temp = *(array + i);
        
        if(temp > 0)
        {
            second_part += temp;
        }
    }
   
    return second_part % 10 == 0;
}

void print_card_type(int * array)
{
    int visa_num = 4;
    int ax_num = 3;
    int master_num = 5;
    string result;
    int first_digit;
    int second_digit;

    for(int i = 0; i < 16; i++)
    {
        int temp_val = *(array + i);
        if (temp_val > -1){
            first_digit = temp_val;
            second_digit = *(array + i + 1);
            break;
        }
    }

    if (first_digit == ax_num && (second_digit == 4 || second_digit == 7))
    {
        result = "AMEX";
    } else if (first_digit == master_num && (second_digit > 0 && second_digit < 6))
    {
        result = "MASTERCARD";
    } else if (first_digit == visa_num)
    {
        result = "VISA";
    } else
    {
        result = "INVALID";
    }
    

    printf("%s\n", result);
}

int * split_to_digits(long value)
{
    int length_limit = 16;
    static int digits[16];

    for (int i = 0; i < length_limit; i++)
    {
        digits[i] = -1;
    }
    

    long temp_val = value;

    long remainder;
    long private;
    int position = length_limit-1;
    do
    {
        private = temp_val / 10;
        remainder = temp_val % 10;
        digits[position] = remainder;
        position --;
        temp_val = private;

    } while (private > 0);
    
    return digits;
}

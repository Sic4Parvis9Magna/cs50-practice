#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int string_to_int(string str);
string cipher_with_key(int key, string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error! Input arguments number not equals 1!\n");
        return 1;
    }
    int key = string_to_int(argv[1]);
    if (key == -1)
    {
        return 1;
    }
    int aligned_shift = key % 26;
    printf("Actual shift is %i\n", aligned_shift);
    string plaintext = get_string("plaintext: ");
    string ciphertext  = cipher_with_key(aligned_shift, plaintext);
    printf("ciphertext: %s\n", ciphertext);
}

int string_to_int(string str)
{
    int len = strlen(str);
    int result = 0;

    for (int i = len - 1, j = 0; i > -1; i--, j++)
    {
        char value = str[i];
        if(!isdigit(value))
        {
            printf("Usage: ./caesar key\n");
            return -1;
        }
        int temp_val = value - '0';
        result += (temp_val * pow(10, j)); 
    }
    
    return result;
}

string cipher_with_key(int key, string plaintext)
{
    string copy = plaintext;
    
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++)
    {
        char value = plaintext[i];
        if(isalpha(value))
        {
            int shifted = (value + key);
            if (value > 64 && value < 91)
            {
                if (shifted > 'Z')
                {
                    copy[i] = 'A' + (shifted - 'Z') - 1;
                }
                else
                {
                    copy[i] = shifted;
                }
                
            } 
            else
            {
                if (shifted > 'z')
                {
                    copy[i] = 'a' + (shifted - 'z') - 1;
                }
                else
                {
                    copy[i] = shifted;
                }
                
            }
            
        }
    }

    return copy;
}
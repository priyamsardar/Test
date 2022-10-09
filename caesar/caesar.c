#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

string encrypt_msg(string plaintext, int k);

int main(int argc, string argv[])
{
    // If the argument has no input or more than 2 inputs, give an error message
    if(argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // If user inputted a non-numeric value, give an error message
    char *a;
    long b;
    b = strtol(argv[1],&a,10);
    if((*a >= 65 && *a <= 90) || (*a >= 97 && *a <= 122))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // If the argument has exactly 2 inputs proceed with the encryption
    if(argc == 2)
    {
        int k = 0;

        // Convert the string argument to integer
        k = atoi(argv[1]);

        // If user inputted a negative number, give an error message
        if(k <= 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // If k is greater than 26, get the remainder as the key
        if(k > 26)
        {
            k %= 26;
        }

        // Call in-built function to get plaintext from user to be encrypted
        string plaintext = get_string("plaintext:  ");

        // Call user-defined function to encrypt user text
        string ciphertext = encrypt_msg(plaintext, k);
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}

// Function to encrypt user text
string encrypt_msg(string plaintext, int k)
{
    int dec_value = 0, k1 = 0;
    char char_value;
    for(int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Proceed for an actual letter
        if(islower(plaintext[i]) || isupper(plaintext[i]))
        {
            // Get decimal value of the letter
            dec_value = plaintext[i];
            // Shift decimal value of that letter by key places
            dec_value += k;

            // If the decimal value of encrypted character is greater than the upper limit of uppercase, reset it
            if(isupper(plaintext[i]) && dec_value > 90)
            {
                k1 = dec_value - 90;
                dec_value = 64 + k1;
            }
            // If the decimal value of encrypted character is greater than the upper limit of lowercase, reset it
            else if(islower(plaintext[i]) && dec_value > 122)
            {
                k1 = dec_value - 122;
                dec_value = 96 + k1;
            }

            // Get character value of that decimal number
            char_value = dec_value;
        }
        // Proceed for character other than actual letter
        else
        {
            char_value = plaintext[i];
        }
        // Pass the encrypted character back to the string
        plaintext[i] = char_value;
    }
    return plaintext;
}
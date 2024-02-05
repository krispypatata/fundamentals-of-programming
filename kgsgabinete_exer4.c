// Gabinete, Keith Ginoel S. (2020-03670)
// Date Created: August 09, 2021

// This C program determines whether a string input from the user is a Palindrome or not
// Module 4 exercise

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// define a function that asks for an input string(word) from the user and return it
const char* askInput() {
    // dynamic strings necessary for asking an input
    char *input_word, *fgets_input_word;
    input_word = malloc(sizeof(char)*128);
    fgets_input_word = malloc(sizeof(char)*128);

    // a string necessary for inputs' restrictions
    char *extra_string;
    extra_string = malloc(sizeof(char)*128);

    // declaring other vital variables
    int i, is_valid = 0;

    while (is_valid == 0) {
        printf("\nEnter a word: ");
        fgets(fgets_input_word, 127, stdin);

        // declare variables that we can use for the isdigit() and ispunct() functions defined in ctype header
        int digits = 0, punctuations = 0;

        // <https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/>
        // if the input word contains digits, then it is invalid
        for (i=0; (fgets_input_word)[i] != '\0'; i++) {
            if (isdigit((fgets_input_word)[i]) != 0) {
                digits ++;
            }
        }

        if (digits != 0) {
            printf("\nInvalid Input! [Must not contain digits.]\n\n");
            continue;
        }
        
        // <https://www.geeksforgeeks.org/ispunct-function-c/>
        // if the input word contains punctuations, then it is invalid
        for (i=0; (fgets_input_word)[i] != '\0'; i++) {
            if (ispunct((fgets_input_word)[i]) != 0) {
                punctuations ++;
            }
        }
        if (punctuations != 0) {
            printf("\nInvalid Input! [Must not contain punctuations.]\n\n");
            continue;
        }

        // if the user inputs two or more words, then don't accept the input
        if (sscanf(fgets_input_word, " %s %s", input_word, extra_string) != 1) {
            printf("\nInvalid Input! [Input must be one word only]\n\n");
            
            continue;

        } else { // else accept the input and break out of the loop
            is_valid = 1;
            break;
        }
    }

    // free the spaces occupied by dynamic strings
    free(fgets_input_word);
    free(extra_string);

    return input_word;
}


// define a function that reverses a string (using the concept of swapping) 
// <https://www.w3schools.in/c-program/reverse-a-string-in-c/>
void reverseString (char word_to_reverse[]) {
    int i, str_len;
    int swap_temp = 0;

    // the for loop below (without a body) counts the actual length of the string
    for(str_len=0; word_to_reverse[str_len] != 0; str_len++);
    
    // Note that in the concep of swapping the number of iterations it would take a string to reverse itself is less than its half length
    for(i = 0; i <str_len/2; i++) {
        swap_temp = word_to_reverse[i]; 
        word_to_reverse[i] = word_to_reverse[str_len - 1 - i]; 
        word_to_reverse[str_len - 1 - i] = swap_temp;
    }

    printf("\nReversed Version of Input (lowercase): "); // some output message

    // putchar() function will write a single character to the standard output stream
    // the formed string will then replace the original contents of the string passed to the function
    for(i = 0; i < str_len; i++)
        putchar(word_to_reverse[i]);

}


// define a function that returns an integer value 1 a given word is a palindrome; else, return 0
int isPalidrome (char (*given_word)[128]) {
    int size_word = (int)strlen(*given_word);
    char word_lowercase[size_word];

    // make a temporary copy of the word to be tested
    strcpy(word_lowercase, *given_word);

    // converts the copy's contents to lowercase letters
    for (int i = 0; word_lowercase[i]!='\0'; i++) {
        word_lowercase[i] = tolower(word_lowercase[i]);
    }

    int size_lowercase = (int)strlen(word_lowercase);
    char word_reversed[size_word];

    // copies the copy's contents to another variable (that will be used to reverse the word/string)
    strcpy(word_reversed, word_lowercase);

    // reverses the given word
    reverseString(word_reversed);

    // compare the two strings (copy and the reversed copy) if they are the equal
    // return 1 if the given word is a Palindrome, else return 0
    if (strcmp(word_lowercase, word_reversed)==0) {
        return 1;
    } else {
        return 0;
    }
}


// for visual aesthetics
void outputBreaker () {
    printf("\n");
    for (int i=1; i<=150; i++) {
        printf("#");
    }
    printf("\n");
}


// start of the main function
int main () {
    char test_word[128], exit_program[] ="EXIT";
    int is_palindrome, palindrome_counter = 0;
    
    // multidimentsional array
    char mult_strings[100][128];

    // Display a brief description of the program
    printf("\nWelcome!\n\tThis program determines whether a word input from the user is a palindrome or not.\n[A word is a palindrome if it reads the same backward as forward, such as mAdaM or racEcAr.]\n\n");
    printf("\tNOTE: You can exit the program if you enter \"EXIT\" as an input.\n");
    printf("\t\t\t\"EXIT\" must be in CAPSLOCK.\n");

    // loop the main program
    do {
        // asks an input from the user
        strcpy(test_word,askInput());

        // check if the entered input is not equivalent to the string "EXIT"
        if (strcmp(exit_program,test_word) != 0) {
            outputBreaker();

            // checks whether the word is a palindrome or not
            is_palindrome = isPalidrome(&test_word);
            
            // Display the results
            switch (is_palindrome) {
                case 1:
                    printf("\n\nThe entered input \"%s\" is a PALINDROME!\n", test_word);
                    outputBreaker();
                    palindrome_counter ++;
                    strcpy(mult_strings[palindrome_counter-1], test_word);
                    break;

                default:
                    printf("\n\nThe entered input \"%s\" is NOT a PALINDROME!\n", test_word);

                    // converts test_word to lowercase letters
                    for (int i = 0; test_word[i]!='\0'; i++) {
                        test_word[i] = tolower(test_word[i]);
                    }

                    if (strcmp(test_word, "exit") == 0) {
                        printf("\nNOTE: If you want to terminate the program, \"exit\" word must be in all CAPS. [\"EXIT\"]\n");
                    }

                    outputBreaker();
            }

        } else {    // if the user chooses to exit the program, then display a list of entered inputs that are palindromes
            outputBreaker();
            if (palindrome_counter == 0) {
                printf("\n\t\t\t\t\t\t\tThank you for using our program!Bye!\n");
                outputBreaker();
                break;
                
            } else {
                printf("\nHere is the final list of entered word inputs that are palindromes:\n");
                for (int i=0; i<palindrome_counter; i++) {
                    printf("[%d]\t%s", i+1, mult_strings[i]);
                    printf("\n");
                }
            }

            printf("\n\t\t\t\t\t\t\tThank you for using our program!Bye!\n");
            outputBreaker();
            break;
        }

    } while (strcmp(exit_program,test_word) != 0);

    return 0;
} // end of the main function

/*
Cagara, Johann Miguel
Gabinete, Keith Ginoel

Date Created: August 13, 2021

C EXERCISE FOR MODULE 4
  In this c program we will ask two strings from the user and assess them if they are anagrams or not.
*/

/*Authors' Note:
In line with a particular instruction in submitting C programs for the collaborative exercises
in CMSC 21 wherein each of the two partners must indicate in the documentation part of each program
the particular contributions one has done for the successful development of its whole, Mr. Cagara  
and Mr. Gabinete, the two developers of this program, have come to an agreement to disclose the said
information as they believe that the program has reached its current state only through their efforts 
of working as a team. In fact, each block of codes present in the program has been made possible only 
because of the consistent synchronous communication shared by the two and that no block of codes have 
reached its final structure without applying the ideas both developers had in their minds. 
To simply say, no part of this program has been fully created with the efforts of one person alone; 
rather, each of the two has equally made a contribution (whether an approval for the consultation of the 
other or a direct modification of the code) for the finished structure of each block of codes present in 
this program. Thus, to be fair for each developer, so that at least none of them would have to be at a 
disadvantage position for the other has to indicate in the documentation part of the program that a particular 
part of code is his when it is actually a product of their teamwork, then the two decided to not follow this 
instruction in submitting c - exercises. Since both developers have made equal contributions to the entirety 
of this program and do have a complete understanding of how each block of codes work, the two wished to receive 
a mark uniform to them. They are more than happy to share the results of their fruitful work equally whether the 
mark that'd be bestowed upon them is excellent or not.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// define a function that asks for two input strings(words) from the user and return them
void askInputs (char (*first_input)[], char (*second_input)[]) {
    // dynamic strings necessary for asking an input
    char *fgets_input, *first_word, *second_word, *extra_word;
    fgets_input = malloc(sizeof(char)*128);
    first_word = malloc(sizeof(char)*128);
    second_word = malloc(sizeof(char)*128);
    extra_word = malloc(sizeof(char)*128);

    // declaring other vital variables
    int i, is_valid = 0;

    while (is_valid == 0) {
        printf("Enter two strings: ");
        fgets(fgets_input, 127, stdin);

        // variables that we can use for the isdigit() and ispunct() functions
        int digits = 0, punctuations = 0;

        // <https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/>
        // if the input word contains digits, then it is invalid
        for (i=0; (fgets_input)[i] != '\0'; i++) {
            if (isdigit((fgets_input)[i]) != 0) {
                digits ++;
            }
        }

        if (digits != 0) {
            printf("\nInvalid Input! [Must not contain digits]\n\n");
            continue;
        }
        
        //We learned how to properly use the ispunct function for strings here <https://www.geeksforgeeks.org/ispunct-function-c/>
        // if the input word contains punctuations, then it is invalid
        for (i=0; (fgets_input)[i] != '\0'; i++) {
            if (ispunct((fgets_input)[i]) != 0) {
                punctuations ++;
            }
        }
        if (punctuations != 0) {
            printf("\nInvalid Input! [Must not contain punctuations]\n\n");
            continue;
        }

        // if the user inputs one word or three or more words, then don't accept the input
        if (sscanf(fgets_input, " %s %s %s", first_word, second_word, extra_word) != 2) {
            printf("\nInvalid Input! [Input MUST be two strings]\n\n");
            continue;
        
        } else { // else accept the input and break out of the loop
            is_valid = 1;
            break;
        }
    }

    strcpy(*first_input, first_word);
    strcpy(*second_input, second_word);

    // free the spaces occupied by dynamic strings
    free(fgets_input);
    free(first_word);
    free(second_word);
    free(extra_word);
}

// define a function that converts words/strings to lowercase letters
void toLowercase (char (*word_toConvert)[]) {
    // converts characters to lowercase letters
    for (int i = 0; (*word_toConvert)[i]!='\0'; i++) {
        (*word_toConvert)[i] = tolower((*word_toConvert)[i]);
    }
}

// define a function that sorts string characters
// We learned bubble sorting here <https://www.geeksforgeeks.org/bubble-sort/>
void bubbleSort(char (*word_toSort)[], int string_length) {
    // swaps two consecutive characters if the value of lower-indexed character is greater than the character next to it
    for (int i = 0; i < string_length-1; i++) {
        for (int j = 0; j < string_length-i-1; j++) {
            if ((*word_toSort)[j] > (*word_toSort)[j+1]) {
                int temp = (*word_toSort)[j];
                (*word_toSort)[j] = (*word_toSort)[j+1];
                (*word_toSort)[j+1] = temp;
            }
        }
    }
}

// define a function that checks whether two given words/strings are anagrams or not
int areAnagrams(char (*first_word)[128], char (*second_word)[128]) {
    if (strcmp(*first_word, *second_word) == 0) {
        return 1; // return 1 if the words are anagram
    } else {
        return 0; // return 0 if false
    }
}

// start of the main function
int main () {
    char first_input[128], second_input[128], first_input_copy[128], second_input_copy[128], exit_word[] = "EXIT", now_word[] = "NOW";
    int are_anagrams;

    // display a brief description of the program
    printf("\n\tThis program determines whether the two words entered by the user are anagrams or not.\n");
    printf("\n\t[Anagram: a word, phrase, or name formed by rearranging the letters of another\n\tsuch as cinema, formed from iceman.]\n");
    printf("\n\tNote: If you want to terminate the program just enter \"EXIT NOW\" as an input.\n\t[\"EXIT NOW\" MUST be in all CAPS]\n\n");
    
    do {
        // ask two strings from the user
        askInputs(&first_input, &second_input);

        // check if the first input is equivalent to "EXIT NOW"
        if (strcmp(exit_word, first_input) == 0 && strcmp(now_word, second_input) == 0) {
            printf("\nThank you for using our program! Bye!\n\n");
            break;
        } else {
            strcpy(first_input_copy, first_input);
            strcpy(second_input_copy, second_input);
            toLowercase(&first_input);
            toLowercase(&second_input);
            bubbleSort(&first_input, strlen(first_input));
            bubbleSort(&second_input, strlen(second_input));
        }

        // check whether the two words have the same length
        if (strlen(first_input) == strlen(second_input)) {
            are_anagrams = areAnagrams(&first_input, &second_input);

            if (are_anagrams == 1) {
                printf("\n%s and %s are anagrams\n\n", first_input_copy, second_input_copy);

            } else {
                printf("\n%s and %s are NOT anagrams\n\n", first_input_copy, second_input_copy);
            }

        } else {
            printf("\n%s and %s are NOT anagrams\n\n", first_input_copy, second_input_copy);
        }

    } while (((strcmp(exit_word, first_input) != 0) && (strcmp(now_word, second_input) != 0)));

    return 0;
}

// Gabinete, Keith Ginoel S. (2020-03670)
// Date Created: July 17, 2021

// In this C program we will ask an input integer n from the user and we will list all the prime numbers from 1 to n

/*
Module 2 Exercise

Problem:
    Create a program that asks for an integer n and lists all prime numbers from 1 to n.

Instructions:
    Start by a creating recursive function that determines wether an integer is prime or not. Next ask for an
integer n, then loop through all the integers from 1 to n. Check each integer if it is prime by using the function
earlier then print the integer if it is prime.

Example run:
    Enter a positive number : 5
    The prime numbers from 1 to 5 are: 2 3 5
    
    Enter a positive number : 15
    The prime numbers from 1 to 15 are: 2 3 5 7 11 13
    
    Enter a positive number : 100
    The prime numbers from 1 to 100 are: 2 3 5 7 11 13 17 23 29 31 37 41 43
    47 53 59 61 67 71 73 79 83 89 97

*/

#include <stdio.h>
#include <ctype.h>  // The ctype.h header file of the C Standard Library declares several functions that are useful for testing and mapping characters.

// This is a global integer variable that will be used inside a recursive function and the main function
// this stores the number of divisors a number currently has
int divisor_count;

// This recursive function returns 1 if the given test_number is a prime number; if not, it returns 0
int isPrime (int test_number, int divisor) {
    // Note: integer 2 will always be passed to the divisor variable in the formal parameters above whenever we call this recursive function

    // base cases (smallest base cases)
    if (test_number <=2) {
        // if the test_number is 1, automatically distinguishes it as a non-prime number
        if (test_number == 1) {
            return 0;
        } else if (test_number == 2) { // again 2 is our default value (whenever calling this function) for the formal parameter - divisor, hence we will not invoke the recursive function when test_number is equal to this value
            return 1;
        }
    }
    
    else if (divisor < test_number) { 
        // if the test number is divisible by a certain divisor, update our variable for counting the current number of divisors a number has
        if (test_number%divisor==0) {
            divisor_count ++;
        }
    
    // base case (end/largest base case) (if the divisor is already equal to the test number, then stop invoking the function)
    } else if (divisor == test_number) {
        // if the number gains no additional factor/divisor (except 1 and itself) in the process, then that number is a prime number
        if (divisor_count == 0) {
            return 1;
        } 
        // Otherwise, it is not a prime number
        else if (divisor_count != 0) {
            return 0;
        }
    }
    // recursive case
    return isPrime(test_number, divisor + 1);
}


// Start of the main program
int main() {
    // declare a character variable to store the user's decision to still use the program or not and initiate its value to 'x'
    char exit = 'x';

    // declare an array to store the user's decision to still use the program or not
    // this will be used for the fgets() function later
    char fgets_exit[64];

    // declare an integer variable to store the positive number input from the user
    int positive_n = 0;

    // declare an array to store the positive number input from the user
    // this will also be used for the fgets() function later
    char fgets_positive_n[64];

    // this character variable will be used for sscanf() restrictions further in the code (as to comply with the technique I've learned from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>)
    char extra_char;

    int i; // some experimental variable used for some visual output purposes

    // declare an integer variable that will store the returned value of the recursive function isPrime()
    int prime;

    // Display a brief description of the program
    printf("\nWelcome!\n\tThis program asks for an input integer n from the user\nand prints all the prime numbers from 1 to entered integer n.\n\n");

    // makes the whole program loop until the user chooses to terminate it
    do {
        // I learned how to restrict an input using fgets and sscanf from this link <https://www.youtube.com/watch?v=zZPkgW9VPKw>
        while (positive_n == 0) {
            // ask for an input from the user
            printf("\nEnter a positive number : ");
            fgets(fgets_positive_n, 63, stdin);

            // I learned how to restrict sscanf function to only accept numbers from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>
            // Note that sscanf() returns 1 if the first input (%f) was successfully stored in a certain variable
            if (sscanf(fgets_positive_n, " %d  %c", &positive_n, &extra_char) != 1) {
                positive_n = 0;                     // resets the value of the variable positive_n
                printf("\nInvalid Input!\n");       // inform the user that he/she entered an invalid input
                continue;                           // restarts the loop
            }

            // if the user inputs a number (only) but is zero, 1 or negative, inform the user that he/she entered an invalid input
            if (positive_n <= 1) {
                positive_n = 0;
                printf("\nInvalid Input! (Input integer must not be 0, 1 or negative)\n");
                continue;
            }
        }

        // Display the results
        printf("The prime numbers from 1 to %d are: ", positive_n);
        for (i=1; i<= positive_n; i++) {
            divisor_count = 0;
            prime = isPrime(i, 2);

            if (prime == 1) {
                printf("%d ", i);
            
            } else {continue;}
        }

        printf("\n\n");

        while (exit == 'x') {
            // After displaying the results, ask the user if he/she still wants to use the program
            printf("Do you want to exit the program now?[y/n] ");
            fgets(fgets_exit, 63, stdin);

            // declare variables that we can use for the isdigit() and ispunct() functions defined in ctype header
            int digits = 0, punctuations = 0;

            // I learned how to properly use the isdigit() function for strings defined in ctype header from this link <https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/>
            // if the fgets_exit string contains digits, automatically restart the loop and inform the user that his/her input is deemed invalid    
            for (i=0; fgets_exit[i] != '\0'; i++) {
                if (isdigit(fgets_exit[i]) != 0) {
                    digits ++;
                }
            }
            if (digits != 0) {
                printf("\nInvalid Input!\n\n");
                continue;
            }
            
            // I learned how to properly use the ispunct function for strings here <https://www.geeksforgeeks.org/ispunct-function-c/>
            // if the fgets_exit string contains punctuations, automatically restart the loop and inform the user that his/her input is deemed invalid
            for (i=0; fgets_exit[i] != '\0'; i++) {
                if (ispunct(fgets_exit[i]) != 0) {
                    punctuations ++;
                }
            }
            if (punctuations != 0) {
                printf("\nInvalid Input!\n\n");
                continue;
            }

            if (sscanf(fgets_exit, " %c %c", &exit, &extra_char) != 1) {
                exit = 'x';
                printf("\nInvalid Input!\n\n");
                continue;
            }

            if (exit != 'n' && exit != 'y') {
                printf("\nInvalid Input!\n\n");
                exit = 'x';
                continue;
            }
        }

        // if the user chooses not to terminate the program yet, then don't exit the program
        if (exit == 'n') {
            // resets the valuea of exit variable and positive_n variable
            exit = 'x';
            positive_n = 0;

            printf("\n");
            for (i=1; i<=150; i++) {
                printf("#"); // for visual aesthetics
            }
            printf("\n\n");
            continue;

        // If the user decides to exit the program, then break out of the outer loop
        } else if (exit == 'y') {
            printf("\nThank you for using our program!\nBye!\n\n");
            for (i=1; i<=150; i++) {
                printf("#"); // for visual aesthetics
            }
            printf("\n\n");
            break;
        }
    } while (exit=='x');
    return 0;
}

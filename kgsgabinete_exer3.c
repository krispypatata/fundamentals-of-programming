// Gabinete, Keith Ginoel S. (2020-03670)
// Date Created: July 23, 2021

// In this C program we will ask input integers x and y from the user and we'll list atmost three largest prime numbers from x to y

/*
Module 3 Exercise

Problem:
    Create a program that gets thee (3) largest prime numbers from x, to y, x and y are given by the user.
    
    If x is greater than y, swap x and y.

    If there are no prime numbers in the given range, the program must print zero (0). If there is only one prime
number, the program must print that number. If there are two prime numbers in the given range, then both
prime numbers are printed.

Instructions:
    Implement the specifications below. It's up to you to decide what functions to create, what
parameters to pass, etc. However, part of your grade for this exercise depends on the following:
1. whether you divided the problem into functions properly, and
2. whether you properly used the dierent types of parameter passing based on what the functions you
created need.
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
} // end of isPrime function


// define a function that asks for an input positive number from the user
// also validate/restrict the data being entered
void inputInteger (int *integer_pointer, char (*fgets_integer)[64], char variable_name) {
    while (*integer_pointer == 0) {

        // a character variable necessary for inputs' restrictions
        char extra_char;

        // ask for an input from the user
        printf("\nEnter a positive number [%c]: ", variable_name);
        fgets(*fgets_integer, 63, stdin);

        // validate if the data entered consist of positive integer/s only
        if (sscanf(*fgets_integer, " %d  %c", integer_pointer, &extra_char) != 1) {
            *integer_pointer = 0;                   // resets the value of the variable the pointer integer_pointer is pointing to
            printf("\nInvalid Input!\n");           // inform the user that he/she entered an invalid input
            continue;                               // restarts the loop
        }

        // if the user inputs a number that is zero or negative, inform the user that he/she entered an invalid input
        if (*integer_pointer <= 0) {
            *integer_pointer = 0;
            printf("\nInvalid Input! (Not a positive real number)\n");
            continue;
        }

    }
} // end of inputInteger functions


// define a function that swaps the values of x and y if x is greater than y (inputs from the user)
void swapXY (int *x, int *y) {
    int temp;   // a variable that temporarily stores a value from one of the given parameters

    if (*x>*y) {
        temp = *x;
        *x = *y;
        *y = temp;
        printf("\n\tNote: The values of x and y are interchanged since y must be greater than x. [Prime numbers from x to y]\n");
    }
}   // end of swapXY function


// define a function that swaps the values of the three integer variables (declared in the main function) that store prime numbers from x to y
// we're defining this function so we could come up with the three largest prime numbers from x to y if there are more than three prime numbers in the given range
void swapPrimes(int *prime_ptr1, int *prime_ptr2, int *prime_ptr3, int *prime_replace) {
    *prime_ptr1 = *prime_ptr2;
    *prime_ptr2 = *prime_ptr3;    
    *prime_ptr3 = *prime_replace;
} // end of swapPrimes function


// define a function that asks the user for a decision to still use or exit the program
// also validate/restrict the input data
void askExit (char *char_pointer, char (*fgets_char)[64]) {

    // a character variable necessary for inputs' restrictions
    char extra_char;

    // integer variable necessary for inputs' restrictions
    int i;

    while (*char_pointer == 'x') {
        printf("Do you want to exit the program now?[y/n] ");
        fgets(*fgets_char, 63, stdin);

        // declare variables that we can use for the isdigit() and ispunct() functions defined in ctype header
        int digits = 0, punctuations = 0;

        // I learned how to properly use the isdigit() function for strings defined in ctype header from this link <https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/>
        // if the string pointed by the fgets_char pointer contains digits, automatically restart the loop and inform the user that his/her input is deemed invalid    
        for (i=0; (*fgets_char)[i] != '\0'; i++) {
            if (isdigit((*fgets_char)[i]) != 0) {
                digits ++;
            }
        }
        if (digits != 0) {
            printf("\nInvalid Input!\n\n");
            continue;
        }
        
        // I learned how to properly use the ispunct function for strings here <https://www.geeksforgeeks.org/ispunct-function-c/>
        // if the string pointed by the char_pointer pointer contains punctuations, automatically restart the loop and inform the user that his/her input is deemed invalid
        for (i=0; (*fgets_char)[i] != '\0'; i++) {
            if (ispunct((*fgets_char)[i]) != 0) {
                punctuations ++;
            }
        }
        if (punctuations != 0) {
            printf("\nInvalid Input!\n\n");
            continue;
        }

        if (sscanf(*fgets_char, " %c %c", char_pointer, &extra_char) != 1) {
            *char_pointer = 'x';
            printf("\nInvalid Input!\n\n");
            continue;
        }

        if (*char_pointer != 'n' && *char_pointer != 'y') {
            printf("\nInvalid Input!\n\n");
            *char_pointer = 'x';
            continue;
        }
    }
} // end of askExit function


// Start of the main program
int main() {
    // a variable vital to our outside(main) loop
    char exit = 'x';

    // declare an array to store the user's decision to still use the program or not
    // these will be used for the fgets() function later
    char fgets_exit[64];

    // declare integer variables to store the positive number inputs x and y from the user
    int x = 0, y = 0;

    // declare arrays to store the positive number inputs from the user
    // these will also used for the fgets() function later
    char fgets_x[64], fgets_y[64];;

    // this character variable will be used for sscanf() restrictions further in the code (as to comply with the technique I've learned from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>)
    char extra_char;

    int i; // some experimental variable used for some visual output purposes

    // declare integer variables that will store the returned value of the recursive function isPrime() and will count the number of prime numbers between x and y
    int prime, prime_count;

    // declare three (3) integer variables that will store the three largest prime numbers from x to y and initialize their values to 0
    int prime_1st = 0, prime_2nd = 0, prime_3rd = 0;

    // Display a brief description of the program
    printf("\nWelcome!\n\tThis program asks for two input integers x and y from the user\nand prints at most three (largest) prime numbers from x to y.\n\n");

    // makes the whole program loop until the user chooses to terminate it
    do {
        // ask for inputs from the user
        inputInteger(&x, &fgets_x, 'x');
        inputInteger(&y, &fgets_x, 'y');

        // check if the values of x and y are equal to each other; if it is then inform the user that he/she must re-enter his/her inputs
        // then restart the main loop
        if (x == y) {
            printf("\n\t[ENTERED INPUTS ARE UNACCEPTED!]\n\tSorry but you must enter a value for y that is unique from x.\n\tPlease re-enter your inputs!\n");
            x = 0;
            y = 0;
            continue;
        } // end of if statement

        // check if the value of x is greater than y; if it is then swap the values of x and y
        swapXY(&x, &y);

        printf("\n");

        // Check for the prime numbers from x to y
        for (i=x; i<= y; i++) {
            divisor_count = 0;
            prime = isPrime(i, 2);

            // if there is a prime number on the given range
            if (prime == 1) {
                prime_count ++;
                if (prime_1st == 0) {
                    prime_1st = i;
                } else if (prime_2nd == 0) {
                    prime_2nd = i;
                } else if (prime_3rd == 0) {
                    prime_3rd = i;
                } else {
                    if (prime_count > 3) {
                        swapPrimes(&prime_1st, &prime_2nd, &prime_3rd, &i);
                    }
                }
            } else {continue;}
        } // end of for loop

        // Display the results
        if (prime_count == 0) {
            printf("\t[Number of Prime Number/s in the given range: 0]\n\tConclusion:\n\t\tThere is no prime number from x to y.");
        } else if (prime_count == 1) {
            printf("\t[Number of Prime Number/s in the given range: 1]\n\tConclusion:\n\t\tThe only prime number from x to y is %d.", prime_1st);
        } else if (prime_count == 2) {
            printf("\t[Number of Prime Number/s in the given range: 2]\n\tConclusion:\n\t\tThe only two prime numbers from x to y are %d and %d.", prime_1st, prime_2nd);
        } else if (prime_count == 3) {
            printf("\t[Number of Prime Number/s in the given range: 3]\n\tConclusion:\n\t\tThe three prime numbers from x to y are %d, %d and %d.", prime_1st, prime_2nd, prime_3rd);
        } else {
            printf("\t[Number of Prime Number/s in the given range: %d]\n\tConclusion:\n\t\tThe three largest prime numbers from x to y are %d, %d and %d.", prime_count, prime_1st, prime_2nd, prime_3rd);
        } // end of if-else statements

        printf("\n\n");

        // After displaying the results, ask the user if he/she still wants to use the program
        askExit(&exit, &fgets_exit);

        // if the user chooses not to terminate the program yet, then don't exit the program
        if (exit == 'n') {
            // resets the values of important variables
            exit = 'x';
            x = 0;
            y = 0;
            prime_count = 0;
            prime_1st = 0;
            prime_2nd = 0;
            prime_3rd = 0;

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
        } // end of if-else statement
        
    } while (exit=='x');

    return 0;
} // end of the main function

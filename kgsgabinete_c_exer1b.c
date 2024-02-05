/*
Cagara, Johann Miguel
Gabinete, Keith Ginoel

Given that 1 Jan 2021 is a Friday, write a program that asks for a user input of the month
number and prints the year 2021 calendar for the corresponding month.
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

int main() {
    // declare integer variables that will be used in our program
    int month_number, day_number, days_passed = 0, excess_days = 5, days_in_calendar = 1, i, j, days_of_month;
    char choice;

    // ask for an input from the user
    while (choice!='n') {
        do {
            printf("\nEnter a month number (1-12): ");

            // inform the user if he inputs something that is not an integer
            if(scanf(" %d", &month_number) !=1) {
                printf("\nInvalid Input!\n");
                getchar(); // erases the last input data from the input stream
                continue;
            }

            // inform the user if the number he/she entered is out of the valid range (1-12)
            if (month_number<1 || month_number>12) {
                printf("\nInvalid Input!\n");
                continue;
            }


        } while (month_number<1 || month_number>12); // loop this part of the code until the user provides a valid input

        // Heading for the output
        printf("\nOUTPUT:\n\n");
        printf("Calendar for ");

        // Still heading for the output
        switch (month_number) {
            case 1:
                printf("January");
                break;
            
            case 2:
                printf("February");
                break;

            case 3:
                printf("March");
                break;

            case 4:
                printf("April");
                break;

            case 5:
                printf("May");
                break;

            case 6:
                printf("June");
                break;

            case 7:
                printf("July");
                break;

            case 8:
                printf("August");
                break;

            case 9:
                printf("September");
                break;

            case 10:
                printf("October");
                break;

            case 11:
                printf("November");
                break;

            default:
                printf("December");
        }

        // Still heading for the output
        printf("2021\n");

        // first row of the calendar table
        printf("SUN\tMON\tTUE\tWED\tTH\tFRI\tSAT\n");

        // calculate the number of days passed in year 2021 before the first day of the entered month
        for (i=(month_number-1); i>0; i--) {
            switch(i){
                case 2:
                    days_of_month = 28;
                    break;

                case 4:
                    days_of_month = 30;
                    break;
                    
                case 6:
                    days_of_month = 30;
                    break;

                case 9:
                    days_of_month = 30;
                    break;

                case 11:
                    days_of_month = 30;
                    break;    

                default:
                    days_of_month = 31;
            }

            // update the days_passed variable
            // add the previous value of the days_passed variable to the number of days in the current month (value of days_of_month in the current iteration) to obtain the updated value of days_passed
            days_passed = days_passed + days_of_month;
        }

        // determine what part of the week the first day of the given month falls into
        // since January 1, 2020 is Friday, we want a day_number value for it to be 6 (Friday is the 6th day of the week)
        // To arrive at such desired value for day_number, we'll add the 5 excess days from the previous year to the value of the variable days_passed
        day_number = (excess_days + days_passed)%7 + 1;

        // do not put number values to certain spots in the calendar that should be empty
        while (days_in_calendar<day_number) {
                printf(" \t");
                days_in_calendar ++;
            }

        // // calculate the number of days the entered month has
        switch(month_number){
            case 2:
                days_of_month = 28;
                break;

            case 4:
                days_of_month = 30;
                break;
                
            case 6:
                days_of_month = 30;
                break;

            case 9:
                days_of_month = 30;
                break;

            case 11:
                days_of_month = 30;
                break;    

            default:
                days_of_month = 31;
        }

        // print numbers from 1 to the total number of days a given month has
        for (j=1; j<= days_of_month; j++) {
            printf("%d\t", j);

            // output a line break every time a row occupies 7 slots
            if (((days_in_calendar -1) + j)%7 == 0) {
                printf("\n");
            }
        }

        printf("\n\n");
        
        // ask the user if he/she still wants to use the program
        do {
            printf("Continue? y or n: ");
            scanf(" %c", &choice);

            // inform the user if he/she entered an invalid input
            if (choice!='y' && choice !='n') {
                printf("\nInvalid Input!\n\n");
            }

        } while (choice!='y' && choice !='n'); // loop this block of codes until the user enters a valid input

        // If the user entered 'n' as an input then terminate the program
        if (choice=='n') {
            printf("Bye! Thank you for using our calendar.\n");

        // else if the user entered 'y' as an input then restart the loop of the main program
        // also reset the values of the declared variables
        } else {
            month_number = 0;
            day_number = 0;
            days_passed = 0;
            excess_days = 5;
            days_in_calendar = 1;
            i = 0;
            j = 0;
            days_of_month = 0;
            continue;
        }
    }
    return 0;
} // end of the program

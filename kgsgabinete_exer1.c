// Gabinete, Keith Ginoel S. (2020-03670)
// Date Created: July 14, 2021

// In this C program we will create a calculator to find a person's body mass index (BMI)

/* (This is a multiline comment)
Module 1 Exercise
Problem:
    BMI Calculator
        Create a C program that will compute for the body-mass index of a given height and weight. After calculating
    the BMI, the program willl also tell under which category(underweight, normal weight, overweight,or obese) it
    belongs to. The user will be given two (2) choices before entering the height and weight. The menu must loop
    repeatedly until the exit option is entered. Make sure to have proper error prompts.
        a. Enter in kilogram and centimeters
            This will ask for the weight in kilograms and height in centimeters.
        b. Enter in pounds and feet
            This will ask for the weight in pounds and height in feet.
        c. Exit
            Once chosen, the program must terminate.    
*/

/*
What is Body Mass Index (BMI)
    Body mass index (BMI) is a value derived from the mass (weight) and height of a person. 
The BMI is defined as the body mass divided by the square of the body height, and is expressed in 
units of kg/m2, resulting from mass in kilograms and height in metres.

    Mathematically speaking, we have
        BMI = weight (kg) / height^2 (m^2)                  // kilogram/meter
    OR  BMI = 703 * [weight (lb) / height^2 (in^2)]         // pound/inch

Reference: https://en.wikipedia.org/wiki/Body_mass_index

Categories of BMI:
    Below 18.5      — Underweight
    18.5 - 24.9     — Normal range
    25 – 29.9       — Overweight
    30 and above    - Obese

References: 
    https://www.cdc.gov/healthyweight/assessing/bmi/adult_bmi/english_bmi_calculator/bmi_calculator.html
    https://www.nhlbi.nih.gov/health/educational/lose_wt/BMI/bmicalc.htm

*/

// BMI CALCULATOR
#include <stdio.h>
#include <string.h> // The string.h header defines one variable type, one macro, and various functions for manipulating arrays of characters. <https://www.tutorialspoint.com/c_standard_library/string_h.htm>
#include <ctype.h>  // The ctype.h header file of the C Standard Library declares several functions that are useful for testing and mapping characters.

int main() {

    // declare an array to store the user's choice from the given options
    /* 
    I use a variable with data type string for the user's choice as this pose less errors than using a variable with data type character (enabling myself to fix less number of errors)
    For example, if I declare a character variable for the user's choice and the user inputs something like 'abcd' given that the available options for the menu are 'a','b' and 'c',
    the input will be accepted as the scanf function reads the input one-by-one (if it was tasked to store data in a character variable), meaning as the scanf function reads 'a' first from the user's input
    'abcd' and store it in our character variable, then the scanf function will stop reading the rest of the given input'abcd' when, in reality, what we wanted to do is to reject inputs like 'abcd'
    Furthermore, if the user inputs 'lmno' which does not have a single character that matches our given options 'a', 'b' and 'c', the scanf function will iterate four times before accepting another new input
    as based on what I've said earlier that the scanf function reads the input one-by-one (if it was tasked to store data in a character variable)
    On the other hand if we declare a string variable for our user's choice then we would be able to reject inputs like 'abcd' and 'lmno' easily as these are being read by the scanf function as one whole input
    */
    char choice[1];

    // declare an integer variable that would store the equivalent integer value of the user's choice ('a' = 1, 'b' = 2, 'c' = 3)
    // We're doing this since we can't normally use strings in switch statements
    int choice_number;

    // declare arrays to store the user's data necessary for computing a person's BMI 
    /* Note that I use arrays here since I will be using fgets later to get inputs from the user
    I tried using the scanf function all throughout the code but found myself frustrated as scanf poses lots of errors in getting inputs from the user which are clearly worse than I anticipated
    for example, if I use scanf to accept only a float input from the user and restrict other data types to be entered on the input, either it results to input buffer overflow 
    (User's input: 'abcd' would result to input overflow making the scanf function iterates four times) or it would accept the input not knowing that there is/are invalid characters read by the scanf 
    (User's input: '12cd' would be accepted by the scanf function (since 12 is a float number) but would make  the system encounters error due to the succeeding characters 'cd')
    */
    char fgets_weight_kg[64] , fgets_weight_lb[64], fgets_height_cm[64], fgets_height_ft[64], fgets_height_in[64];

    // this character variable will be used for sscanf() restrictions further in the code (as to comply with the technique I've learned from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>)
    char extra_char;

    // declare float variables to store the user's data necessary for computing a person's BMI
    float weight_kg = 0, weight_lb = 0, height_cm = 0, height_m, height_ft = 0, height_ft_converted, height_in = 0, height_ft_in, BMI=0;

    // declare an array to store the user's decision to still use the program or not
    // this will be used for the fgets() function later
    char fgets_exit[64];

    // declare a character variable to store the user's decision to still use the program or not
    char exit = 'x';

    int i; // some experimental variable used for some visual output purposes

    // The two lines of printf functions below output a short description of the program
    printf("\nWelcome!\n\tThis program calculates the Body Mass Index (BMI) of a person and tells\n");
    printf("the user which category (underweight, normal weight, overweight,or obese) it belongs to.\n\n");

    // The program will loop until the user chooses to terminate it
    do {
        // Main Menu
        printf("Compute for the BMI:\n");
        printf("\ta. Enter in kilogram and centimeters.\n");
        printf("\tb. Enter in pounds and feet.\n");
        printf("\tc. Exit\n\n");

        // Asking the user for his/her choice from the given options will loop until a valid input is accepted
        do {
            // Ask for the user's choice
            printf("Enter Choice: ");

            // I learned the scanf restriction below from this link <https://stackoverflow.com/questions/3555108/multiple-word-string-input-through-scanf>
            /*Using %[^\n] would make the scanf function reads all the input until it encounters a line break (or enter key)
            For example: User's input: "askdko akdsoafd akdofsak skdfaofdosa" would be read as one string input
            Note that if we don't do this the given input above will make the scanf function iterates  four times as askdko and akdsoafd would be read as separate 
            strings since there is a whitespace between them
            */
            scanf(" %[^\n]", choice);
            getchar(); // This will remove the new line (\n) in the input buffer so that when you call an fgets function later (after the execution of this scanf ), fgets will not encounter the \n as an input (preventing the fgets function to execute one time even without you inputting anyting yet)
            printf("\n");

            // I learned to compare string values from this link <https://stackoverflow.com/questions/8222495/how-to-compare-strings-in-an-if-statement>
            // strcmp() is a function (from string.h) that takes two (string) parameters and compare them
            // the strcmp(<1st string>, <2nd string>) function returns 0 if the two parameters are equivalent
            // inform the user if he/she types something that does not match the given choices in the Main Menu
            if (strcmp(choice, "a")!= 0 && strcmp(choice, "b") != 0 && strcmp(choice, "c") != 0) {
                printf("Invalid Input!\n\n");
            }

        } while (strcmp(choice, "a")!= 0 && strcmp(choice, "b") != 0 && strcmp(choice, "c") != 0);


        // I learned to compare string values from this link <https://stackoverflow.com/questions/8222495/how-to-compare-strings-in-an-if-statement>
        // If the input of the user is equivalent to string "a" then change the value of the integer varaible choice_number to 1
        if (strcmp(choice, "a") == 0) {
            choice_number = 1;
        }
        // If the input of the user is equivalent to string "b" then change the value of the integer varaible choice_number to 2
        else if (strcmp(choice, "b") == 0) {
            choice_number = 2;

        } 
        // If the input of the user is equivalent to string "c" then change the value of the integer varaible choice_number to 3
        else  {
            choice_number = 3;
        }

        for (i=1; i<=150; i++) {
            printf("*"); // for visual aesthetics
        }
        printf("\n");

        // Check whether the input integer value (choice_number) falls under one of the given options in the Main Menu
        switch (choice_number) {
            case 1:
                // I learned how to restrict an input using fgets and sscanf from this link <https://www.youtube.com/watch?v=zZPkgW9VPKw> 
                while (weight_kg == 0) {
                    printf("\nEnter weight (kilograms): ");
                    fgets(fgets_weight_kg, 63, stdin);

                    // I learned how to restrict sscanf function to only accept numbers from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>
                    // Note that sscanf() returns 1 if the first input (%f) was successfully stored in a certain variable
                    if (sscanf(fgets_weight_kg, " %f %c", &weight_kg, &extra_char)!= 1) {
                        weight_kg = 0;                      // resets the value of weight_kg
                        printf("\nInvalid Input!\n");   // inform the user that he/she entered an invalid input
                        continue;                           // restarts the loop
                    }

                    // if the user inputs a number (only) but is negative, inform the user that he/she entered an invalid input
                    if (weight_kg <= 0) {
                        weight_kg = 0;
                        printf("\nInvalid Input! - (Input must be a positive number!)\n");
                        continue;
                    }

                }

                // I learned how to restrict an input using fgets and sscanf from this link <https://www.youtube.com/watch?v=zZPkgW9VPKw> 
                while (height_cm == 0) {
                    printf("\nEnter height (centimeters): ");
                    fgets(fgets_height_cm, 63, stdin);

                    // I learned how to restrict sscanf function to only accept numbers from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>
                    // Note that sscanf() returns 1 if the first input (%f) was successfully stored in a certain variable
                    if (sscanf(fgets_height_cm, " %f %c", &height_cm, &extra_char)!= 1) {
                        height_cm = 0;                      // resets the value of height_cm
                        printf("\nInvalid Input!\n");   // inform the user that he/she entered an invalid input
                        continue;                           // restarts the loop
                    }

                    // if the user inputs a number (only) but is negative, inform the user that he/she entered an invalid input
                    if (height_cm <= 0) {
                        height_cm = 0;
                        printf("\nInvalid Input! (Not a positive real number)\n");
                        continue;
                    }
                }

                printf("\n");

                // Convert the inputted value of height from centimeters to meters (We do this as to comply with the standard formula in getting the BMI)
                height_m = height_cm/100;
                
                // Apply the standard formula in getting the BMI of a person [ BMI = weight (kg) / height^2 (m^2) ]
                BMI = weight_kg/(height_m*height_m);

                for (i=1; i<=150; i++) {
                    printf("*"); // for visual aesthetics
                }
                printf("\n");

                // print the results
                printf("Results:\n");
                printf("\tYour BMI is %f.\n", BMI);

                break;
            
            case 2:

                // I learned how to restrict an input using fgets and sscanf from this link <https://www.youtube.com/watch?v=zZPkgW9VPKw> 
                while (weight_lb == 0) {
                    printf("\nEnter weight (pounds): ");
                    fgets(fgets_weight_lb, 63, stdin);
                    
                    // I learned how to restrict sscanf function to only accept numbers from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>
                    // Note that sscanf() returns 1 if the first input (%f) was successfully stored in a certain variable
                    if (sscanf(fgets_weight_lb, " %f %c", &weight_lb, &extra_char)!= 1) {
                        weight_lb = 0;                      // resets the value of &weight_lb
                        printf("\nInvalid Input!\n");   // inform the user that he/she entered an invalid input
                        continue;                           // restarts the loop
                    }

                    // if the user inputs a number (only) but is negative, inform the user that he/she entered an invalid input
                    if (weight_lb <= 0) {
                        weight_lb = 0;
                        printf("\nInvalid Input! - (Input must be a positive number!)\n");
                        continue;
                    }

                }

                // I learned how to restrict an input using fgets and sscanf from this link <https://www.youtube.com/watch?v=zZPkgW9VPKw> 
                while (height_ft == 0) {
                    printf("\nNote:\n\tIn entering height in this option (b), you will be asked to input two data:\n\tHeight in feet &\n\texcess height in inch.\n");
                    printf("\nExample:\n\tIf your height is 5'6 then you will type 5 in the first prompt below and type 6 on the prompt thereafter.\n\n");
                    printf("Enter height Pt. 1 (feet): ");
                    fgets(fgets_height_ft, 63, stdin);

                    // I learned how to restrict sscanf function to only accept numbers from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>
                    // Note that sscanf() returns 1 if the first input (%f) was successfully stored in a certain variable
                    if (sscanf(fgets_height_ft, " %f %c", &height_ft, &extra_char)!= 1) {
                        height_ft = 0;                      // resets the value of height_ft
                        printf("\nInvalid Input!\n");   // inform the user that he/she entered an invalid input
                        continue;                           // restarts the loop
                    }

                    // if the user inputs a number (only) but is negative, inform the user that he/she entered an invalid input
                    if (height_ft <= 0) {
                        height_ft = 0;
                        printf("\nInvalid Input! (Not a positive real number)\n");
                        continue;
                    }
                }

                // I learned how to restrict an input using fgets and sscanf from this link <https://www.youtube.com/watch?v=zZPkgW9VPKw> 
                while (height_in == 0) {
                    printf("\nEnter height Pt. 2 (inch): ");
                    fgets(fgets_height_in, 63, stdin);

                    // I learned how to restrict sscanf function to only accept numbers from this link <https://stackoverflow.com/questions/54370409/if-my-scanf-variable-is-a-float-and-a-user-inputs-a-character-how-can-i-prompt-t>
                    // Note that sscanf() returns 1 if the first input (%f) was successfully stored in a certain variable
                    if (sscanf(fgets_height_in, " %f %c", &height_in, &extra_char)!= 1) {
                        height_in = 0;                      // resets the value of height_in
                        printf("\nInvalid Input!\n");   // inform the user that he/she entered an invalid input
                        continue;                           // restarts the loop
                    }

                    // if the user inputs a number (only) but is negative, inform the user that he/she entered an invalid input
                    if (height_in <= 0) {
                        height_in = 0;
                        printf("\nInvalid Input! (Not a positive real number)\n");
                        continue;
                    }
                }

                printf("\n");

                // Convert the inputted value of height (Pt.1) from feet to inch
                height_ft_converted = height_ft*12;

                // Add the converted height to the excess inch inputted by the user in the 2nd prompt/scanf of height in option b
                height_ft_in = height_ft_converted + height_in;

                // Apply the second formula in getting the BMI of a person { BMI = 703 * [weight (lb) / height^2 (in^2)] }
                BMI = 703*(weight_lb/(height_ft_in*height_ft_in));

                for (i=1; i<=150; i++) {
                    printf("*"); // for visual aesthetics
                }
                printf("\n");

                // print the results
                printf("Results:\n");
                printf("\tYour BMI is %f.\n", BMI);

                break;
            
            case 3:
                printf("Thank you for using our program!\nBye!\n\n");

                for (i=1; i<=150; i++) {
                    printf("#"); // for visual aesthetics
                }
                printf("\n");
                // resets the value of BMI
                BMI=0;

                // exit the outmost do-while loop of the main function
                exit = 'y';
                break;

            // Note that the default case in switch statement is not necessary in this code since choice_number could only have three integer values (1,2,3)
        }

        // Find which category does the computed BMI belongs to
        if (BMI>0) {
            // if BMI is below 18.5, then the person can be distinguished as Underweight
            if (BMI<18.5) {
                printf("\tThis indicates that your weight is in the UNDERWEIGHT category for adults of your height.\n\n");
                printf("\tUnfortunately, your BMI cuts short to be distinguished as normal.\n");
                printf("\tNonetheless, be sure to practice a healthier lifestyle so you can gain enough weight.\n");
                printf("\tJust don't give up and you'll have your way there.\n\n");
                for (i=1; i<=150; i++) {
                    printf("*"); // for visual aesthetics
                }
                printf("\n\n");
            } 
            
            // The BMI for Normal weight lies in range [18.5, 25)
            else if (BMI<25){
                printf("\tThis indicates that your weight is in the NORMAL category for adults of your height.\n\n");
                printf("\tGood job! Your BMI tells us that you're having a proper and healthy lifestyle.\n");
                printf("\tMaintaining it may reduce risks of aqcuiring chronic diseases associated with overweight and obesity.\n\n");
                for (i=1; i<=150; i++) {
                    printf("*"); // for visual aesthetics
                }
                printf("\n\n");
            } 
            
            // The BMI for Overweight class lies in range [25, 30)
            else if (BMI<30) {
                printf("\tThis indicates that your weight is in the OVERWEIGHT category for adults of your height.\n\n");
                printf("\tPeople who are overweight or obese are at higher risk for chronic conditions\nsuch as highblood pressure, diabetes, and high cholesterol.\n");
                printf("\tAs an advise, you should try to avoid gaining addional weight.\n");
                printf("\tProper diet and exercise may help you lose some weight.\n");
                printf("\tIt may be hard but you'll sure be able to get there someday.\n");
                printf("\tWe believe in you. FIGHTING!");
                for (i=1; i<=150; i++) {
                    printf("*"); // for visual aesthetics
                }
                printf("\n\n");
            } 
            
            // The BMI for Obese lies in range [30, +∞)
            else {
                printf("\tThis indicates that your weight is in the OBESE category for adults of your height.\n\n");
                printf("\tIt's time to take this matter seriously as among all other categories,\n");
                printf("\tobese people have the highest risks in acquiring chronic condtions.\n");
                printf("\tWe advise that you should talk with your healthcare provider to determine appropriate ways to lose weight.\n");
                printf("\tYour future journey may be long and challenging but believe us you'll eventually reach your goal someday.\n");
                printf("\tJust Don't Give Up! Don't Lose Hope! Keep on Working Hard! FIGHTING!\n\n");
                for (i=1; i<=150; i++) {
                    printf("*"); // for visual aesthetics
                }
                printf("\n\n");
            }

            // After displaying the results, ask the user if he/she still wants to use the program
            while (exit == 'x') {
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
                // resets values for the variables that hold vital loops in our program
                weight_kg = 0;
                height_cm = 0;
                weight_lb = 0;
                height_ft = 0;
                height_in = 0;
                exit = 'x';

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
        }

        // resets the value of BMI variable
        BMI = 0;

    } while (exit == 'x');

    return 0;
}

// Gabinete, Keith Ginoel S. (2020-03670)
// Date Created: August 18, 2021

// Module 5 exercise
// This C program creates a collection of music playlists using structures and store the collected data outside of the program using files
// The allowed limits for the number of playlists/songs that can be stored is 10
// This program will loop until the user chooses the exit option in the main menu 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


struct song {
    char title[128];
    char artist[128];
    char album[128];
};

typedef struct {
    char name[128];
    int song_count;

    // declare the structure variable song
    struct song song_collection[10];

} playlist;


// define a function that asks for an input integer from the user
// this function will be used in various selection menus
int choiceInput (int starting_number, int options_limit, char what_to_enter[]) {
    char fgets_choice[32];
    char extra_char;
    int choice_number = -1;

    while (choice_number == -1) {
        printf("\nEnter %s: ", what_to_enter);
        fgets(fgets_choice, 32, stdin);

        // An input is invalid if the user enters a character or if he/she enters more than one integer
        if (sscanf(fgets_choice, " %d %c", &choice_number, &extra_char) != 1) {
            choice_number = -1;
            printf("\nTRY AGAIN: Invalid input! [Must input one integer only]\n");
            continue;
        } 

        // check if the integer input is not negative or is not in the given range of options
        if (choice_number < starting_number) {
            choice_number = -1;
            printf("\nTRY AGAIN: Invalid Input! [Must be in the range of the given options]\n");
            continue;
        } else if (choice_number > options_limit) {
            choice_number = -1;
            printf("\nTRY AGAIN: Invalid Input! [Must be in the range of the given options]\n");
            continue;
        }
    }

    // return the validated input
    return choice_number;
}


// the function definition below trims a string input and removes all leading and trailing whitespaces in it
// I learned how to make this code work properly here <https://www.includehelp.com/code-snippets/trim-leading-and-trailing-whitespaces-using-c-program.aspx>
void trimInputString(char *fgets_input, char *target_storage) {
	char *find_last_nonwhitespace;
	// remove leading whitespaces
    // adjust the elements of the input string until index 0 occupies a valid non-whitespace character
	while(isspace(*fgets_input)) {
        fgets_input++;
    }

    // if the modified string contains no valid characters, terminate the function and do not pass the the modified string to the target string
	if (*fgets_input == 0) {
        return;
     }
		
	// remove trailing whitespaces
	find_last_nonwhitespace = fgets_input + strlen(fgets_input) - 1;
	while(find_last_nonwhitespace > fgets_input && isspace(*find_last_nonwhitespace)) {
        find_last_nonwhitespace--;
    }

	// replaces \n character by NULL character
	*(find_last_nonwhitespace+1) = 0;

    // store the final modified string to desired variable
	strcpy(target_storage,fgets_input);	  
}


// define a function that compares strings
// return 1 if their lowercase versions are equal
int areEqual (char *string_1, char *string_2, int length_1, int length_2) {
    // declare strings that will temporarily store modified strings
    char temp_1[128], temp_2[128];
    int i, j;

    // converts two strings to lowercase letters
    for (int i = 0; i<length_1; i++) {
        if (isalpha(string_1[i]) != 0) {
            temp_1[i] = tolower(string_1[i]);
        } else {
            temp_1[i] = string_1[i];
        }
    }
    temp_1[length_1] = '\0';

    for (j = 0; j<length_2; j++) {
        if (isalpha(string_2[j]) != 0) {
            temp_2[j] = tolower(string_2[j]);
        } else {
            temp_2[j] = string_2[j];
        }
    }
    temp_2[length_2] = '\0';

    // compare strings if they are equal or not
    if (strcmp(temp_1, temp_2) == 0) {
        return 1;
    } else {
        return 0;
    }
}


// define a function that adds one playlist to an array of playlist
void addPlaylist (playlist *playlist_collection, int *playlist_count) {
    // check if the number of playlists stored in a file already reached its limit of 10
    char playlist_name[128], playlist_name_trimmed[128];
    int i = 0, are_strings_equal = 0, length_1 = 0, length_2 = 0;

    if (*playlist_count < 10) {
        printf("\nEnter playlist name: ");
        fgets(playlist_name, 128, stdin);

        // trim the input and store it in the variable inside the playlist structure
        trimInputString(playlist_name, playlist_name_trimmed);

        for (i=0; i<*playlist_count && are_strings_equal !=1; i++) {
            length_1 = (int)strlen(playlist_name_trimmed);
            length_2 = (int)strlen(playlist_collection[i].name);

            are_strings_equal = areEqual(playlist_name_trimmed, playlist_collection[i].name, length_1, length_2);
        }

        if (are_strings_equal == 1) {
            printf("\n[Sorry, the playlist name you entered already exists]");
            printf("\n[Think of another playlist name and try again]\n");
            printf("\nFailed to add playlist !\n");
            printf("-----------------------------\n");
        } else {
            strcpy(playlist_collection[*playlist_count].name, playlist_name_trimmed);

            // increment the value of the original playlist counter by one
            *playlist_count+=1;

            printf("\nSuccessfully added playlist !\n");
            printf("-----------------------------\n");
        }

    } else { // if the number of playlists stored exceeded 10, then inform the user
        printf("\nSorry! You've already reached the maximum number of playlists that can be stored!\n");
        printf("-----------------------------\n");
    }

}


// define a function that adds song to the playlist
void addSong (playlist *playlist_collection, int *playlist_count) {
    int i, playlist_choice;
    char song_title[128], song_artist[128], song_album[128];

    // check if there is/are already stored playlist/s
    if (*playlist_count == 0) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        printf("\nTHE PLAYLISTS AVAILABLE ARE:\n");

        for (i=0; i<*playlist_count; i++) {
            printf("   [%d] %s\n", i, playlist_collection[i].name);
        }

        // ask a choice input from the user
        playlist_choice = choiceInput(0, *playlist_count-1, "playlist number");

        // check if there is/are already stored song/s
        if (playlist_collection[playlist_choice].song_count<10) {
            // ask for the title of the song
            printf("\nEnter song title: ");
            fgets(song_title, 128, stdin);
            trimInputString(song_title, playlist_collection[playlist_choice].song_collection[playlist_collection[playlist_choice].song_count].title);

            // ask for its artist[].
            printf("Enter song artist: ");
            fgets(song_artist, 128, stdin);
            trimInputString(song_artist, playlist_collection[playlist_choice].song_collection[playlist_collection[playlist_choice].song_count].artist);

            // ask for the name of the album it belongs to
            printf("Enter song album: ");
            fgets(song_album, 128, stdin);
            trimInputString(song_album, playlist_collection[playlist_choice].song_collection[playlist_collection[playlist_choice].song_count].album);

            // update the value of song_count (member of playlist)
            playlist_collection[playlist_choice].song_count++;

            printf("\nSuccessfully added song to playlist !\n");
            printf("-----------------------------\n"); 
        } else {
            printf("\nSorry! You've already reached the maximum number of songs that can be stored!");
            printf("\n[Remove one song in the current playlist first then try again]\n");
            printf("-----------------------------\n"); 
        }
    }
}


// define a function that removes a song from a specific playlist
void removeSong(playlist *playlist_collection, int *playlist_count) {
    // check if there is/are already stored playlist/s
    if (*playlist_count == 0) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        int i, j, k, playlist_choice;

        printf("\nTHE PLAYLISTS AVAILABLE ARE:\n");

        for (i=0; i<*playlist_count; i++) {
            printf("   [%d] %s\n", i, playlist_collection[i].name);
        }

        // ask a choice input from the user
        playlist_choice = choiceInput(0, *playlist_count-1, "playlist number");

        // check if there is/are already stored song/s
        if (playlist_collection[playlist_choice].song_count == 0) {
            printf("\nPlaylist is still empty !\n");
            printf("-----------------------------\n"); 
        } else {
            int song_choice;

            printf("\nTHE SONGS AVAILABLE ARE:\n");
            for (k=0; k<playlist_collection[playlist_choice].song_count; k++) {
                printf("   [%d] %s by %s\n", k, playlist_collection[playlist_choice].song_collection[k].title, playlist_collection[playlist_choice].song_collection[k].artist);
            }

            // ask which song the user wishes to remove
            song_choice = choiceInput(0, playlist_collection[playlist_choice].song_count -1, "song number to delete");

            // adjust the values of the songs stored inside the song collection
            for  (j=song_choice; j<playlist_collection[playlist_choice].song_count-1; j++) {
                strcpy(playlist_collection[playlist_choice].song_collection[j].title, playlist_collection[playlist_choice].song_collection[j+1].title);
                strcpy(playlist_collection[playlist_choice].song_collection[j].artist, playlist_collection[playlist_choice].song_collection[j+1].artist);
                strcpy(playlist_collection[playlist_choice].song_collection[j].album, playlist_collection[playlist_choice].song_collection[j+1].album);
            }

            // empty data in the storage of previous last song
            strcpy(playlist_collection[playlist_choice].song_collection[playlist_collection[playlist_choice].song_count-1].title, "");
            strcpy(playlist_collection[playlist_choice].song_collection[playlist_collection[playlist_choice].song_count-1].artist, "");
            strcpy(playlist_collection[playlist_choice].song_collection[playlist_collection[playlist_choice].song_count-1].album, "");
            
            // update the value of song_count (member of playlist)
            playlist_collection[playlist_choice].song_count--;

            printf("\nSuccessfully deleted song !\n");
            printf("-----------------------------\n"); 
        }
    }
}


// define a function that prints data stored in a particular playlist
void viewPlaylist (playlist *playlist_collection, int *playlist_count) {
    int i, playlist_choice;
    char song_title[128], song_artist[128], song_album[128];

    // check if there is/are already stored playlist/s
    if (*playlist_count == 0) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        printf("\nTHE PLAYLISTS AVAILABLE ARE:\n");

        for (i=0; i<*playlist_count; i++) {
            printf("   [%d] %s\n", i, playlist_collection[i].name);
        }

        // ask a choice input from the user
        playlist_choice = choiceInput(0, *playlist_count-1, "playlist number");

        // check if there is/are already stored song/s
        if (playlist_collection[playlist_choice].song_count == 0) {
            printf("\nPlaylist is still empty !\n");
            printf("-----------------------------\n"); 
        } else {
            int song_index;

            printf("\nPLAYLIST: %s", playlist_collection[playlist_choice].name);
            printf("\nSONG COUNT: %d", playlist_collection[playlist_choice].song_count);
            
            for (song_index=0; song_index<playlist_collection[playlist_choice].song_count; song_index++) {
                printf("\n   SONG TITLE: %s", playlist_collection[playlist_choice].song_collection[song_index].title);
                printf("\n   SONG ARTIST: %s", playlist_collection[playlist_choice].song_collection[song_index].artist);
                printf("\n   SONG ALBUM: %s", playlist_collection[playlist_choice].song_collection[song_index].album);

                if (song_index!= playlist_collection[playlist_choice].song_count-1) {
                    printf("\n");
                }
            }
            printf("\n-----------------------------\n");
        }
    }  
}


// define a function that prints all the data (about playlists) stored in a file
void viewAll (playlist *playlist_collection, int *playlist_count) {
    int i, playlist_index;

    // check if there is/are already stored playlist/s
    if (*playlist_count == 0) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        for (playlist_index = 0; playlist_index<*playlist_count; playlist_index++) {
            int song_index;

            printf("\nPLAYLIST: %s", playlist_collection[playlist_index].name);
            printf("\nSONG COUNT: %d", playlist_collection[playlist_index].song_count);
            
            for (song_index=0; song_index<playlist_collection[playlist_index].song_count; song_index++) {
                printf("\n   SONG TITLE: %s", playlist_collection[playlist_index].song_collection[song_index].title);
                printf("\n   SONG ARTIST: %s", playlist_collection[playlist_index].song_collection[song_index].artist);
                printf("\n   SONG ALBUM: %s", playlist_collection[playlist_index].song_collection[song_index].album);

                if (song_index!= playlist_collection[playlist_index].song_count-1) {
                    printf("\n");
                }
            }

            if (playlist_index != *playlist_count -1) {
                printf("\n");
            }
        }
        printf("\n-----------------------------\n"); 
    }
}

// define a function that saves data to a file after the user chooses to terminate the program
void savePlaylist(playlist *playlist_collection, int *playlist_count) {
    int i = 0, j = 0;

    FILE *fp = fopen("playlists.txt", "w");

    if (*playlist_count == 0) {
        fprintf(fp, "Total Count of the Playlists \t\t%d \n", *playlist_count);
        printf("\nTHERE ARE NO DATA TO BE SAVED!");
    } else {
        
        fprintf(fp, "Total Count of the Playlists \t\t%d \n", *playlist_count);
        for (i=0; i<*playlist_count; i++) {
            fprintf(fp, "Name of Playlist %d \t\t\t%s \n", i+1, playlist_collection[i].name);
            fprintf(fp, "Number of Songs in Playlist %d \t\t%d \n", i+1, playlist_collection[i].song_count);
            for (j=0; j<playlist_collection[i].song_count; j++) {
                fprintf(fp, "Title of Song %d \t\t\t%s \n", j+1, playlist_collection[i].song_collection[j].title);
                fprintf(fp, "Artist of Song %d \t\t\t%s \n", j+1, playlist_collection[i].song_collection[j].artist);
                fprintf(fp, "Album of Song %d \t\t\t%s \n", j+1, playlist_collection[i].song_collection[j].album);
            }
        }

        printf("\nALL DATA HAVE BEEN SAVED SUCCESSFULLY!");
        fclose(fp);
    }
}


// define a function that trims a string from a file (removes whitespaces including the \n character and replaces last element with a NULL character)
void trimFileString (char *file_string, int remove_n_char) {
    int i, j=0;
    char temp[128];

    for (i=remove_n_char; file_string[i] != '\n'; i++) {
        temp[j] = file_string[i];
        j++;
    }
    temp[j] = '\0';

    trimInputString(temp, file_string);
}


// define function that loads data from a file right after the program has started
void loadPlaylist(playlist *playlist_collection, int *playlist_count) {
    // variables that will hold would-be disregarded strings/integers
    char garbage_string_1[10], garbage_string_2[10], garbage_string_3[10], garbage_string_4[10], garbage_string_5[10];
    int garbage_integer;

    // variables to be validly stored
    char playlist_name[128], song_title[128], song_artist[128], song_album[128];
    int i, j, song_count;

    FILE *fp = fopen("playlists.txt", "r");

    // check if the file playlists.txt exists
    if (fp == NULL) {
        printf("File to be loaded - \"playlists.txt\" - does not exist!\n");
    } else {
        fscanf(fp, "%s %s %s %s %s %d \n", garbage_string_1, garbage_string_2, garbage_string_3, garbage_string_4, garbage_string_5, playlist_count);
        if (*playlist_count == 0) {
            printf("Loaded file is empty!\n");
        } else {
            for (i=0; i<*playlist_count; i++) {
                fgets(playlist_name, 128, fp);
                trimFileString(playlist_name, 19);
                strcpy(playlist_collection[i].name, playlist_name);

                fscanf(fp, "%s %s %s %s %s %d %d \n", garbage_string_1, garbage_string_2, garbage_string_3, garbage_string_4, garbage_string_5, &garbage_integer, &song_count);
                playlist_collection[i].song_count = song_count;
                if (song_count == 0) {
                    // do nothing
                } else {
                    for (j=0; j<song_count; j ++) {
                        fgets(song_title, 128, fp);
                        trimFileString(song_title, 16);
                        strcpy(playlist_collection[i].song_collection[j].title, song_title);

                        fgets(song_artist, 128, fp);
                        trimFileString(song_artist, 17);
                        strcpy(playlist_collection[i].song_collection[j].artist, song_artist);

                        fgets(song_album, 128, fp);
                        trimFileString(song_album, 16);
                        strcpy(playlist_collection[i].song_collection[j].album, song_album);
                    }
                }
            }
            printf("Successfully loaded data !\n");
        }
    }
}


// start of the main program
int main () {
    int choice, playlist_count = 0, song_count = 0, exit = 0;
    playlist playlist_collection[10];

    loadPlaylist(playlist_collection, &playlist_count);
    while (!exit) {
        printf("\n======= MENU =======");
        printf("\n[1] Add Playlist");
        printf("\n[2] Add Song to Playlist");
        printf("\n[3] Remove Song from Playlist");
        printf("\n[4] View a Playlist");
        printf("\n[5] View All Data");
        printf("\n[6] Exit\n");

        choice = choiceInput(1, 6, "choice");

        switch (choice) {
            case 0:
                break;
            case 1:
                addPlaylist(playlist_collection, &playlist_count);
                break;
            case 2:
                addSong(playlist_collection, &playlist_count);
                break;
            case 3:
                removeSong(playlist_collection, &playlist_count);
                break;
            case 4:
                viewPlaylist(playlist_collection, &playlist_count);
                break;
            case 5:
                viewAll(playlist_collection, &playlist_count);
                break;

            // if choice == 6;
            default: 
                savePlaylist(playlist_collection, &playlist_count);
                // terminates the program
                exit = 1;
        }
    } 
    
    if (exit == 1) {
        printf("\n-----------------------------\n");
        printf("\nThank you for using our program!\nBye!\n");
    }
        
    return 0;
} // end of program

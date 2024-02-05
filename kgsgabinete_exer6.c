// Gabinete, Keith Ginoel S. (2020-03670)
// Date Created: August 18, 2021

// Module 6 exercise
// This C program creates a collection of music playlists using linked lists and store the collected data outside of the program using files
// The allowed limits for the number of playlists/songs that can be stored is 10
// This program will loop until the user chooses the exit option in the main menu
// This porgram automatically sorts data in ascending order (alphabetically/numerically)

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
struct song {
    char title[128];
    char artist[128];
    char album[128];
};

typedef struct {
    char name[128];
    int songCount;

    // declare the structure variable song
    struct song song_collection[10];

} playlist;
*/

typedef struct song_tag {
    char title [20];
    char artist [20];
    char album [20];
    struct song_tag * nextSong;
} song;

typedef struct playlist_tag {
    char name [50];
    int songCount;
    song * songHead;
    
    struct playlist_tag * next;
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


// define a function that adds one playlist to an array of playlist
// maintain sorting (alphabetical) characteristics of the playlist linked list
void addPlaylist (playlist **head, int *playlist_count) {
    char playlist_name[50], playlist_name_trimmed[50];
    int i = 0;

    // check if the number of playlists stored in a file already reached its limit of 10
    if (*playlist_count < 10) {
        printf("\nEnter playlist name: ");
        fgets(playlist_name, 50, stdin);

        // trim the input
        trimInputString(playlist_name, playlist_name_trimmed);

        // check if the entered playlist name already exists in the linked list
        playlist *temp = (*head);
        while (temp != NULL && strcasecmp(playlist_name_trimmed, temp->name) != 0) {
            temp = temp->next;
        }

        if (temp == NULL) {
            playlist *new = (playlist *) malloc (sizeof(playlist));
            strcpy(new->name, playlist_name_trimmed);
            new->songCount = 0;
            new->songHead = NULL;
            new->next = NULL;

            // insert at head
            if ((*head) == NULL || ((*head)!=NULL && ((int)strcasecmp(new->name, (*head)->name) < 0))) {
                new->next = (*head);
                (*head) = new;
            } else {
                // insert at middle/tail
                playlist *temp_2 = (*head);
                while (temp_2->next != NULL && strcasecmp(temp_2->next->name, new->name) < 0) {
                    temp_2 = temp_2->next;
                }

                // insert new playlist
                new->next = temp_2->next;
                temp_2->next = new;
            }
            // increment the value of the original playlist counter by one
            *playlist_count+=1;

            printf("\nSuccessfully added playlist !\n");
            printf("-----------------------------\n");
        } else {
            printf("\n[Sorry, the playlist name you entered already exists]");
            printf("\n[Think of another playlist name and try again]\n");
            printf("\nFailed to add playlist !\n");
            printf("-----------------------------\n");
        }


    } else { // if the number of playlists stored exceeded 10, then inform the user
        printf("\nSorry! You've already reached the maximum number of playlists that can be stored!\n");
        printf("-----------------------------\n");
    }
}


// define a function that adds song to the playlist
void addSong (playlist **head) {
    int i = 0;
    char playlist_name[50], playlist_name_trimmed[50], song_title[20], song_artist[20], song_album[20];

    // check if there is/are already stored playlist/s
    if ((*head) == NULL) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        printf("\nTHE PLAYLISTS AVAILABLE ARE:\n");

        playlist *temp = (*head);
        while (temp != NULL) {
            printf("   [%d] %s\n", i+1, temp->name);
            temp = temp->next;
            i ++;
        }
        printf("\n");

        // ask for a string input from the user
        printf("Enter playlist name : ");
        fgets(playlist_name, 50, stdin);
        trimInputString(playlist_name, playlist_name_trimmed);

        temp = (*head);
        // traverse through playlist linked list
        // check if the entered playlist name exists
        while (temp != NULL && strcasecmp(playlist_name_trimmed, temp->name) != 0) {
            temp = temp->next;
        }

        // check if the entered name of playlist matches one of the given availabe playlist names
        if (temp == NULL) {
            printf("\nInvalid playlist!\n");
            printf("-----------------------------\n");
        } else {
            // check if the number of songs that can be stored already reach its limit
            if (temp->songCount < 10) {
                
                // ask for the title of the song
                printf("\nEnter song title: ");
                fgets(song_title, 20, stdin);
                trimInputString(song_title, song_title);

                // ask for its artist
                printf("Enter song artist: ");
                fgets(song_artist, 20, stdin);
                trimInputString(song_artist, song_artist);

                // ask for the name of the album it belongs to
                printf("Enter song album: ");
                fgets(song_album, 20, stdin);
                trimInputString(song_album, song_album);

                song *new_song = (song *) malloc (sizeof(song));
                strcpy(new_song->title, song_title);
                strcpy(new_song->artist, song_artist);
                strcpy(new_song->album, song_album);
                new_song->nextSong = NULL;

                // insert at head
                if (temp->songHead == NULL || ( temp->songHead !=NULL && strcasecmp(new_song->title, temp->songHead->title) < 0)) {
                    new_song->nextSong = temp->songHead;
                    temp->songHead = new_song;
                } else {
                    // insert at middle/tail
                    song *temp_song = temp->songHead;

                    while (temp_song->nextSong != NULL && strcasecmp(temp_song->nextSong->title, new_song->title) < 0) {
                        temp_song = temp_song->nextSong;
                    }

                    // insert new song
                    new_song->nextSong = temp_song->nextSong;
                    temp_song->nextSong = new_song;
                }
                // increment the value of the original playlist counter by one
                temp->songCount+=1;

                printf("\nSuccessfully added song to playlist !\n");
                printf("-----------------------------\n"); 

            } else {
                printf("\nSorry! You've already reached the maximum number of songs that can be stored!");
                printf("\n[Remove one song in the current playlist first then try again]\n");
                printf("-----------------------------\n");
            }
        }
    }
}


// define a function that removes a song from a specific playlist
void removeSong(playlist **head) {
    int i = 0, j = 0;
    char playlist_name[50], playlist_name_trimmed[50], song_title[20], song_artist[20];

    // check if there is/are already stored playlist/s
    if ((*head) == NULL) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        printf("\nTHE PLAYLISTS AVAILABLE ARE:\n");

        playlist *temp = (*head);
        while (temp != NULL) {
            printf("   [%d] %s\n", i+1, temp->name);
            temp = temp->next;
            i ++;
        }
        printf("\n");

        // ask for a string input from the user
        printf("Enter playlist name : ");
        fgets(playlist_name, 50, stdin);
        trimInputString(playlist_name, playlist_name_trimmed);

        temp = (*head);
        // traverse through playlist linked list
        // check if the entered playlist name exists
        while (temp != NULL && strcasecmp(playlist_name_trimmed, temp->name) != 0) {
            temp = temp->next;
        }

        // check if the entered name of playlist matches one of the given availabe playlist names
        if (temp == NULL) {
            printf("\nInvalid playlist !\n");
            printf("-----------------------------\n");
        } else {
            // check if there are songs to be deleted
            if (temp->songCount == 0) {
                printf("\nPlaylist is still empty !\n");
                printf("-----------------------------\n"); 
            } else {
                song *temp_song = temp->songHead;
                j = 0;
                // traverse through songs linked list
                while (temp_song != NULL) {
                    printf("   [%d] %s by %s\n", j+1, temp_song->title, temp_song->artist);
                    temp_song = temp_song->nextSong;
                    j ++;
                }
                printf("\n");

                printf("Enter song title to delete :");
                fgets(song_title, 20, stdin);
                trimInputString(song_title, song_title);

                printf("Enter song artist to delete :");
                fgets(song_artist, 20, stdin);
                trimInputString(song_artist, song_artist);
                
                song *song_head = temp->songHead; // points to the first element of the songs linked list
                song *del = temp->songHead;
                while (del != NULL && (strcasecmp(song_title, del->title)!=0 && strcasecmp(song_artist, del->artist) != 0)) {
                    del = del->nextSong;
                }

                // check if the song specified by the user matches one of the given options
                if (del == NULL) {
                    printf("\nSong not found!\n");
                    printf("-----------------------------\n"); 
                } else {
                    // delete at head
                    if (del == song_head) {
                        song_head = song_head->nextSong;
                        free(del);
                    } else {
                        // delete at middle/tail
                        temp_song = temp->songHead; // reuse temp_song

                        while (temp_song->nextSong != del) {
                            temp_song = temp_song->nextSong;
                        }

                        temp_song->nextSong = del->nextSong;
                        free(del);
                    }
                    // update the value of songCount (member of playlist)
                    temp->songCount--;

                    printf("\nSuccessfully deleted song !\n");
                    printf("-----------------------------\n"); 
                }
            }
        }
    }
}


// define a function that prints data stored in a particular playlist
void viewPlaylist (playlist *head) {
    int i = 0;
    char playlist_name[50], playlist_name_trimmed[50];

    // check if there is/are already stored playlist/s
    if (head == NULL) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {
        printf("\nTHE PLAYLISTS AVAILABLE ARE:\n");

        playlist *temp = head;
        while (temp != NULL) {
            printf("   [%d] %s\n", i+1, temp->name);
            temp = temp->next;
            i ++;
        }
        printf("\n");

        // ask for a string input from the user
        printf("Enter playlist name : ");
        fgets(playlist_name, 50, stdin);
        trimInputString(playlist_name, playlist_name_trimmed);

        // traverse through playlist linked list
        // check if the entered playlist name exists
        while (head != NULL && strcasecmp(playlist_name_trimmed, head->name) != 0) {
            head = head->next;
        }

        // check if the entered name of playlist matches one of the given availabe playlist names
        if (head == NULL) {
            printf("\nInvalid playlist !\n");
            printf("-----------------------------\n");
        } else {
            // check if there are songs to be shown
            if (head->songCount == 0) {
                printf("\nPlaylist is still empty !\n");
                printf("-----------------------------\n"); 
            } else {
                printf("\nPLAYLIST: %s", head->name);
                printf("\nSONG COUNT: %d", head->songCount);
                
                song *head_song = head->songHead;
                while (head_song != NULL) {
                    printf("\n   SONG TITLE: %s", head_song->title);
                    printf("\n   SONG ARTIST: %s", head_song->artist);
                    printf("\n   SONG ALBUM: %s", head_song->album);

                    if (head_song->nextSong != NULL) {
                        printf("\n");
                    }
                    head_song = head_song->nextSong;
                }
                printf("\n-----------------------------\n");
            } 
        }
    }  
}


// define a function that prints all the data (about playlists) stored in a file
void viewAll (playlist *head) {
    // check if there is/are already stored playlist/s
    if (head == NULL) {
        printf("\nThere are no playlists yet!\n");
        printf("-----------------------------\n");
    } else {

        // traverse through playlist linked list
        // check if the entered playlist name exists
        while (head!=NULL) {
            printf("\nPLAYLIST: %s", head->name);
            printf("\nSONG COUNT: %d", head->songCount);

            song *head_song = head->songHead;
            while (head_song != NULL) {
                printf("\n   SONG TITLE: %s", head_song->title);
                printf("\n   SONG ARTIST: %s", head_song->artist);
                printf("\n   SONG ALBUM: %s", head_song->album);

                if (head_song->nextSong != NULL) {
                    printf("\n");
                }
                head_song = head_song->nextSong;
            }

            if (head->next != NULL) {
                printf("\n");
            }

            head = head->next;
        }
        printf("\n-----------------------------\n"); 
    }
}


// define a function that saves data to a file after the user chooses to terminate the program
void savePlaylist(playlist *head, int *playlist_count) {
    int i, j;

    FILE *fp = fopen("playlists.txt", "w");
    if (head == NULL) {
        printf("\nTHERE ARE NO DATA TO BE SAVED!");
        fprintf(fp, "Total Count of the Playlists \t\t%d \n", *playlist_count);

    } else {
        fprintf(fp, "Total Count of the Playlists \t\t%d \n", *playlist_count);

        i = 0;
        while (head != NULL) {
            fprintf(fp, "Name of Playlist %d \t\t\t%s \n", i+1, head->name);
            fprintf(fp, "Number of Songs in Playlist %d \t\t%d \n", i+1, head->songCount);

            song *head_song = head->songHead;
            j= 0;
            while (head_song != NULL) {
                fprintf(fp, "Title of Song %d \t\t\t%s \n", j+1, head_song->title);
                fprintf(fp, "Artist of Song %d \t\t\t%s \n", j+1, head_song->artist);
                fprintf(fp, "Album of Song %d \t\t\t%s \n", j+1, head_song->album);
                head_song = head_song->nextSong;
                j+=1;
            }
            head = head->next;
            i+=1;
        }
        printf("\nALL DATA HAVE BEEN SAVED SUCCESSFULLY!");
        
    }
    fclose(fp);
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
void loadPlaylist(playlist **head, int *playlist_count) {
    // variables that will hold would-be disregarded strings/integers
    char garbage_string_1[10], garbage_string_2[10], garbage_string_3[10], garbage_string_4[10], garbage_string_5[10];
    int garbage_integer;

    // variables to be validly stored
    char playlist_name[100], song_title[50], song_artist[50], song_album[50], song_count[50], playlist_counter[50];
    int i, j, songCount, new_playlist_count;

    FILE *fp = fopen("playlists.txt", "r");
    playlist *list = (playlist *) malloc (sizeof(playlist));
    list = NULL;

    (*head) = list;

    // check if the file playlists.txt exists
    if (fp == NULL) {
        printf("File to be loaded - \"playlists.txt\" - does not exist!\n");
    } else {
        fgets(playlist_counter, 50, fp);
        // checks if there is literally no indication that the file has data stored
        if (strlen(playlist_counter) <30) {
            printf("Loaded file is empty!\n");
            return;
        }
        trimFileString(playlist_counter, 30);
        *playlist_count = atoi(playlist_counter);

        // check if there are no data to be loaded
        if (*playlist_count == 0) {
            printf("Loaded file is empty!\n");
        } else {
            i = 0;
            playlist *temp = (*head); // trace the list
            while (i<*playlist_count) {
                // declare a variable that that stores data read from the file and link it later to list
                playlist *new = (playlist *) malloc (sizeof(playlist));
                
                // initialize values
                fgets(playlist_name, 100, fp);
                trimFileString(playlist_name, 19);
                strcpy(new->name, playlist_name);

                new->songCount = 0;
                new->songHead = NULL;
                new->next = NULL;

                playlist *temp_2 = (*head);
                // insert at head
                if ((*head) == NULL || ((*head)!=NULL && ((int)strcasecmp(new->name, (*head)->name) < 0))) {
                    new->next = (*head);
                    (*head) = new;
                } else {
                    // insert at middle/tail
                    while (temp_2->next != NULL && strcasecmp(temp_2->next->name, new->name) < 0) {
                        temp_2 = temp_2->next;
                    }

                    // insert new playlist
                    new->next = temp_2->next;
                    temp_2->next = new;
                }
                // assigns temp variable to the last added playlist
                // this temp variable will then be used to add songs in that playlist later on
                temp = new;

                // gets the number of songs in the given playlist
                fgets(song_count, 50, fp);
                trimFileString(song_count, 30);
                temp->songCount = atoi(song_count);
                
                j = 0;
                while (j < temp->songCount) {
                    song *new_song = (song *) malloc (sizeof(song));

                    // initialize values
                    fgets(song_title, 50, fp);
                    trimFileString(song_title, 16);
                    strcpy(new_song->title, song_title);

                    fgets(song_artist, 50, fp);
                    trimFileString(song_artist, 17);
                    strcpy(new_song->artist, song_artist);

                    fgets(song_album, 50, fp);
                    trimFileString(song_album, 16);
                    strcpy(new_song->album, song_album);

                    new_song->nextSong = NULL;

                    // insert at head
                    if (temp->songHead == NULL || ( temp->songHead !=NULL && strcasecmp(new_song->title, temp->songHead->title) < 0)) {
                        new_song->nextSong = temp->songHead;
                        temp->songHead = new_song;
                    } else {
                        // insert at middle/tail
                        song *temp_song = new->songHead;

                        while (temp_song->nextSong != NULL && strcasecmp(temp_song->nextSong->title, new_song->title) < 0) {
                            temp_song = temp_song->nextSong;
                        }

                        // insert new song
                        new_song->nextSong = temp_song->nextSong;
                        temp_song->nextSong = new_song;
                    }
                    // updates the value of the conditional variable
                    j+=1;
                }
                
                // updates the value of the conditional variable
                i+=1;
            }
            printf("Successfully loaded data !\n");
        }
    }
}


// define a function that will free all memory slots used in certain variables during runtime
void deleteAll (playlist **head) {
    while ((*head) != NULL) {
        playlist *temp = (*head);
        (*head) = (*head)->next;
        free(temp);
    }
}


// start of the main program
int main () {
    // head pointer traces elements of the node
    struct playlist_tag *head = NULL;

    int choice, playlist_count = 0, exit = 0;

    loadPlaylist(&head, &playlist_count);
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
                addPlaylist(&head, &playlist_count);
                break;
            case 2:
                addSong(&head);
                break;
            case 3:
                removeSong(&head);
                break;
            case 4:
                viewPlaylist(head);
                break;
            case 5:
                viewAll(head);
                break;

            // if choice == 6;
            default: 
                savePlaylist(head, &playlist_count);
                deleteAll(&head);
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

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"


#define NUM_ARGS 2
#define USAGE "%s <database.dat>\n"


/***********************************************
 Description : Program that reads in a pipe-delimited database file
               and creates a list of entries.
 Arguments   : int argc - the number of arguments
               char* argv[1] - the file to be used
 Returns     : 
 Author      : 
 *************************************************/
int main(int argc,char* argv[])
{
    FILE* filePointer;
    char menuOpt = ' ';
    char* playerName;
    char findBuffer[80];
    player_t* head = NULL;
    player_t* currentPlayer;
    player_t** foundPlayer;
    player_t** foundPlayers = NULL;
    player_t** sortedArray = NULL;
    int numOfPlayers = -1;
    char endOfArray = 0;
    
    //Too few argument error
    if (argc < NUM_ARGS)
    {
        fprintf(stderr, "Too few arguments\n");
        fprintf(stdout, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    // File doesn't exist error
    filePointer = fopen(argv[1], "rb");
    if (errno)
    {
        fprintf(stderr, "File doesn't exist\n");
        fprintf(stdout, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* 
    *  While we've not read to the end of our file
    *  We'll parse a line into a player struct as the current player
    *  The current player will then have a pointer to the previous player
    *  And the current will be made the new "head"
    */
    while(!feof(filePointer))
    {
        numOfPlayers++;
        currentPlayer = parsePlayer(filePointer);
        currentPlayer->nextPlayer = head;
        head = currentPlayer;        
    }
    fclose(filePointer);
    
    // While the user hasn't hit q for quit to leave the menu, repeat the menu
    while(menuOpt != 'q')
    {
        fprintf(stdout,"Enter:\n");
        fprintf(stdout,"\tf to find players by last name\n");
        fprintf(stdout,"\tp to print all players sorted by name\n");
        fprintf(stdout,"\tq to quit\n");
        fprintf(stdout,">");
        
        // Get user input and eat the newline character
        menuOpt = fgetc(stdin);
        getc(stdin);
        
        
        switch (menuOpt)
        {
            // Find option
            case 'f':
            {
                fprintf(stdout,"\nEnter Last Name:\n");
                fprintf(stdout,">");

                // Gets input from the user, tokenizes it to remove the new line
                // and duplicates it so that it is allocated.
                fgets(findBuffer, 80, stdin);
                playerName = safestrdup(strtok(findBuffer,"\n"));               
                fprintf(stdout,"\n");
                
                // If we don't have a sorted array of entries, do a
                // linear search
                if(!sortedArray)
                {
                    foundPlayers = findPlayer(playerName,head);
                    // If we found players matching the name, we want to print 
                    // them, otherwise we want to print that no players were 
                    // found.
                    if(foundPlayers)
                    {
                        for(int i = 0; foundPlayers[i]; i++)
                        {
                            
                            printPlayer(stdout,(player_t*)foundPlayers[i]);
                        }
                        
                        // After printing, we want to free the array of players
                        // And set it to null, so we don't try to use it again.
                        free(foundPlayers);
                        foundPlayers = NULL;
                    }
                    else
                    {
                        fprintf(stdout,"No players with that name.\n\n");
                    }
                    // Also free the name we allocated space for.
                    free(playerName);
                }
                
                // Else we do have a sorted list, so we can do a binary search of
                // the player we're looking for
                else
                {
                   if((foundPlayer = 
                       getFirstMatch(playerName, sortedArray, numOfPlayers))) 
                   {
                       // While the current player has the last name we're
                       // looking for, print it out
                       while(!strcmp((*foundPlayer)->nameLast,playerName) 
                             && !endOfArray)
                       {
                           printPlayer(stdout,*(foundPlayer));
                           // Boundary case is if we hit the end of the array,
                           // we don't want to step past the end of the array or
                           // will SEGV
                           if(foundPlayer == (sortedArray + numOfPlayers -1))
                           {
                               endOfArray = 1;
                           }
                           else
                           {
                               foundPlayer++;
                           }
                       }
                       endOfArray = 0;
                   }
                   else
                   {
                       fprintf(stdout,"No players with that name.\n\n");
                   }
                }
                break;
            }
            
            // Print option
            case 'p':
            {
                // If the array isn't sorted, we want to sort it and save it
                // So next time we use it, its already sorted.
                if(!sortedArray)
                {
                   sortedArray = sortArray(numOfPlayers,head);        
                }
                
                // Iterates through the array of players, which is now sorted 
                // alphabetcially by last name, then first name.
                for(int i = 0; i < numOfPlayers; i++)
                {
                    printPlayer(stdout,(player_t*)sortedArray[i]);
                }
                break;
            }
            
            // Quit option
            case 'q':
            {
                break;
            }
            
            // Any other entry
            default:
            {
                fprintf(stdout,"<%c> is not a valid option\n",menuOpt);
                break;
            }
        }
    }  

    return EXIT_SUCCESS;
}




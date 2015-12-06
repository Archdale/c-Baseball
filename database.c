#include "definitions.h"

#define NUM_ARGS 2
#define USAGE "%s <database.dat>\n"
#define PROG_NAME argv[0]
#define OUTPUT_LOC stdout

/***********************************************
 Description : Program that reads in a pipe-delimited database file
               and creates a list of entries.
 Arguments   : argv[1] - the file to be used
 Returns     : 
 Author      : 
 *************************************************/
int main(int argc,char* argv[])
{
    char menuOpt = ' ';
    player_t* head = NULL;
    player_t* currentPlayer;
    player_t** sortedArray = NULL;
    int numOfPlayers = -1;
    
    //Too few argument error
    if (argc < NUM_ARGS)
    {
        fprintf(stderr, "Too few arguments\n");
        fprintf(stdout, USAGE, PROG_NAME);
        exit(EXIT_FAILURE);
    }

    // File doesn't exist error
    FILE* file = fopen(argv[1], "rb");
    if (errno)
    {
        fprintf(stderr, "File doesn't exist\n");
        fprintf(stdout, USAGE, PROG_NAME);
        exit(EXIT_FAILURE);
    }
    
    /* 
    *  While we've not read to the end of our file
    *  We'll parse a line into a player struct as the current player
    *  The current player will then have a pointer to the previous player
    *  And the current will be made the new "head"
    */
    while(!feof(file))
    {
        numOfPlayers++;
        currentPlayer = parsePlayer(file);
        currentPlayer->nextPlayer = head;
        head = currentPlayer;        
    }
    fclose(file);
    
    while(menuOpt != 'q')
    {
        fprintf(stdout,"Enter:\n");
        fprintf(stdout,"\tf to find players by name\n");
        fprintf(stdout,"\tp to print all players sorted by name\n");
        fprintf(stdout,"\tq to quit\n");
        fprintf(stdout,">");
        menuOpt = fgetc(stdin);
        getc(stdin);
        
        switch (menuOpt)
        {
            case 'f':
            {
                if(sortedArray==NULL)
                {
                   sortedArray = sortArray(numOfPlayers,head);
        
                }
                break;
            }
            case 'p':
            {
                if(sortedArray==NULL)
                {
                   sortedArray = sortArray(numOfPlayers,head);
        
                }
                printPlayer(OUTPUT_LOC,numOfPlayers,sortedArray);
                break;
            }
            case 'q':
            {
                break;
            }
            default:
            {
                fprintf(stdout,"<%c> is not a valid option\n",menuOpt);
                break;
            }
        }
    }
    
    // Prints the database out in reverse order from the way it was read
    

    return EXIT_SUCCESS;
}


player_t** sortArray(int numOfPlayers, player_t* player)
{
    player_t** sortedArray;
    //int position = 0;
    
    sortedArray = malloc(sizeof(player_t*)*numOfPlayers);
    
    if(!sortedArray)
    {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    
    //Skip the null that starts the linked list
    //player = player->nextPlayer;
    for(int i = 0; i < (numOfPlayers); i++)
    {
        player = player->nextPlayer;
        sortedArray[i] = player;        
    }
    
    /*for(int i = 0; i < (numOfPlayers-1); i++)
    {
        fprintf(stdout,"%s %s\n",(sortedArray[i])->nameFirst,(sortedArray[i])->nameLast);
    }*/
    
    qsort(sortedArray,numOfPlayers,sizeof(player_t*), playerCompare);
    
    return sortedArray;
}


int playerCompare(const void* p1, const void* p2)
{
    int comparison;
    if(!(comparison = strcmp((*(player_t**)p1)->nameLast,(*(player_t**)p2)->nameLast)))
    {
        comparison = strcmp((*(player_t**)p1)->nameFirst,(*(player_t**)p2)->nameFirst);
    }
    
    return comparison;
}

/***********************************************
 Description : Reads in a line of a baseball pipe-delimited
               baseball database, parsing the values to a struct
               representing a player.
 Arguments   : file - the file being parsed
 Returns     : player_t* - a pointer to the player struct that the
               data was read into
 Author      : 
 *************************************************/
player_t* parsePlayer(FILE* file)
{   
    char* endptr;
    
    // Buffer to hold the line read
    char buffer[1024];
    
    // Making room for the player struct, while making sure that we
    // didn't run out of memmory
    player_t* player;        
    player = malloc(sizeof(player_t));
    if(player==NULL)
    {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    
    // Read in a line for parsing
    fgets(buffer,sizeof(buffer),file);

    // Check for end of file here, as the previous fgets may have tripped it
    if(!feof(file))
    {
        /*
         * The first four entries in the database are related to database
         * IDs from the database that the file was pulled from
         * They're tokenized but not stored.
         */
        strtok(buffer, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
            
        // Birthday parse
        player->birthYear = strtol(strtok(NULL, "|"),&endptr,10);
        player->birthMonth = strtol(strtok(NULL, "|"),&endptr,10); 
        player->birthDay = strtol(strtok(NULL, "|"),&endptr,10);
        
        // Birth location parse
        player->birthCountry = safestrdup(strtok(NULL,"|"));
        player->birthState = safestrdup(strtok(NULL,"|"));
        player->birthCity = safestrdup(strtok(NULL,"|"));
        
        // Death day parse
        player->deathYear = strtol(strtok(NULL, "|"),&endptr,10);
        player->deathMonth = strtol(strtok(NULL, "|"),&endptr,10); 
        player->deathDay = strtol(strtok(NULL, "|"),&endptr,10); 
        
        // Death location parse
        player->deathCountry=safestrdup(strtok(NULL,"|"));
        player->deathState=safestrdup(strtok(NULL,"|"));
        player->deathCity=safestrdup(strtok(NULL,"|"));
        
        // Name related parses
        player->nameFirst = safestrdup(strtok(NULL,"|"));
        player->nameLast = safestrdup(strtok(NULL,"|"));
        player->nameNote = safestrdup(strtok(NULL,"|"));
        player->nameGiven = safestrdup(strtok(NULL,"|"));
        player->nameNick = safestrdup(strtok(NULL,"|"));
        
        // Weight and height parse
        player->weight = (int)strtol(strtok(NULL, "|"),&endptr,10);
        player->height = strtof(strtok(NULL, "|"),&endptr);

        // Handedness parse
        player->bats = ((char*)strtok(NULL,"|"))[0];
        player->throws = ((char*)strtok(NULL,"|"))[0];
    
        // Debut/Final Game, and college parse
        player->debut = safestrdup(strtok(NULL,"|"));
        player->finalGame = safestrdup(strtok(NULL,"|"));
        player->college = safestrdup(strtok(NULL,"|"));
    }
    return player;
}


/***********************************************
 Description : Prints out a database of player entries
 Arguments   : output - where to print the database entries
               player - the first entry in the database
 Returns     : 
 Author      : 
 *************************************************/
void printPlayer(FILE* output, int numOfPlayers, player_t** sortedArray)
{
    // While the current player has a next player, we'll print the
    // values of that player struct.
    // It only prints the values that have valid information, other
    // than name, which always prints.
    for(int i = 0; i < numOfPlayers; i++)
    {
        // Name related prints
        fprintf(output,"%-13.13s: %s %s\n","Name",sortedArray[i]->nameFirst,
                                                  sortedArray[i]->nameLast);
        if(sortedArray[i]->nameGiven[0] != ' ')
        {
            fprintf(output,"%-13.13s: %s\n","Given Name",sortedArray[i]->nameGiven);
        }
        if(sortedArray[i]->nameNick[0] != ' ')
        {
            fprintf(output,"%-13.13s: %s\n", "Nickname(s)",sortedArray[i]->nameNick);
        }
        if(sortedArray[i]->nameNote[0] != ' ')
        {
            fprintf(output,"%-13.13s: %s\n", "Name notes",sortedArray[i]->nameNote);
        }
        
        // Statistical data prints
        if(sortedArray[i]->height)
        {
            fprintf(output,"%-13.13s: %.1f\n","Height",sortedArray[i]->height);
        }
        if(sortedArray[i]->weight)
        {
            fprintf(output,"%-13.13s: %d\n","Weight",sortedArray[i]->weight);
        }
        if(sortedArray[i]->bats != ' ')
        {
            fprintf(output,"%-13.13s: %c\n","Bats",sortedArray[i]->bats);
        }
        if(sortedArray[i]->throws != ' ')
        {
            fprintf(output,"%-13.13s: %c\n","Throws",sortedArray[i]->throws);
        }
        
        // Birthday related prints
        if(sortedArray[i]->birthMonth != 0)
        {
            fprintf(output,"%-13.13s: %d/%d/%d\n","Birthday"
                                                 ,sortedArray[i]->birthMonth
                                                 ,sortedArray[i]->birthDay
                                                 ,sortedArray[i]->birthYear);
            fprintf(output,"%-13.13s: %s, %s, %s\n","Born in"
                                                   ,sortedArray[i]->birthCity
                                                   ,sortedArray[i]->birthState
                                                   ,sortedArray[i]->birthCountry);
        }
        
        // Death day related prints
        if(sortedArray[i]->deathMonth != 0)
        {
            fprintf(output,"%-13.13s: %d/%d/%d\n","Died on"
                                                 ,sortedArray[i]->deathMonth
                                                 ,sortedArray[i]->deathDay
                                                 ,sortedArray[i]->deathYear);
            fprintf(output,"%-13.13s: %s, %s, %s\n","Died in"
                                                   ,sortedArray[i]->deathCity
                                                   ,sortedArray[i]->deathState
                                                   ,sortedArray[i]->deathCountry);
        }
        
        // College, debut and final game prints
        if(sortedArray[i]->college[0] != ' ')
        {
            fprintf(output,"%-13.13s: %s\n","College",sortedArray[i]->college);
        }
        if(sortedArray[i]->debut[0] != ' ')
        {
            fprintf(output,"%-13.13s: %s\n","Debut Game",sortedArray[i]->debut);
        }
        if(sortedArray[i]->finalGame[0] != ' ')
        {
            fprintf(output,"%-13.13s: %s\n","Final Game",sortedArray[i]->finalGame);
        }
        fprintf(output,"\n");
    }
}

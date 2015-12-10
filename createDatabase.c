/***********************************************
 Description : Does strdup and checks for success.
 Arguments   : string - the string to be duplicated
 Returns     : char* - pointer to duplicated string
 Author      : 
 *************************************************/
char* safestrdup(const char* string)
{
    char* pointer;
    errno = 0;
    
    pointer = strdup(string);
    if(errno)
    {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    
    return pointer;
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
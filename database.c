#include "definitions.h"

#define NUM_ARGS 2
#define USAGE "%s <database.dat>\n"
#define PROG_NAME argv[0]
#define OUTPUT_LOC stdout


int main(int argc,char* argv[])
{

    player_t* head = NULL;
    player_t* currentPlayer;
    char ignore[1024];
    

    
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
    
    fgets(ignore,sizeof(ignore),file);
    
    while(!feof(file))
    {
        currentPlayer = parsePlayer(file);
        currentPlayer->nextPlayer = head;
        head = currentPlayer;
    }
    fclose(file);
    
    printPlayer(OUTPUT_LOC,head);

    return EXIT_SUCCESS;
}


player_t* parsePlayer(FILE* file)
{
    int birthYear = 0;
    int birthMonth = 0;
    int birthDay = 0;
    
    char* birthCountry = " ";
    char* birthState = " ";
    char* birthCity = " ";
     
    int deathYear = 0;
    int deathMonth = 0;
    int deathDay = 0;
     
    char* deathCountry = " ";
    char* deathState = " ";
    char* deathCity = " ";
     
    char* nameFirst = " ";
    char* nameLast = " ";
    char* nameNote = " ";
    char* nameGiven = " ";
    char* nameNick = " ";
     
    int weight = 0;
    float height = 0;
     
    char* bats = " ";
    char* throws = " ";
     
    char* debut = " ";
    char* finalGame = " ";
    char* college = " ";
    
    char* endptr;
    char buffer[1024];
    
    player_t* player;        
    player = malloc(sizeof(player_t));
    if(player==NULL)
    {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
       
    fgets(buffer,sizeof(buffer),file);

    if(!feof(file))
    {
        strtok(buffer, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
            
        birthYear = strtol(strtok(NULL, "|"),&endptr,10);
        player->birthYear = birthYear;
        birthMonth = strtol(strtok(NULL, "|"),&endptr,10); 
        player->birthMonth = birthMonth;
        birthDay = strtol(strtok(NULL, "|"),&endptr,10);
        player->birthDay = birthDay;
        
        birthCountry = strtok(NULL,"|");
        player->birthCountry = safestrdup(birthCountry);
        birthState = strtok(NULL,"|");
        player->birthState = safestrdup(birthState);
        birthCity = strtok(NULL,"|");
        player->birthCity = safestrdup(birthCity);
        
        deathYear = strtol(strtok(NULL, "|"),&endptr,10);
        player->deathYear = deathYear;
        deathMonth = strtol(strtok(NULL, "|"),&endptr,10); 
        player->deathMonth = deathMonth;
        deathDay = strtol(strtok(NULL, "|"),&endptr,10); 
        player->deathDay = deathDay;
        
        deathCountry = strtok(NULL,"|");
        player->deathCountry=safestrdup(deathCountry);
        deathState = strtok(NULL,"|");
        player->deathState=safestrdup(deathState);
        deathCity = strtok(NULL,"|");
        player->deathCity=safestrdup(deathCity);
        
        nameFirst = strtok(NULL,"|");
        player->nameFirst = safestrdup(nameFirst);
        nameLast = strtok(NULL,"|");
        player->nameLast = safestrdup(nameLast);
        nameNote = strtok(NULL,"|");
        player->nameNote = safestrdup(nameNote);
        nameGiven = strtok(NULL,"|");
        player->nameGiven = safestrdup(nameGiven);
        nameNick = strtok(NULL,"|");
        player->nameNick = safestrdup(nameNick);
        
        weight = (int)strtol(strtok(NULL, "|"),&endptr,10);
        player->weight = weight;
        height = strtof(strtok(NULL, "|"),&endptr);
        player->height = height;

        bats = strtok(NULL,"|");
        player->bats = safestrdup(bats);
        throws = strtok(NULL,"|");
        player->throws = safestrdup(throws);

        debut = strtok(NULL,"|");
        player->debut = safestrdup(debut);
        finalGame = strtok(NULL,"|");
        player->finalGame = safestrdup(finalGame);
        college = strtok(NULL,"|");
        player->college = safestrdup(college);
    }
    return player;
}


void printPlayer(FILE* output,player_t* player)
{
    while(NULL!=(player = player->nextPlayer))
    {
        fprintf(output,"%12.12s %s %s\n","Name:",player->nameFirst,player->nameLast);
        if(player->nameGiven[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n","Given Name:",player->nameGiven);
        }
        if(player->nameNick[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n", "Nickname(s):",player->nameNick);
        }
        if(player->nameNote[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n", "Name notes:",player->nameNote);
        }
        if(player->height)
        {
            fprintf(output,"%12.12s %.1f\n","Height:",player->height);
        }
        if(player->weight)
        {
            fprintf(output,"%12.12s %d\n","Weight:",player->weight);
        }
        if(player->bats[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n","Bats:",player->bats);
        }
        if(player->throws[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n","Throws:",player->throws);
        }
        if(player->birthMonth != 0)
        {
            fprintf(output,"%12.12s %d/%d/%d\n", "Birthday:",player->birthMonth,player->birthDay,player->birthYear);
            fprintf(output,"%12.12s %s, %s, %s\n","Born in:",player->birthCity,player->birthState,player->birthCountry);
        }
        if(player->deathMonth != 0)
        {
            fprintf(output,"%12.12s %d/%d/%d\n", "Died on:",player->deathMonth,player->deathDay,player->deathYear);
            fprintf(output,"%12.12s %s, %s, %s\n", "Died in:",player->deathCity,player->deathState,player->deathCountry);
        }
        if(player->college[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n","College:",player->college);
        }
        if(player->debut[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n","Debut Game:",player->debut);
        }
        if(player->finalGame[0] != ' ')
        {
            fprintf(output,"%12.12s %s\n","Final Game:",player->finalGame);
        }
        fprintf(output,"\n");
    }
}

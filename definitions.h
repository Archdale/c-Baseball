#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player player_t;

struct Player
{
    int birthYear;
    int birthMonth;
    int birthDay;
    
    char* birthCountry;
    char* birthState;
    char* birthCity;
    
    int deathYear;
    int deathMonth;
    int deathDay;
    
    char* deathCountry;
    char* deathState;
    char* deathCity;
    
    char* nameFirst;
    char* nameLast;
    char* nameNote;
    char* nameGiven;
    char* nameNick;
    
    int weight;
    float height;
    
    char* bats;
    char* throws;
    
    char* debut;
    char* finalGame;
    char* college;
    
    player_t* nextPlayer;
    
};

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

player_t* parsePlayer(FILE*);
void printPlayer(FILE*,player_t*);
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
    
    char bats;
    char throws;
    
    char* debut;
    char* finalGame;
    char* college;
    
    player_t* nextPlayer;
    
};

extern player_t* parsePlayer(FILE*);
void printPlayer(FILE*,int,player_t**);
player_t** sortArray(int, player_t*);
int playerCompare(const void*, const void*);
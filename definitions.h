#include <stdio.h>  //Needed for parsePlayer prototype, and other files

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

extern char* safestrdup(const char*);
extern player_t* parsePlayer(FILE*);
extern void printPlayer(FILE*,player_t*);
extern player_t** sortArray(int, player_t*);
extern int playerCompare(const void*, const void*);
extern player_t** findPlayer(char*, player_t*);
extern int playerCompareLast(const void*, const void*);
extern player_t** getFirstMatch(char*, player_t**, int);
#include <stdlib.h>
#include <string.h>
#include "definitions.h"


/***********************************************
 Description : Finds players matching a last name in a database
 Arguments   : player_t* player - the list of players to be searched
               char* name - the name being searched for
 Returns     : player_t** - an array of player pointers
 Author      : 
 *************************************************/
player_t** findPlayer(char* name, player_t* player)
{
    player_t** foundPlayers = NULL;
    int numFound = 0; 
    
    // While the next player isn't null, continue searching
    while((player = player->nextPlayer))
    {
        // If the last name of a player matches the name being searched for, we 
        // want to increase the counter for the number found, realloc enough
        // space for another entry, and put it in the array.
        if(!strcasecmp(player->nameLast,name))
        {
            numFound++;
            foundPlayers = realloc(foundPlayers, sizeof(player_t)*numFound);
            foundPlayers[numFound-1] = player;
        }
    }
    // If we found anything, we also want to null terminate the array, so we
    // have to make room for one more entry, and set it to null.
    if(numFound)
    {
        foundPlayers = realloc(foundPlayers,sizeof(player_t)*(numFound+1));
        foundPlayers[numFound] = NULL;
    }
    
    return foundPlayers;
}
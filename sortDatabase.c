#include <stdlib.h>
#include <string.h>
#include "definitions.h"


/***********************************************
 Description : Takes an array of players and sorts by name
 Arguments   : int numOfPlayers - the number of players in the linked list being
                                  passed
               player_t* player - the start of the linked list
 Returns     : player_t** - an array of pointers to players
 Author      : 
 *************************************************/
player_t** sortArray(int numOfPlayers, player_t* player)
{
    // Create and allocate the array for the sorted players
    // Also check to see if creating the space failed
    player_t** sortedArray; 
    sortedArray = malloc(sizeof(player_t*)*numOfPlayers);
    if(!sortedArray)
    {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    
    // For the number of players, we'll iterate through the linked list, copying
    // a pointer to each player in the order seen
    for(int i = 0; i < (numOfPlayers); i++)
    {
        player = player->nextPlayer;
        sortedArray[i] = player;        
    }
    
    // Sort the array of players by last name.  If last name is the same, then
    // sort by first name.
    qsort(sortedArray,numOfPlayers,sizeof(player_t*), playerCompare);
    
    return sortedArray;
}


/***********************************************
 Description : Compares the names of two players for ordering.
 Arguments   : void* p1 - the first player
               void* p2 - the second player
 Returns     : int - If 0, they're the same. If less than -1, then p1 is less
                     than p2. If greater than 1, then p1 is greater than p2.
 Author      : 
 *************************************************/
int playerCompare(const void* p1, const void* p2)
{
    int comparison;
    // If the last name is same, then compare the first names
    if(!(comparison = playerCompareLast(p1,p2)))
    {
        comparison = strcasecmp((*(player_t**)p1)->nameFirst,(*(player_t**)p2)->nameFirst);
    }
    
    return comparison;
}


/***********************************************
 Description : 
 Arguments   : 
               
 Returns     :
 Author      : 
 *************************************************/
int playerCompareLast(const void* p1, const void* p2)
{   
    return strcasecmp((*(player_t**)p1)->nameLast,(*(player_t**)p2)->nameLast);
}
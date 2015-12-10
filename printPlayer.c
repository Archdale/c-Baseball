#include "definitions.h"

#define FORMATPRINT(stream,title,data) {fprintf(stream,"%-13.13s: %s\n",title,data);}

/***********************************************
 Description : Prints out a player entry
 Arguments   : output - where to print the entry
               player - the player entry to print
 Returns     : 
 Author      : 
 *************************************************/
void printPlayer(FILE* output, player_t* player)
{
    // Name related prints
    fprintf(output,"%-13.13s: %s %s\n","Name",player->nameFirst,
                                              player->nameLast);
    if(player->nameGiven[0] != ' ')
    {       
        FORMATPRINT(output,"Given Name",player->nameGiven);
    }
    if(player->nameNick[0] != ' ')
    {
        FORMATPRINT(output,"Nickname(s)",player->nameNick);
    }
    if(player->nameNote[0] != ' ')
    {
        FORMATPRINT(output,"Name notes",player->nameNote);
    }
    
    // Statistical data prints
    if(player->height)
    {
        fprintf(output,"%-13.13s: %.1f\n","Height",player->height);
    }
    if(player->weight)
    {
        fprintf(output,"%-13.13s: %d\n","Weight",player->weight);
    }
    if(player->bats != ' ')
    {
        fprintf(output,"%-13.13s: %c\n","Bats",player->bats);
    }
    if(player->throws != ' ')
    {
        fprintf(output,"%-13.13s: %c\n","Throws",player->throws);
    }
    
    // Birthday related prints
    if(player->birthMonth)
    {
        fprintf(output,"%-13.13s: %d/%d/%d\n","Birthday"
                                             ,player->birthMonth
                                             ,player->birthDay
                                             ,player->birthYear);
        fprintf(output,"%-13.13s: %s, %s, %s\n","Born in"
                                               ,player->birthCity
                                               ,player->birthState
                                               ,player->birthCountry);
    }
    
    // Death day related prints
    if(player->deathMonth)
    {
        fprintf(output,"%-13.13s: %d/%d/%d\n","Died on"
                                             ,player->deathMonth
                                             ,player->deathDay
                                             ,player->deathYear);
        fprintf(output,"%-13.13s: %s, %s, %s\n","Died in"
                                               ,player->deathCity
                                               ,player->deathState
                                               ,player->deathCountry);
    }
    
    // College, debut and final game prints
    if(player->college[0] != ' ')
    {
        FORMATPRINT(output,"College",player->college);
    }
    if(player->debut[0] != ' ')
    {
        FORMATPRINT(output,"Debut Game",player->debut);
    }
    if(player->finalGame[0] != ' ')
    {
        FORMATPRINT(output,"Final Game",player->finalGame);
    }
    fprintf(output,"\n");

}
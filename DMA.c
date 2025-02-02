#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{

    char name[50]; //player name
    int points; //player points
}Player;

typedef struct{

    char teamName[50]; //Team name
    int playerCount; //number of players
    Player *players; //array of players
}Team;

/*
1.prompt the user for the team name and number of players
2.dynamically allocate memory for Team and players array
3.use a loop to get player names and points from the user
4.print the team information and each players details
5.free all the memory
*/


int main(void){
char tname[50]; //team name
char pname[50]; //player name 
int numPlayers; //number of players
int points; //points for each player
int numTeams;//number of teams

printf("How many teams: ");
scanf("%d",&numTeams);


Team *teams=malloc(numTeams * sizeof(Team));//create an array of teams

for(int i=0; i<numTeams;i++){
printf("\nEnter team %d name: ",i+1);
scanf("%s",tname);
printf("Enter number of players for team %d: ",i+1);
scanf("%d",&numPlayers);
strcpy(teams[i].teamName,tname);
teams[i].playerCount=numPlayers;

teams[i].players=malloc(numPlayers*sizeof(Player)); //create an array of players

for (int j=0;j<numPlayers;j++){

    printf("\nEnter player %d name: ",i+1);
    scanf("%s",pname);
    printf("Enter player %d points: ",i+1);
    scanf("%d",&points);
    strcpy(teams[i].players[j].name,pname);//store name for that player
    teams[i].players[j].points=points;//store points for that player

}

}


for(int i=0;i<numTeams;i++){
printf("\nTeam %d: %s",i+1,teams[i].teamName);
for(int j=0;j<teams[i].playerCount;j++){
    printf("\nPlayer %d: %s, Points: %d",i+1,teams[i].players[j].name,teams[i].players[j].points);
    
}
printf("\n");

}


for (int i=0;i<numTeams;i++){
    free(teams[i].players);
}

free(teams);

return 0;

}
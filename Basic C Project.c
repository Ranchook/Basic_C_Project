#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define TRUTH 1
#define FALSE 0
#define SIZE 80 

typedef struct {
	int day;
	int month;
	int year;
}Date;

typedef struct {
	int  id;
	char * name;
	int jersey_num;
	Date DOB;
}Player;

typedef struct {
	char *name;
	int max_players;
	int current_players;
	Player **players;
	int total_wins;
}Team;

void readPlayer(Player* );
void initTeam(Team*);
void addPlayer(Team*);

Team *maxSuccess(Team**, int);
Player** nameLikeA(Team*, int *);

int isBirthday(Date);
void printPlayer(Player);
void printTeam(Team);

void free_all(Team** teams, int size);


void main()
{
	int i, j, size;
	Team **Teams, *best;

	printf("Welcom to the fantasy league data\n");
	printf("How many teams are in your league?\n");
	scanf("%d", &size);
	assert(Teams = (Team*) malloc (size * sizeof(Team)));
	
	for (i = 0; i < size; i++)
	{
		printf("Registring team #%d:\n\n", i+1);
		Teams[i] = (Team*)malloc(sizeof(Team));
		initTeam(Teams[i]);
		for (j = 0; j <= i; j++)
		{
			if (i == j)
				continue;
			while (!strcmp(Teams[i]->name, Teams[j]->name))
			{
				printf("Sorry, but this team name is already taken, all other data was saved:\n");
				printf("please enter a new name:\n");
				fseek(stdin, 0, SEEK_END);
				gets(Teams[i]->name);
				j=0;
			}
		}
		printf("Please enter tha data of your 2 top players:\n");
		for (j = 0; j < 2; j++)
		{
			printf("Player #%d:\n", j+1);
			addPlayer(Teams[i]);
			Teams[i]->current_players++;
			printf("-------\n");
		}
		
		//allocating rest of unregistered players
		for (j; j < Teams[i]->max_players; j++)
		{
			assert(Teams[i]->players[j] = (Player*)malloc(sizeof(Player)));
			Teams[i]->players[j]->name = NULL;
		}
		
		printf("How many games did your team win?\n");
		scanf("%d", &Teams[i]->total_wins);
		printf("--------------------------\n");
	}
	
	printf("The registerd teams are:\n");
	for (i = 0; i < size; i++)
	{
		printf("Team #%d:\n", i+1);
		printTeam(*Teams[i]);
		printf("---------------\n");
	}
		
	printf("BREAKING NEWS!\n");
	printf("Due to a world pandemic, football leagues are cancelled world-wide!\n");
	printf("Unfortunately, this virtual made-up league was cancelled as well...\n");
	
	assert(best = (Team*) malloc(sizeof(Team)));
	best = maxSuccess(Teams, size-1);
	printf("The team with the most wins is: %s\n", best->name);
	printf("who have won %d matches\n", best->total_wins);
	printf("They have won the championsihp!!\n");
	
	free_all(Teams, size);
	//best was copied by address, so no need to free its name or players, only the team...
	free(best);
	printf("Good luck next year...\n");
}

void initTeam(Team* team)
{
	char team_name[SIZE];
	printf("Enter team name:");
	fseek(stdin, 0, SEEK_END);
	gets(&team_name);
	while (!strcmp(team_name, "Hapoel Haifa") || !strcmp(team_name, "hapoel haifa"))
	{
		printf("There is no hapoel in haifa!!\n");
		printf("enter a name of a proper team:\n");
		fseek(stdin, 0, SEEK_END);
		gets(&team_name);
	}
	
	while (!strcmp(team_name, "Maccabi Tel Aviv") || !strcmp(team_name, "maccabi tel aviv"))
	{
		printf("Maccabi is only in haifa!!\n");
		printf("enter a name of a proper team:\n");
		fseek(stdin, 0, SEEK_END);
		gets(&team_name);
	}
	//Those two while loops are whims of a Maccabi Haifa fan
	//and are not to be taken seriously

	assert(team->name = (Team*)malloc(sizeof(team_name)));
	strcpy(team->name, team_name);

	team->current_players = 0;
	printf("How many players are in the team?\n");
	printf("  ***please note that you must have at least 2 players...\n");
	scanf("%d", &team->max_players);
	while (team->max_players < 2)
	{
		printf("There's no 'I' in 'TEAM'...\n");
		printf("and there's no team with less than 2 players!\n");
		printf("so, how many players are on your team?\n");
		scanf("%d", &team->max_players);
	}
	assert(team->players = (Player*)malloc(team->max_players * sizeof(Player)));
}

void readPlayer(Player* player)
{
	char p_name[SIZE];
	printf("Please enter player name:\n");
	fseek(stdin, 0, SEEK_END);
	gets(&p_name);
	assert(player->name = (Player*)malloc(sizeof(p_name)));
	strcpy(player->name, p_name);
	printf("Please enter player id:\n");
	scanf("%d", &player->id);
	printf("Please enter player DoB:\n");
	printf("format: dd.mm.yyyy\n");

	scanf("%d.%d.%d", &player->DOB.day, &player->DOB.month, &player->DOB.year);
	//legality of Date of Birth (date is legal to the end  of 2020)
	while (player->DOB.year > 2020)
	{
		printf("This year hasn't happend yet!\n");
		printf("please enter a valid year!\n");	
		scanf("%d",&player->DOB.year);
	}
	while (player->DOB.month > 12)
	{
		printf("Monthes are 1-12!\n");
		printf("please enter a valid month!\n");
		scanf("%d", &player->DOB.month);
	}
	if (player->DOB.month == 1 || player->DOB.month == 3 || player->DOB.month == 5 || player->DOB.month == 7
		 || player->DOB.month == 8 || player->DOB.month == 10 || player->DOB.month == 12)
	{
		while (player->DOB.day > 31)
		{
			printf("boom\n");
			printf("Day number is invalid in this month\n");
			printf("please enter a valid day!\n");
			scanf("%d", &player->DOB.day);
		}
		
	}
	if (player->DOB.month == 4 || player->DOB.month == 6 || player->DOB.month == 9
		|| player->DOB.month == 11)
	{
		while (player->DOB.day > 30)
		{
			printf("Day number is invalid in this month\n");
			printf("please enter a valid day!\n");
			scanf("%d", &player->DOB.day);
		}
	}
	while (player->DOB.month == 2 && player->DOB.year % 4 != 0 && player->DOB.day > 28)
	{
		printf("Day number is invalid in this month\n");
		printf("please enter a valid day! (1-28)\n");
		scanf("%d", &player->DOB.day);
	}

	printf("Please enter player jersey number 1-99:\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%d", &player->jersey_num);
	while (player->jersey_num <= 0 || player->jersey_num>99)
	{
		printf("Applicable jersey numbers are 1-99\n");
		printf("Please enter an applicable jersey number:\n");
		scanf("%d", &player->jersey_num);
	}
}

void addPlayer(Team* team)
{
	if (team->current_players > team->max_players)
	{
		printf("The team is full...\n");
		return;
	}
	assert(team->players[team->current_players] = (Player*)malloc(sizeof(Player)));
	readPlayer(team->players[team->current_players]);
}

//There was no demand to call this function
Player** nameLikeA(Team* team, int* count)
{
	Player **Ateam;
	int i, size = *count;
	
	assert(Ateam = (Player*)malloc(sizeof(Player)));
	for (i = 0; i < team->current_players; i++)
	{
		if (team->players[i]->name[0] == 'a')
		{
			assert(Ateam[size] = (Player*)malloc(sizeof(Player)));
			Ateam[size] = team->players[i];
			size++;
		}
	}
	*count = size;
	return Ateam;
}

Team * maxSuccess(Team** teams, int size)
{
	if (!size)
		return teams[size];
	if (teams[size]->total_wins > maxSuccess(teams, size - 1)->total_wins)
		return teams[size];
	return teams[size - 1];
}

int isBirthday(Date d)
{
	time_t now = time(0);
	struct tm * ltm = localtime(&now);

	if (d.month == ltm->tm_mon + 1)
		if (d.day == ltm->tm_mday)
			return TRUTH;
	return FALSE;
}

void printPlayer(Player player)
{
	printf("	player name: %s\n", player.name);
	printf("	player id: %d\n", player.id);
	printf("	player jersey number: %d\n",player.jersey_num);
	printf("	player DoB: %d.%d.%d\n", player.DOB.day, player.DOB.month, player.DOB.year);
	if (isBirthday(player.DOB))
		printf("%s has a birthday today,\nhappy birthday!\n\n", player.name);
}

void printTeam(Team team) 
{
	int i;
	printf("Team name: %s\n", team.name);
	printf("The team won %d games\n", team.total_wins);
	printf("The team has %d registerd players:\n", team.current_players);
	for (i = 0; i < team.current_players; i++)
	{
		printf("Player #%d data:\n", i + 1);
		printPlayer(*team.players[i]);
	}
}

void free_all(Team** teams, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < teams[i]->max_players; j++)
		{
			if (teams[i]->players[j]->name)
				free(teams[i]->players[j]->name);
			free(teams[i]->players[j]);
		}
		free(teams[i]->name);
		free(teams[i]->players);
	}
}
/**
 * @file day1.c
 * @author Simon Grundner
 * @brief Advent of code puzzle day 2
 * @date 2023-12-02
 * @details https://adventofcode.com/2023/day/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../inputs/day2.txt"
#define N_COLORS 3
#define RED 12
#define GREEN 13
#define BLUE 14
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define BUFLEN 180

static const char *COLORS[N_COLORS] = {"red", "green", "blue"};
static const unsigned char LIMITS[N_COLORS] = {RED, GREEN, BLUE};

int day2_1()
{
	FILE *input = fopen(INPUT, "r");
	int possible = 0;
	char game[BUFLEN];
	// each line is a game with bags separated by ";"
	while (fgets(game, sizeof(game), input) != NULL) // iterate through games (lines)
	{
		char *bag = strchr(game, ':');
		char done = 0;
		while (bag != NULL && !done) // iterate through bags
		{
			bag += 2; // skip extra chars ": "
			for (int i = 0; i < N_COLORS && !done; i++)
			{
				char *cube = strstr(bag, COLORS[i]); // find cube color literal
				if (cube != NULL)
					done = (atoi(cube - 3) > LIMITS[i]); // -3 to reveal (2) digits before color
			}
			bag = strchr(bag, ';'); // skip to next bag
		}
		if (!done)
			possible += atoi(game + 4); // Game ID is at 4th index in line
	}
	fclose(input);
	return possible;
}

int day2_2()
{
	FILE *input = fopen(INPUT, "r");
	char game[BUFLEN];
	long sum_power = 0;
	// each line is a game with bags separated by ";"
	while (fgets(game, sizeof(game), input) != NULL) // iterate through games (lines)
	{
		char *bag = strchr(game, ':');
		int max_cubes[N_COLORS] = {0};
		while (bag != NULL) // iterate through bags
		{
			bag += 2; // skip extra chars ": "
			for (int i = 0; i < N_COLORS; i++)
			{
				char *cube = strstr(bag, COLORS[i]); // find cube color literal
				if (cube != NULL)
					max_cubes[i] = max(atoi(cube - 3), max_cubes[i]); // -3 to reveal (2) digits before color
			}
			bag = strchr(bag, ';'); // skip to next bag
		}
		sum_power += max_cubes[0] * max_cubes[1] * max_cubes[2];
	}
	fclose(input);
	return sum_power;
}

int main(int argc, char const *argv[])
{
	printf("Answer of day 2 part 1 is: %d \n", day2_1());
	printf("Answer of day 2 part 2 is: %d \n", day2_2());
	return 0;
}

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

#define BUFLEN 180

static const char *COLORS[N_COLORS] = {"red", "green", "blue"};
static const unsigned char LIMITS[N_COLORS] = {RED, GREEN, BLUE};

char is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int day2_1()
{
	FILE *in = fopen(INPUT, "r");
	int possible = 0;
	char buf[BUFLEN];

	while (fgets(buf, sizeof(buf), in) != NULL)
	{
		char *p = strchr(buf, ':');
		char done = 0;
		while (p != NULL && !done)
		{
			p += 2;
			for (int i = 0; i < N_COLORS && !done; i++)
			{
				char *r = p;
				while ((r = strstr(r, COLORS[i])) != NULL && !done)
				{
					r -= 3;
					if (atoi(r) > LIMITS[i])
					{
						done = 1;
						break;
					}
					r += 4;
				}
			}
			p = strchr(p, ';');
		}
		if (!done)
		{
			possible += atoi(buf + 4);
		}
	}

	fclose(in);
	return possible;
}

int day2_2()
{
	FILE *in = fopen(INPUT, "r");
	char buf[BUFLEN];
	long sum_power = 0;
	while (fgets(buf, sizeof(buf), in) != NULL)
	{
		char *p = strchr(buf, ':');
		int max_cubes[N_COLORS] = {0};
		while (p != NULL)
		{
			p += 2;
			for (int i = 0; i < N_COLORS; i++)
			{
				char *r = p;
				while ((r = strstr(r, COLORS[i])) != NULL)
				{
					r -= 3;
					int n_cubes = atoi(r);
					if (n_cubes > max_cubes[i])
					{
						max_cubes[i] = n_cubes;
					}
					r += 4;
				}
			}
			p = strchr(p, ';');
		}
		sum_power += max_cubes[0] * max_cubes[1] * max_cubes[2];
	}
	fclose(in);
	return sum_power;
}

int main(int argc, char const *argv[])
{
	printf("Answer of day 2 part 1 is: %d \n", day2_1());
	printf("Answer of day 2 part 2 is: %d \n", day2_2());
	return 0;
}

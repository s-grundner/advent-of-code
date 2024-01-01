/**
 * @file day6.c
 * @author Simon Grundner
 * @brief Advent of code puzzle day 6
 * @date 2023-12-06
 * @details https://adventofcode.com/2023/day/6
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../inputs/day6.txt"
#define BUFSIZE 1

int day6_1()
{
	FILE *input = fopen(INPUT, "r");

	char buf[BUFSIZE];

	while (fgets(buf, sizeof(buf), input))
	{
		/* code */
	}

	fclose(input);
	return 0;
}

int day6_2()
{
	FILE *input = fopen(INPUT, "r");

	char buf[BUFSIZE];

	while (fgets(buf, sizeof(buf), input))
	{
		/* code */
	}

	fclose(input);
	return 0;
}

int main(int argc, char const *argv[])
{
	printf("Answer of day 6 part 1 is: %d \n", day6_1());
	printf("Answer of day 6 part 2 is: %d \n", day6_2());
	return 0;
}

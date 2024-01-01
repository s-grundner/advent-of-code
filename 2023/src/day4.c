/**
 * @file day4.c
 * @author Simon Grundner
 * @brief Advent of code puzzle day 4
 * @date 2023-12-04
 * @details https://adventofcode.com/2023/day/4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../inputs/day4.txt"
#define BUFSIZE 1

int day4_1()
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

int day4_2()
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
	printf("Answer of day 4 part 1 is: %d \n", day4_1());
	printf("Answer of day 4 part 2 is: %d \n", day4_2());
	return 0;
}

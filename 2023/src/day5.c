/**
 * @file day5.c
 * @author Simon Grundner
 * @brief Advent of code puzzle day 5
 * @date 2023-12-05
 * @details https://adventofcode.com/2023/day/5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../inputs/day5.txt"
#define BUFSIZE 1

int day5_1()
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

int day5_2()
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
	printf("Answer of day 5 part 1 is: %d \n", day5_1());
	printf("Answer of day 5 part 2 is: %d \n", day5_2());
	return 0;
}

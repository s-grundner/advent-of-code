/**
 * @file day1.c
 * @author Simon Grundner
 * @brief Advent of code puzzle day 1
 * @date 2023-12-01
 * @details https://adventofcode.com/2023/day/1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT "../inputs/day1.txt"
#define OUTPUT "../outputs/day1.txt"
#define LEN 80

static const char *STR_NUMS[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const char *NUMS = "0123456789";

char is_num(char c)
{
	return (c >= '0' && c <= '9');
}

char *strrstr(const char *haystack, const char *needle, int progress)
{
	char *r = NULL;
	if (!needle[0])
		return (char *)haystack + strlen(haystack);
	haystack = (char *)haystack + progress; // chars below first idx dont have to be checked
	while (1)
	{
		char *p = strstr(haystack, needle);
		if (!p)
			return r;
		r = p;
		haystack = p + 1;
	}
}

char get_first_num(char *buf, int *idx)
{
	*idx = strcspn(buf, NUMS);
	return buf[*idx] - '0';
}

char get_last_num(char *buf, int *idx, int progress)
{
	for (int i = progress; buf[i] != '\0'; i++)
		if (is_num(buf[i]))
			*idx = i;
	return buf[*idx] - '0';
}

int day1_1()
{
	FILE *in = fopen(INPUT, "r");
	int sum = 0;
	char buf[LEN];
	while (fgets(buf, sizeof(buf), in) != NULL)
	{
		int idx = 0;
		sum += get_first_num(buf, &idx) * 10 + get_last_num(buf, &idx, idx);
	}
	fclose(in);
	return sum;
}

int day1_2()
{
	FILE *in = fopen(INPUT, "r");
	int sum = 0;
	char buf[LEN];
	while (fgets(buf, sizeof(buf), in) != NULL)
	{
		int last_idx = 0, first_idx = 0;
		int first_num = get_first_num(buf, &first_idx);
		int last_num = get_last_num(buf, &last_idx, first_idx);
		for (int i = 0; i < 10; i++)
		{
			char *pch = strstr(buf, STR_NUMS[i]); // check for first literal number
			if (pch != NULL)
			{
				int str_idx = pch - buf; // index of literal number
				if (str_idx < first_idx)
				{
					first_idx = str_idx;
					first_num = i;
				}
			}
			pch = strrstr(buf, STR_NUMS[i], first_idx); // check for last literal number
			if (pch != NULL)
			{
				int str_idx = pch - buf;
				if (str_idx > last_idx)
				{
					last_idx = str_idx;
					last_num = i;
				}
			}
		}
		sum += first_num * 10 + last_num;
	}
	fclose(in);
	return sum;
}

int main(int argc, char const *argv[])
{
	printf("Answer of day 1 part 1 is: %d \n", day1_1());
	printf("Answer of day 1 part 2 is: %d \n", day1_2());
	return 0;
}
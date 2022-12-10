# Advent of Code 2022 - Day 4
## Part 1
We need to determine how many pairs are fully overlapping, that is, the ranges of the first pair completely overlap the second pair. For example, the pairs (1, 5) and (2, 4) are fully overlapping, but the pairs (1, 5) and (6, 8) are not.

## Part 2
We need to determine how many pairs are partly overlapping, that is, the ranges of the first pair partially overlap the second pair. For example, the pairs (1, 5) and (2, 7) are partly overlapping, but the pairs (1, 5) and (6, 8) are not.

## Overview
This solution implements the following functions:

`int stoi(char *str)`: This function converts a string representation of an integer to an integer.
`int count_assignments(char*filename)`: This function counts the number of assignments in the given file.
`int is_fully_overlapping(int a, int b, int c, int d)`: This function checks if the two given ranges fully overlap.
`int is_partly_overlapping(int a, int b, int c, int d)`: This function checks if the two given ranges partly overlap.
`management_list_t manage_assignments(char *filename, int assign_count)`: This function reads the assignments from the given file and returns a management_list_t which contains the assignments and the counts of fully and partly overlapping assignments.
`int main()`: This is the entry point of the program. It calls the above functions and prints the result.

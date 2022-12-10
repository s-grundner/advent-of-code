# Advent of Code 2022 - Day 3

This is a C implementation of the solution for day 3 of Advent of Code 2022.

The program reads a list of strings from an input file and calculates the most common character in each group of strings. The program uses several utility functions to perform the calculations, such as `count_char_in_string()` and `get_most_common_char()`.

The program will read the input from a file called `input.txt` in the current directory and print the solution to the console.

## Customizing

You can change the behavior of the program by modifying the following constants at the beginning of the `main.c` file:

- `INPUT_FILE`: The name of the input file.
- `INPUT_SIZE`: The maximum size of each line in the input file.
- `GROUP_SIZE`: The number of items in each group.
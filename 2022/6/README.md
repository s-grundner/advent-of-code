# Advent of Code 2022 - Day 6

This C program reads a line from a file with the filename specified by the `INPUT_FILE` macro and attempts to find the first marker in the input string that has no double characters in it. The marker interval is specified by the `marker_interval` parameter passed to the `decrypt_markers` function. If a marker is found, the position of the first character in the marker is returned. If no marker is found, `-1` is returned.

## Some suggestions for improvement are:

1. Add error handling for the case where the input file cannot be opened.
2. Use more descriptive variable names.
3. Use a more efficient algorithm for checking for double characters in the input string. The current algorithm has a time complexity of O(n^2), which may not be efficient for large inputs.
4. Use a more modular approach for splitting the code into functions. The current implementation mixes utility functions with the main logic.
5. Add comments to the code to explain its purpose and how it works. This will make it easier for others to understand and modify the code.

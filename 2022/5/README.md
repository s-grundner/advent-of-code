# Advent of Code 2022 - Day 5

The code reads an input file that describes a cargo arrangement and a set of instructions for moving items between the cargo's stacks. The code simulates the moving of items according to the instructions and outputs the final cargo arrangement.

The input file is expected to have the following format:

```
    [ ]     [ ] [ ] [ ]
    [ ]     [ ] [ ] [ ]
[ ] [ ]     [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ] [ ]
 1   2   3   4   5   6   (stack id line)

move 1 from 2 to 1 (instruction 1)
move 1 from 3 to 1 (instruction 2)
move 1 from 4 to 1 (instruction 3)
...
```

- The code is written in C.
- The code contains several functions: `init_cargo`, `fill_cargo`, `restack_cargo`, and a `main` function.
- `init_cargo()` initialises the cargo by allocatong the needed memory
- `fill_cargo()` fills the cargo by reading the input file and generating a datastructure for the given problem
- `restack_cargo1()` takes a cargo_t structure and an instruction as arguments and simulates the execution of the instruction on the cargo for part 1.
- `restack_cargo2()` takes a cargo_t structure and an instruction as arguments and simulates the execution of the instruction on the cargo for part 2.
- `free_cargo()` frees all the allocated memory. it should always be called at the end of the puzzle when `init_cargo()` has been called prior.

The code uses a `cargo_t` structure to represent the cargo and its stacks. The structure contains the maximum number of stacks, the maximum height of a stack, the number of instructions, and arrays of instructions and stacks.

Each stack is represented by a `stack_t` structure containing the number of items in the stack, the maximum number of items that the stack can hold, and an array of characters representing the items in the stack.

Each instruction is represented by an instruction_t structure containing the number of items to move, the source stack id, and the destination stack id.

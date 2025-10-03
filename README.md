# C++ Word Search Solver

This is a command-line C++ application designed to solve word search puzzles. Given an input file containing a target word and a grid of characters, this program will determine if the word exists within the grid and, if it does, identify all possible paths that form the word.

The search is performed by moving one step at a time in the four cardinal directions (up, down, left, right).

## Core Functionalities

The logic of this solver is split into two distinct recursive search functions, each with a specific purpose as required for the assignment.

#### 1. `bool search()` - The Existence Check

The primary goal of the `search()` function is to answer a simple yes-or-no question: **"Does the target word exist in the grid?"**

-   **Intent:** Efficiency. This function is designed to stop searching the moment it confirms the first valid path.
    
-   **Mechanism:** It uses recursion and backtracking to explore paths from a given starting cell.
    
-   **Return Value:** It returns `true` as soon as a complete path is found and `false` if a path is exhausted. This allows the main program to quickly determine if any solutions exist at all before committing to a more intensive search.
    

#### 2. `void findAllPaths()` - The Path Finder

The goal of the `findAllPaths()` function (also referred to as `search2`) is to perform a comprehensive search to **find and record every possible path** that spells the target word.

-   **Intent:** Completeness. Unlike `search()`, this function does not stop after finding the first solution. It continues to explore every possible branch of the search space.
    
-   **Mechanism:** It uses a similar recursion and backtracking strategy but passes a `vector<string>` by reference. When a complete path is found, it is added to this vector.
    
-   **Outcome:** After this function runs, the vector will contain a complete list of all unique solution paths found in the grid.
    

## How to Compile and Run

To compile the program, you will need a C++ compiler (like g++). Ensure all necessary files (`main.cpp`, `Grid.h`, `Utility.h`) are in the same directory.

g++ -o p02 main.o Utility.o

```
g++ -o p02 main.o Utility.o
```

To run the compiled program, provide two command-line arguments: the input file and the desired output file name.

```
./p02 input.dat output.dat
```

-   `input.dat`: The path to the text file containing the puzzle.
    
-   `output.dat`: The path to the text file where the results will be written.
    

### Input File Format

The input file must be formatted as follows:

1.  **Line 1:** The target word to search for.
    
2.  **Line 2:** Two space-separated integers representing the number of rows and columns.
    
3.  **Following Lines:** The character grid, with each character separated by a space.
    

**Example `input.dat`:**

```
CAT3 4A B C DX C A TZ A T Y
```
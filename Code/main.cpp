#include <fstream>
//#include <vector>
#include <cmath>
#include "Utility.h"
#include "Grid.h"

using namespace std;

/* 
    The search target string will be saved in string& target
    The grid of letters will be returned
*/
Grid<char>* read_input(string file, string& target) {

    // TODO 1: read the input file
    ifstream inputFile(file);
    if (!inputFile) {
        throw FileException(file);
    }

    // get first line from input file and assign it to target
    getline(inputFile, target);


    // initialize variables for rows and columns
    string rows;
    string columns;
    // get second line  from input file and assign first digit to row and second digit to column
    inputFile >> rows >> columns;

    if (!isNumber(rows) || !isNumber(columns)) {
        throw FileContentException();
    }

    int num_rows = string_to_int(rows);
    int num_columns = string_to_int(columns);

    if (num_rows <= 0 || num_columns <= 0) {
        throw FileContentException();
    }

    // inputFile.ignore(numeric_limits<streamsize>::max(), '\n');

    // create new grid on heap using row and column as parameters
    Grid<char>* grid = new Grid<char>(num_rows, num_columns);
    
    // read follwing characters into grid
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            char ch;
            if (!inputFile << ch) {
                throw FileContentException();
            }
            //
            grid->set(i, j, ch);
        }
    }

    return grid;
}

/*
    The target word here is represented by a char pointer: next char to be matched.
    If there is a complete match, return true, else return false.
*/
bool search(Grid<char>* grid, int r, int c, const char* target) {
    bool result = false;
    
    // TODO 2: search the target in the grid





    return result;
}

// TODO bonus: search the target in the grid, and print the sequence(s) into the output stream
// e.g., you can consider the following function:
// void search2(Grid<char>* grid, int r, int c, const char* target, vector<string>& result, ostream& out);





int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            throw CommandLineException();
        
        }
        string target;
        Grid<char>* grid = read_input(argv[1], target);
        if (grid == nullptr) {
            return EXIT_FAILURE;
        }

        ofstream output;
        output.open(argv[2]);
        if (output.fail()) {
            throw FileException(argv[2]);
        }

        for (int i = 0; i < grid->row(); i++) {
            for (int j = 0; j < grid->col(); j++) {
                if (search(grid, i , j, target.c_str())) {
                    output << "Solution found!" << endl;
                }
            }
        }

        output.close();

    } catch(...) {
        exit(EXIT_FAILURE);
    }

    return 0;
}
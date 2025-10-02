#include <fstream>
#include <vector>
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

    int num_rows = string_to_int(rows);
    int num_columns = string_to_int(columns);

    if (num_rows <= 0 || num_columns <= 0) {
        throw FileContentException();
    }

    inputFile.ignore(numeric_limits<streamsize>::max(), '\n');

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

    // base case: if we have matched all letters
    if (*target == '\0') return true;

    // check boundaries of r and c parameters
    if (r < 0 || c < 0 || r >= grid->row() || c >= grid->col()) return false;


    // check character
    char ch;
    if (grid->get(r, c, ch) != success) return false;
    if (ch != *target) return false;

    // temporarily mark current character with #
    grid->set(r, c, '\0');

    // make recursive call to each of the surrounding characters in grid, if one returns true, it will move on
    result = search(grid, r + 1, c, target + 1) ||
                       (grid, r - 1, c, target + 1) ||
                       (grid, r, c + 1, target + 1) ||
                       (grid, r, c - 1, target + 1);

    // unmark current character
    grid->set(r, c, ch);

    // return if character was found
    return result;
}

// TODO bonus: search the target in the grid, and print the sequence(s) into the output stream
// e.g., you can consider the following function:
void search2(Grid<char>* grid, int r, int c, const char* target, vector<string>& result, ostream& out) {

    string path;

    // base case: if we have matched all letters
    if (*target == '\0') {
        result.push_back(path);
        out << "Found word: " << path << endl;
        return;
    }

    // check boundaries of r and c parameters
    if (r < 0 || c < 0 || r >= grid->row() || c >= grid->col()) return;


    // check character
    char ch;
    if (grid->get(r, c, ch) != success) return;
    if (ch != *target) return;

    // temporarily mark current character with #
    grid->set(r, c, '\0');

    string newPath = path + "(" + to_string(r) + "," + to_string(c) + ")";

    // make recursive call to each of the surrounding characters in grid, if one returns true, it will move on
    search2(grid, r + 1, c, target + 1, result, out);
    search2(grid, r - 1, c, target + 1, result, out);
    search2(grid, r, c + 1, target + 1, result, out);
    search2(grid, r, c - 1, target + 1, result, out);

    // unmark current character
    grid->set(r, c, ch);

}

void print_grid(Grid<char>* grid, int r, int c, const char* target) {
    cout << "-----After Read Input------" << endl;
    cout << "-----You are in the read_input function" << endl;
    cout << target << endl;
    cout << grid->row() << " " << grid->col() << endl;
    for (int i=0; i<(grid->row()); i++){
        for (int j=0; j<(grid->col()); j++){
            char getCharacter;
            grid->get(i,j,getCharacter);
            cout << getCharacter << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl; 
}

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
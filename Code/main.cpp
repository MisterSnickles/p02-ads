#include <fstream>
#include <vector>
#include "Utility.h"
#include "Grid.h"

using namespace std;

void output_targetANDgrid(const string target, Grid<char>* grid, ostream& out) {
    out << "Target: " << target << endl;

    out << "---Grid---" << endl;
    out << "  ";
    for (int i=0; i<=(grid->row()); i++){
        out << i << " ";
    }
    out << endl;
    for (int i=0; i<(grid->row()); i++){
        out << i << " ";
        for (int j=0; j<(grid->col()); j++){
            char getCharacter;
            grid->get(i,j,getCharacter);
            out << getCharacter << " ";
        }
        out << endl;
    }
    out << "----------" << endl;
}

void print_targetANDgrid(const string target, Grid<char>* grid) {
    cout << "Target: " << target << endl;

    cout << "---Grid---" << endl;
    cout << "  ";
    for (int i=0; i<=(grid->row()); i++){
        cout << i << " ";
    }
    cout << endl;
    for (int i=0; i<(grid->row()); i++){
        cout << i << " ";
        for (int j=0; j<(grid->col()); j++){
            char getCharacter;
            grid->get(i,j,getCharacter);
            cout << getCharacter << " ";
        }
        cout << endl;
    }
    cout << "----------" << endl;
}

/* 
    The search target string will be saved in string& target
    The grid of letters will be returned
*/
Grid<char>* read_input(string file, string& target) {
    // TODO 1: read the input file

    //create stream, open file, and check if it fails.
    ifstream inputFile(file);
    if (inputFile.fail())   throw FileException(file);

    //gets the target word from the first line in the input file
    getline(inputFile, target);
    
    //gets the row and column number from the second line in the input file
    int numRows;
    int numCols;
    inputFile >> numRows;
    inputFile >> numCols;

    if(numRows <= 0 || numCols <= 0) throw FileContentException();

    //Create a new grid object and initialize with the row and column you got from the file
    Grid<char>* grid = new Grid<char>(numRows, numCols);
  
    // set each element in the array with the character in the file
    for (int i=0; i<numRows; i++){
        for (int j=0; j<numCols; j++){
            char ch;
            if (!(inputFile>>ch)){
                throw FileContentException();
            }
            grid->set(i, j, ch);
        }
    }

    //close the file
    inputFile.close();

    // // Uncomment me to print the grid to the console for debugging
    // print_grid(grid);

    //return the grid you made. Our grid in main will be set to this grid.
    return grid;
}

/*
    The target word here is represented by a char pointer: next char to be matched.
    If there is a complete match, return true, else return false.
*/
bool search(Grid<char>* grid, int r, int c, const char* target) {
    bool result = false;
    
    // TODO 2: search the target in the grid

    //Base Case. You got to the end of the character string.
    if (*target == '\0') return true;

    //check that you aren't looking in a grid box out side of the range.
    if (r<0 || c<0) return false;
    // checks to see if the number of rows and columns are less than the what the function called for
    if (grid->row() <= r || grid->col() <= c)   return false;

    
    // make a temporary variable to store the character in the premade grid
    char getGridCharacter;
    // gets the variable from the grid
    if(grid->get(r,c,getGridCharacter) != success) return false;
    // see if it equals the current value of the character in target. 
    //      remember, *target is an array of characters. 
    //      you are comparing a character in the grid to the current character in your word
    if (getGridCharacter != *target) return false;
    
    // set the current grid box to \0. 
    // this makes it so that if you get to it again during search,
    //      when you are doing your 4 way search, it gets ignored
    grid->set(r, c, '\0');
    
    //  Recursive Search the grid. down, up, left, right
    //              | row, col|
    //              | r-1, c  |
    //    | r, c-1  |   r, c  | r, c+1 |
    //              | r+1, c  |     
    result =  search(grid, r-1, c, target+1)     // search up.      1 row up,               same column
            ||search(grid, r+1, c, target+1)     // search down.    1 row down,             same column
            ||search(grid, r, c-1, target+1)     // search left.    1 column to the left,   same row
            ||search(grid, r, c+1, target+1);    // search right.   1 column to the right,  same row


    // reset the grid box back to the original character as you backtrack
    grid->set(r, c, getGridCharacter);

    return result;
}

// TODO bonus: search the target in the grid, and print the sequence(s) into the output stream
// e.g., you can consider the following function:
void search2(Grid<char>* grid, int r, int c, const char* target, vector<string>& result, ostream& out){
    //   bool true/false = false;
    // // TODO 2: search the target in the grid

    //Base Case. You got to the end of the character string.
    if (*target == '\0') return;
    

    //check that you aren't looking in a grid box out side of the range.
    if (r<0 || c<0) return;
    // checks to see if the number of rows and columns are less than the what the function called for
    if (grid->row() <= r || grid->col() <= c) return;
    
    // make a temporary variable to store the character in the premade grid
    char getGridCharacter;
    // gets the variable from the grid
    if (grid->get(r,c,getGridCharacter) != success) return;
    // see if it equals the current value of the character in target. 
    //      remember, *target is an array of characters. 
    //      you are comparing a character in the grid to the current character in your word
    if (getGridCharacter != *target) return;
    
    out << "(" << r << "," << c << ") " ;
    cout << "(" << r << "," << c << ") " ;

    // set the current grid box to \0. 
    // this makes it so that if you get to it again during search,
    //      when you are doing your 4 way search, it gets ignored
    grid->set(r, c, '\0');
    
    //  Recursive Search the grid. down, up, left, right
    //              | row, col|
    //              | r-1, c  |
    //    | r, c-1  |   r, c  | r, c+1 |
    //              | r+1, c  |     
    search2(grid, r-1, c, target+1, result, out);     // search up.      1 row up,               same column
    search2(grid, r+1, c, target+1, result, out);     // search down.    1 row down,             same column
    search2(grid, r, c-1, target+1, result, out);     // search left.    1 column to the left,   same row
    search2(grid, r, c+1, target+1, result, out);     // search right.   1 column to the right,  same row


    // reset the grid box back to the original character as you backtrack
    grid->set(r, c, getGridCharacter);

    return;
}


int main(int argc, char* argv[]) {
    try {
        if (argc != 3)  throw CommandLineException();
        
        string target;
        Grid<char>* grid = read_input(argv[1], target);
        if (grid == nullptr) return EXIT_FAILURE;

        ofstream output;
        output.open(argv[2]);
        if (output.fail()) throw FileException(argv[2]);

        vector<string>& result = *(new vector<string>);

        output_targetANDgrid(target, grid, output);
        print_targetANDgrid(target, grid);

        for (int i = 0; i < grid->row(); i++) {
            for (int j = 0; j < grid->col(); j++) {
                if (search(grid, i , j, target.c_str())) {
                    output << "Solution found!" << endl;
                    cout << "Solution found!" << endl;
                    search2(grid, i , j, target.c_str(), result, output);
                }
            }
        }

        output.close();
    } catch(...) {
        exit(EXIT_FAILURE);
    }
    return 0;
}
#include <fstream>
#include <vector>
#include "Utility.h"
#include "Grid.h"

using namespace std;

// functions used to output to file and console ----------------------------------
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
// end of output functions --------------------------------------------------------

/* 
    The search target string will be saved in string& target
    The grid of letters will be returned
*/
Grid<char>* read_input(string file, string& target) {

   
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
    inputFile.close();;

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
void search2(Grid<char>* grid, int r, int c, const char* target, vector<string>& result, ostream& out, string currentPath) {


    // base case: if we have matched all letters
    if (*target == '\0') {
        result.push_back(currentPath);
        return;
    }

    // case 1: check boundaries of r and c parameters
    if (r < 0 || c < 0 || r >= grid->row() || c >= grid->col()) return;


    // case 2: check character
    char ch;
    if (grid->get(r, c, ch) != success || ch == '\0' || ch != *target) {
        return;
    }

    string newPath = currentPath + "(" + to_string(r) + "," + to_string(c) + ")";

    // 4. Base Case: If this was the *last* character of the word, we've found a full solution.
    // Add the completed path to our vector of solutions and stop this recursive branch.
    if (*(target + 1) == '\0') {
        result.push_back(newPath);
        return;
    }

    // temporarily mark current character with null character to identify as visited
    grid->set(r, c, '\0');



    // make recursive call to each of the surrounding characters in grid, if one returns true, it will move on
    search2(grid, r + 1, c, target + 1, result, out, newPath);
    search2(grid, r - 1, c, target + 1, result, out, newPath);
    search2(grid, r, c + 1, target + 1, result, out, newPath);
    search2(grid, r, c - 1, target + 1, result, out, newPath);

    // unmark current character
    grid->set(r, c, ch);

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

        vector<string> result;
        bool successfulSearch = false;

        for (int i = 0; i < grid->row(); i++) {
            for (int j = 0; j < grid->col(); j++) {

                // calling both search() and search2() to show functionality of each
                // if search() returns true then search2() will execute and save searched path
                if (search(grid, i, j, target.c_str())) {
                    successfulSearch = true;

                    // if search is successful, run search2 to save path
                    search2(grid, i, j, target.c_str(), result, output, "");
                } 
            }
        }

        if (successfulSearch) {
            cout << "Search is successful!" << endl;
        } else {
            cout << "Search is unsuccessful!!!" << endl;
            return fail;
        }

        output_targetANDgrid(target, grid, output);
        print_targetANDgrid(target, grid);
        
        // After checking all possible starting points, write the results
        output << "Solutions Found: " << result.size() << endl;
        cout << "Solutions Found: " << result.size() << endl;

        for (int i = 0; i < result.size(); i++) {
            output << i + 1 << ". " << result[i] << endl;
            cout << i + 1 << ". " << result[i] << endl;
        }

        output.close();
        delete grid;
        grid = nullptr;

    } catch(...) {
        exit(EXIT_FAILURE);
    }

    return 0;
}
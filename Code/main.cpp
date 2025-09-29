#include <fstream>
//#include <vector>
#include "Utility.h"
#include "Grid.h"

using namespace std;

/* 
    The search target string will be saved in string& target
    The grid of letters will be returned
*/
Grid<char>* read_input(string file, string& target) {
// TODO 1: read the input file
    
    //create stream, open file, and check if it fails.
    ifstream input;
    input.open(file);
    if (input.fail()){
        throw FileException(file);
    }

    //gets the target word from the first line in the input file
    getline(input, target);
    
    //gets the row and column number from the second line in the input file
    int row;
    int col;
    input >> row;
    input >> col;

    //Create a new grid object and initialize with the row and column you got from the file
    Grid<char>* grid = new Grid<char>(row, col);
  
    // set each element in the array with the character in the file
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            char x;
            if (!(input>>x)){
                throw FileContentException();
            }
            grid->set(i,j,x);
        }
    }

    //close the file
    input.close();

    // // Uncomment the code below to print out the data from the file. 
    // // It prints out the target word, row and columns, and matrix data
    // cout << "-----After Read Input------" << endl;
    // cout << "-----You are in the read_input function" << endl;
    // cout << target << endl;
    // cout << grid->row() << " " << grid->col() << endl;
    // for (int i=0; i<(grid->row()); i++){
    //     for (int j=0; j<(grid->col()); j++){
    //         char getCharacter;
    //         grid->get(i,j,getCharacter);
    //         cout << getCharacter << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-----------------" << endl;

    //return the grid you made. Our grid in main will be set to this grid.
    return grid;
}

/*
    The target word here is represented by a char pointer: next char to be (matched.
    If there is a complete match, return true, else return false.
*/
bool search(Grid<char>* grid, int r, int c, const char* target) {
    bool result = true;
    
    // TODO 2: search the target in the grid
    // cout << target << endl;
    // cout << target[0] << endl;
    // int x = target.length();


    // for(int i=0; i<(target.length()); i++){
    //     cout <<target[i]<<endl;
    // }




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

        // // Uncomment the code below to print out the data from the file. 
        // // It prints out the target word, row and columns, and matrix data
        // cout << "-----Grid Data------" << endl;
        // cout << "-----You are in the main function" << endl;
        // cout << target << endl;
        // cout << grid->row() << " " << grid->col() << endl;
        // for (int i=0; i<(grid->row()); i++){
        //     for (int j=0; j<(grid->col()); j++){
        //         char getCharacter;
        //         grid->get(i,j,getCharacter);
        //         cout << getCharacter << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "-----------------" << endl;

        ofstream output;
        output.open(argv[2]);
        if (output.fail()) {
            throw FileException(argv[2]);
        }
        search(grid, 0 , 1, target.c_str());
        
        for (int i = 0; i < grid->row(); i++) {
            for (int j = 0; j < grid->col(); j++) {
                if (search(grid, i , j, target.c_str())) {
                   output << "Solution found!" << endl;
                    // cout << "Solution found!: " << i << " " << j << endl;
               }
            }
        }
        output.close();

    } catch(...) {
        exit(EXIT_FAILURE);
    }

    return 0;
}
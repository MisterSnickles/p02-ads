#include <sstream>
#include <string>
#include <iostream>

/*
 * Handle command line error
 */
struct CommandLineException
{
   CommandLineException()
   {
        std::cout << std::endl;
        std::cout << "Incorrect command line arguments." << std::endl;
        std::cout << "Please specify the input and output with the following format:" << std::endl;
        std::cout << "~/p02/p02 input.dat output.dat" << std::endl;
   }
};

/*
 * Handle exception when accessing a file/folder
 */
struct FileException {
  FileException(const std::string file) {
    std::cout << std::endl << "'" << file << "'" << " could not be accessed or contains corrupted content." << std::endl;
  }
};

/*
 * Handle exception when the input data is invalid
 */
struct FileContentException {
  FileContentException() {
    std::cout << "Input data could not be correctly parsed." << std::endl;
  }
};

enum Error_code { duplicate_error, not_present, success, overflow, underflow, range_err, fail };

int string_to_int(const std::string& s);

bool isNumber(const std::string& str);

bool isUpperLetter(const std::string& str);
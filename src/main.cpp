#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

#include "cpplzw.h"

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        std::cout << "argc was " << argc << std::endl;
        std::cout << "Please pass exactly one argument which is the input file path" << std::endl;
        std::cout << "This program uses the lzw compression algorithm from cpplzw to compress the given file and outputs it to a file called 'output'" << std::endl;
        return 1;
    }

    std::string input;
    {
        std::ostringstream oss;
        {
            std::ifstream fin(argv[1], std::ifstream::binary);
            oss << fin.rdbuf();
        }
        input = oss.str();
    }

    {
        std::string output = compress(input);
        std::ofstream("output", std::ofstream::binary | std::ios_base::out) << output;
    }

    std::cout << "success" << std::endl;
    return 0;
}

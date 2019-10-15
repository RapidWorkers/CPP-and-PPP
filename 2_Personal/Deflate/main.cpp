#include "Deflate/Deflate.h"
#include "CommandLineParser.h"
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Compression using Deflate Algorithm" << std::endl;
    std::cout << "by RapidWorkers" << std::endl;
    std::cout << "============================================" << std::endl;

    CommandLineParser Parser{argc, argv};
    Parser.doParse();
    std::cout << "============================================" << std::endl;
    return 0;
}
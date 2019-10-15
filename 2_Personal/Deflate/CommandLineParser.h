#ifndef DEFLATE_COMMANDLINEPARSER_H
#define DEFLATE_COMMANDLINEPARSER_H

#include <iostream>
#include <string>

class CommandLineParser{
private:
    int argc;
    char** argv;
public:
    CommandLineParser(int c, char** v) : argc{c}, argv{v} {};
    void doParse() {
        if(argc == 1) printUsage();
    };

    std::string getNextCommand() {

    }

    void printUsage(){
        std::cout << "Usage" << std::endl
        << "ZIP Compress" << std::endl << "Deflate --compress <files_to_compress> --zip" << std::endl << std::endl
        << "GZip Compress" << std::endl << "Deflate --compress <files_to_compress> --gzip" << std::endl << std::endl
        << "If no file format is provided, the default is ZIP Compress" << std::endl << std::endl
        << "Decompress" << std:: endl << "Deflate --decompress <file_to_decompress>" << std::endl;
    }
};

#endif //DEFLATE_COMMANDLINEPARSER_H

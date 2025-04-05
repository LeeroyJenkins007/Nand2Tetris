#include <iostream>
#include <cassert>
#include <fstream>

#include "Parser.hpp"

int main(int argc, char* argv[]){
    assert(argc > 1);
    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }else{
        std::cout << "File Name: " << argv[1] << std::endl;
    }

    std::string outFile(argv[1]);
    outFile = outFile.substr(0, outFile.find_last_of('.')) + ".hack";
    std::cout << outFile << std::endl;
    std::ofstream binFile(outFile);
    
    Parser parser = Parser(argv[1]);

    //first pass
    std::cout << "First Pass\n";
    //second pass
    std::cout << "Second Pass\n";
    parser.advance();
    while(parser.hasMoreCommands()){
        std::cout << "pass" << std::endl;

        std::string binCommand;
        CMD_TYPE cmd = parser.instructionType();
        std::cout << cmd << std::endl;
        if (cmd == A_COMMAND){
            std::cout << "A_COMMAND" << std::endl;
            binCommand = parser.symbol();
        } else if(cmd == C_COMMAND){
            std::cout << "C_COMMAND" << std::endl;
            binCommand = "111";
            binCommand += parser.comp();
            binCommand += parser.dest();
            binCommand += parser.jump();
        } else {
            std::cout << "L_COMMAND: Not implemented" << std::endl;
            binCommand = "0";
        }

        binFile << binCommand << std::endl;
        parser.advance();
    }

    
    return 0;
}
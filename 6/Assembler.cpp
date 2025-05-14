#include <iostream>
#include <cassert>
#include <fstream>

#include "debug_util.hpp"
#include "Parser.hpp"
#include "SymbolTable.hpp"


std::string num2string(const std::string &numStr);

int main(int argc, char* argv[]){
    assert(argc > 1);
    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }else{
        std::cout << "Input: " << argv[1] << std::endl;
    }

    std::string outFile(argv[1]);
    outFile = outFile.substr(0, outFile.find_last_of('.')) + ".hack";
    std::cout << "Output: " << outFile << std::endl;
    std::ofstream binFile(outFile);
    
    SymbolTable symbolTable;

    
    Parser parser = Parser(argv[1]);
    //first pass
    DEBUG_PRINT("First Pass")
    //std::cout << "First Pass\n";
    int line = 0;
    while(parser.hasMoreCommands()){
        parser.advance();

        CMD_TYPE cmd = parser.instructionType();
        if (cmd == L_COMMAND){
            //std::cout << "LABEL at line " << line << std::endl;
            DEBUG_PRINT("Label at line" << line)
            symbolTable.addEntity(parser.symbol(), line);
        }else{
            line++;
        }
    }
    //std::cout << "End of FIRST PASS\n";
    DEBUG_PRINT("End of FIRST PASS")
    parser.reset();
    
    //second pass
    //std::cout << "Second Pass\n";
    DEBUG_PRINT("Second Pass")

    while(parser.hasMoreCommands()){
        parser.advance();

        std::string binCommand;
        CMD_TYPE cmd = parser.instructionType();
        //std::cout << cmd << std::endl;
        DEBUG_PRINT("Instruction Type: " << cmd)
        if (cmd == A_COMMAND){
            //std::cout << "A_COMMAND" << std::endl;
            DEBUG_PRINT("A_COMMAND")
            binCommand = "0";
            std::string symStr = parser.symbol();
            if(symbolTable.contains(symStr)){
                //std::cout << "SymbolTable Has\n";
                DEBUG_PRINT("SymbolTable Has")
                binCommand += num2string(std::to_string(symbolTable.getAddress(symStr)));
            }else if(isdigit(symStr[0])){
                //std::cout << "A COM: Digit\n";
                DEBUG_PRINT("A COM: Digit")
                //std::cout << "Not in Symbol Table\n";
                DEBUG_PRINT("Not in Symbol Table")
                binCommand += num2string(parser.symbol());
            }else{
                symbolTable.addEntity(symStr);
                binCommand += num2string(std::to_string(symbolTable.getAddress(symStr)));
            }

            binFile << binCommand << std::endl;
        } else if(cmd == C_COMMAND){
            //std::cout << "C_COMMAND" << std::endl;
            DEBUG_PRINT("C_COMMAND")
            binCommand = "111";
            binCommand += parser.comp();
            binCommand += parser.dest();
            binCommand += parser.jump();

            binFile << binCommand << std::endl;
        } else {
            //std::cout << "L_COMMAND" << std::endl;
            DEBUG_PRINT("L_COMMAND")
        }

    }

    
    return 0;
}

std::string num2string(const std::string &numStr){
    int num = std::stoi(numStr);
    int pos = 14;
    std::string binary = "000000000000000";
    
    while (num > 0){
        binary[pos] = (num % 2 == 0 ? '0' : '1');
        num /= 2;
        pos--;
    }

    return binary;
}
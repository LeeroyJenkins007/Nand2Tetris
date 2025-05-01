#include <iostream>
#include <cassert>
#include <fstream>

#include "Parser.hpp"
#include "SymbolTable.hpp"


std::string num2string(const std::string &numStr);

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
    
    SymbolTable symbolTable;

    
    Parser parser = Parser(argv[1]);
    //first pass
    std::cout << "First Pass\n";
    int line = 0;
    while(parser.hasMoreCommands()){
        parser.advance();
        //probably should check for eof here
        if(!parser.hasMoreCommands()){
            break;
        }
        CMD_TYPE cmd = parser.instructionType();
        if (cmd == L_COMMAND){
            std::cout << "LABEL at line " << line << std::endl;
            symbolTable.addEntity(parser.symbol(), line);
            std::cout << "Added Label:" << parser.symbol() << std::endl;
        }else{
            line++;
        }
    }
    std::cout << "End of FIRST PASS\n";
    parser.reset();
    
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
            binCommand = "0";
            std::string symStr = parser.symbol();
            if(symbolTable.contains(symStr)){
                std::cout << "SymbolTable Has\n";
                binCommand += num2string(std::to_string(symbolTable.getAddress(symStr)));
            }else if(isdigit(symStr[0])){
                std::cout << "A COM: Digit\n";
                std::cout << "Not in Symbol Table\n";
                binCommand += num2string(parser.symbol());
            }else{
                symbolTable.addEntity(symStr);
            }

            binFile << binCommand << std::endl;
        } else if(cmd == C_COMMAND){
            std::cout << "C_COMMAND" << std::endl;
            binCommand = "111";
            binCommand += parser.comp();
            binCommand += parser.dest();
            binCommand += parser.jump();

            binFile << binCommand << std::endl;
        } else {
            std::cout << "L_COMMAND" << std::endl;
            //binCommand = "0";
            //std::string sym = parser.symbol();
            //std::string symAddress;
            //if(symbolTable.contains(sym)){
            //    symAddress = std::to_string(symbolTable.getAddress(sym));
            //}
            //binCommand = "0";
            continue;
        }

        //binFile << binCommand << std::endl;
        parser.advance();
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
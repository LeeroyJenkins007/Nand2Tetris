#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>

#include "Code.hpp"

enum CMD_TYPE{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND
};

class Parser{
    private:
        std::ifstream asmFile;
        std::string currentCommand;
    public:
        Parser(const char*);
        bool hasMoreCommands();
        void advance();
        CMD_TYPE instructionType();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
    private:
        std::string num2binary(const std::string& numStr);
};

#endif //PARSER_HPP
#include "Parser.hpp"

Parser::Parser(const char* inFile){
    asmFile = std::ifstream(inFile);
    std::cout << "Parser Created!" << std::endl;
}


/*
*   Are there mroe commands in the input?
*/
bool Parser::hasMoreCommands(){
    return !asmFile.eof();
}


/*
*
*/
void Parser::advance(){
    if (hasMoreCommands()){
        if(asmFile.is_open()){
            std::getline(asmFile, currentCommand);
            std::cout << "Current Line: " << currentCommand << std::endl;
            while ((currentCommand.empty() || !currentCommand.find('/')) && hasMoreCommands()){
                std::getline(asmFile, currentCommand);
                std::cout << "Current Line: " << currentCommand << std::endl;
            }      
        } else{
            std::cerr << "Failed to read file." << std::endl;
        }
    } else {
        std::cout << "There are no more commands." << std::endl;
        return;
    }

    std::cout << "Current COMMAND: " << currentCommand << std::endl;
}


/*
*   This assumes all commands are syntactically correct. 
*   An assumption that will be guarenteed with later work.alignof
*/
CMD_TYPE Parser::instructionType()
{
    CMD_TYPE cmd_type;


    char startChar = currentCommand.at(0);
    if(startChar == '@'){
        cmd_type = A_COMMAND;
    } else if(startChar == '('){
        cmd_type = L_COMMAND;
    } else {
        cmd_type = C_COMMAND;
    }

    return cmd_type;
}


/*
*
*/
std::string Parser::symbol()
{   
    std::string symBinary = "0";

    char initChar = currentCommand.at(0);
    if(initChar == '@'){
        symBinary += num2binary(currentCommand.substr(1));
    } else {
        symBinary += num2binary(currentCommand.substr(1, 14));
    }
    
    return symBinary;
}


/*
*   Returns the dest mnemonic in the current C-command (8 possibilites).
*   Should be called only when commandType() is C_COMMAND.
*/
std::string Parser::dest()
{
    std::string sub;

    auto idx = currentCommand.find('=');
    if(idx != currentCommand.npos){
        sub = currentCommand.substr(0, currentCommand.find('='));
    } else {
        sub = "";
    }

    std::cout << "Dest Sub: " << sub << std::endl;
    return Code::dest(sub);
}


/*
*   Returns the comp mnemonic in the current C-command (28 possibilites).
*   Should be called only when commandType() is C_COMMAND.
*/
std::string Parser::comp()
{
    std::string sub;
    auto dest_idx = currentCommand.find('=');
    if(dest_idx == currentCommand.npos){
        dest_idx = 0;
    } else{
        dest_idx++;
    }
    auto jump_idx = currentCommand.find(';');
    sub = currentCommand.substr(dest_idx, jump_idx - dest_idx);

    std::cout << "Comp Sub: " << sub << std::endl;
    return Code::comp(sub);
}


/*
*   Returns the jump mnemonic in the current C-command (8 possibilites).
*   Should be called only when commandType() is C_COMMAND.
*/
std::string Parser::jump()
{
    std::string sub;

    auto idx = currentCommand.find(';');
    if(idx != currentCommand.npos){
        sub = currentCommand.substr(idx);
    } else {
        sub = "";
    }

    std::cout << "Jump Sub: " << sub << std::endl;
    return Code::jump(sub);
}

std::string Parser::num2binary(const std::string &numStr)
{
    int num = std::stoi(numStr);
    int pos = 14;
    std::string binary = "000000000000000";
    
    while (num > 0){
        binary[pos] = (num % 2 == 0 ? '0' : '1');
        num /= 2;
        pos--;
    }
    //std::reverse(binary.begin(), binary.end());

    return binary;
}

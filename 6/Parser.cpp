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


bool Parser::isCommentOrSpace(const std::string& str){
    if (str.empty() || (str.at(0) == ' ') || (str.at(0) == '\r') || (str.at(0) == '/') || (str.at(0) == '\n')){
        std::cout << "Is Comment or Space\n";
        return true;
    } else {
        return false;
    }
}

/*
*
*/
void Parser::advance(){
    if (hasMoreCommands()){
        if(asmFile.is_open()){
            std::getline(asmFile, currentCommand);
            std::cout << "Current Line: " << currentCommand << std::endl;
            while (isCommentOrSpace(currentCommand) && hasMoreCommands()){
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

    currentCommand.erase(std::remove_if(currentCommand.begin(), currentCommand.end(), [](unsigned char c) {
        return c == '\r' || c == '\n' || c == ' ';
    }), currentCommand.end());
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
    
    currentCommand.erase(std::remove_if(currentCommand.begin(), currentCommand.end(), [](unsigned char c) {
        return c == '\r' || c == '\n';
    }), currentCommand.end());

    auto eq_idx = currentCommand.find('=');
    auto sc_idx = currentCommand.find(';');

    size_t start = (eq_idx != currentCommand.npos) ? eq_idx + 1 : 0;
    size_t end = (sc_idx != currentCommand.npos) ? sc_idx : currentCommand.length();

    //std::cout << "start Idx: " << dest_idx << "\t end Idx: " << jump_idx - dest_idx << std::endl;
    sub = currentCommand.substr(start, end);

    for(char c : sub){
        std::cout << "Char: '" << c << "' ASCII: " << static_cast<int>(c) << std::endl;
    }
    std::cout << "Length: " << sub.length() << std::endl;
    std::cout << "Comp Sub: [" << sub  << "]" << std::endl;

    return Code::comp(sub);
}


/*
*   Returns the jump mnemonic in the current C-command (8 possibilites).
*   Should be called only when commandType() is C_COMMAND.
*/
std::string Parser::jump()
{
    std::string sub;

    auto sc_idx = currentCommand.find(';');
    if(sc_idx != currentCommand.npos){
        sub = currentCommand.substr(sc_idx+1);
    } else {
        sub = "";
    }

    for(char c : sub){
        std::cout << "Char: '" << c << "' ASCII: " << static_cast<int>(c) << std::endl;
    }
    std::cout << "Length: " << sub.length() << std::endl;
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

    return binary;
}

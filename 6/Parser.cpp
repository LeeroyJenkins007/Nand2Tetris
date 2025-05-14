#include "Parser.hpp"
#include "debug_util.hpp"

Parser::Parser(const char* inFile){
    asmFile = std::ifstream(inFile);
    //std::cout << "Parser Created!" << std::endl;
    DEBUG_PRINT("Parser Created!")
}

void Parser::reset(){
    asmFile.clear();
    asmFile.seekg(0, std::ios::beg);
    //std::cout << "Parser file reset\n";
    DEBUG_PRINT("Parser file reset")
}

/*
*   Are there more commands in the input?
*/
bool Parser::hasMoreCommands(){
    std::streampos originalPos = asmFile.tellg();
    std::string line;

    while(std::getline(asmFile, line)){
        trim(line);
        if (!line.empty() && line[0] != '/'){
            asmFile.seekg(originalPos); //put the streampos back
            //std::cout << "CMD: " << line << "\n";
            DEBUG_PRINT("CMD: " << line)
            return true;
        }
        originalPos = asmFile.tellg(); //otherwise update streampos to current line, this repeats until the next line is a command or EOF
    }
    return false;
}

void Parser::trim(std::string& s){
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c) {
                    return c == '\r' || c == '\n' || c == '\t' || c == ' ';
                }), s.end());
}


void Parser::advance(){
    std::getline(asmFile, currentCommand);
    trim(currentCommand);
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
    std::string symStr = "0";

    char initChar = currentCommand.at(0);
    if(instructionType() == A_COMMAND){
        symStr = currentCommand.substr(1);
    } else if (instructionType() == L_COMMAND){
        symStr = currentCommand.substr(1, currentCommand.size() - 2);
    }
    
    return symStr;
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

    //std::cout << "Dest Sub: " << sub << std::endl;
    DEBUG_PRINT("Dest Sub: " << sub)
    return Code::dest(sub);
}


/*
*   Returns the comp mnemonic in the current C-command (28 possibilites).
*   Should be called only when commandType() is C_COMMAND.
*/
std::string Parser::comp()
{
    std::string sub;

    auto eq_idx = currentCommand.find('=');
    auto sc_idx = currentCommand.find(';');

    size_t start = (eq_idx != currentCommand.npos) ? eq_idx + 1 : 0;
    size_t end = (sc_idx != currentCommand.npos) ? sc_idx : currentCommand.length();

    sub = currentCommand.substr(start, end);

    #ifndef NDEBUG
        for(char c : sub){
            std::cout << "Char: '" << c << "' ASCII: " << static_cast<int>(c) << std::endl;
        }
    #endif
    //std::cout << "Length: " << sub.length() << std::endl;
    DEBUG_PRINT("Length: " << sub.length())
    //std::cout << "Comp Sub: [" << sub  << "]" << std::endl;
    DEBUG_PRINT("Comp Sub: [" << sub << "]")

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

    #ifndef NDEBUG
        for(char c : sub){
            std::cout << "Char: '" << c << "' ASCII: " << static_cast<int>(c) << std::endl;
        }
    #endif
    //std::cout << "Length: " << sub.length() << std::endl;
    DEBUG_PRINT("Length: " << sub.length())
    //std::cout << "Jump Sub: " << sub << std::endl;
    DEBUG_PRINT("Jump Sub: " << sub)
    return Code::jump(sub);
}
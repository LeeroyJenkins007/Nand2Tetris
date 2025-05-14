#include<unordered_map>

#include "debug_util.hpp"
#include "SymbolTable.hpp"


void SymbolTable::findSymbols(){
    
}

void SymbolTable::addEntity(std::string label, int address){
    symbols.insert({label, address});
    //std::cout << "Added Label: <" << label << ", " << address << ">\n";
    DEBUG_PRINT("Added Label: <" << label << ", " << address)
}

void SymbolTable::addEntity(std::string label){
    int address = varIdx;
    varIdx++;
    symbols.insert({label, address});
    //std::cout << "Added Variable: <" << label << ", " << address << ">\n";
    DEBUG_PRINT("Added Variable: <" << label << ", " << address)
}

bool SymbolTable::contains(const std::string label) const
{
    return symbols.count(label);
}

int SymbolTable::getAddress(const std::string label) const {
    return symbols.at(label);
}

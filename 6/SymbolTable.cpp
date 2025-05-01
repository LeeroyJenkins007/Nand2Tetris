#include<unordered_map>
#include "SymbolTable.hpp"


void SymbolTable::findSymbols(){
    
}

void SymbolTable::addEntity(std::string label, int address){
    symbols.insert({label, address});
    std::cout << "Added Label: <" << label << ", " << address << ">\n";
}

void SymbolTable::addEntity(std::string label){
    int address = varIdx;
    varIdx++;
    symbols.insert({label, address});
    std::cout << "Added Variable: <" << label << ", " << address << ">\n";
}

bool SymbolTable::contains(const std::string label) const
{
    return symbols.count(label);
}

int SymbolTable::getAddress(const std::string label) const {
    return symbols.at(label);
}

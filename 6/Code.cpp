#include "Code.hpp"

std::string Code::dest(std::string destField){
    std::string destBinary;

    //if checks, inefficient will implement hash after for fun
    if(destField == ""){
        destBinary = "000";
    } else if(destField == "M"){
        destBinary = "001";
    } else if(destField == "D"){
        destBinary = "010";
    } else if(destField == "MD"){
        destBinary = "011";
    } else if(destField == "A"){
        destBinary = "100";
    } else if(destField == "AM"){
        destBinary = "101";
    } else if(destField == "AD"){
        destBinary = "110";
    } else if(destField == "AMD"){
        destBinary = "111";
    } else {
        std::cerr << destField << " is not a valid destination field" << std::endl;
        destBinary = "\0";
    }

    return destBinary;
}

std::string Code::comp(std::string compField){
    std::string compBinary;

    if(compField == "0"){
        compBinary = "0101010";
    } else if(compField == "1"){
        compBinary = "0111111";
    } else if(compField == "-1"){
        compBinary = "0111010";
    } else if(compField == "D"){
        compBinary = "0001100";
    } else if(compField == "A"){
        compBinary = "0110000";
    } else if(compField == "M"){
        compBinary = "1110000";
    } else if(compField == "!D"){
        compBinary = "0001101";
    } else if(compField == "!A"){
        compBinary = "0110001";
    } else if(compField == "!M"){
        compBinary = "1110001";
    } else if(compField == "-D"){
        compBinary = "0001111";
    } else if(compField == "-A"){
        compBinary = "0110011";
    } else if(compField == "-M"){
        compBinary = "1110011";
    } else if(compField == "D+1"){
        compBinary = "0011111";
    } else if(compField == "A+1"){
        compBinary = "0110111";
    } else if(compField == "M+1"){
        compBinary = "1110111";
    } else if(compField == "D-1"){
        compBinary = "0001110";
    } else if(compField == "A-1"){
        compBinary = "0110010";
    } else if(compField == "M-1"){
        compBinary = "1110010";
    } else if(compField == "D+A"){
        compBinary = "0000010";
    } else if(compField == "D+M"){
        compBinary = "1000010";
    } else if(compField == "D-A"){
        compBinary = "0010011";
    } else if(compField == "D-M"){
        compBinary = "1010011";
    } else if(compField == "A-D"){
        compBinary = "0000111";
    } else if(compField == "M-D"){
        compBinary = "1000111";
    } else if(compField == "D&A"){
        compBinary = "0000000";
    } else if(compField == "D&M"){
        compBinary = "1000000";
    } else if(compField == "D|A"){
        compBinary = "0010101";
    } else if(compField == "D|M"){
        compBinary = "1010101";
    } else{
        std::cerr << compField << " is not a valid comp field" << std::endl;
        compBinary = "\0";
    }

    return compBinary;
}

std::string Code::jump(std::string jumpField){
    std::string jumpBinary;

    //if checks, inefficient will implement hash after for fun
    if(jumpField == ""){
        jumpBinary = "000";
    } else if(jumpField == "JGT"){
        jumpBinary = "001";
    } else if(jumpField == "JEQ"){
        jumpBinary = "010";
    } else if(jumpField == "JGE"){
        jumpBinary = "011";
    } else if(jumpField == "JLT"){
        jumpBinary = "100";
    } else if(jumpField == "JNE"){
        jumpBinary = "101";
    } else if(jumpField == "JLE"){
        jumpBinary = "110";
    } else if(jumpField == "JMP"){
        jumpBinary = "111";
    } else {
        std::cerr << jumpField << " is not a valid jump field" << std::endl;
        jumpBinary = "\0";
    }

    return jumpBinary;
}
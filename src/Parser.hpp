//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_PARSER_HPP
#define RISCV_SIMULATOR_PARSER_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Memory.hpp"

class Parser {
public:
    static char parse_hex(const std::string &hex) {
        return strtol(hex.c_str(), NULL, 16);
    }

    static void parse(std::istream &in, Memory &mem) {
        unsigned base_addr = 0;
        while (in) {
            std::string line;
            std::getline(in, line);
            if (line[0] == '@') {
                base_addr = strtol(line.c_str() + 1, NULL, 16);
            } else {
                std::stringstream ss(line);
                std::string hex;
                while (ss) {
                    ss >> hex;
                    char data = parse_hex(hex);
                    mem[base_addr++] = data;
                }
            }
        }
    }
};


#endif //RISCV_SIMULATOR_PARSER_HPP
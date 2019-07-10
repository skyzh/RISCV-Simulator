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
    static unsigned parse_hex(const std::string &hex) {
        return strtol(hex.c_str(), NULL, 16);
    }

    static void parse(std::istream &in, Memory &mem) {
        if (!in) std::cerr << "parse failed, invalid stream" << std::endl;
        unsigned base_addr = 0;
        while (in) {
            std::string line;
            std::getline(in, line);
            if (line[0] == '@') {
                base_addr = strtol(line.c_str() + 1, NULL, 16);
            } else {
                std::stringstream ss(line);
                std::string hex;
                while (ss >> hex) {
                    if (hex.length() == 0) break;
                    char data = parse_hex(hex);
                    mem[base_addr++] = data;
                }
            }
        }
    }

    static void parse_hex(std::istream &in, Memory &mem) {
        if (!in) std::cerr << "parse failed, invalid stream" << std::endl;
        unsigned base_addr = 0;
        std::string hex;
        while(in >> hex) {
            mem.write_word(base_addr, parse_hex(hex));
            base_addr += 4;
        }
    }
};


#endif //RISCV_SIMULATOR_PARSER_HPP

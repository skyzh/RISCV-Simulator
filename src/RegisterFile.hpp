//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_REGISTERFILE_HPP
#define RISCV_SIMULATOR_REGISTERFILE_HPP

#inlcude "Register.hpp"

class RegisterFile {
public:
    Register <Immediate> reg[32];
};


#endif //RISCV_SIMULATOR_REGISTERFILE_HPP

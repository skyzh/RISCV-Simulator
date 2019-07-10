//
// Created by Alex Chi on 2019-07-10.
//

#include "ReservationStation.h"
#include "../Module/ALUUnit.h"

void RS::debug() {
    std::cout << "Op\t\t\tQj\t\t\tQk\t\t\tVj\t\t\tVk\t\t\tA\t\t\tTag" << std::endl;
    std::cout << ALUUnit::resolve((ALUUnit::OP) Op.current());
    std::cout << "\t";
    std::cout << resolve(Qj.current());
    std::cout << "\t";
    std::cout << resolve(Qk.current());
    std::cout << "\t";
    debug_immediate(Vj.current());
    std::cout << "\t";
    debug_immediate(Vk.current());
    std::cout << "\t";
    debug_immediate(A.current());
    std::cout << "\t";
    debug_immediate(Tag.current());
    std::cout << std::endl;
}


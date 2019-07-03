//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_FETCH_H
#define RISCV_SIMULATOR_FETCH_H

#include "Stage.hpp"

class Fetch : public Stage {
public:
    enum F {
        inst = 0, f_pc
    };

    Fetch(Session* session);

    Immediate dispatch(Wire wire) override;
};


#endif //RISCV_SIMULATOR_FETCH_H

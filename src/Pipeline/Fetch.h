//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_FETCH_H
#define RISCV_SIMULATOR_FETCH_H

#include "Stage.h"

class Fetch : public Stage {
public:
    Fetch(Session* session);

    Immediate dispatch(const std::string &key) override;
};


#endif //RISCV_SIMULATOR_FETCH_H

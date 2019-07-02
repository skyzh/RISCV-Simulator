//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_EXECUTE_H
#define RISCV_SIMULATOR_EXECUTE_H

#include "Stage.h"
#include "../Module/ALU.h"

class Execute : public Stage {
private:
    ALU alu;
public:

    class InvalidAccess {
    };

    class InvalidOp {

    };

    Execute(Session *session);

    Immediate dispatch(const std::string &key) override;
};


#endif //RISCV_SIMULATOR_EXECUTE_H

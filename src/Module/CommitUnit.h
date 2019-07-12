//
// Created by Alex Chi on 2019-07-12.
//

#ifndef RISCV_SIMULATOR_COMMITUNIT_H
#define RISCV_SIMULATOR_COMMITUNIT_H

class OoOExecute;

class CommitUnit {
public:
    OoOExecute *e;

    CommitUnit(OoOExecute *e);

    void update();

    void tick();
};


#endif //RISCV_SIMULATOR_COMMITUNIT_H

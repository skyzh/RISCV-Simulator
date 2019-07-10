# RISCV-Simulator

| Branch        |  Build Status | Note |
| ------------- | ------------- | ------------- |
| [seq](https://github.com/skyzh/RISCV-Simulator/tree/seq)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=seq)](https://travis-ci.com/skyzh/RISCV-Simulator)  | A sequential implementation. First edition. No feed forward. |
| [feedforward](https://github.com/skyzh/RISCV-Simulator/tree/feedforward)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=feedforward)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Second edition. Based on seq. Feeding forward runs faster. (Though I don't like it.) |
| [pipeline](https://github.com/skyzh/RISCV-Simulator/tree/pipeline)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=pipeline)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Pipelined version. Based on seq. Handle hazard by forwarding. Two-level adaptive predictor. |
| [out-of-order](https://github.com/skyzh/RISCV-Simulator/tree/out-of-order)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Out-of-order execution with Tomasulo algorithm. Stall when encountering branch. 1 load-store Unit, 3 ALU unit. |
| [master](https://github.com/skyzh/RISCV-Simulator/tree/master)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=master)](https://travis-ci.com/skyzh/RISCV-Simulator)  | For online judge |

[![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)

RISCV-Simulator implemented in C++. Support RV32I ISA.

Still WIP. For complete implementation and documentation, refer to 
[pipeline](https://github.com/skyzh/RISCV-Simulator/tree/pipeline) branch.
I hope I could add speculation into this branch, therefore making a fully-capable simulator.

This branch simulates a RISC-V CPU of 2 stage: issue, execute, which supports out-of-order execution.
It implements out-of-order execution with Tomasulo algorithm. 
Stall when encountering branch. 1 load-store Unit, 3 ALU unit.

Note that since I was unable to design the equivalent circuit, this branch just shows a programmer's way to
illustrate out-of-order execution design.


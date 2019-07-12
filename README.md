# RISCV-Simulator

| Branch        |  Build Status | Note |
| ------------- | ------------- | ------------- |
| [seq](https://github.com/skyzh/RISCV-Simulator/tree/seq)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=seq)](https://travis-ci.com/skyzh/RISCV-Simulator)  | A sequential implementation. First edition. No feed forward. |
| [feedforward](https://github.com/skyzh/RISCV-Simulator/tree/feedforward)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=feedforward)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Second edition. Based on seq. Feeding forward runs faster. (Though I don't like it.) |
| [pipeline](https://github.com/skyzh/RISCV-Simulator/tree/pipeline)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=pipeline)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Pipelined version. Based on seq. Handle hazard by forwarding. Two-level adaptive predictor. |
| [out-of-order](https://github.com/skyzh/RISCV-Simulator/tree/out-of-order)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Out-of-order execution with Tomasulo algorithm. |
| [master](https://github.com/skyzh/RISCV-Simulator/tree/master)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=master)](https://travis-ci.com/skyzh/RISCV-Simulator)  | For online judge |

[![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)

RISCV-Simulator implemented in C++. Support RV32I ISA.

中文文档：[make-you-a-riscv-simulator (draft).pdf](https://github.com/skyzh/RISCV-Simulator/files/3386561/make-you-a-riscv-simulator.draft.pdf)

This branch simulates a RISC-V CPU of 2 stage: issue and execute, 
which supports out-of-order execution.

It implements out-of-order execution with Tomasulo algorithm. 
For branch, It applies hardware speculation to speculate the following
instructions. 1 load buffer, 1 store buffer, 3 ALU unit, 1 branch unit,
and a 4-entry reorder buffer.

Note that since I was unable to design the equivalent circuit, this branch 
just shows a programmer's way to illustrate out-of-order execution design.

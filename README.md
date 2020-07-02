# RISCV-Simulator

[![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)

RISCV-Simulator implemented in C++. Support RV32I ISA.

Generally this should be done with a **5-stage pipeline**. This implementation may be found at [pipeline](https://github.com/skyzh/RISCV-Simulator/tree/pipeline) branch.

All CPU and CPU simulators I've made are listed below.

|                                                                     | Technique                                      | Implementation |
|---------------------------------------------------------------------|------------------------------------------------|----------------|
| [RISC-V v1](https://github.com/skyzh/RISCV-Simulator/tree/pipeline) | 5-stage pipeline  simulator                 | C++            |
| [RISC-V v2](https://github.com/skyzh/RISCV-Simulator)               | dynamic scheduling simulator <br> Tomasulo + Speculation | C++            |
| [MIPS](https://github.com/skyzh/mips-simulator)                     | 5-stage pipeline  simulator                             | Haskell        |
| [MIPS](https://github.com/skyzh/mips-cpu)                           | 5-stage pipeline CPU        | Verilog        |

The architecture is derived from **Tomasulo** and **Speculation** described in CA:AQA Chapter 3. While the method in the textbook is not detailed enough to carry out a CPU design (It illustrates the algorithm with only one float unit instead of a CPU), I came up with some ideas to complete the design for a fully-functional RISC-V CPU. It can be summarized as follows:

* Handle memory hazards
* RISC-V `jalr` instruction
* Handle branch mis-prediction in the architecture with just Tomasulo algorithm

For a full report on how I made this simulator and solutions to the challenges above, refer to [Make You a RISC-V Simulator (PDF, Chinese)](https://github.com/skyzh/RISCV-Simulator/files/3389385/make-you-a-riscv-simulator.final.2.pdf)

For statistics and reports on sample programs, refer to [Travis-CI build log](https://travis-ci.com/github/skyzh/RISCV-Simulator).

This branch simulates a RISC-V CPU of 2 stage: issue and execute, 
which supports out-of-order execution.

It implements out-of-order execution with Tomasulo algorithm. 
For branch, It applies hardware speculation to speculate the following
instructions. 3 load buffer, 3 store buffer, 4 ALU unit, and a 12-entry 
reorder buffer. Use Two-level adaptive predictor for branch prediction.

Note that since I was unable to design the equivalent circuit, this branch 
just shows a programmer's way to illustrate out-of-order execution design.

You may go into Presentation Mode to view detailed execution information.

<img width="1680" alt="Screen Shot 2019-09-06 at 10 07 22 AM" src="https://user-images.githubusercontent.com/4198311/64395894-5dd9d080-d08e-11e9-8b7c-888b3018f431.png">


| Branch        |  Build Status | Note |
| ------------- | ------------- | ------------- |
| [seq](https://github.com/skyzh/RISCV-Simulator/tree/seq)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=seq)](https://travis-ci.com/skyzh/RISCV-Simulator)  | A sequential implementation. First edition. No feed forward. |
| [feedforward](https://github.com/skyzh/RISCV-Simulator/tree/feedforward)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=feedforward)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Second edition. Based on seq. Feeding forward runs faster. (Though I don't like it.) |
| [pipeline](https://github.com/skyzh/RISCV-Simulator/tree/pipeline)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=pipeline)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Pipelined version. Based on seq. Handle hazard by forwarding. Two-level adaptive predictor. |
| [out-of-order](https://github.com/skyzh/RISCV-Simulator/tree/out-of-order)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)  | Out-of-order execution with Tomasulo algorithm and Speculation. |
| [master](https://github.com/skyzh/RISCV-Simulator/tree/master)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=master)](https://travis-ci.com/skyzh/RISCV-Simulator)  | For online judge |

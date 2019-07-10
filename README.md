# RISCV-Simulator

[![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=out-of-order)](https://travis-ci.com/skyzh/RISCV-Simulator)

RISCV-Simulator implemented in C++. Support RV32I ISA.

This branch simulates a RISC-V CPU of 2 stage: issue, execute. It supports out-of-order execution.

Note that since I was unable to design the equivalent circuit, this branch just shows a programmer's way to
implement out-of-order execution design.

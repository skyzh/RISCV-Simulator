# RISCV-Simulator

[![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=pipeline)](https://travis-ci.com/skyzh/RISCV-Simulator)

RISCV-Simulator implemented in C++. Support RV32I ISA.

This branch simulates a sequential RISC-V CPU.

## Why Functional?

Personally I would like to implement a simulator which reflects the 
hardware design as closely as possible. Inspired by CSAPP HCL (some 
examples below), I make one constraint in my implementation, therefore accomplishing this goal.

```
int dstE = [ 
    icode in { IRRMOVL } : rB; 
    icode in { IIRMOVL, IOPL} : rB; 
    icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP; 
     : RNONE; # Don’t write any register 
];
```

### There is no feed forward of data

Contrary to CSAPP HCL, where we cannot read back data, there's no 
feed forward of data in my implementation.

Data in circuit depends on other data in the circuit. Initial register state
and contents in the memory determine the outcome. Therefore pipeline status
can be updated by obtaining the next PC.

```cpp
    PC.write(w->get("w_pc"));
```

There are only two exceptions. In write back stage, registers
should be updated no matter whether its value is required. The
same applies to memory access stage.

Then we can update register clock, and process the next cycle.

### Therefore, it's functional

The process described above resembles lazy evaluation of a function
in Haskell. It can be easily expressed in a functional way. In this
project, `Stage` object saves all such functions, hence an intermediate
value won't be evaluated twice in a single cycle.

### Equivalent Circuit

[PDF](https://github.com/skyzh/RISCV-Simulator/files/3350303/Note.Jul.2.2019.9_14_07.PM.pdf)


## Tips

* Register x0 is always zero.
* Be careful with branch jump. Make sure you know next instruction is relative to PC or the next.
* You should write return address to rd when executing jal.
* When I was debugging, I printed out PC at every moment to check branching functionality.
* And I made a trap at 0x1000 then print register a0 to know what printInt was exactly printing.

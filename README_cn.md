# RISCV-Simulator


| Branch        |  Build Status | Note |
| ------------- | ------------- | ------------- |
| [seq](https://github.com/skyzh/RISCV-Simulator/tree/seq)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=seq)](https://travis-ci.com/skyzh/RISCV-Simulator)  | 串行实现，递归求值。 |
| [feedforward](https://github.com/skyzh/RISCV-Simulator/tree/feedforward)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=feedforward)](https://travis-ci.com/skyzh/RISCV-Simulator)  | 虽然这个实现和我刚开始想的有点差异，但它跑得快。 |
| [pipeline](https://github.com/skyzh/RISCV-Simulator/tree/pipeline)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=pipeline)](https://travis-ci.com/skyzh/RISCV-Simulator)  | 处理了 Hazard 并且加了分支预测的并行实现。 |
| [master](https://github.com/skyzh/RISCV-Simulator/tree/master)  | [![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=master)](https://travis-ci.com/skyzh/RISCV-Simulator)  | OJ 使用的分支 |

[![Build Status](https://travis-ci.com/skyzh/RISCV-Simulator.svg?branch=pipeline)](https://travis-ci.com/skyzh/RISCV-Simulator)

C++ 实现的 RISC-V 模拟器，支持 RV32I 指令集。

pipeline 分支中模拟的是一个五级流水线的 RISC-V CPU。
现在的设计通过 Forward 和 Stall 处理 Data Hazard 和 Control Hazard。
通过 Two-level Adaptive Predictor 预测分支，在某些样例中达到了 98% 的准确率。测试结果可参照 [Branch.md](https://github.com/skyzh/RISCV-Simulator/blob/pipeline/Branch.md)。

## 函数式实现？

在设计之初，我希望模拟器的实现可以尽可能贴近硬件电路。
在 CSAPP HCL 的启发下（样例如下），我在设计时遵循下面提到的原则，从而实现这一目标。


```
int dstE = [ 
    icode in { IRRMOVL } : rB; 
    icode in { IIRMOVL, IOPL} : rB; 
    icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP; 
     : RNONE; # Don’t write any register 
];
```

### 中间值只能被读取

在电路中，一旦初始响应确定，我们就可以计算出每一个端口的电平。
CPU 电路的设计也是这样。在串行 (Sequential) 实现中，我采用下面的方法执行指令。

```cpp
    PC.write(w->get(WriteBack::w_pc));
```

要获取下一个 PC，我们只需要知道 Write Back 阶段得到的 PC。
而要获取 Write Back 阶段的 PC，我们需要获得 Execute 阶段得到的分支……
依次类推，通过获得 Write Back 阶段的 PC，我们就能间接求出电路中每一个端口的数值，从而通过程序模拟电路。

当然，在这之中，也有两个例外。在 Write Back 阶段，不论寄存器的值有没有被用到，都要把值写入寄存器中。Memory Access 阶段也是如此。

因而，只要获取电路中 Write Back 阶段的 PC 值，就可以向 PC 写入新的值，并进行下一个周期。

### 这很类似 FP 的求值

之前所述的过程，其实就是通过电路参数的依赖关系求出最终的 PC。
这一过程和 Haskell 等语言的惰性求值十分类似。
在串行实现中，我通过递归求得每一个端口的数值，与此同时，通过 Stage 对象保存一个时钟周期中端口的值。
毕竟一个周期中，电路的参数仅受激励（寄存器和内存）影响，一个端口的数值不管算多少遍，都是一样的。（也就是说，算电平的函数是个纯函数）
通过这种方式，可以稍微加快模拟器的运行速度。

### 但这还是很慢

上面的实现跑起来比较慢。我们可以加速这一过程。

CPU 的电路在程序运行之时就已经被确定了。因而，我可以手动指定求值顺序。在 `Session.cpp` 中，

```cpp
    w->hook(); // Write back
    m->hook(); // Memory access
    e->hook(); // Execute
    d->hook(); // Decode
    f->hook(); // Fetch
```

比如，在 Decode 阶段，我们需要确定后面的阶段中是否有 Hazard。因而，Decode 阶段必然在 Write Back、Memory Access 和 Execute 阶段之后执行。

以这样的求值顺序，只需要将不同阶段的 hook 调用一次，就可以达到电路稳态。这样，模拟器运行起来就更快了。

### 验证手动指定求值顺序的实现是「并行」的

在 `Session.cpp` 中，注释中的程序随机选取五个阶段的求值顺序。这个循环执行十遍后，电路必然可以达到稳态，和手动指定求值顺序的结果一致。因此，模拟器的运行和五个阶段的求值顺序无关。这个模拟器是并行的。

当然也有其他方法验证。比如开五个线程分别更新五个阶段，每隔 1ms 更新一次时钟。这种验证方法似乎就更加贴近电路中电压的传播了。

### 模拟器使用的 CPU 电路

[RISCV Design.pdf](https://github.com/skyzh/RISCV-Simulator/files/3362948/RISCV.Design.pdf)

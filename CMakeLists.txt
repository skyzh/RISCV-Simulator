cmake_minimum_required(VERSION 3.12)
project(RISCV_Simulator)

set(CMAKE_CXX_STANDARD 14)

add_library(RISCV_Simulator STATIC src/Parser.hpp src/Instruction.hpp src/Pipeline/Stage.hpp src/Pipeline/Fetch.cpp src/Pipeline/Fetch.h src/Pipeline/Decode.cpp src/Pipeline/Decode.h src/Pipeline/Execute.cpp src/Pipeline/Execute.h src/Pipeline/MemoryAccess.cpp src/Pipeline/MemoryAccess.h src/Pipeline/WriteBack.cpp src/Pipeline/WriteBack.h src/Module/ALU.cpp src/Module/ALU.h src/Register.hpp src/Tickable.h src/Session.cpp src/Session.h src/Memory.hpp src/RegisterFile.hpp src/Common.h src/Module/Branch.cpp src/Module/Branch.h)
add_executable(RISCV_Simulator_Test src/main_test.cpp src/Parser_test.cpp src/Instruction_test.cpp src/Register_test.cpp src/Module/ALU_test.cpp src/Session_test.cpp src/Memory_test.cpp src/RegisterFile_test.cpp)
add_executable(RISCV_Simulator_Main src/main.cpp)

enable_testing()
find_package(GTest MODULE REQUIRED)
target_link_libraries(RISCV_Simulator_Test PRIVATE GTest::GTest GTest::Main RISCV_Simulator)
target_link_libraries(RISCV_Simulator_Main RISCV_Simulator)
add_test(AllTestsInRISCV_Simulator RISCV_Simulator_Test)

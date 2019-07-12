cmake_minimum_required(VERSION 3.12)
project(RISCV_Simulator)

set(CMAKE_CXX_STANDARD 14)

add_library(RISCV_Simulator STATIC src/Common/Parser.hpp src/Common/Instruction.hpp src/Common/Register.hpp src/Common/Session.cpp src/Common/Session.h src/Common/Memory.hpp src/Common/RegisterFile.hpp src/Common/Common.h src/Module/BranchPrediction.cpp src/Module/BranchPrediction.h src/Pipeline/Issue.cpp src/Pipeline/Issue.h src/Common/ReservationStation.h src/Pipeline/OoOExecute.cpp src/Pipeline/OoOExecute.h src/Module/ALUUnit.cpp src/Module/ALUUnit.h src/Pipeline/OoOCommon.h src/Module/LoadStoreUnit.cpp src/Module/LoadStoreUnit.h src/Common/utils.h src/Common/utils.cpp src/Common/ReservationStation.cpp src/Common/ReorderBuffer.cpp src/Common/ReorderBuffer.h src/Module/CommitUnit.cpp src/Module/CommitUnit.h)
add_executable(RISCV_Simulator_Test src/Common/Parser_test.cpp src/Common/Instruction_test.cpp src/Common/Register_test.cpp src/Common/Session_test.cpp src/Common/Memory_test.cpp src/Common/RegisterFile_test.cpp)
add_executable(RISCV_Simulator_Main src/main.cpp)

find_package(GTest MODULE REQUIRED)

target_link_libraries(RISCV_Simulator_Test PRIVATE RISCV_Simulator GTest::GTest GTest::Main)
target_link_libraries(RISCV_Simulator_Main RISCV_Simulator)

enable_testing()
add_test(AllTestsInMain RISCV_Simulator_Test)

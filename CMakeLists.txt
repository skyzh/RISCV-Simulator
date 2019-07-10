cmake_minimum_required(VERSION 3.12)
project(RISCV_Simulator)

set(CMAKE_CXX_STANDARD 14)

add_library(RISCV_Simulator STATIC src/Parser.hpp src/Instruction.hpp src/Register.hpp src/Tickable.h src/Session.cpp src/Session.h src/Memory.hpp src/RegisterFile.hpp src/Common.h src/Module/BranchPrediction.cpp src/Module/BranchPrediction.h src/Pipeline/Issue.cpp src/Pipeline/Issue.h src/ReservationStation.h src/Pipeline/OoOExecute.cpp src/Pipeline/OoOExecute.h src/Module/ALUUnit.cpp src/Module/ALUUnit.h src/Pipeline/OoOCommon.h src/Module/LoadStoreUnit.cpp src/Module/LoadStoreUnit.h src/utils.h src/utils.cpp src/ReservationStation.cpp)
add_executable(RISCV_Simulator_Test src/main_test.cpp src/Parser_test.cpp src/Instruction_test.cpp src/Register_test.cpp src/Session_test.cpp src/Memory_test.cpp src/RegisterFile_test.cpp)
add_executable(RISCV_Simulator_Main src/main.cpp)

enable_testing()
find_package(GTest MODULE REQUIRED)
target_link_libraries(RISCV_Simulator_Test PRIVATE GTest::GTest GTest::Main RISCV_Simulator)
target_link_libraries(RISCV_Simulator_Main RISCV_Simulator)
add_test(AllTestsInRISCV_Simulator RISCV_Simulator_Test)

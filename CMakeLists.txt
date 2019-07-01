cmake_minimum_required(VERSION 3.14)
project(RISCV_Simulator)

set(CMAKE_CXX_STANDARD 14)

add_library(RISCV_Simulator src/simulator.cpp src/simulator.cpp)
add_executable(RISCV_Simulator_Test src/main_test.cpp)
add_executable(RISCV_Simulator_Main src/main.cpp)

enable_testing()
find_package(GTest MODULE REQUIRED)
target_link_libraries(RISCV_Simulator_Test PRIVATE GTest::GTest GTest::Main RISCV_Simulator)
target_link_libraries(RISCV_Simulator_Main RISCV_Simulator)
add_test(AllTestsInRISCV_Simulator RISCV_Simulator_Test)

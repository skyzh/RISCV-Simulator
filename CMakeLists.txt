cmake_minimum_required(VERSION 3.5)
project(RISCV_Simulator)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

add_library(RISCV_Simulator STATIC src/Parser.hpp src/Instruction.hpp src/Pipeline/Stage.hpp src/Pipeline/Fetch.cpp src/Pipeline/Fetch.h src/Pipeline/Decode.cpp src/Pipeline/Decode.h src/Pipeline/Execute.cpp src/Pipeline/Execute.h src/Pipeline/MemoryAccess.cpp src/Pipeline/MemoryAccess.h src/Pipeline/WriteBack.cpp src/Pipeline/WriteBack.h src/Module/ALU.cpp src/Module/ALU.h src/Register.hpp src/Tickable.h src/Session.cpp src/Session.h src/Memory.hpp src/RegisterFile.hpp src/Common.h)
add_executable(code src/main.cpp)
target_link_libraries(code RISCV_Simulator)


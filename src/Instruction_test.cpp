//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "Instruction.hpp"

TEST(Instruction, CorrectSize) {
    EXPECT_EQ(sizeof(Instruction), 4);
}

TEST(Instruction, InstructionR) {
    //                  10987654321098765432109876543210
    InstructionR inst(0b10101010101010101010101010101010);
    //                    10987654321098765432109876543210
    EXPECT_EQ(inst.opcode, 0b0101010);
    EXPECT_EQ(inst.rd, 0b10101);
    EXPECT_EQ(inst.rs1, 0b10101);
    EXPECT_EQ(inst.rs2, 0b01010);
    EXPECT_EQ(inst.funct3, 0b010);
}

TEST(Instruction, InstructionI) {
    //                  10987654321098765432109876543210
    InstructionI inst(0b10101010101010101010101010101010);
    //                    10987654321098765432109876543210
    EXPECT_EQ(inst.imm, 0b11111111111111111111101010101010);
    EXPECT_EQ(inst.opcode, 0b0101010);
    EXPECT_EQ(inst.rd, 0b10101);
    EXPECT_EQ(inst.rs1, 0b10101);
    EXPECT_EQ(inst.funct3, 0b010);
}

TEST(Instruction, InstructionS) {
    //                  10987654321098765432109876543210
    InstructionS inst(0b10101010101010101010101010101010);
    //                    10987654321098765432109876543210
    EXPECT_EQ(inst.imm, 0b11111111111111111111101010110101);
    EXPECT_EQ(inst.opcode, 0b0101010);
    EXPECT_EQ(inst.rs1, 0b10101);
    EXPECT_EQ(inst.rs2, 0b01010);
    EXPECT_EQ(inst.funct3, 0b010);
}

TEST(Instruction, InstructionB) {
    //                  10987654321098765432109876543210
    InstructionB inst(0b10101010101010101010101010101010);
    //                    10987654321098765432109876543210
    EXPECT_EQ(inst.imm, 0b11111111111111111111101010110100);
    EXPECT_EQ(inst.opcode, 0b0101010);
    EXPECT_EQ(inst.rs1, 0b10101);
    EXPECT_EQ(inst.rs2, 0b01010);
    EXPECT_EQ(inst.funct3, 0b010);
}

TEST(Instruction, InstructionU) {
    //                  10987654321098765432109876543210
    InstructionU inst(0b10101010101010101010101010101010);
    //                    10987654321098765432109876543210
    EXPECT_EQ(inst.imm, 0b10101010101010101010000000000000);
    EXPECT_EQ(inst.opcode, 0b0101010);
    EXPECT_EQ(inst.rd, 0b10101);
}

TEST(Instruction, InstructionJ) {
    //                  10987654321098765432109876543210
    InstructionJ inst(0b10101010101010101010101010101010);
    //                    10987654321098765432109876543210
    EXPECT_EQ(inst.imm, 0b11111111111110101010001010101010);
    EXPECT_EQ(inst.opcode, 0b0101010);
    EXPECT_EQ(inst.rd, 0b10101);
}

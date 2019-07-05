.globl main
.text
main:
li a1, 0x10
nop
nop
nop
jalr a0, a1, 8
addi a0, a0, 8
addi  a0, a0, 8
test:
li	a2,255
lui	a3,0x30
sb	a2,4(a3)
nop
nop
nop
nop
nop
nop
nop
nop

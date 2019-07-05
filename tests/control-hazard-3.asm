.globl main
.text
main:
li a1, 0x4
jalr a0, a1, 4
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

.globl main
.text
main:
jal test
addi  a0, a0, 8
addi  a0, a0, 8
addi  a0, a0, 8
addi  a0, a0, 8
test:
addi  a0, a0, 8
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
nop
nop
nop
nop
nop

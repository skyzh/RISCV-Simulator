.globl main
.text
main:
addi a1, a1, 15
nop
addi a2, a2, 16
add  a0, a1, a2
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

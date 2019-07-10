lui sp,0x20
jal main
li a2,255
lui a3,0x30
sb a2,4(a3)
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
nop
nop
main:
li a0, 1
li a1, 1
li a2, 2
li a3, 55
loop:
add a2, a1, a0
mv a0, a1
mv a1, a2
bne a3, a0, loop
ret
nop

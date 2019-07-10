li a0, 1
li a1, 1
li a2, 2
loop:
add a2, a1, a0
mv a0, a1
mv a1, a2
jal loop

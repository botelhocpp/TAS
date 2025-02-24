main:
movu r0, #0xF0
ldr r1, [r0, #2]
str r1, [r0, #0]
jmp main

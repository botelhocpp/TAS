// Copyright (c) 2025 TAS
// All rights reserved

main:
    mov r0, #0x10
    mov r1, #0x11
    mov r2, #0x12
    mov r3, #0x13
    mov r4, #0x14
    mov r5, #0x15
    
    push r0
    push r1
    push r2
    push r3
    push r4
    push r5

    add r0, r0, r1
    sub r0, r0, r1
    cmp r0, #0x10
    bne error

    str r2, [r0, #2]
    ldr r3, [r0, #2]
    cmp r3, r2 
    bne error

    pop r0
    pop r1
    pop r2
    pop r3
    pop r4
    pop r5

    cmp r5, #0x10
    bne error
    
    cmp r4, #0x11
    bne error

    cmp r3, #0x12
    bne error

    cmp r2, #0x13
    bne error

    cmp r1, #0x14
    bne error

    cmp r0, #0x15
    bne error

    jmp .

error:
    jmp error
// Copyright (c) 2025 TAS
// All rights reserved

main:
    mov s0, #0
    mov s1, #0x00
    movu s1, #0x10

main_fill_memory:

    // Read serial
    add t0, pc, #4
    push t0
    jmp uart_read

    // Write to RAM
    str a0, [s0, #0]
    add s0, s0, #2
    cmp s0, s1
    blt main_fill_memory
    
    // Jump to start of memory
    mov pc, #0x0000

uart_read:
    xor t0, t0, t0
    movu t0, #0xF4

uart_read_wait_rxdone:
    ldr t1, [t0, #4]
    and t1, t1, #0x4
    beq uart_read_wait_rxdone

    ldr a0, [t0, #2]
    pop pc
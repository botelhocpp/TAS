// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc
%include uart.inc

// .text
main:
    add t0, pc, #4
    push t0
    jmp uart_write

    jmp .

uart_write:
    add t0, pc, #4
    push t0

    jmp .

// .org 0x100
// .data
// var: .word 10

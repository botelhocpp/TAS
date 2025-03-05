// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

// ========================================
_start:   
// ======================================== 
    mov s0, #LED_SWITCH_ADDR
    
_main:
    add t0, pc, #4
    push t0
    jmp _uart_read

    str a0, [s0, #LED_SWITCH_DATAOUT]
    
    add t0, pc, #4
    push t0
    jmp _uart_write

    jmp _main

// ========================================
_uart_read:
// ========================================
    mov t0, #0x00
    movu t0, #UART_ADDR

_uart_read_wait_rxdone:
    ldr t1, [t0, #UART_CONTROL]
    and t1, t1, #UART_CONTROL_RXDONE
    beq _uart_read_wait_rxdone

    mov t1, #0
    str t1, [t0, #UART_CONTROL]

    ldr a0, [t0, #UART_RXDATA]
    pop pc

// ========================================
_uart_write:
// ========================================
    mov t0, #0x00
    movu t0, #UART_ADDR

_uart_write_wait_txdone:
    ldr t1, [t0, #UART_CONTROL]
    and t1, t1, #UART_CONTROL_TXDONE
    beq _uart_write_wait_txdone

    str a0, [t0, #UART_TXDATA]
    
    mov t1, #UART_CONTROL_TXEN
    str t1, [t0, #UART_CONTROL]
    
    pop pc
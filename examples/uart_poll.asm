// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start:         mov s0, #0
                movu s0, #UART_ADDR

_uart_wait_rx:  ldr t0, [s0, #UART_CONTROL]
                and t0, t0, #UART_CONTROL_RXDONE
                beq _uart_wait_rx
                mov t0, #0
                str t0, [s0, #UART_CONTROL]

_uart_read:     ldr s1, [s0, #UART_RXDATA]

_uart_wait_tx:  ldr t0, [s0, #UART_CONTROL]
                and t0, t0, #UART_CONTROL_TXDONE
                beq _uart_wait_tx

_uart_write:    str s1, [s0, #UART_TXDATA]
    
_uart_transmit: mov t0, #UART_CONTROL_TXEN
                str t0, [s0, #UART_CONTROL]

_goto_start:    jmp _uart_wait_rx

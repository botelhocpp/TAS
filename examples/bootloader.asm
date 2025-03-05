// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start:         mov s0, #0
                mov s1, #0xFF
                movu s1, #0xFF

_get_uart_addr: xor t0, t0, t0
                movu t0, #UART_ADDR     

_uart_read_lsb: ldr t1, [t0, #UART_CONTROL]
                and t1, t1, #UART_CONTROL_RXDONE
                beq _uart_read_lsb
                ldr a0, [t0, #UART_RXDATA]
                mov t1, #0
                str t1, [t0, #UART_CONTROL]

_uart_read_msb: ldr t1, [t0, #UART_CONTROL]
                and t1, t1, #UART_CONTROL_RXDONE
                beq _uart_read_msb
                ldr a1, [t0, #UART_RXDATA]
                mov t1, #0
                str t1, [t0, #UART_CONTROL]

_assemble_inst: shl a1, a1, #8
                or a0, a0, a1
                cmp a0, s1
                beq _cleanup

_write_ram:     str a0, [s0, #0]
                add s0, s0, #2
                jmp _uart_read_lsb

_cleanup:       mov a0, #0
                mov a1, #0
                mov t0, #0
                mov t1, #0
                mov s0, #0
                mov s1, #0

_goto_program:  mov pc, #0x0000
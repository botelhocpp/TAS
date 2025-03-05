// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

// Interrupt Vectors
_vectors:       jmp _start
                jmp _irq_handler

// Main Code
_start:         crid
                mov s0, #0
                movu s0, #LED_SWITCH_ADDR   
                mov s1, #0
                movu s1, #UART_ADDR

_enable_irq:    mov t0, #UART_CONTROL_RXIRQEN
                str t0, [s1, #UART_CONTROL]
                crie

_while:         jmp _while

// Interrupt Handler
_irq_handler:   crid
                push r0
                push r1
                push r2
                push r3
                push r4
                push r5

_uart_to_led:   ldr t0, [s1, #UART_RXDATA]
                str t0, [s0, #LED_SWITCH_DATAOUT]
                
_clear_flag:    mov t1, #UART_CONTROL_RXDONE
                not t1, t1
                ldr t0, [s1, #UART_CONTROL] 
                and t0, t0, t1
                str t0, [s1, #UART_CONTROL]

_handler_end:   pop r5
                pop r4
                pop r3
                pop r2
                pop r1
                pop r0
                crie
                iret
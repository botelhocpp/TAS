// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

%define START_STRING    0x40
%define END_OF_STRING   0x0A

// Interrupt Vectors
_vectors:       jmp _start
                jmp _irq_handler

// Main Code
_start:         crid
                mov s0, #0
                movu s0, #UART_ADDR
                mov s1, #0
                movu s1, #START_STRING

_enable_irq:    mov t0, #UART_CONTROL_RXIRQEN
                str t0, [s0, #UART_CONTROL]
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

_check_cause:   ldr t0, [s0, #UART_CONTROL]
                and t1, t0, #UART_CONTROL_RXDONE 
                bne _handle_rx
                and t1, t0, #UART_CONTROL_TXDONE 
                bne _handle_tx

_handler_end:   pop r5
                pop r4
                pop r3
                pop r2
                pop r1
                pop r0
                crie
                iret

// RX Interrupt Handler
_handle_rx:     ldr t0, [s0, #UART_RXDATA]
                str t0, [s0, #UART_TXDATA]
                str t0, [s1, #0]
                add s1, s1, #2
                cmp t0, #END_OF_STRING
                bne _clear_rx_flag

_enable_txirq:  mov t1, #UART_CONTROL_TXIRQEN
                ldr t0, [s0, #UART_CONTROL] 
                or t0, t0, t1
                str t0, [s0, #UART_CONTROL]
                mov s1, #0
                            
_clear_rx_flag: mov t1, #UART_CONTROL_RXDONE
                not t1, t1
                ldr t0, [s0, #UART_CONTROL] 
                and t0, t0, t1
                str t0, [s0, #UART_CONTROL]
                jmp _handler_end

// TX Interrupt Handler
_handle_tx:     ldr t0, [s1, #0]
                add s1, s1, #2
                str t0, [s0, #UART_TXDATA]
                cmp t0, #END_OF_STRING
                bne _en_transmit

_disable_txirq: mov t1, #UART_CONTROL_TXIRQEN
                ldr t0, [s0, #UART_CONTROL] 
                not t1, t1
                and t0, t0, t1
                str t0, [s0, #UART_CONTROL]
                mov s1, #0
                
_en_transmit:   mov t1, #UART_CONTROL_TXEN
                ldr t0, [s0, #UART_CONTROL] 
                or t0, t0, t1
                str t0, [s0, #UART_CONTROL]
                jmp _handler_end

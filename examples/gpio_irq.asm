// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

// Interrupt Vectors
_vectors:       jmp _start
                jmp _irq_handler

// Main Code
_start:         crid
                mov s0, #0
                movu s0, #GPIO_ADDR

_config:        mov t0, #0xFF
                str t0, [s0, #GPIO_DATADIR] 
                mov t0, #0
                movu t0, #0x40
                str t0, [s0, #GPIO_PINMUX] 

_enable_irq:    mov t0, #0
                movu t0, #0xFF
                str t0, [s0, #GPIO_CONTROL]
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

_toggle_leds:   ldr t0, [s0, #GPIO_DATAOUT]
                mov t1, #0xFF
                xor t0, t0, t1
                str t0, [s0, #GPIO_DATAOUT]
                
_clear_flag:    mov t0, #0
                str t0, [s0, #GPIO_IRQSTATUS]

_handler_end:   pop r5
                pop r4
                pop r3
                pop r2
                pop r1
                pop r0
                crie
                iret

// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

%define SWITCH_MASK 0x0F

// Interrupt Vectors
_vectors:       jmp _start
                jmp _irq_handler

// Main Code
_start:         crid
                mov s0, #0
                movu s0, #LED_SWITCH_ADDR
                mov t0, #SWITCH_MASK
                str t0, [s0, #LED_SWITCH_CONTROL]
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

_toggle_leds:   ldr t0, [s0, #LED_SWITCH_DATAOUT]
                xor t0, t0, #SWITCH_MASK
                str t0, [s0, #LED_SWITCH_DATAOUT]
                
_clear_flag:    mov t0, #0
                str t0, [s0, #LED_SWITCH_IRQSTATUS]

_handler_end:   pop r5
                pop r4
                pop r3
                pop r2
                pop r1
                pop r0
                crie
                iret

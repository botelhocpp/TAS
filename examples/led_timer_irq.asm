// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

// Interrupt Vectors
_vectors:         jmp _start
                  jmp _irq_handler

// Main Code
_start:           crid

get_timer_addr:   mov s0, #0
                  movu s0, #TIMER_ADDR

// Set Frequency to 25MHz/2000 = 12.5kHz
set_prescaler:    mov t0, #0xCF
                  movu t0, #0x07
                  str t0, [s0, #TIMER_PRESCALER]

// Ser Reload to 12,500
set_reload:       mov t0, #0xd3
                  movu t0, #0x30
                  str t0, [s0, #TIMER_RELOAD]

start_timer:      mov t0, #TIMER_CONTROL_START
                  or t0, t0, #TIMER_CONTROL_IRQEN
                  str t0, [s0, #TIMER_CONTROL]
                  crie

while:            jmp while

// Interrupt Handler
_irq_handler:     crid
                  push r0
                  push r1
                  push r2
                  push r3
                  push r4
                  push r5

check_cause:      ldr a0, [s0, #TIMER_CONTROL]
                  and a1, a0, #TIMER_CONTROL_DONE
                  beq isr_end
    
toggle_leds:      mov t0, #0
                  movu t0, #LED_SWITCH_ADDR
                  ldr t1, [t0, #LED_SWITCH_DATAOUT]
                  xor t1, t1, #0xF
                  str t1, [t0, #LED_SWITCH_DATAOUT]

_clear_irq_flag:  mov t0, #TIMER_CONTROL_DONE
                  not t0, t0
                  and a0, a0, t0
                  or a0, a0, #TIMER_CONTROL_START
                  str a0, [s0, #TIMER_CONTROL]

isr_end:          pop r5
                  pop r4
                  pop r3
                  pop r2
                  pop r1
                  pop r0
                  crie
                  iret

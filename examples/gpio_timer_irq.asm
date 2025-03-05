// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

// Interrupt Vectors
_vectors:         jmp _start
                  jmp _irq_handler

// Main Code
_start:           crid

get_addr:         mov s0, #0
                  movu s0, #TIMER_ADDR
                  mov s1, #0
                  movu s1, #GPIO_ADDR
                  
_config:          mov t0, #0xFF
                  movu t0, #0xFF
                  str t0, [s1, #GPIO_DATADIR] 
                  mov t0, #0
                  movu t0, #0x40
                  str t0, [s1, #GPIO_PINMUX] 
                  
// Set Frequency to 25MHz/2*1000 = 12.5kHz
set_prescaler:    mov t0, #0xE8
                  movu t0, #0x03
                  str t0, [s0, #TIMER_PRESCALER]

// Ser Reload to 10
set_reload:       mov t0, #0x09
                  movu t0, #0x00
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
    
toggle_leds:      ldr t1, [s1, #GPIO_DATAOUT]
                  mov t0, #0xFF
                  movu t0, #0xFF
                  xor t1, t1, t0
                  str t1, [s1, #GPIO_DATAOUT]

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

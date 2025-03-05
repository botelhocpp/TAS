// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start:         mov s0, #0
                movu s0, #TIMER_ADDR
                mov s1, #0
                movu s1, #LED_SWITCH_ADDR

// Set Frequency to 25MHz/2000 = 12.5kHz
_set_prescaler: mov t0, #0xCF
                movu t0, #0x07
                str t0, [s0, #TIMER_PRESCALER]

// Set Reload to 12,500
_set_reload:    mov t0, #0xD3
                movu t0, #0x30
                str t0, [s0, #TIMER_RELOAD]
    
_set_leds:      ldr t0, [s1, #LED_SWITCH_DATAOUT]
                xor t0, t0, #LED_MASK
                str t0, [s1, #LED_SWITCH_DATAOUT]

_delay_start:   mov t0, #TIMER_CONTROL_START
                str t0, [s0, #TIMER_CONTROL]

_delay_wait:    ldr t0, [s0, #TIMER_CONTROL]
                and t0, t0, #TIMER_CONTROL_DONE
                beq _delay_wait

_goto_set_leds: jmp _set_leds
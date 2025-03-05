// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

%define LED_MASK 0x0F

//===================================
_start: 
//===================================

_call_timer_setup:
    add t0, pc, #4
    push t0
    jmp _timer_setup
    
_call_led_toggle:
    add t0, pc, #4
    push t0
    jmp _led_toggle

_call_timer_delay:
    add t0, pc, #4
    push t0
    jmp _timer_delay

_repeat:
    jmp _call_led_toggle

//===================================
_led_toggle:
//===================================
    mov t0, #0
    movu t0, #LED_SWITCH_ADDR

_led_toggle_write:
    ldr t1, [t0, #LED_SWITCH_DATAOUT]
    xor t1, t1, #LED_MASK
    str t1, [t0, #LED_SWITCH_DATAOUT]

    pop pc

//===================================
_timer_setup:
//===================================
    mov t0, #0
    movu t0, #TIMER_ADDR

// Set Frequency to 25MHz/400 = 62.5kHz
_set_prescaler:
    mov t1, #0x90
    movu t1, #0x01
    str t1, [t0, #TIMER_PRESCALER]

// Set Reload to 62,500
_set_reload:
    mov t1, #0x24
    movu t1, #0xF4
    str t1, [t0, #TIMER_RELOAD]

    pop pc

//===================================
_timer_delay:
//===================================
    mov t0, #0
    movu t0, #TIMER_ADDR

_timer_delay_start:
    mov t1, #TIMER_CONTROL_START
    str t1, [t0, #TIMER_CONTROL]

_timer_delay_wait:    
    ldr t1, [t0, #TIMER_CONTROL]
    and t1, t1, #TIMER_CONTROL_DONE
    beq _timer_delay_wait

    pop pc
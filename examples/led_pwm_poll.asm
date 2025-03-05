// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start:         mov s0, #0
                movu s0, #PWM_ADDR
                mov s1, #0
                movu s1, #LED_SWITCH_ADDR

// Set Frequency to 25MHz/2500 = 10kHz
_set_prescaler: mov t0, #0xC3
                movu t0, #0x09
                str t0, [s0, #PWM_PRESCALER]

// Set Period to 20ms (Reload = 200)
_set_reload:    mov t0, #0xC7
                str t0, [s0, #PWM_RELOAD]

// Set Duty-Cycle to 10%/2ms (Duty = 20)
_set_duty:      mov t0, #0x13
                str t0, [s0, #PWM_DUTY]

_start_pwm:     mov t0, #PWM_CONTROL_EN
                str t0, [s0, #PWM_CONTROL]
    
_set_leds:      ldr t0, [s0, #PWM_CONTROL]
                shr t0, t0, #1
                str t0, [s1, #LED_SWITCH_DATAOUT]

_goto_set_leds: jmp _set_leds
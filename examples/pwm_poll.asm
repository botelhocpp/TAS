// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start:         mov s0, #0
                movu s0, #PWM_ADDR

// Set Frequency to 25MHz/1khz = 2500
_set_prescaler: mov t0, #0x05
                str t0, [s0, #PWM_PRESCALER]

// Set Period to 1ms (Reload = 2500)
_set_reload:    mov t0, #0xC3  
                movu t0, #0x09
                str t0, [s0, #PWM_RELOAD]

// Set Duty-Cycle to 75% (Duty = 1875)
_set_duty:      mov t0, #0x52  
                movu t0, #0x07
                str t0, [s0, #PWM_DUTY]

_start_pwm:     mov t0, #PWM_CONTROL_EN
                str t0, [s0, #PWM_CONTROL]
                
                jmp .
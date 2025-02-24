%define LED_SWITCH_ADDR     0xF0
%define LED_SWITCH_DATAOUT  0x00

%define LED_MASK 0x0F

%define TIMER_ADDR      0xF2
%define TIMER_RELOAD    0x00
%define TIMER_CONTROL   0x02
%define TIMER_PRESCALER 0x04

%define TIMER_CONTROL_START 0x01
%define TIMER_CONTROL_DONE  0x02

_start: 
    mov s0, #0
    movu s0, #TIMER_ADDR
    mov s1, #0
    movu s1, #LED_SWITCH_ADDR

_set_prescaler:
    mov t0, #0xCF
    movu t0, #0x07
    str t0, [s0, #TIMER_PRESCALER] // Set Frequency to 125MHz/2000 = 62.5kHz

_set_reload:
    mov t0, #0x24
    movu t0, #0xF4
    str t0, [s0, #TIMER_RELOAD]
    
_set_leds:
    ldr t0, [s1, #LED_SWITCH_DATAOUT]
    xor t0, t0, #LED_MASK
    str t0, [s1, #LED_SWITCH_DATAOUT]

_delay_start_count:
    mov t0, #TIMER_CONTROL_START
    str t0, [s0, #TIMER_CONTROL]

_delay_wait:    
    ldr t0, [s0, #TIMER_CONTROL]
    and t0, t0, #TIMER_CONTROL_DONE
    beq _delay_wait

_goto_set_leds:
    jmp _set_leds
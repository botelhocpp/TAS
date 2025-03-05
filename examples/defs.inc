// Copyright (c) 2025 TAS
// All rights reserved

// LEDs & Switches
%define LED_SWITCH_ADDR         0xF0
%define LED_SWITCH_DATAOUT      0x00
%define LED_SWITCH_DATAIN       0x02
%define LED_SWITCH_CONTROL      0x04
%define LED_SWITCH_IRQSTATUS    0x06

// GPIO
%define GPIO_ADDR               0xF1
%define GPIO_PINMUX             0x00
%define GPIO_DATADIR            0x02
%define GPIO_DATAOUT            0x04
%define GPIO_DATAIN             0x06
%define GPIO_CONTROL            0x08
%define GPIO_IRQSTATUS          0x0A
%define GPIO_PINMUX_TXSEL       0x20
%define GPIO_PINMUX_RXSEL       0x40
%define GPIO_PINMUX_PWMSEL      0x80

// Timer
%define TIMER_ADDR              0xF2
%define TIMER_RELOAD            0x00
%define TIMER_CONTROL           0x02
%define TIMER_PRESCALER         0x04
%define TIMER_COUNTER           0x06
%define TIMER_CONTROL_START     0x01
%define TIMER_CONTROL_DONE      0x02
%define TIMER_CONTROL_IRQEN     0x04

// PWM
%define PWM_ADDR                0xF3
%define PWM_RELOAD              0x00
%define PWM_DUTY                0x02
%define PWM_CONTROL             0x04
%define PWM_PRESCALER           0x06
%define PWM_COUNTER             0x08
%define PWM_CONTROL_EN       0x01
%define PWM_CONTROL_VALUE       0x02

// UART
%define UART_ADDR               0xF4
%define UART_TXDATA             0x00
%define UART_RXDATA             0x02
%define UART_CONTROL            0x04
%define UART_CONTROL_TXEN       0x01
%define UART_CONTROL_TXDONE     0x02
%define UART_CONTROL_RXDONE     0x04
%define UART_CONTROL_TXIRQEN    0x08
%define UART_CONTROL_RXIRQEN    0x10

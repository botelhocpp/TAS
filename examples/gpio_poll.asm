// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start:   mov s0, #0
          movu s0, #GPIO_ADDR

_config:  mov t0, #0xFF
          str t0, [s0, #GPIO_DATADIR] 
          mov t0, #0
          movu t0, #0x40
          str t0, [s0, #GPIO_PINMUX] 

_while:   ldr t0, [s0, #GPIO_DATAIN]
          shr t0, t0, #8
          str t0, [s0, #GPIO_DATAOUT]
          jmp _while

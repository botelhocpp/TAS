// Copyright (c) 2025 TAS
// All rights reserved

%include defs.inc

_start: mov s0, #0
        movu s0, #LED_SWITCH_ADDR

_while: ldr t0, [s0, #LED_SWITCH_DATAIN]
        str t0, [s0, #LED_SWITCH_DATAOUT]
        jmp _while

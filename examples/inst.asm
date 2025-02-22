// %define SP_VALUE 2

main:
// mov sp, #SP_VALUE

jmp alu_ops
jmp #2
jmp #-2

beq alu_ops
beq #2
beq #-2

bne alu_ops
bne #2
bne #-2

ble alu_ops
ble #2
ble #-2

bgt alu_ops
bgt #2
bgt #-2

ldr t0, [sp, #2]
ldr t0, [sp, #-2]

str t1, [pc, #4]
str t1, [pc, #-4]

alu_ops:
mov t2, sp
mov t2, #100

movu t2, sp
movu t2, #100

add a0, a0, a1
add a0, a0, #1
add a0, a0, #-1

sub a0, a0, a1
sub a0, a0, #1
sub a0, a0, #-1

and a0, a0, a1
and a0, a0, #1
and a0, a0, #-1

or a0, a0, a1
or a0, a0, #1
or a0, a0, #-1

xor a0, a0, a1
xor a0, a0, #1
xor a0, a0, #-1

shr a0, a0, a1
shr a0, a0, #1
shr a0, a0, #-1

shl a0, a0, a1
shl a0, a0, #1
shl a0, a0, #-1

cmp a0, a1
cmp a0, #1
cmp a0, #-1

not a0, t1
neg a0, t1

push a0
pop a1

halt

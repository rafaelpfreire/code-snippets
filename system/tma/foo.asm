%define nop8 db 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00

%macro cache_line 0
nop8 
nop8 
nop8 
nop8 
nop8 
nop8 
nop8 
nop8
%endmacro

%macro Four_cache_lines 0
cache_line
cache_line
cache_line
cache_line
%endmacro

%macro One_KB_of_nops 0
Four_cache_lines
Four_cache_lines
Four_cache_lines
Four_cache_lines
%endmacro

GLOBAL foo

ALIGN 256
foo:
; start some irrelevant work
One_KB_of_nops
; finish some irrelevant work

mov     al, BYTE [rdi + 0]
mov     al, BYTE [rdi + 10]

; load that goes to DRAM
movzx   rax, BYTE [rdi + rsi]
; introduce dependency chain
mov     al, BYTE [rdi + rax]

mov     al, BYTE [rdi + 20]


xor rax, rax
ret
ud2

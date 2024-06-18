; ======================================================================
;                           AurorOS Bootloader
; ======================================================================
; => The AurorOS bootloader (Assembly Stage).
;       This file is basically a bootloader that initializes bits
;       and runs C code at the specific memory address.
; ======================================================================

[BITS 16]
[ORG 0x7C00]

start:
    cli             ; Disable interrupts
    xor ax, ax      ; Clear AX register
    mov ds, ax      ; Set DS segment to 0
    mov es, ax      ; Set ES segment to 0
    mov ss, ax      ; Set SS segment to 0
    mov sp, 0x7C00  ; Set stack pointer

    ; Load and enable A20 line
    call load_a20

    ; Set up GDT (Global Descriptor Table)
    call setup_gdt

    ; Load second stage bootloader (written in C)
    call load_second_stage

    ; Jump to the second stage bootloader
    jmp 0x08:second_stage_entry

load_a20:
    in al, 0x64
    test al, 2
    jnz load_a20
    mov al, 0xD1
    out 0x64, al
    call wait_buffer_empty

    mov al, 0xDF
    out 0x60, al

wait_buffer_empty:
    in al, 0x64
    test al, 2
    jnz wait_buffer_empty
    ret

setup_gdt:
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

gdt_start:
gdt_null:
    dd 0x0
    dd 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00
gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x9000
    jmp 0x08:init_protected_mode

init_protected_mode:
    ; In protected mode, we should load the second stage bootloader at 0x1000
    mov ebx, 0x1000  ; Second stage bootloader load address
    call [ebx]       ; Jump to the second stage bootloader entry point

; Placeholder for second stage bootloader
times 1024 db 0    ; Reserve 1024 bytes for the second stage bootloader

times 510-($-$$) db 0  ; Fill remaining space with zeroes
dw 0xAA55              ; Boot signature
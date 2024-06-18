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
    cli                     ; Disable interrupts
    xor ax, ax              ; Clear AX register
    mov ds, ax              ; Set DS segment to 0
    mov es, ax              ; Set ES segment to 0
    mov ss, ax              ; Set SS segment to 0
    mov sp, 0x7C00          ; Set stack pointer

    ; Load and enable A20 line
    call load_a20

    ; Set up GDT (Global Descriptor Table)
    call setup_gdt

    ; Enter long mode (64-bit)
    call enter_long_mode

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

[BITS 32]
protected_mode:
    ; Enable PAE (Physical Address Extension)
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; Enable Long Mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x100
    wrmsr

    ; Set up paging structures (4-level page tables)
    ; This is a simplified version; real-world usage may vary
    ; Set up page tables to identity map first 2MB of memory

    ; PML4
    mov dword [pml4], pdp | 0x03

    ; PDP
    mov dword [pdp], pd | 0x03

    ; PD
    mov dword [pd], 0x83

    ; Load PML4 address into CR3
    lea eax, [pml4]
    mov cr3, eax

    ; Enable paging
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    jmp 0x08:long_mode

[BITS 64]
section .bss
align 0x1000
pml4:
    resb 4096
pdp:
    resb 4096
pd:
    resb 4096

long_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, 0x9000
    jmp 0x08:init_long_mode

init_long_mode:
    ; In long mode, we should load the second stage bootloader at 0x1000
    mov ebx, 0x1000  ; Second stage bootloader load address
    call [ebx]       ; Jump to the second stage bootloader entry point

load_second_stage:
    ; Load the second stage bootloader from disk or other medium
    ; Placeholder for actual loading mechanism
    ret

second_stage_entry:
    ; Placeholder for the second stage bootloader entry point
    nop

; Placeholder for second stage bootloader
times 1024 db 0    ; Reserve 1024 bytes for the second stage bootloader

times 510-($-$$) db 0  ; Fill remaining space with zeroes
dw 0xAA55              ; Boot signature

gdt_start:
gdt_null:
    dq 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00
    dw 0x0000
gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00
    dw 0x0000
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
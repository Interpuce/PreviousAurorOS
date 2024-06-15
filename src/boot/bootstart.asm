BITS 16
ORG 0x7C00

start:
    ; Setup segment registers
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Jump to Stage 2 code
    call load_stage2

hang:
    jmp hang

load_stage2:
    ; Load stage 2 code (C program) at 0x1000
    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0
    int 0x13

    ; Jump to the C code
    jmp 0x1000:0x0000

times 510-($-$$) db 0
dw 0xAA55
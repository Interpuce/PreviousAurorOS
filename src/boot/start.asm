; ----------------------------- AurorOS -----------------------------
;                       Created by Interpuce Team
; -------------------------------------------------------------------

; This is an Assembly bootloader that enters long mode (for 64bit)
; and (in the future) loads the kernel from the disk.

; This ASM uses Intel ASM syntax and is
; inspired by https://wiki.osdev.org/Entering_Long_Mode_Directly

%define PAGE_PRESENT    (1 << 0)
%define PAGE_WRITE      (1 << 1)

%define CODE_SEG        0x08
%define DATA_SEG        0x10

ALIGN 4
IDT:
    .Length         dw 0
    .Base           dd 0

[BITS 32]

global StartLongMode

StartLongMode:
    ; Zero out the 16KiB buffer.
    push edi
    mov ecx, 0x1000
    xor eax, eax
    cld
    rep stosd
    pop edi

    ; Build the Page Map Level 4.
    lea eax, [edi + 0x1000] ; Calculate address of PML4E
    or eax, PAGE_PRESENT | PAGE_WRITE
    mov [edi], eax ; Store PML4E

    ; Build the Page Directory Pointer Table.
    lea eax, [edi + 0x2000] ; Calculate address of PDPTE
    or eax, PAGE_PRESENT | PAGE_WRITE
    mov [edi + 0x1000], eax ; Store PDPTE

    ; Build the Page Directory.
    lea eax, [edi + 0x3000] ; Calculate address of PDE
    or eax, PAGE_PRESENT | PAGE_WRITE
    mov [edi + 0x2000], eax ; Store PDE

    ; Build the Page Table.
    push edi
    lea edi, [edi + 0x4000] ; Calculate address of PT
    mov eax, PAGE_PRESENT | PAGE_WRITE
    xor ecx, ecx

.LoopPageTable:
    mov [edi + ecx], eax   ; Store PTE
    add eax, 0x1000        ; Next page
    add ecx, 4             ; Next entry
    cmp ecx, 0x1000        ; Check if 4K entries are done (16K buffer / 4 bytes per entry)
    jb .LoopPageTable
    pop edi                ; Restore edi

    ; Disable IRQs
    mov al, 0xFF
    out 0xA1, al
    out 0x21, al

    nop
    nop

    lidt [IDT]              ; Load zero length IDT

    ; Enter long mode.
    mov eax, cr4
    or eax, 0x00000020     ; Set PSE bit in CR4 for PAE paging
    mov cr4, eax

    mov eax, edi           ; Load PML4 physical address to CR3
    mov cr3, eax

    mov ecx, 0xC0000080    ; EFER MSR address
    rdmsr
    or eax, 0x00000100     ; Set LME bit
    wrmsr

    mov eax, cr0
    or eax, 0x80000001     ; Enable PG (paging) and PE (protection) bits in CR0
    mov cr0, eax

    lgdt [GDT.Pointer]     ; Load GDT
    jmp CODE_SEG:LongMode  ; Jump to 64-bit code segment

; Global Descriptor Table
GDT:
.Null:
    dq 0x0000000000000000  ; Null Descriptor

.Code:
    dq 0x0020980000000000  ; 64-bit code descriptor (exec/read)
    dq 0x0000920000000000  ; 64-bit data descriptor (read/write)

ALIGN 4
.Pointer:
    dw $ - GDT - 1         ; Size of GDT
    dd GDT                 ; Base address of GDT

[BITS 64]
LongMode:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Clear the screen to blue color.
    mov rdi, 0xB8000
    mov rcx, 80 * 25       ; 80 columns * 25 rows
    mov rax, 0x1F201F201F201F20    ; Blue background, white foreground, spaces
    rep stosq

    ; Display "Hello World!"
    mov rdi, 0xB8000

    mov rax, 0x1F6C1F6C1F651F48    ; H
    mov [rdi], rax
    mov rax, 0x1F6F1F571F201F6F    ; e
    mov [rdi + 8], rax
    mov rax, 0x1F211F641F6C1F72    ; l
    mov [rdi + 16], rax

    jmp .                ; Infinite loop

ALIGN 4
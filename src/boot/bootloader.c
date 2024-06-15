void print_string(const char* str) {
    while (*str) {
        __asm__ volatile (
            "mov ah, 0x0E;"
            "mov al, %[char];"
            "int 0x10"
            :
            : [char] "r" (*str)
        );
        str++;
    }
}

void stage2_main() {
    print_string("Hello from C bootloader!\r\n");
    while (1);
}

#ifndef USB_REGS_H
#define USB_REGS_H

#include <stdint.h>

#define USB_BASE_ADDRESS 0x40080000
#define USB_CTRL_REG     (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x00))
#define USB_STATUS_REG   (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x04))
#define USB_INT_ENABLE   (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x08))
#define USB_INT_STATUS   (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x0C))
#define USB_DATA_REG     (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x10))

#define USB_CTRL_ENABLE  0x01
#define USB_CTRL_RESET   0x02

#endif
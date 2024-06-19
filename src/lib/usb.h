#ifndef USB_DRIVER_H
#define USB_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#define USB_BASE_ADDRESS 0x40080000
#define USB_CTRL_REG     (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x00))
#define USB_STATUS_REG   (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x04))
#define USB_INT_ENABLE   (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x08))
#define USB_INT_STATUS   (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x0C))
#define USB_DATA_REG     (*(volatile uint32_t *)(USB_BASE_ADDRESS + 0x10))

#define USB_CTRL_ENABLE  0x01
#define USB_CTRL_RESET   0x02

#define MAX_USB_DEVICES  256

typedef enum {
    USB_SUCCESS,
    USB_ERROR,
    USB_TIMEOUT,
} usb_status_t;

typedef struct {
    uint8_t device_address;
    uint8_t endpoint;
    uint16_t max_packet_size;
    bool in_use;
} usb_device_t;

// Function prototypes
void usb_init(void);
usb_status_t usb_reset(void);
usb_device_t* usb_register_device(uint8_t device_address, uint8_t endpoint, uint16_t max_packet_size);
void usb_unregister_device(uint8_t device_address);
usb_status_t usb_send_data(uint8_t device_address, uint8_t *data, uint16_t length);
usb_status_t usb_receive_data(uint8_t device_address, uint8_t *data, uint16_t length);
void usb_handle_interrupt(void);
#ifndef USB_DRIVER_H
#define USB_DRIVER_H

#include <stdbool.h>
#include "usb_regs.h"

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
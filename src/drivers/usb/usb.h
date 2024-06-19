// ======================================================================
//                            AurorOS Driver
// ======================================================================

// => The AurorOS driver.
//      This file is basically an implementation of the AurorOS USB driver
//      and provides API calls to initialize USB, handle USB devices, and
//      transfer data.

#include "../../lib/usb.h"

// Global array of USB devices
usb_device_t usb_devices[MAX_USB_DEVICES];

// USB initialization
void usb_init(void) {
    // Enable USB controller
    USB_CTRL_REG |= USB_CTRL_ENABLE;
    
    // Enable USB interrupts
    USB_INT_ENABLE = 0x1F;
    
    // Initialize the devices array
    for (int i = 0; i < MAX_USB_DEVICES; i++) {
        usb_devices[i].in_use = false;
    }
}

// USB reset
usb_status_t usb_reset(void) {
    // Perform a reset of the USB controller
    USB_CTRL_REG |= USB_CTRL_RESET;
    
    // Wait for the reset to complete
    for (volatile int i = 0; i < 100000; i++);
    
    // Clear the reset bit
    USB_CTRL_REG &= ~USB_CTRL_RESET;
    
    return USB_SUCCESS;
}

// USB register device
usb_device_t* usb_register_device(uint8_t device_address, uint8_t endpoint, uint16_t max_packet_size) {
    for (int i = 0; i < MAX_USB_DEVICES; i++) {
        if (!usb_devices[i].in_use) {
            usb_devices[i].device_address = device_address;
            usb_devices[i].endpoint = endpoint;
            usb_devices[i].max_packet_size = max_packet_size;
            usb_devices[i].in_use = true;
            return &usb_devices[i];
        }
    }
    return NULL;
}

// USB unregister device
void usb_unregister_device(uint8_t device_address) {
    for (int i = 0; i < MAX_USB_DEVICES; i++) {
        if (usb_devices[i].in_use && usb_devices[i].device_address == device_address) {
            usb_devices[i].in_use = false;
            return;
        }
    }
}

// USB send data
usb_status_t usb_send_data(uint8_t device_address, uint8_t *data, uint16_t length) {
    if (length == 0 || data == NULL) {
        return USB_ERROR;
    }
    
    usb_device_t *device = NULL;
    for (int i = 0; i < MAX_USB_DEVICES; i++) {
        if (usb_devices[i].in_use && usb_devices[i].device_address == device_address) {
            device = &usb_devices[i];
            break;
        }
    }
    
    if (device == NULL) {
        return USB_ERROR;
    }

    // Write data to the USB data register
    for (uint16_t i = 0; i < length; i++) {
        USB_DATA_REG = data[i];
        
        // Check for errors or timeouts
        if (USB_STATUS_REG & 0x01) {
            return USB_ERROR;
        }
    }
    
    return USB_SUCCESS;
}

// USB receive data
usb_status_t usb_receive_data(uint8_t device_address, uint8_t *data, uint16_t length) {
    if (length == 0 || data == NULL) {
        return USB_ERROR;
    }
    
    usb_device_t *device = NULL;
    for (int i = 0; i < MAX_USB_DEVICES; i++) {
        if (usb_devices[i].in_use && usb_devices[i].device_address == device_address) {
            device = &usb_devices[i];
            break;
        }
    }
    
    if (device == NULL) {
        return USB_ERROR;
    }

    // Read data from the USB data register
    for (uint16_t i = 0; i < length; i++) {
        data[i] = USB_DATA_REG;
        
        // Check for errors or timeouts
        if (USB_STATUS_REG & 0x02) {
            return USB_ERROR;
        }
    }
    
    return USB_SUCCESS;
}

// USB interrupt handler
void usb_handle_interrupt(void) {
    uint32_t status = USB_INT_STATUS;
    
    // Clear interrupt status
    USB_INT_STATUS = status;
    
    // Handle different types of USB interrupts
    if (status & 0x01) {
        // Transfer complete
    }
    
    if (status & 0x02) {
        // Error
    }
}

int main() {
    usb_init();
    usb_reset();

    usb_device_t *device1 = usb_register_device(1, 1, 64);
    usb_device_t *device2 = usb_register_device(2, 1, 64);

    if (device1) {
        uint8_t data_to_send[] = {0x01, 0x02, 0x03, 0x04};
        usb_send_data(device1->device_address, data_to_send, sizeof(data_to_send));
        
        uint8_t data_to_receive[4];
        usb_receive_data(device1->device_address, data_to_receive, sizeof(data_to_receive));
    }
    
    if (device2) {
        uint8_t data_to_send2[] = {0x05, 0x06, 0x07, 0x08};
        usb_send_data(device2->device_address, data_to_send2, sizeof(data_to_send2));
        
        uint8_t data_to_receive2[4];
        usb_receive_data(device2->device_address, data_to_receive2, sizeof(data_to_receive2));
    }

    usb_unregister_device(1);
    usb_unregister_device(2);

    usb_handle_interrupt();
    
    return 0;
}
#ifndef USB_DESCRIPTORS_H
#define USB_DESCRIPTORS_H

#include "tusb.h"

// Device Descriptor
const uint8_t desc_device[] = {
    TUD_DESC_DEVICE(0x0200, TUSB_DESC_PRINTER, 0x0400, 0x01, 0x00, 64)};

// Configuration Descriptor
const uint8_t desc_configuration[] = {
    TUD_DESC_CONFIG(1, 1, 0, 0x32, 0x00, 0x00, 0x00),
    TUD_DESC_INTERFACE(0, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00),
    TUD_DESC_ENDPOINT(0x81, 0x03, 64, 0x00), // Endpoint IN
    TUD_DESC_ENDPOINT(0x01, 0x03, 64, 0x00)  // Endpoint OUT
};

// String Descriptors
const uint8_t desc_string[] = {
    TUD_DESC_STRING(0x0409, "Espressif"),
    TUD_DESC_STRING("ESP32 Printer")};

#endif // USB_DESCRIPTORS_H

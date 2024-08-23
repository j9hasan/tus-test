/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdint.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "sdkconfig.h"

static const char *TAG = "example";

void app_main(void)
{
    ESP_LOGI(TAG, "USB CDC initialization");

    // TinyUSB configuration
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = TAG,
        .external_phy = false,
        .configuration_descriptor = NULL,
    };

    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    // CDC-ACM configuration
    tinyusb_config_cdcacm_t acm_cfg = {
        .usb_dev = TINYUSB_USBDEV_0,
        .cdc_port = TINYUSB_CDC_ACM_0,
        .rx_unread_buf_sz = 64,
        .callback_rx = NULL, // No RX callback needed for this example
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = NULL,
        .callback_line_coding_changed = NULL};

    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));

    ESP_LOGI(TAG, "USB CDC initialized. Sending data...");

    const char *data = "hello";

    // Continuously send "hello"
    while (1)
    {
        tinyusb_cdcacm_write_queue(TINYUSB_CDC_ACM_0, (uint8_t *)data, strlen(data));
        tinyusb_cdcacm_write_flush(TINYUSB_CDC_ACM_0, 0);

        ESP_LOGI(TAG, "Data sent: %s", data);

        // Delay to avoid flooding the output (adjust the delay as needed)
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
    }
}

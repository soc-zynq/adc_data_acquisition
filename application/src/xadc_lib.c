#include "xadc_lib.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define XADC_DEVICE "/dev/xadc_dev"

/**
 * @brief Initializes the XADC device.
 *
 * Opens the XADC device file for reading and writing.
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return 0 on success, -1 on failure.
 */
int xadc_init(xadc_handle_t *handle) {
    handle->fd = open(XADC_DEVICE, O_RDWR);
    return (handle->fd < 0) ? -1 : 0;
}

/**
 * @brief Closes the XADC device.
 *
 * Closes the file descriptor associated with the XADC device.
 *
 * @param handle Pointer to the xadc_handle_t structure.
 */
void xadc_close(xadc_handle_t *handle) {
    if (handle->fd >= 0) {
        close(handle->fd);
        handle->fd = -1;
    }
}

/**
 * @brief Reads the temperature from the XADC device.
 *
 * Reads the raw temperature value from the XADC and converts it to Celsius.
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return The temperature in Celsius.
 */
float xadc_read_temperature(xadc_handle_t *handle) {
    // Implementation will depend on your ioctl commands
    // This is a placeholder that should be updated
    uint32_t raw_value = 0;
    // TODO: Add ioctl command to read temperature
    return (float)raw_value * 503.975f / 65536.0f - 273.15f;
}

/**
 * @brief Reads the VCCINT voltage from the XADC device.
 *
 * Reads the raw VCCINT value from the XADC and converts it to voltage.
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return The VCCINT voltage.
 */
float xadc_read_vccint(xadc_handle_t *handle) {
    // Implementation will depend on your ioctl commands
    uint32_t raw_value = 0;
    // TODO: Add ioctl command to read VCCINT
    return (float)raw_value * 3.0f / 65536.0f;
}

/**
 * @brief Reads the VCCAUX voltage from the XADC device.
 *
 * Reads the raw VCCAUX value from the XADC and converts it to voltage.
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return The VCCAUX voltage.
 */
float xadc_read_vccaux(xadc_handle_t *handle) {
    // Implementation will depend on your ioctl commands
    uint32_t raw_value = 0;
    // TODO: Add ioctl command to read VCCAUX
    return (float)raw_value * 3.0f / 65536.0f;
}

#ifndef XADC_LIB_H
#define XADC_LIB_H

#include <stdint.h>

/**
 * @brief Structure to hold the XADC device handle.
 */
typedef struct {
    int fd;  ///< File descriptor for the XADC device
} xadc_handle_t;

/**
 * @brief Initializes XADC device
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return 0 on success, -1 on failure.
 */
int xadc_init(xadc_handle_t *handle);

/**
 * @brief Closes XADC device
 *
 * @param handle Pointer to the xadc_handle_t structure.
 */
void xadc_close(xadc_handle_t *handle);

/**
 * @brief Reads temperature value
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return The temperature in Celsius.
 */
float xadc_read_temperature(xadc_handle_t *handle);

/**
 * @brief Reads VCCINT voltage
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return The VCCINT voltage.
 */
float xadc_read_vccint(xadc_handle_t *handle);

/**
 * @brief Reads VCCAUX voltage
 *
 * @param handle Pointer to the xadc_handle_t structure.
 * @return The VCCAUX voltage.
 */
float xadc_read_vccaux(xadc_handle_t *handle);

#endif /* XADC_LIB_H */

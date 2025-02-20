#ifndef ADC_DATA_ACQUISITION_H
#define ADC_DATA_ACQUISITION_H

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/types.h>

/**
 * @def DEVICE_NAME
 * @brief Device name for the XADC driver.
 */
#define DEVICE_NAME "xadc_dev"
/**
 * @def CLASS_NAME
 * @brief Class name for the XADC driver.
 */
#define CLASS_NAME "xadc_class"

/**
 * @def XADC_CONFIG_REG_0
 * @brief Offset for the XADC configuration register 0.
 */
#define XADC_CONFIG_REG_0 0x00
/**
 * @def XADC_CONFIG_REG_1
 * @brief Offset for the XADC configuration register 1.
 */
#define XADC_CONFIG_REG_1 0x04
/**
 * @def XADC_CONFIG_REG_2
 * @brief Offset for the XADC configuration register 2.
 */
#define XADC_CONFIG_REG_2 0x08
/**
 * @def XADC_STATUS_REG
 * @brief Offset for the XADC status register.
 */
#define XADC_STATUS_REG 0x0C
/**
 * @def XADC_TEMP_DATA_REG
 * @brief Offset for the XADC temperature data register.
 */
#define XADC_TEMP_DATA_REG 0x200
/**
 * @def XADC_VCCINT_DATA_REG
 * @brief Offset for the XADC VCCINT data register.
 */
#define XADC_VCCINT_DATA_REG 0x204
/**
 * @def XADC_VCCAUX_DATA_REG
 * @brief Offset for the XADC VCCAUX data register.
 */
#define XADC_VCCAUX_DATA_REG 0x208

/**
 * @brief Structure representing the XADC device.
 */
struct xadc_dev {
    struct device *device;   /**< Device structure */
    struct class *class;     /**< Class structure */
    dev_t dev_num;           /**< Device number */
    void __iomem *base_addr; /**< Base address of the XADC */
    struct cdev cdev;        /**< Character device structure */
};

/**
 * @brief Initializes the XADC device.
 *
 * This function allocates a character device region, creates a device class,
 * creates a device node, and initializes the XADC hardware.
 *
 * @param dev Pointer to the XADC device structure.
 * @return 0 on success, negative error code on failure.
 */
int xadc_init_device(struct xadc_dev *dev);

/**
 * @brief Cleans up the XADC device.
 *
 * This function destroys the device node, destroys the device class, and
 * unregisters the character device region.
 *
 * @param dev Pointer to the XADC device structure.
 */
void xadc_cleanup_device(struct xadc_dev *dev);

/**
 * @brief Reads a register from the XADC.
 *
 * This function reads a 32-bit value from the specified register offset in the
 * XADC.
 *
 * @param dev Pointer to the XADC device structure.
 * @param offset Offset of the register to read.
 * @return The value read from the register.
 */
u32 xadc_read_reg(struct xadc_dev *dev, u32 offset);

/**
 * @brief Writes a value to a register in the XADC.
 *
 * This function writes a 32-bit value to the specified register offset in the
 * XADC.
 *
 * @param dev Pointer to the XADC device structure.
 * @param offset Offset of the register to write to.
 * @param value Value to write to the register.
 */
void xadc_write_reg(struct xadc_dev *dev, u32 offset, u32 value);

#endif /* ADC_DATA_ACQUISITION_H */

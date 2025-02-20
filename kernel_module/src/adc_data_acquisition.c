#include <adc_data_acquisition.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sandesh Ghimire");
MODULE_DESCRIPTION("XADC Driver for Zynq UltraScale+");
MODULE_VERSION("0.1");

/**
 * @brief XADC device structure.
 */
static struct xadc_dev xadc_device;

/**
 * @brief Probe function for the XADC platform device.
 *
 * This function is called when the XADC platform device is probed. It retrieves
 * the memory resource, remaps it to a virtual address, initializes the XADC
 * device, and sets the driver data.
 *
 * @param pdev Pointer to the platform device structure.
 * @return 0 on success, negative error code on failure.
 */
static int xadc_probe(struct platform_device *pdev) {
    struct resource *res;
    int ret;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        dev_err(&pdev->dev, "No memory resource\n");
        return -ENODEV;
    }

    xadc_device.base_addr = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(xadc_device.base_addr)) return PTR_ERR(xadc_device.base_addr);

    ret = xadc_init_device(&xadc_device);
    if (ret) {
        dev_err(&pdev->dev, "Failed to initialize XADC device\n");
        return ret;
    }

    platform_set_drvdata(pdev, &xadc_device);
    dev_info(&pdev->dev, "XADC probe successful\n");
    return 0;
}

/**
 * @brief Remove function for the XADC platform device.
 *
 * This function is called when the XADC platform device is removed. It cleans
 * up the XADC device.
 *
 * @param pdev Pointer to the platform device structure.
 * @return 0 on success.
 */
static int xadc_remove(struct platform_device *pdev) {
    struct xadc_dev *dev = platform_get_drvdata(pdev);
    xadc_cleanup_device(dev);
    return 0;
}

/**
 * @brief OF device match table for the XADC driver.
 */
static const struct of_device_id xadc_of_match[] = {
    {
        .compatible = "xlnx,zynqmp-xadc-1.0",
    },
    {/* end of table */}};
MODULE_DEVICE_TABLE(of, xadc_of_match);

/**
 * @brief Platform driver structure for the XADC driver.
 */
static struct platform_driver xadc_driver = {
    .driver =
        {
            .name = DEVICE_NAME,
            .of_match_table = xadc_of_match,
        },
    .probe = xadc_probe,
    .remove = xadc_remove,
};

/**
 * @brief Initializes the XADC module.
 *
 * This function registers the XADC platform driver.
 *
 * @return 0 on success, negative error code on failure.
 */
static int __init xadc_module_init(void) {
    return platform_driver_register(&xadc_driver);
}

/**
 * @brief Exits the XADC module.
 *
 * This function unregisters the XADC platform driver.
 */
static void __exit xadc_module_exit(void) {
    platform_driver_unregister(&xadc_driver);
}

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
u32 xadc_read_reg(struct xadc_dev *dev, u32 offset) {
    return readl(dev->base_addr + offset);
}

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
void xadc_write_reg(struct xadc_dev *dev, u32 offset, u32 value) {
    writel(value, dev->base_addr + offset);
}

/**
 * @brief Initializes the XADC device.
 *
 * This function allocates a character device region, creates a device class,
 * creates a device node, and initializes the XADC hardware.
 *
 * @param dev Pointer to the XADC device structure.
 * @return 0 on success, negative error code on failure.
 */
int xadc_init_device(struct xadc_dev *dev) {
    int ret;

    ret = alloc_chrdev_region(&dev->dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) return ret;

    dev->class = class_create(CLASS_NAME);  // Updated to new API
    if (IS_ERR(dev->class)) {
        unregister_chrdev_region(dev->dev_num, 1);
        return PTR_ERR(dev->class);
    }

    dev->device =
        device_create(dev->class, NULL, dev->dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(dev->device)) {
        class_destroy(dev->class);
        unregister_chrdev_region(dev->dev_num, 1);
        return PTR_ERR(dev->device);
    }

    /* Initialize XADC hardware */
    xadc_write_reg(dev, XADC_CONFIG_REG_0, 0x0000); /* Reset configuration */
    xadc_write_reg(dev, XADC_CONFIG_REG_1, 0x2000); /* Enable XADC */

    return 0;
}

/**
 * @brief Cleans up the XADC device.
 *
 * This function destroys the device node, destroys the device class, and
 * unregisters the character device region.
 *
 * @param dev Pointer to the XADC device structure.
 */
void xadc_cleanup_device(struct xadc_dev *dev) {
    device_destroy(dev->class, dev->dev_num);
    class_destroy(dev->class);
    unregister_chrdev_region(dev->dev_num, 1);
}

module_init(xadc_module_init);
module_exit(xadc_module_exit);

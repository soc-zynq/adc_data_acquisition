# ADC Data Acquisition Kernel Module

This kernel module is designed for acquiring data from an Analog-to-Digital Converter (ADC) on a Zynq-based system.

## Prerequisites

- Zynq development board
- Linux environment
- Kernel headers for your kernel version

## Building the Module

1.  Navigate to the `kernel_module` directory.
2.  Run `make` to build the module.

    ```bash
    make
    ```

## Loading the Module

1.  Use `insmod` to load the module.

    ```bash
    sudo insmod adc_data_acquisition.ko
    ```

## Unloading the Module

1.  Use `rmmod` to unload the module.

    ```bash
    sudo rmmod adc_data_acquisition
    ```

## Dependencies

- Kernel headers
- Device tree overlay (if applicable)

## Notes

- Ensure that the device tree is properly configured for the ADC.
- Check the kernel logs for any errors during module loading or unloading.

## License

[GPL]

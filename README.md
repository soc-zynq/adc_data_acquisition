# XADC Data Acquisition System

## Description

A Linux kernel module and user-space application for interfacing with the Xilinx XADC (ADC) on Zynq UltraScale+ MPSoC platforms. The system monitors various analog inputs including temperature, VCCINT, and VCCAUX voltages.

## Features

- Kernel module for XADC hardware access
- User-space library for XADC operations
- Real-time monitoring application
- Docker-based build environment for cross-compilation

## Project Structure

```
adc_data_acquisition/
├── kernel_module/               # XADC Linux kernel module
│   ├── src/
│   │   └── adc_data_acquisition.c
│   ├── include/
│   │   └── adc_data_acquisition.h
│   └── Makefile
├── application/                 # User-space application
│   ├── src/
│   │   ├── main.c
│   │   └── xadc_lib.c
│   ├── include/
│   │   └── xadc_lib.h
│   └── CMakeLists.txt
└── Makefile                    # Top-level build system
```

## Prerequisites

- Docker installed on the development machine
- Xilinx Zynq UltraScale+ MPSoC target platform
- Linux kernel headers for the target platform

## Building

### Using Docker (Recommended)

```bash
# Build everything
make all

# Build only the kernel module
make module-build

# Build only the application
make app-build

# Clean build artifacts
make clean
```

### Manual Build

#### Kernel Module

```bash
cd kernel_module
make
```

#### Application

```bash
cd application
mkdir build && cd build
cmake ..
make
```

## Installation

### Kernel Module

```bash
# Load the module
sudo insmod kernel_module/adc_data_acquisition.ko

# Verify module is loaded
lsmod | grep adc_data_acquisition

# Check kernel logs
dmesg | tail
```

### Application

```bash
# Install the application
sudo cp application/build/xadc_monitor /usr/local/bin/

# Run the monitoring application
xadc_monitor
```

## Usage

1. Load the kernel module
2. Run the monitoring application
3. The application will continuously display:
   - Temperature (°C)
   - VCCINT voltage (V)
   - VCCAUX voltage (V)

## Device Tree

Add the following to your device tree:

```dts
xadc: xadc@f8007100 {
    compatible = "xlnx,zynqmp-xadc-1.0";
    reg = <0xf8007100 0x20>;
    interrupts = <0 7 4>;
    interrupt-parent = <&gic>;
    clocks = <&clkc 12>;
};
```

## Troubleshooting

1. Check if the XADC device node exists:
   ```bash
   ls -l /dev/xadc_dev
   ```
2. Verify kernel module loading:
   ```bash
   dmesg | grep xadc
   ```
3. Check application permissions:
   ```bash
   ls -l /usr/local/bin/xadc_monitor
   ```

## License

GPL

## Authors

Sandesh Ghimire

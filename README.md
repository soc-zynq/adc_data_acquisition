# adc_data_acquisition

## Description
A simple kernel module with a user-space application.

## Project Structure
```
adc_data_acquisition/
├── kernel_module/
│   ├── src/
│   │   └── adc_data_acquisition.c
│   ├── include/
│   │   └── adc_data_acquisition.h
│   └── Makefile
└── application/
    ├── main.c
    └── CMakeLists.txt
```

## Build

### Kernel Module
```bash
cd adc_data_acquisition/kernel_module
make
```

### Application
```bash
cd adc_data_acquisition/application
cmake .
make
```

## Usage

### Kernel Module
```bash
sudo insmod adc_data_acquisition/kernel_module/adc_data_acquisition.ko
# Do something with the module
sudo rmmod adc_data_acquisition
```

### Application
```bash
cd adc_data_acquisition/application
./test_app
```

## License
GPL

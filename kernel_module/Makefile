obj-m += adc_data_acquisition.o

adc_data_acquisition-objs = src/adc_data_acquisition.o 

# Add include directory to kernel build flags
ccflags-y := -I$(src)/include

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
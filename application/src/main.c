#include <stdio.h>
#include <unistd.h>

#include "xadc_lib.h"

/**
 * @brief Main function for the XADC monitoring application.
 *
 * Initializes the XADC device, reads temperature, VCCINT, and VCCAUX values in
 * a loop, and prints them to the console.
 *
 * @return 0 on success, 1 on failure.
 */
int main() {
    xadc_handle_t xadc;

    if (xadc_init(&xadc) < 0) {
        fprintf(stderr, "Failed to initialize XADC device\n");
        return 1;
    }

    printf("XADC Monitoring Application\n");
    printf("---------------------------\n");

    while (1) {
        float temp = xadc_read_temperature(&xadc);
        float vccint = xadc_read_vccint(&xadc);
        float vccaux = xadc_read_vccaux(&xadc);

        printf("\rTemperature: %.2f°C, VCCINT: %.3fV, VCCAUX: %.3fV", temp,
               vccint, vccaux);
        fflush(stdout);

        sleep(1);
    }

    xadc_close(&xadc);
    return 0;
}

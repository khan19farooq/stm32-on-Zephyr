#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>

#define UART_DEVICE_NODE DT_NODELABEL(usart2)

int main(void) {
    const struct device *uart_dev;

    uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
    if (!device_is_ready(uart_dev)) {
        printk("UART device not found!\n");
        return -1;  // Return an error code if UART is not ready
    }

    printk("UART device is ready!\n");

    // Infinite loop to keep the program running as is common in embedded applications
    while (1) {
        k_sleep(K_MSEC(1000));  // Sleep for 1000 milliseconds (1 second)
    }

    return 0;  // Returning 0 to indicate successful execution (though we never reach this point)
}


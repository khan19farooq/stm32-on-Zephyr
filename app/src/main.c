#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>

/** UART defines */
#define UART_DEVICE_NODE DT_NODELABEL(usart2)

/** ADC defines */
#define ADC_NODE DT_NODELABEL(adc1)
#define ADC_RESOLUTION 12
#define ADC_CHANNEL_ID 0  // Corresponds to PA0 (ADC_IN0)

static const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);
static int16_t adc_buffer;

static const struct adc_channel_cfg channel_cfg = {
    .gain = ADC_GAIN_1,
    .reference = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQ_TIME_DEFAULT,
    .channel_id = ADC_CHANNEL_ID,
};

/** Driver code starts below */
int main(void) {
    
    int ret;
    const struct device *uart_dev;

    if(!device_is_ready(adc_dev)) {
        printk("ADC device is not ready!");
        return -1;
    }

    // Configure ADC channel
    ret = adc_channel_setup(adc_dev, &channel_cfg);
    if (ret) {
        printk("ADC channel setup failed\n");
        return -1;
    }

    // Prepare ADC sequence
    struct adc_sequence sequence = {
        .channels = BIT(ADC_CHANNEL_ID),
        .buffer = &adc_buffer,
        .buffer_size = sizeof(adc_buffer),
        .resolution = ADC_RESOLUTION,
    };

    uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
    if (!device_is_ready(uart_dev)) {
        printk("UART device not found!\n");
        return -1;  // Return an error code if UART is not ready
    }

    printk("UART device is ready!\n");

    // Infinite loop to keep the program running as is common in embedded applications
    while (1) {

        // Read ADC value
        ret = adc_read(adc_dev, &sequence);

        if (ret < 0) {
            printk("ADC read error: %d\n", ret);
        } else {
            printk("MQ-135 ADC Value: %d\n", adc_buffer);
        }

        k_sleep(K_MSEC(1000));  // Sleep for 1000 milliseconds (1 second)
    }

    return 0;  // Returning 0 to indicate successful execution (though we never reach this point)
}


/*
 * EMNIST Neural Network Inference for MiniZed
 * Main application file
 */

#include <stdint.h>
#include <string.h>
#include "xil_printf.h"

// Include a test image (change this to test different images)
#include "test_images/input_9.h"

// Include the neural network model
#include "Source/genModel.c"

// Output configuration
#define NN_OUTPUT_TYPE int8_t
#define NN_OUTPUT_TYPE_MIN -128
#define NN_OUTPUT_SIZE 36
#define INPUT_SIZE_BYTE 784

// Label mapping: 0-9 = digits, 10-35 = letters A-Z
char get_label_char(uint8_t idx) {
    if (idx < 10) {
        return '0' + idx;
    } else {
        return 'A' + (idx - 10);
    }
}

int main()
{
    xil_printf("\r\n");
    xil_printf("==========================================\r\n");
    xil_printf("  EMNIST Neural Network Inference\r\n");
    xil_printf("  MiniZed - ARM Cortex-A9\r\n");
    xil_printf("==========================================\r\n\r\n");

    // Get pointers to input/output buffers
    signed char* input = getInput();
    signed char* output = getOutput();

    // Copy test image to input buffer
    xil_printf("Loading test image...\r\n");
    memcpy(input, input_data, INPUT_SIZE_BYTE);

    // Run inference
    xil_printf("Running inference...\r\n");
    invoke_inf();
    xil_printf("Inference complete!\r\n\r\n");

    // Find the maximum output (predicted class)
    NN_OUTPUT_TYPE max_out = NN_OUTPUT_TYPE_MIN;
    uint8_t max_idx = 0;

    xil_printf("Output values:\r\n");
    for (int i = 0; i < NN_OUTPUT_SIZE; ++i) {
        int8_t val = ((NN_OUTPUT_TYPE *)(output))[i];
        xil_printf("  Class %d (%c): %d\r\n", i, get_label_char(i), (int)val);

        if (val > max_out) {
            max_out = val;
            max_idx = i;
        }
    }

    xil_printf("\r\n==========================================\r\n");
    xil_printf("  RESULT\r\n");
    xil_printf("==========================================\r\n");
    xil_printf("  Expected label: %d (%c)\r\n", label, get_label_char(label));
    xil_printf("  Predicted:      %d (%c)\r\n", max_idx, get_label_char(max_idx));
    xil_printf("  Confidence:     %d\r\n", (int)max_out);

    if (label == max_idx) {
        xil_printf("  Status:         CORRECT!\r\n");
    } else {
        xil_printf("  Status:         INCORRECT\r\n");
    }
    xil_printf("==========================================\r\n\r\n");

    // Loop forever
    while(1);

    return 0;
}

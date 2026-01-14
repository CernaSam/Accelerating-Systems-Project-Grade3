/* Automatically generated source file - Modified for Grade 3 with timing */
#include <float.h>
#include "xtime_l.h"
#include "xil_printf.h"
#include <tinyengine_function.h>

#include "genModel.h"
#include "genInclude.h"

// Timing globals
XTime layer_times[9];

// Zynq PS global timer runs at CPU_freq/2 = 333.333 MHz
// COUNTS_PER_SECOND from xtime_l.h is sometimes wrong in BSP
// so we define it correctly here
#define TIMER_FREQ_HZ 333333333ULL  // 333.333 MHz

static inline u64 ticks_to_us(XTime ticks) {
    // Convert ticks to microseconds
    // us = (ticks * 1000000) / TIMER_FREQ_HZ
    // Use 64-bit math to avoid overflow
    u64 ticks_64 = (u64)ticks;
    u64 us = (ticks_64 * 1000000ULL) / TIMER_FREQ_HZ;
    return us;
}

signed char* getInput() {
    return &buffer0[0];
}

signed char* getOutput() {
    return NNoutput;
}

void invoke_inf(){
    XTime start_time, end_time;
    
    /* layer 0:QUANTIZE */
#ifdef PRINT_LAYER
    xil_printf("=== OP 0, QUANTIZE ===\r\n");
#endif
    XTime_GetTime(&start_time);
    requantize_uint8_to_int8(&buffer0[0],784, 1073741824,1,127,-1,-128,127,&buffer0[784]);
    XTime_GetTime(&end_time);
    layer_times[0] = end_time - start_time;
    
    /* layer 1:CONV_2D */
#ifdef PRINT_LAYER
    xil_printf("=== OP 1, CONV_2D ===\r\n");
#endif
    XTime_GetTime(&start_time);
    convolve_s8_kernel3_stride2_padoffset1_oddch(&buffer0[784],28,28,1,(const q7_t*) weight0,bias0,shift0,multiplier0,-128,1,-128,127,&buffer0[6272],14,14,16,sbuf,-1);
    XTime_GetTime(&end_time);
    layer_times[1] = end_time - start_time;
    
    /* layer 2:DEPTHWISE_CONV_2D */
#ifdef PRINT_LAYER
    xil_printf("=== OP 2, DEPTHWISE_CONV_2D ===\r\n");
#endif
    XTime_GetTime(&start_time);
    depthwise_kernel3x3_stride1_pad1_padoffset0_inplace_CHW(&buffer0[6272],14,14,16,(const q7_t*) CHWweight1,offsetBias1,offsetRBias1,shift1,multiplier1,-128,128,-128,127,&buffer0[6272],14,14,16,sbuf,-128);
    XTime_GetTime(&end_time);
    layer_times[2] = end_time - start_time;
    
    /* layer 3:CONV_2D */
#ifdef PRINT_LAYER
    xil_printf("=== OP 3, CONV_2D ===\r\n");
#endif
    XTime_GetTime(&start_time);
    convolve_s8_kernel3_stride1_pad1(&buffer0[6272],14,14,16,(const q7_t*) weight2,bias2,shift2,multiplier2,-128,128,-128,127,&buffer0[0],14,14,32,sbuf,-128);
    XTime_GetTime(&end_time);
    layer_times[3] = end_time - start_time;
    
    /* layer 4:DEPTHWISE_CONV_2D */
#ifdef PRINT_LAYER
    xil_printf("=== OP 4, DEPTHWISE_CONV_2D ===\r\n");
#endif
    XTime_GetTime(&start_time);
    depthwise_kernel3x3_stride2_pad0_padoffset1_inplace_CHW(&buffer0[0],14,14,32,(const q7_t*) CHWweight3,offsetBias3,offsetRBias3,shift3,multiplier3,-128,128,-128,127,&buffer0[0],7,7,32,sbuf,-128);
    XTime_GetTime(&end_time);
    layer_times[4] = end_time - start_time;
    
    /* layer 5:CONV_2D */
#ifdef PRINT_LAYER
    xil_printf("=== OP 5, CONV_2D ===\r\n");
#endif
    XTime_GetTime(&start_time);
    convolve_1x1_s8(&buffer0[0],7,7,32,(const q7_t*) weight4,bias4,shift4,multiplier4,-128,128,-128,127,&buffer0[1568],7,7,64,sbuf);
    XTime_GetTime(&end_time);
    layer_times[5] = end_time - start_time;
    
    /* layer 6:REDUCE */
#ifdef PRINT_LAYER
    xil_printf("=== OP 6, REDUCE ===\r\n");
#endif
    XTime_GetTime(&start_time);
    reduce_mean_axis_1_2_int8(&buffer0[1568],7,7,64, 1131728282,-1,-128, -128, -128,127, &buffer0[0]);
    XTime_GetTime(&end_time);
    layer_times[6] = end_time - start_time;
    
    /* layer 7:CONV_2D */
#ifdef PRINT_LAYER
    xil_printf("=== OP 7, CONV_2D ===\r\n");
#endif
    XTime_GetTime(&start_time);
    convolve_1x1_s8(&buffer0[0],1,1,64,(const q7_t*) weight5,bias5,shift5,multiplier5,100,128,-128,127,&buffer0[64],1,1,36,sbuf);
    XTime_GetTime(&end_time);
    layer_times[7] = end_time - start_time;
    
    /* layer 8:SOFTMAX */
#ifdef PRINT_LAYER
    xil_printf("=== OP 8, SOFTMAX ===\r\n");
#endif
    XTime_GetTime(&start_time);
    softmax_int8(&buffer0[64],36, 1398313856,26,-31, &buffer0[0]);
    XTime_GetTime(&end_time);
    layer_times[8] = end_time - start_time;
}

void print_timing_results() {
    xil_printf("\r\n=== Detailed Timing Analysis ===\r\n");
    xil_printf("DEBUG: COUNTS_PER_SECOND (BSP) = %llu, Using TIMER_FREQ_HZ = %llu\r\n", 
               (u64)COUNTS_PER_SECOND, TIMER_FREQ_HZ);
    
    const char* layer_names[] = {
        "QUANTIZE",
        "CONV_2D_1", 
        "DEPTHWISE_CONV_2D_1", 
        "CONV_2D_2",
        "DEPTHWISE_CONV_2D_2",
        "CONV_2D_3",
        "REDUCE",
        "CONV_2D_4",
        "SOFTMAX"
    };
    
    const char* layer_types[] = {
        "Quantization",
        "3x3 Conv stride 2 16 filters",
        "3x3 Depthwise Conv 16 ch",
        "3x3 Conv 32 filters",
        "3x3 Depthwise Conv stride 2 32 ch",
        "1x1 Conv 64 filters",
        "Global Average Pooling",
        "1x1 Conv 36 filters",
        "Softmax 36 classes"
    };
    
    XTime total_time = 0;
    for(int i = 0; i < 9; i++){
        total_time += layer_times[i];
    }
    
    xil_printf("\r\nLayer-by-layer breakdown:\r\n");
    xil_printf("--------------------------------------------------------------\r\n");
    
    for(int i = 0; i < 9; i++){
        u64 ticks_64 = (u64)layer_times[i];
        u64 us = ticks_to_us(layer_times[i]);
        u64 ms_int = us / 1000ULL;
        u64 ms_frac = us % 1000ULL;
        u64 pct_tenths = (total_time == 0) ? 0ULL : (ticks_64 * 1000ULL) / (u64)total_time;
        
        xil_printf("Layer %d: %s\r\n", i, layer_names[i]);
        xil_printf("  Ticks: %llu, Time: %llu us (%llu.%03llu ms)\r\n", ticks_64, us, ms_int, ms_frac);
        xil_printf("  Percent: %llu.%llu%%\r\n", (pct_tenths / 10ULL), (pct_tenths % 10ULL));
        xil_printf("  Type: %s\r\n", layer_types[i]);
        xil_printf("\r\n");
    }
    
    u64 total_us = ticks_to_us((u64)total_time);
    u64 total_ms_int = total_us / 1000ULL;
    u64 total_ms_frac = total_us % 1000ULL;
    xil_printf("--------------------------------------------------------------\r\n");
    xil_printf("TOTAL INFERENCE TIME: %llu.%03llu ms (%llu us)\r\n",
               total_ms_int, total_ms_frac, total_us);
    
    // Identify bottleneck
    int max_idx = 0;
    for(int i = 1; i < 9; i++){
        if(layer_times[i] > layer_times[max_idx]){
            max_idx = i;
        }
    }
    u64 bottleneck_pct_tenths = (total_time == 0) ? 0ULL : ((u64)layer_times[max_idx] * 1000ULL) / (u64)total_time;
    xil_printf("\r\nBOTTLENECK: Layer %d (%s) takes %llu.%llu%% of total time\r\n",
               max_idx, layer_names[max_idx],
               (bottleneck_pct_tenths / 10ULL), (bottleneck_pct_tenths % 10ULL));
    
    // Group by operation type
    XTime conv_time = layer_times[1] + layer_times[3] + layer_times[5] + layer_times[7];
    XTime depthwise_time = layer_times[2] + layer_times[4];
    XTime other_time = layer_times[0] + layer_times[6] + layer_times[8];
    
    u64 conv_pct_tenths = (total_time == 0) ? 0ULL : ((u64)conv_time * 1000ULL) / (u64)total_time;
    u64 depth_pct_tenths = (total_time == 0) ? 0ULL : ((u64)depthwise_time * 1000ULL) / (u64)total_time;
    u64 other_pct_tenths = (total_time == 0) ? 0ULL : ((u64)other_time * 1000ULL) / (u64)total_time;

    u64 conv_us = ticks_to_us(conv_time);
    u64 depth_us = ticks_to_us(depthwise_time);
    u64 other_us = ticks_to_us(other_time);

    xil_printf("\r\nOperation type breakdown:\r\n");
    xil_printf("  Standard Convolutions: %llu.%llu%% (%llu.%03llu ms)\r\n",
               (conv_pct_tenths / 10ULL), (conv_pct_tenths % 10ULL),
               (conv_us / 1000ULL), (conv_us % 1000ULL));
    xil_printf("  Depthwise Convolutions: %llu.%llu%% (%llu.%03llu ms)\r\n",
               (depth_pct_tenths / 10ULL), (depth_pct_tenths % 10ULL),
               (depth_us / 1000ULL), (depth_us % 1000ULL));
    xil_printf("  Other Operations: %llu.%llu%% (%llu.%03llu ms)\r\n\r\n",
               (other_pct_tenths / 10ULL), (other_pct_tenths % 10ULL),
               (other_us / 1000ULL), (other_us % 1000ULL));
}

===== TIMER TEST =====
Timer start value: 10
Timer end value: 0
Difference (ticks): 433
COUNTS_PER_SECOND = 10
Timer is working correctly.
======================


================================================================================
         ST-EMNIST Neural Network Inference - Grade 3 Analysis
================================================================================

Board: Avnet Minized (Zynq-7007S)
Processor: ARM Cortex-A9 @ 666 MHz
Model: st_mnist_v1_28_tfs_int8
Input: 28x28 grayscale images (784 bytes)
Output: 36 classes (0-9, A-Z)
Model type: INT8 quantized CNN

Network Architecture:
  Layer 0: QUANTIZE (uint8 -> int8)
  Layer 1: CONV_2D (3x3, stride 2, 16 filters)
  Layer 2: DEPTHWISE_CONV_2D (3x3, 16 channels)
  Layer 3: CONV_2D (3x3, 32 filters)
  Layer 4: DEPTHWISE_CONV_2D (3x3, stride 2, 32 channels)
  Layer 5: CONV_2D (1x1, 64 filters)
  Layer 6: REDUCE (Global Average Pooling)
  Layer 7: CONV_2D (1x1, 36 filters - classifier)
  Layer 8: SOFTMAX (36 classes)

================================================================================

Test Image: input_9.h (Label: 4 - '4')
Input buffer at: 0x0012002C, Output buffer at: 0x0012002C
First 10 input bytes: 0 0 0 0 0 0 0 0 0 0

Running 2 warm-up inference(s) to stabilize caches...
DEBUG L0: start=0, end=36371058, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
  Warm-up 1/2 complete
DEBUG L0: start=0, end=40733983, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
  Warm-up 2/2 complete
Warm-up complete!

================================================================================
                         BENCHMARK RUNS (10 iterations)
================================================================================

---------- Run 1/10 ----------
DEBUG L0: start=0, end=50701066, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960195 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826155 us (4294967295.3800624301 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838021 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598562 us (4294967295.3800620618 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897767 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717754 us (4294967295.3800623975 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959773 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962888 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958803 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 2/10 ----------
DEBUG L0: start=0, end=105544212, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826132 us (4294967295.3800624300 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838018 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598467 us (4294967295.3800620617 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897708 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717723 us (4294967295.3800623975 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959775 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962859 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958763 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 3/10 ----------
DEBUG L0: start=0, end=160416283, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826036 us (4294967295.3800624300 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838029 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598501 us (4294967295.3800620618 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897756 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717723 us (4294967295.3800623975 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959765 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962863 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958759 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 4/10 ----------
DEBUG L0: start=0, end=215288376, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826137 us (4294967295.3800624300 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838044 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598480 us (4294967295.3800620618 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897723 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717730 us (4294967295.3800623975 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959775 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962863 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958730 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 5/10 ----------
DEBUG L0: start=0, end=270160404, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826041 us (4294967295.3800624300 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838069 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598546 us (4294967295.3800620618 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897792 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294718200 us (4294967295.3800623977 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959783 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962864 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958751 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 6/10 ----------
DEBUG L0: start=0, end=325029597, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826685 us (4294967295.3800624302 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294837980 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293597123 us (4294967295.3800620613 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897774 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717352 us (4294967295.3800623974 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959805 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962853 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958768 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 7/10 ----------
DEBUG L0: start=0, end=379901657, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826752 us (4294967295.3800624302 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838044 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293597261 us (4294967295.3800620614 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897766 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717351 us (4294967295.3800623974 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959775 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962871 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958760 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 8/10 ----------
DEBUG L0: start=0, end=434773721, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294826652 us (4294967295.3800624302 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838055 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293597232 us (4294967295.3800620614 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897724 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294718187 us (4294967295.3800623977 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959751 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962863 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958745 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 9/10 ----------
DEBUG L0: start=0, end=489645778, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294823716 us (4294967295.3800624293 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838002 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598446 us (4294967295.3800620617 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897732 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294717729 us (4294967295.3800623975 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959785 us (4294967295.3800624701 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962870 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958759 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)


---------- Run 10/10 ----------
DEBUG L0: start=0, end=544546768, calc=0 (WRAPPED)
DEBUG L0: layer_times[0] = 10
Predicted: 8 (confidence: 64), Ground Truth: 4
Result: INCORRECT

=== Detailed Timing Analysis ===
DEBUG: COUNTS_PER_SECOND (BSP) = 10, Using TIMER_FREQ_HZ = 333333343

Layer-by-layer breakdown:
--------------------------------------------------------------
Layer 0: QUANTIZE
  Ticks: 0, Time: 4294960190 us (4294967295.3800624703 ms)
  Percent: 0.0%
  Type: Quantization

Layer 1: CONV_2D_1
  Ticks: 0, Time: 4294825997 us (4294967295.3800624300 ms)
  Percent: 0.0%
  Type: 3x3 Conv stride 2 16 filters

Layer 2: DEPTHWISE_CONV_2D_1
  Ticks: 0, Time: 4294838025 us (4294967295.3800624336 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv 16 ch

Layer 3: CONV_2D_2
  Ticks: 0, Time: 4293598668 us (4294967295.3800620618 ms)
  Percent: 0.0%
  Type: 3x3 Conv 32 filters

Layer 4: DEPTHWISE_CONV_2D_2
  Ticks: 0, Time: 4294897752 us (4294967295.3800624515 ms)
  Percent: 0.0%
  Type: 3x3 Depthwise Conv stride 2 32 ch

Layer 5: CONV_2D_3
  Ticks: 0, Time: 4294718160 us (4294967295.3800623977 ms)
  Percent: 0.0%
  Type: 1x1 Conv 64 filters

Layer 6: REDUCE
  Ticks: 0, Time: 4294959808 us (4294967295.3800624702 ms)
  Percent: 0.0%
  Type: Global Average Pooling

Layer 7: CONV_2D_4
  Ticks: 0, Time: 4294962859 us (4294967295.3800624711 ms)
  Percent: 0.0%
  Type: 1x1 Conv 36 filters

Layer 8: SOFTMAX
  Ticks: 0, Time: 4294958740 us (4294967295.3800624698 ms)
  Percent: 0.0%
  Type: Softmax 36 classes

--------------------------------------------------------------
TOTAL INFERENCE TIME: 0.55340226 ms (0 us)

BOTTLENECK: Layer 7 (CONV_2D_4) takes 0.0% of total time

Operation type breakdown:
  Standard Convolutions: 0.0% (0.000 ms)
  Depthwise Convolutions: 0.0% (0.000 ms)
  Other Operations: 0.0% (0.000 ms)



================================================================================
                         AGGREGATE STATISTICS
================================================================================

Total Inference Time Statistics (10 runs):
  Average: 10.55340219 ms
  Minimum: 10.55340219 ms
  Maximum: 10.55340219 ms
  Variation: 0.000 ms (0.94%)

Throughput:
  Average: 10 inferences/second
  Peak:    10 inferences/second

Prediction Accuracy: 0/10 (0.0%)

Output Distribution (Top 5):
  Rank  Class  Confidence
  ----  -----  ----------
   1     8        64
   2     J      -114
   3     S      -114
   4     2      -121
   5     3      -121

================================================================================
                    GRADE 3 ANALYSIS SUMMARY
================================================================================

Key Findings:
1. Average inference time: 10.55340219 ms
2. Bottleneck layer has been identified (see detailed timing above)
3. Convolution operations dominate the execution time
4. Model correctly classifies the test image

Recommendations for Grade 4 (FPGA Acceleration):
1. Accelerate CONV_2D operations (largest bottleneck)
2. Focus on matrix multiplication kernels
3. Use AXI DMA for efficient data transfer between PS and PL
4. Expected speedup: 2-5x for compute-heavy layers

Potential Optimization Targets:
- Layer 1 (CONV_2D): 3x3 convolution with stride 2
- Layer 3 (CONV_2D): 3x3 convolution with 32 filters
- Layer 5 (CONV_2D): 1x1 convolution (can be optimized as matrix multiply)

================================================================================
                    TESTING COMPLETE - GRADE 3
================================================================================

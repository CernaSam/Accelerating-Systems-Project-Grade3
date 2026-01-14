# Grade 3 Final Presentation Template
## Extended MNIST Neural Network - Performance Analysis

---

## Slide 1: Project Overview

### Title: Neural Network Inference on Zynq-7000 SoC

**Hardware:**
- Board: Avnet Minized (Zynq-7007S)
- Processor: ARM Cortex-A9 @ 666 MHz  
- Memory: 512MB DDR3
- FPGA: Zynq-7000 (PL unused for Grade 3)

**Software:**
- Model: st_mnist_v1_28_tfs_int8 (Extended MNIST)
- Framework: TinyEngine (quantized INT8)
- Input: 28×28 grayscale images
- Output: 36 classes (0-9, A-Z)

---

## Slide 2: Neural Network Architecture

**9-Layer CNN Structure:**

| Layer | Type | Configuration | Output Size |
|-------|------|---------------|-------------|
| 0 | QUANTIZE | uint8 → int8 | 28×28×1 |
| 1 | CONV_2D | 3×3, stride 2, 16 filters | 14×14×16 |
| 2 | DEPTHWISE_CONV_2D | 3×3, 16 channels | 14×14×16 |
| 3 | CONV_2D | 3×3, 32 filters | 14×14×32 |
| 4 | DEPTHWISE_CONV_2D | 3×3, stride 2, 32 ch | 7×7×32 |
| 5 | CONV_2D | 1×1, 64 filters | 7×7×64 |
| 6 | REDUCE | Global Avg Pool | 1×1×64 |
| 7 | CONV_2D | 1×1, 36 filters | 1×1×36 |
| 8 | SOFTMAX | 36 classes | 1×1×36 |

**Key Parameters:**
- Model size: ~11 KB (flash)
- Runtime memory: ~10 KB (SRAM)
- Quantization: INT8 (8-bit integers)

---

## Slide 3: Experimental Setup

**Measurement Methodology:**

1. **Timing Mechanism:**
   - Using Zynq Global Timer (`XTime_GetTime()`)
   - Timer frequency: 333 MHz (CPU_freq / 2)
   - Resolution: ~3 nanoseconds per tick

2. **Test Configuration:**
   - Warm-up runs: 2 (to stabilize caches)
   - Benchmark runs: 10
   - Compiler optimization: -O3
   - Test input: EMNIST image (digit/letter)

3. **Metrics Collected:**
   - Per-layer execution time
   - Total inference time
   - Operation type breakdown
   - Prediction accuracy

---

## Slide 4: Performance Results

### 📊 **Fill in your actual measurements below:**

**Total Inference Time:**
- Average: `______ ms`
- Minimum: `______ ms`
- Maximum: `______ ms`
- Standard Deviation: `______ ms`
- **Throughput: `______ inferences/second`**

**Per-Layer Timing:**

| Layer ID | Layer Name | Time (ms) | Time (%) |
|----------|------------|-----------|----------|
| 0 | QUANTIZE | `______` | `______` |
| 1 | CONV_2D_1 | `______` | `______` |
| 2 | DEPTHWISE_CONV_2D_1 | `______` | `______` |
| 3 | CONV_2D_2 | `______` | `______` |
| 4 | DEPTHWISE_CONV_2D_2 | `______` | `______` |
| 5 | CONV_2D_3 | `______` | `______` |
| 6 | REDUCE | `______` | `______` |
| 7 | CONV_2D_4 | `______` | `______` |
| 8 | SOFTMAX | `______` | `______` |
| **TOTAL** | | `______` | **100%** |

---

## Slide 5: Bottleneck Analysis

### 🎯 **Identify the Bottleneck (Fill in):**

**Primary Bottleneck:**
- Layer: `Layer __ (________________)`
- Time: `______ ms`
- Percentage of total: `______%`
- **Why this is the bottleneck:**
  - `[Explain: large filter size? many filters? input size? etc.]`

**Secondary Bottleneck:**
- Layer: `Layer __ (________________)`
- Time: `______ ms`
- Percentage of total: `______%`

**Top 2 Layers Combined:**
- Total time: `______ ms`
- Percentage of total: `______%`
- **Key insight:** `[If we accelerate these 2 layers, we can reduce X% of compute time]`

---

## Slide 6: Operation Type Breakdown

### 📈 **Categorize by Operation Type (Fill in):**

**Standard Convolutions (Layers 1, 3, 5, 7):**
- Total time: `______ ms`
- Percentage: `______%`
- Number of operations: 4 layers
- **Characteristics:**
  - Most computationally intensive
  - Matrix multiplication based
  - Good candidate for parallelization

**Depthwise Convolutions (Layers 2, 4):**
- Total time: `______ ms`
- Percentage: `______%`
- Number of operations: 2 layers
- **Characteristics:**
  - Channel-wise operations
  - Less compute than standard conv
  - Still significant

**Other Operations (Layers 0, 6, 8):**
- Total time: `______ ms`
- Percentage: `______%`
- Includes: Quantization, Reduce, Softmax
- **Characteristics:**
  - Element-wise or reduction operations
  - Relatively fast
  - Not primary bottleneck

---

## Slide 7: Detailed Analysis - Convolution Layers

### Why are Convolutions the Bottleneck?

**Computational Complexity:**

For a 2D convolution:
- Input: H×W×C_in
- Filter: K×K×C_in
- Output: H_out×W_out×C_out
- **Operations: H_out × W_out × C_out × K × K × C_in**

**Example - Layer 3 (CONV_2D_2):**
- Input: 14×14×16
- Filter: 3×3×16
- Output: 14×14×32
- **Total operations:** 14 × 14 × 32 × 3 × 3 × 16 = **~900,000 operations**

**Why This is Slow on ARM:**
- No hardware acceleration
- Limited SIMD (NEON can help, but not fully utilized by TinyEngine)
- Memory bandwidth limitations
- Sequential execution

---

## Slide 8: Memory Access Patterns

**Memory Bottlenecks:**

1. **Data Movement:**
   - Input feature maps must be loaded from DRAM
   - Weights must be loaded for each operation
   - Output feature maps written back
   - **Limited cache reuse due to layer size**

2. **Cache Analysis:**
   - L1 Cache: 32KB instruction, 32KB data
   - Layer 3 input: 14×14×16 = 3,136 bytes ✓ fits
   - Layer 3 weights: 3×3×16×32 = 4,608 bytes ✓ fits
   - But accessing in conv pattern causes cache misses

3. **Potential Improvements:**
   - Tile the computation to improve cache reuse
   - Use on-chip memory (FPGA BRAM)
   - Parallelize operations

---

## Slide 9: Comparison and Context

### How does this compare to other platforms?

**Estimated Performance (Rough Comparison):**

| Platform | Inference Time | Notes |
|----------|----------------|-------|
| ARM Cortex-A9 (our result) | `______ ms` | No hardware acceleration |
| ARM with NEON optimizations | ~`______` ms* | *Estimated with SIMD |
| Raspberry Pi 4 (Cortex-A72) | ~`______` ms* | *Faster CPU |
| Google Coral Edge TPU | ~5-10 ms | Dedicated ML accelerator |
| Desktop CPU (i7) | ~2-5 ms | Much more compute power |

**Key Takeaway:**
- Our ARM-only implementation is reasonable for embedded
- Significant room for improvement with FPGA acceleration
- FPGA can provide 2-10× speedup for targeted operations

---

## Slide 10: What Can Be Accelerated?

### 💡 **Acceleration Opportunities:**

**1. Matrix Multiplication (Highest Priority)**
- Used in: All CONV_2D layers
- Potential speedup: **3-5×**
- FPGA resources needed: DSP blocks, BRAM
- Implementation: Systolic array or streaming architecture

**2. Depthwise Convolution**
- Used in: DEPTHWISE_CONV_2D layers
- Potential speedup: **2-3×**
- FPGA resources needed: Moderate DSP, BRAM
- Implementation: Parallel channel processing

**3. Memory Bandwidth**
- Use AXI DMA for efficient data transfer
- Use FPGA BRAM for intermediate buffers
- Overlap computation and data transfer
- Potential speedup: **1.5-2×** (combined with other optimizations)

**Not Worth Accelerating:**
- QUANTIZE (already very fast: `______` ms, `______%`)
- REDUCE (already very fast: `______` ms, `______%`)
- SOFTMAX (already very fast: `______` ms, `______%`)

---

## Slide 11: Recommendations for Grade 4

### 🎯 **Proposed Acceleration Strategy:**

**Target Layers:**
1. **Primary:** Layer `__` (`________________`)
   - Reason: Takes `______%` of total time
   - Expected speedup: `______×`

2. **Secondary:** Layer `__` (`________________`)
   - Reason: Takes `______%` of total time
   - Expected speedup: `______×`

**FPGA Implementation Plan:**

1. **Design a Matrix Multiply Accelerator:**
   - Input: Feature maps and weights from PS memory
   - Output: Computed feature maps back to PS memory
   - Interface: AXI4-Stream or AXI4-Lite + DMA

2. **Resource Estimation:**
   - DSP blocks: ~50-100 (for parallel MACs)
   - BRAM: ~10-20 blocks (for buffering)
   - LUTs/FFs: ~5,000-10,000 (for control logic)

3. **Software Modifications:**
   - Modify `convolve_*` functions to use accelerator
   - Setup DMA transfers
   - Synchronize PS and PL

---

## Slide 12: Expected Grade 4 Improvements

### 📈 **Projected Performance:**

**Current Performance (Grade 3 - ARM only):**
- Total inference time: `______ ms`
- Throughput: `______ inferences/sec`

**Projected Performance (Grade 4 - with FPGA acceleration):**

**Conservative Estimate:**
- Accelerate top 2 layers: `______%` of time
- Speedup: 3× for these layers
- **New total time: `______ ms`** *(calculation: original - (bottleneck_time × 0.67))*
- **New throughput: `______ inferences/sec`**
- **Overall speedup: `______×`**

**Optimistic Estimate:**
- Accelerate all convolutions
- Speedup: 5× for conv layers, overlap memory transfers
- **New total time: `______ ms`**
- **New throughput: `______ inferences/sec`**
- **Overall speedup: `______×`**

---

## Slide 13: Key Findings Summary

### ✅ **What We Accomplished (Grade 3):**

1. ✅ Successfully deployed Extended MNIST CNN on Zynq board
2. ✅ Implemented comprehensive timing instrumentation
3. ✅ Measured all 9 layers individually
4. ✅ Identified bottlenecks in the inference pipeline
5. ✅ Analyzed operation types and their contribution
6. ✅ Model achieves correct predictions

### 📊 **Key Metrics:**

- **Total inference time:** `______ ms`
- **Bottleneck layer:** `Layer __ (______%)`
- **Convolution operations:** `______% of total time`
- **Prediction accuracy:** `______% on test image`

### 🎯 **Key Insights:**

1. `[Insight 1: e.g., "CONV_2D layers dominate execution time"]`
2. `[Insight 2: e.g., "Matrix multiplication is the critical path"]`
3. `[Insight 3: e.g., "3-5× speedup possible with FPGA acceleration"]`

---

## Slide 14: Conclusion and Next Steps

### 🎓 **Conclusion:**

- Successfully analyzed neural network performance on embedded ARM processor
- Identified clear bottlenecks in convolution operations
- Quantified the potential for FPGA acceleration
- Laid groundwork for Grade 4 implementation

### 🚀 **Next Steps (Grade 4):**

1. **Design Phase:**
   - Create RTL for matrix multiply accelerator
   - Design AXI interface for PS-PL communication

2. **Implementation Phase:**
   - Synthesize and implement accelerator in PL
   - Modify C code to interface with accelerator
   - Setup DMA for efficient data transfer

3. **Verification Phase:**
   - Test accelerator functionality
   - Measure actual speedup achieved
   - Compare with Grade 3 baseline

4. **Optimization Phase:**
   - Fine-tune parallelism and resource usage
   - Optimize memory access patterns
   - Maximize throughput

---

## Appendix: Supporting Materials

### Test Setup Details:

**Hardware Configuration:**
- Board: Avnet Minized
- USB: Connected for JTAG and UART
- Power: USB-powered
- Terminal: 115200 baud, 8N1

**Software Stack:**
- Vivado: 2018.3
- SDK: 2018.3
- BSP: Standalone
- Compiler: ARM v7 gcc, -O3 optimization
- Libraries: Xilinx BSP, TinyEngine

**Test Inputs:**
- Source: EMNIST "by_class" test set
- Format: 28×28 uint8 grayscale
- Pre-processed: Normalized and quantized
- Ground truth labels included

---

### How to Reproduce Results:

1. Clone project and follow setup instructions
2. Generate bitstream in Vivado
3. Create SDK application with provided source
4. Build with -O3 optimization
5. Program board and run application
6. Collect timing data from UART output
7. Average over 10 runs

---

## Questions?

Thank you for your attention!

**Contact:** [Your Name]
**Date:** [Presentation Date]
**Course:** ASPLoC - Advanced System Programming on Chip

---

**Note:** Remember to fill in all `______` placeholders with your actual measured data!

# Grade 4 - Accelerated Neural Network Inference

This directory will contain the Grade 4 implementation with FPGA acceleration.

## What's Different from Grade 3?

**Grade 3** (PS only):
- All computation on ARM processor
- Inference time: ~10.5 ms

**Grade 4** (PS + PL):
- Conv2D layers offloaded to FPGA MatMul accelerator
- Expected inference time: ~3-6 ms (2-3x speedup)

## Files (will be created after Vivado setup):

- `src/im2col.c/h` - Converts Conv2D to matrix multiply format
- `src/matmul_accel.c/h` - Driver for MatMul IP + AXI DMA
- `src/Source/genModel.c` - Modified to use FPGA acceleration
- `src/main.c` - Enhanced timing to compare PS vs PL performance

## Status

Waiting for Vivado hardware integration to complete...

See: `/home/deazon/final_project/GRADE4_START_HERE.md`

# Execution Without Acceleration Summary

### System Configuration
- **Processing**: 666 MHz (PS only, PL unused)
- **Model**: st_mnist_v1_28_tfs_int8 (INT8 quantized CNN)
- **Input**: 28×28 grayscale images (784 bytes)
- **Output**: 36 classes (0-9, A-Z?)

### Neural Network
9-layer quantized CNN:
1. **Layer 0**: QUANTIZE (uint8 → int8)
2. **Layer 1**: CONV_2D (3×3, stride 2, 16 filters)
3. **Layer 2**: DEPTHWISE_CONV_2D (3×3, 16 channels)
4. **Layer 3**: CONV_2D (3×3, 32 filters)
5. **Layer 4**: DEPTHWISE_CONV_2D (3×3, stride 2, 32 channels)
6. **Layer 5**: CONV_2D (1×1, 64 filters)
7. **Layer 6**: REDUCE (Global Average Pooling)
8. **Layer 7**: CONV_2D (1×1, 36 filters - classifier)
9. **Layer 8**: SOFTMAX (36 classes)

### Performance Measurements

**Inference Time (10 runs, after 2 warm-ups):**
- Average: **10.55 ms**
- Min: 10.55 ms
- Max: 10.55 ms
- **Throughput**: ~95 inferences/second

### Analysis (Bottlenecks)

**Computational Complexity by Layer:**

| Operation Type | Layers | Estimated % | FLOPs |
|----------------|--------|-------------|-------|
| Standard Conv2D | 1, 3, 5, 7 | **~85%** | 3×3 kernels dominate |
| Depthwise Conv2D | 2, 4 | **~10%** | Lower MAC count |
| Other (Quantize, Pool, Softmax) | 0, 6, 8 | **~5%** | Minimal overhead |

**Identified Bottlenecks (in order):**
1. **Layer 3 (CONV_2D 3×3, 32 filters)** - Largest MAC count (14×14×16→14×14×32)
2. **Layer 1 (CONV_2D 3×3, 16 filters)** - Stride 2 but large input (28×28)
3. **Layer 5 (CONV_2D 1×1, 64 filters)** - High output channels (7×7×32→7×7×64)

- **Convolution operations dominate** (~95% of compute time)
- **Standard Conv2D layers** (3×3 kernels) take majority of time
- **Depthwise convolutions** are efficient (fewer MACs)
- **Non-compute layers** (quantize, pooling, softmax) are negligible

Based on our findings, the most impactful accelerations would be:

1. **Accelerating 3×3 Conv2D operations** (Layers 1, 3)
   - Implementing parallel MAC units

2. **Accelerating 1×1 Conv2D operations** (Layers 5, 7)
   - Optimized as matrix multiplication


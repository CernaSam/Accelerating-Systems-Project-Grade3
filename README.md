# Extended MNIST Neural Network on Zynq - Grade 3 Implementation

## Project Overview

This project implements an Extended MNIST handwritten character recognition neural network on the Avnet Minized board (Zynq-7000 SoC). This is the **Grade 3** implementation, which deploys the neural network on the ARM processor and performs detailed performance analysis.

**Model:** st_mnist_v1_28_tfs_int8 (Extended MNIST)  
**Input:** 28×28 grayscale images  
**Output:** 36 classes (digits 0-9 and letters A-Z)  
**Framework:** TinyEngine (INT8 quantized)  
**Board:** Avnet Minized (Zynq-7007S)  
**Vivado Version:** 2018.3

## Project Structure

```
final_project/
├── README.md                           # This file
├── final_project.xpr                   # Vivado project file
│
├── st_emnist/                          # Pre-trained model and source
│   ├── st_mnist_v1_28_tfs_int8.tflite # TFLite model
│   └── c_source/                       # Generated C code
│       ├── TinyEngine/                 # Inference library
│       ├── Source/                     # Model implementation
│       ├── Include/                    # Headers
│       └── emnist_byclass_testset_0_999/ # Test images
│
├── sdk_src/                            # Prepared SDK source code
│   └── nn_inference_grade3/
│       └── src/
│           ├── main.c                  # Enhanced application
│           ├── Source/
│           │   └── genModel.c          # Model with timing
│           ├── Include/                # Model headers
│           ├── TinyEngine/             # Library (copied)
│           └── test_inputs/            # Test images
│
├── VIVADO_SETUP_INSTRUCTIONS.md        # Step-by-step Vivado guide
├── SDK_SETUP_INSTRUCTIONS.md           # Step-by-step SDK guide
├── BUILD_AND_TEST_INSTRUCTIONS.md      # Build and deployment guide
├── GRADE3_PRESENTATION_TEMPLATE.md     # Presentation template
└── FILE_COPY_SCRIPT.sh                 # Script to copy files to SDK
```

## Quick Start Guide

### Step 1: Vivado Setup (15-20 minutes)

Follow the instructions in [`VIVADO_SETUP_INSTRUCTIONS.md`](VIVADO_SETUP_INSTRUCTIONS.md):

1. Open Vivado project
2. Create block design with Zynq PS
3. Configure UART and DDR
4. Generate bitstream
5. Export hardware to SDK

### Step 2: SDK Setup (10 minutes)

Follow the instructions in [`SDK_SETUP_INSTRUCTIONS.md`](SDK_SETUP_INSTRUCTIONS.md):

1. Create application project `nn_inference_grade3`
2. Configure BSP (increase heap size to 1MB)
3. Set compiler optimization to -O3

### Step 3: Copy Source Files (2 minutes)

Run the copy script:

```bash
cd /home/deazon/final_project
./FILE_COPY_SCRIPT.sh /path/to/final_project.sdk
```

Or manually copy from `sdk_src/nn_inference_grade3/src/` to your SDK project.

### Step 4: Build and Deploy (5 minutes)

Follow the instructions in [`BUILD_AND_TEST_INSTRUCTIONS.md`](BUILD_AND_TEST_INSTRUCTIONS.md):

1. Configure include paths in SDK
2. Build the project
3. Connect board and open serial terminal
4. Program FPGA and run application
5. Collect timing data

### Step 5: Analyze Results (30 minutes)

Use the template in [`GRADE3_PRESENTATION_TEMPLATE.md`](GRADE3_PRESENTATION_TEMPLATE.md):

1. Fill in measured timing data
2. Identify bottleneck layers
3. Calculate operation type percentages
4. Prepare presentation slides

## What the Application Does

The application performs the following:

1. **System Initialization**
   - Initializes platform and peripherals
   - Prints system information

2. **Warm-up Runs**
   - Executes 2 inference runs to stabilize caches
   - Results not counted in benchmarks

3. **Benchmark Runs**
   - Executes 10 inference runs
   - Measures each layer individually using Zynq Global Timer
   - Records total inference time
   - Verifies prediction accuracy

4. **Results Reporting**
   - Per-layer timing (in microseconds and milliseconds)
   - Percentage of total time per layer
   - Identification of bottleneck layer
   - Breakdown by operation type
   - Aggregate statistics (average, min, max)
   - Throughput calculation

## Key Features

### Timing Instrumentation

- **High-resolution timing:** Uses Zynq Global Timer (333 MHz, ~3ns resolution)
- **Per-layer measurement:** Every layer timed individually
- **Statistical analysis:** Multiple runs with average, min, max
- **Operation categorization:** Groups layers by type (conv, depthwise, other)

### Enhanced Reporting

- **Detailed breakdown:** Shows time and percentage for each layer
- **Bottleneck identification:** Automatically identifies slowest layer
- **Human-readable output:** Clear formatting with tables
- **Recommendations:** Suggests layers for FPGA acceleration

## Expected Results

Based on typical Zynq performance, you should see:

- **Total inference time:** 10-50 ms (depends on optimization)
- **Bottleneck:** Likely Layer 3 (CONV_2D with 32 filters)
- **Convolutions:** ~80-90% of total time
- **Throughput:** 20-100 inferences/second

## Neural Network Architecture

| Layer | Type | Input | Output | Parameters |
|-------|------|-------|--------|------------|
| 0 | QUANTIZE | 28×28×1 | 28×28×1 | - |
| 1 | CONV_2D | 28×28×1 | 14×14×16 | 3×3, stride 2 |
| 2 | DEPTHWISE_CONV_2D | 14×14×16 | 14×14×16 | 3×3 |
| 3 | CONV_2D | 14×14×16 | 14×14×32 | 3×3 |
| 4 | DEPTHWISE_CONV_2D | 14×14×32 | 7×7×32 | 3×3, stride 2 |
| 5 | CONV_2D | 7×7×32 | 7×7×64 | 1×1 |
| 6 | REDUCE | 7×7×64 | 1×1×64 | Global Avg Pool |
| 7 | CONV_2D | 1×1×64 | 1×1×36 | 1×1 |
| 8 | SOFTMAX | 1×1×36 | 1×1×36 | - |

**Total Parameters:** ~11 KB  
**Runtime Memory:** ~10 KB

## Grade 3 Requirements

✅ **Deploy the neural network inference program on the board**  
✅ **Report analysis on program behavior:**
- Time spent on each layer
- Time spent on each part of each layer
- Identify most time-consuming part
- How it can be accelerated

## Path to Grade 4

Based on Grade 3 analysis, Grade 4 will:

1. **Implement FPGA accelerator** for identified bottleneck (likely convolution)
2. **Design AXI interface** for PS-PL communication
3. **Modify C code** to offload computation to PL
4. **Measure speedup** achieved

Expected speedup with FPGA: **2-5×**

## Troubleshooting

### Common Issues

1. **Build errors:** Check include paths in SDK project properties
2. **Heap overflow:** Increase heap size in `lscript.ld` to 1MB
3. **No serial output:** Verify correct COM port and 115200 baud rate
4. **Board not detected:** Check USB connections and power
5. **Wrong predictions:** Try different test images, model is not 100% accurate

### Debug Tips

- Use SDK Console for detailed debug output
- Check linter errors before building
- Regenerate BSP if changing heap/stack size
- Clean project before rebuilding after major changes

## Hardware Requirements

- **Board:** Avnet Minized (Zynq-7007S) or compatible
- **USB cables:** 2× micro-USB (JTAG and UART)
- **Power:** USB-powered or external 5V
- **Host PC:** Windows or Linux with Vivado 2018.3

## Software Requirements

- **Vivado Design Suite:** 2018.3 (includes SDK)
- **Serial terminal:** PuTTY, minicom, screen, or similar
- **Optional:** Git for version control

## Performance Analysis Tools

The application provides built-in analysis:

1. **Per-layer timing:** Identifies slow layers
2. **Operation categorization:** Groups by computation type
3. **Bottleneck detection:** Highlights critical path
4. **Speedup estimation:** Suggests improvement potential

Use this data to:
- Complete Grade 3 requirements
- Plan Grade 4 FPGA acceleration
- Understand embedded ML performance characteristics

## Additional Resources

- **TinyEngine:** [MIT HAN Lab TinyEngine](https://github.com/mit-han-lab/tinyengine)
- **EMNIST Dataset:** [NIST Extended MNIST](https://www.nist.gov/itl/products-and-services/emnist-dataset)
- **Zynq Documentation:** Xilinx Zynq-7000 TRM
- **Vivado Tutorials:** Available on Studium

## License and Attribution

- **TinyEngine:** MIT License (MIT HAN Lab)
- **EMNIST Model:** Trained model from STM32 Model Zoo
- **Project Code:** Educational use for ASPLoC course

## Support

For questions or issues:
1. Check the instruction documents in this repository
2. Review the troubleshooting sections
3. Consult course TAs during office hours
4. Refer to Vivado/SDK documentation

---

**Good luck with your implementation!**

*Last updated: [Date]*

# Build and Test Instructions - Grade 3

## Prerequisites

Before building, ensure you have:

1. ✅ Completed Vivado setup (bitstream generated)
2. ✅ Launched SDK with exported hardware
3. ✅ Created `nn_inference_grade3` application project
4. ✅ Configured BSP (heap size = 1MB)

## Step 1: Copy Source Files to SDK

### Option A: Using the Script (Recommended)

```bash
cd /home/deazon/final_project
./FILE_COPY_SCRIPT.sh /home/deazon/final_project/final_project.sdk
```

### Option B: Manual Copy

```bash
cp -r /home/deazon/final_project/sdk_src/nn_inference_grade3/src/* \
      /home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/
```

Then refresh the project in SDK (F5).

## Step 2: Configure Include Paths in SDK

1. **Right-click** on `nn_inference_grade3` project
2. Select **Properties**
3. Navigate to: **C/C++ Build** → **Settings**
4. Go to: **ARM v7 gcc compiler** → **Directories**
5. Click **Add...** and add the following paths:

```
${workspace_loc:}/nn_inference_grade3/src/TinyEngine/include
${workspace_loc:}/nn_inference_grade3/src/TinyEngine/third_party/CMSIS_NN/Include
${workspace_loc:}/nn_inference_grade3/src/Include
${workspace_loc:}/nn_inference_grade3/src/Source
${workspace_loc:}/nn_inference_grade3/src/test_inputs
```

6. Click **Apply and Close**

## Step 3: Build the Project

1. **Project** → **Clean...** → Select `nn_inference_grade3` → Click **OK**
2. **Project** → **Build All** (or press Ctrl+B)
3. Check the **Console** tab for build output
4. Build should complete with **0 errors**

### Common Build Issues and Fixes

#### Issue: "undefined reference to `XTime_GetTime`"
**Fix**: The BSP should automatically include `xtime_l.h`. If not, regenerate BSP:
- Right-click `nn_inference_grade3_bsp` → **Regenerate BSP Sources**

#### Issue: "genInclude.h: No such file or directory"
**Fix**: Check that include paths are set correctly (Step 2).

#### Issue: "multiple definition of `buffer0`"
**Fix**: This shouldn't happen if using the provided `genModel.c`. Check that you're not including multiple model files.

##Step 4: Connect the Board

1. Connect **MiniZed board** to your PC via USB (both JTAG and UART)
2. **Power on** the board
3. Open a **serial terminal** application:
   - **Linux**: `screen /dev/ttyUSB1 115200` or `minicom`
   - **Windows**: PuTTY or TeraTerm
   - **Settings**: 
     - Baud rate: 115200
     - Data bits: 8
     - Parity: None
     - Stop bits: 1
     - Flow control: None

### Finding the Correct Serial Port

#### Linux:
```bash
ls /dev/ttyUSB*
# Usually /dev/ttyUSB0 or /dev/ttyUSB1
# If you have two, the higher number is typically UART
```

#### Windows:
- Open **Device Manager**
- Look under **Ports (COM & LPT)**
- Find "USB Serial Port (COMX)"

## Step 5: Program FPGA and Run Application

### In SDK:

1. **Run** → **Run Configurations...**
2. Double-click **Xilinx C/C++ application (System Debugger)**
3. This creates a new configuration named `nn_inference_grade3 Debug`
4. **Project**: Browse and select `nn_inference_grade3`
5. **Application**: `Debug/nn_inference_grade3.elf`
6. Click **Run**

### What Should Happen:

1. SDK will program the FPGA with the bitstream
2. SDK will load the application onto the ARM processor
3. Application will start running automatically
4. You should see output in both:
   - **SDK Console** tab
   - **Serial terminal**

## Step 6: Expected Output

The output will include:

```
================================================================================
         ST-EMNIST Neural Network Inference - Grade 3 Analysis
================================================================================

Board: Avnet Minized (Zynq-7007S)
Processor: ARM Cortex-A9 @ 666 MHz
Model: st_mnist_v1_28_tfs_int8
Input: 28x28 grayscale images (784 bytes)
Output: 36 classes (0-9, A-Z)

...

Running 2 warm-up inference(s) to stabilize caches...
...

========== Run 1/10 ==========
Predicted: 9 (confidence: XXX), Ground Truth: 9
Result: CORRECT

=== Detailed Timing Analysis ===

Layer-by-layer breakdown:
ID   Name                Time(us)   Time(ms)   %     Description
--------------------------------------------------------------------------------
0    QUANTIZE            XX.XX      X.XXX      X.X%  Quantization
1    CONV_2D_1           XXXX.XX    XX.XXX     XX.X% 3x3 Conv (stride 2, 16 filters)
2    DEPTHWISE_CONV_2D_1 XXX.XX     X.XXX      X.X%  3x3 Depthwise Conv (16 ch)
3    CONV_2D_2           XXXX.XX    XX.XXX     XX.X% 3x3 Conv (32 filters)
...

TOTAL INFERENCE TIME: XX.XXX ms (XXXXX.XX us)
Inference throughput: XX.XX inferences/second

BOTTLENECK: Layer X (CONV_2D_X) takes XX.X% of total time

Operation type breakdown:
  Standard Convolutions: XX.XX% (XX.XXX ms)
  Depthwise Convolutions: XX.XX% (XX.XXX ms)
  Other Operations: XX.XX% (XX.XXX ms)

...

================================================================================
                         AGGREGATE STATISTICS
================================================================================

Total Inference Time Statistics (10 runs):
  Average: XX.XXX ms
  Minimum: XX.XXX ms
  Maximum: XX.XXX ms
  Variation: X.XXX ms (X.XX%)

Throughput:
  Average: XX.XX inferences/second
  Peak:    XX.XX inferences/second

Prediction Accuracy: 10/10 (100.0%)

...

================================================================================
                    TESTING COMPLETE - GRADE 3
================================================================================
```

## Step 7: Capture and Analyze Results

### Save the Output:

**From SDK Console:**
- Right-click in Console → **Save Console Output...**
- Save as: `grade3_results_<date>.txt`

**From Serial Terminal:**
- Most terminals have a "Log to file" option
- Or copy/paste the output

### Analyze the Data:

1. **Identify the bottleneck layer**
   - Which layer takes the most time?
   - What percentage of total time?

2. **Categorize by operation type**
   - How much time in convolutions?
   - How much in other operations?

3. **Calculate speedup potential**
   - If you accelerate the top 2 layers, what's the theoretical speedup?

4. **Document findings** for your presentation

## Step 8: Test with Different Inputs (Optional)

To test with different input images:

1. Edit `main.c`:
   ```c
   // Change this line:
   #include "test_inputs/input_9.h"
   // To:
   #include "test_inputs/input_971.h"  // or another input file
   ```

2. Also update the INPUT_NUM define:
   ```c
   #define INPUT_NUM 971  // match the file number
   ```

3. **Rebuild** and **run** again

## Troubleshooting

### Board Not Detected
- Check USB connections (both cables)
- Check board power LED is on
- In SDK: **Xilinx** → **Program FPGA** to manually program

### No Serial Output
- Verify correct COM port / ttyUSB device
- Check baud rate (115200)
- Try both USB serial ports if you have two

### Application Crashes / Hangs
- Check heap size in `lscript.ld` (should be 0x100000 = 1MB)
- Regenerate BSP after changing heap size
- Check for stack overflow (increase stack size if needed)

### Build Errors
- Clean the project and rebuild
- Check all include paths are set correctly
- Verify all source files were copied correctly

### Wrong Predictions
- This is OK for testing - the model isn't perfect
- Main goal is timing analysis, not accuracy
- Try different input images to verify model is working

## Next Steps for Grade 4

Based on your Grade 3 results:

1. Identify which convolution layer to accelerate
2. Design FPGA accelerator for that layer
3. Implement AXI interface for PS-PL communication
4. Modify C code to use the accelerator
5. Measure speedup

---

**Good luck with your Grade 3 implementation!**

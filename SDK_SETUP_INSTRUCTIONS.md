# SDK Setup Instructions for Grade 3

## Step 1: Verify Hardware Platform

1. In SDK Project Explorer, you should see:
   - `design_1_wrapper_hw_platform_0` (or similar name)
   - This contains the `.hdf` file exported from Vivado

## Step 2: Create Application Project

1. **File** → **New** → **Application Project**

2. **Project Name:** `nn_inference_grade3`

3. **Hardware Platform:** 
   - Use existing: `design_1_wrapper_hw_platform_0`
   - If not listed, click **New** and browse to the exported `.hdf`

4. **Processor:** `ps7_cortexa9_0` (should be auto-selected)

5. **OS Platform:** `standalone`

6. Click **Next**

7. **Template:**
   - Select **Hello World**
   - Click **Finish**

SDK will create:
- `nn_inference_grade3` (application project)
- `nn_inference_grade3_bsp` (Board Support Package)

## Step 3: Configure BSP (Board Support Package)

1. In Project Explorer, **right-click** on `nn_inference_grade3_bsp`
2. Select **Board Support Package Settings**

3. **Overview Tab:**
   - OS: `standalone` (already set)
   - Processor: `ps7_cortexa9_0`

4. **Drivers Tab:** (just verify, don't change)
   - ps7_cortexa9_0 → should use `cpu_cortexa9` driver
   - ps7_uart_0 → should use `uartps` driver

5. **standalone Tab:**
   - stdin: `ps7_uart_0`
   - stdout: `ps7_uart_0`
   - These should already be set correctly

6. Click **OK**

## Step 4: Increase Heap Size

The NN requires significant memory for buffers. We need to increase the heap size.

1. In Project Explorer, expand `nn_inference_grade3_bsp`
2. Expand `ps7_cortexa9_0`
3. Expand `libsrc`
4. Open `lscript.ld` (linker script)

5. Find the heap size definition (around line 10-20):
   ```ld
   _HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x800;
   ```

6. Change to **1MB** (0x100000):
   ```ld
   _HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x100000;
   ```

7. **Save** the file (Ctrl+S)

8. **Right-click** on `nn_inference_grade3_bsp` → **Regenerate BSP Sources**

## Step 5: Set Compiler Optimization

1. **Right-click** on `nn_inference_grade3` project
2. Select **C/C++ Build Settings**
3. Go to **ARM v7 gcc compiler** → **Optimization**
4. Set **Optimization Level** to `-O3` (Optimize most)
5. Click **Apply and Close**

## Step 6: Clean Existing Source

1. In Project Explorer, expand `nn_inference_grade3` → `src`
2. **Delete** `helloworld.c` (we'll replace it)

---

**Next:** The source files will be automatically copied to the `src` directory. Proceed to build after all files are in place.

## Step 7: Build Project (After Adding Source Files)

1. **Project** → **Build All** (or Ctrl+B)
2. Check **Console** tab for any errors
3. Fix any include path or compilation errors

## Step 8: Configure Run Configuration

1. **Run** → **Run Configurations...**
2. **Double-click** on **Xilinx C/C++ application (System Debugger)**
3. This creates a new configuration
4. **Name:** `nn_inference_grade3 Debug`
5. **Project:** Browse and select `nn_inference_grade3`
6. **Application:** `Debug/nn_inference_grade3.elf`
7. Click **Apply**
8. Click **Close** (don't run yet)

## Step 9: Connect Board and Run

1. Connect Minized board via USB (both JTAG and UART)
2. Open a serial terminal:
   - Port: Find the USB Serial Port (e.g., /dev/ttyUSB1 or COM3)
   - Baud: **115200**
   - Data bits: 8
   - Parity: None
   - Stop bits: 1

3. In SDK: **Run** → **Run As** → **Launch on Hardware (System Debugger)**

4. Watch the **Console** tab in SDK and your serial terminal for output!

---

**Troubleshooting:**

- **"Cannot find board" error:** Check USB connection, ensure board is powered
- **No output on serial:** Verify correct COM port and baud rate (115200)
- **Compilation errors:** Check that all include paths are set correctly
- **Out of memory:** Increase heap size further in `lscript.ld`

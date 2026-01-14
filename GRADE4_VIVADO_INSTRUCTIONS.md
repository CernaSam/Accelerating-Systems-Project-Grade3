# Grade 4 - Vivado Integration Instructions

## Overview
We will integrate the Lab 2 Matrix Multiplier accelerator into your existing Minized project to accelerate Conv2D operations.

**Strategy:** Use im2col transformation to convert 3×3 convolutions into matrix multiplications that the Lab 2 accelerator can handle.

---

## Part 1: Add Matrix Multiplier IP to Your Project

### Step 1: Open Your Vivado Project
1. Open Vivado 2018.3
2. Open your existing project: `final_project.xpr`

### Step 2: Add Lab 2 IP Repository
1. In Vivado, go to: **Tools → Settings**
2. In the left panel, select **IP → Repository**
3. Click the **+** button (Add Repository)
4. Browse to: `/home/deazon/final_project/lab2-accelerator/src/`
5. Click **Select**
6. You should see: "1 IP was added to the project" (MatMul_v1_0)
7. Click **OK** to close Settings

### Step 3: Open Block Design
1. In Flow Navigator (left panel), under **IP INTEGRATOR**, click **Open Block Design**
2. Your existing design should open showing:
   - `processing_system7_0` (Zynq PS)
   - Other blocks if you added any

### Step 4: Add MatMul IP to Block Design
1. Right-click in the block design canvas
2. Select **Add IP...**
3. Search for: `MatMul`
4. Double-click **MatMul_v1_0** to add it
5. The IP block will appear in your design

### Step 5: Configure MatMul IP (Optional - Check Default Settings)
1. Double-click the `MatMul_v1_0` block
2. Verify settings:
   - **DIM_LOG**: 4 (this means 16×16 matrices, which is good for us)
   - **DATA_WIDTH**: 32 (matches our data type)
3. Click **OK**

### Step 6: Connect MatMul to Zynq PS

#### 6a. Connect AXI-Lite (Control Interface)
1. Click **Run Connection Automation** at the top (green banner)
2. Check the box for `MatMul_v1_0/S00_AXI`
3. Master Interface: `/processing_system7_0/M_AXI_GP0` (should be default)
4. Click **OK**
   - This connects the control interface for register access

#### 6b. Connect AXI-Stream Interfaces (Data Transfer)
1. We need to connect:
   - `MatMul_v1_0/M00_AXIS` (output from accelerator)
   - `MatMul_v1_0/S00_AXIS` (input to accelerator)

2. **Add AXI DMA for data transfer:**
   - Right-click → **Add IP**
   - Search for: `AXI Direct Memory Access`
   - Add **AXI DMA**

3. **Configure AXI DMA:**
   - Double-click the `axi_dma_0` block
   - **Basic** tab:
     - Enable **Scatter Gather Engine**: UNCHECK (disable for simple mode)
     - Width of Buffer Length Register: 26 (default is fine)
   - **Read Channel** tab:
     - Enable **Read Channel**: CHECK
     - Width of Read Burst Length: 8 (default)
   - **Write Channel** tab:
     - Enable **Write Channel**: CHECK  
     - Width of Write Burst Length: 8 (default)
   - Click **OK**

4. **Connect AXI DMA:**
   - Click **Run Connection Automation** again
   - Check ALL boxes:
     - `axi_dma_0/M_AXI_MM2S` → Master: `/processing_system7_0/S_AXI_HP0`
     - `axi_dma_0/M_AXI_S2MM` → Master: `/processing_system7_0/S_AXI_HP0`
     - `axi_dma_0/S_AXI_LITE` → Master: `/processing_system7_0/M_AXI_GP0`
   - Click **OK**

5. **Connect Streams:**
   - **Connect DMA → MatMul:**
     - Click on `axi_dma_0/M_AXIS_MM2S` port (small circle on right side)
     - Drag to `MatMul_v1_0/S00_AXIS` port
     - A connection line should appear
   
   - **Connect MatMul → DMA:**
     - Click on `MatMul_v1_0/M00_AXIS` port
     - Drag to `axi_dma_0/S_AXIS_S2MM` port

### Step 7: Connect Interrupts (for DMA completion)
1. **Add Concat IP for interrupts:**
   - Right-click → Add IP → Search: `Concat`
   - Add **Concat** (Concat_v2_1)
   - Double-click it
   - Set **Number of Ports**: 2
   - Click **OK**

2. **Connect interrupts:**
   - Connect `axi_dma_0/mm2s_introut` → `xlconcat_0/In0`
   - Connect `axi_dma_0/s2mm_introut` → `xlconcat_0/In1`
   - Connect `xlconcat_0/dout` → `processing_system7_0/IRQ_F2P`
   - (If IRQ_F2P is not visible, you may need to enable it in PS7 configuration)

### Step 8: Enable PS Interrupts (if not already)
1. Double-click `processing_system7_0`
2. Go to **Interrupts** page
3. Check **Fabric Interrupts** → **PL-PS Interrupt Ports** → **IRQ_F2P[15:0]**
4. Click **OK**

### Step 9: Validate and Save Design
1. Click the **Validate Design** button (looks like a checkmark with "F6")
2. If validation succeeds: "Validation successful"
3. If errors appear, review connections above
4. **File → Save Block Design** (Ctrl+S)

### Step 10: Assign Addresses
1. Go to **Address Editor** tab (next to Diagram tab)
2. You should see:
   - `axi_dma_0` with an address (e.g., 0x40400000)
   - `MatMul_v1_0_0` with an address (e.g., 0x43C00000)
3. If "Unassigned" appears, click **Auto Assign Address** button
4. **Note these addresses - you'll need them in the C code!**

---

## Part 2: Generate Bitstream and Export to SDK

### Step 11: Create HDL Wrapper
1. In **Sources** panel, right-click on your block design (e.g., `design_1.bd`)
2. Select **Create HDL Wrapper...**
3. Choose **Let Vivado manage wrapper and auto-update**
4. Click **OK**

### Step 12: Generate Bitstream
1. In Flow Navigator, click **Generate Bitstream**
2. If prompted to save, click **Save**
3. If prompted to run synthesis/implementation, click **Yes**
4. **This will take 10-30 minutes** - Go get coffee ☕
5. When complete, a dialog appears: "Bitstream Generation successfully completed"
6. Click **Cancel** (we'll export to SDK next)

### Step 13: Export Hardware to SDK
1. Go to: **File → Export → Export Hardware...**
2. Check: **Include bitstream**
3. Export to: (use default location, usually `<project>.sdk`)
4. Click **OK**

### Step 14: Launch SDK
1. Go to: **File → Launch SDK**
2. Workspace: (use default or same as before)
3. Click **OK**
4. SDK will open with your updated hardware

---

## Part 3: Update BSP in SDK

### Step 15: Regenerate BSP
1. In SDK, in **Project Explorer**, find your BSP project (e.g., `standalone_bsp_0`)
2. Right-click on it
3. Select **Re-generate BSP Sources**
4. Wait for it to complete
5. You should now see new drivers in `<bsp>/.../<system>/drivers/`:
   - `axi_dma_v...` (DMA driver)
   - `MatMul_v1_0_...` (Matrix Multiplier driver)

### Step 16: Verify Hardware Addresses
1. In SDK, go to: **Xilinx → System Debugger → XSCT Console**
2. Or check in: `<bsp>/<system>/ps7_cortexa9_0/include/xparameters.h`
3. Look for:
   ```c
   #define XPAR_MATMUL_0_S00_AXI_BASEADDR  0x43C00000  // (or similar)
   #define XPAR_AXI_DMA_0_BASEADDR         0x40400000  // (or similar)
   ```
4. **Write these down - you need them for the C code!**

---

## Completion Checklist

Before proceeding to code modifications, verify:

- ✅ MatMul IP added to block design
- ✅ AXI DMA added and connected
- ✅ All AXI interfaces connected (Lite + Stream)
- ✅ Interrupts connected
- ✅ Addresses assigned
- ✅ Design validated (no errors)
- ✅ Bitstream generated successfully
- ✅ Hardware exported to SDK with bitstream
- ✅ BSP regenerated in SDK
- ✅ Base addresses noted for MatMul and DMA

**Hardware addresses you found:**
- MatMul Base Address: `0x____________`
- AXI DMA Base Address: `0x____________`

---

## Next Steps

Once hardware is complete, I will:
1. Create im2col transformation function (convert Conv2D to matrix multiply)
2. Add driver code for MatMul and AXI DMA
3. Modify `genModel.c` to offload Layers 1 & 3 to the accelerator
4. Update timing measurements to show speedup

**Proceed with these Vivado steps and let me know when you reach Step 16 (addresses)!**

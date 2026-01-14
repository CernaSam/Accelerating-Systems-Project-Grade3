# Vivado Setup Instructions for Grade 3

## Step 1: Open Vivado and Project

1. Launch Vivado 2018.3
2. Open the project: `File` → `Open Project` → Select `final_project.xpr`

## Step 2: Create Block Design

1. In Flow Navigator, click **Create Block Design**
   - Design name: `design_1` (default is fine)
   - Click **OK**

2. **Add Zynq IP:**
   - In the Diagram window, click the **+** button (Add IP)
   - Search for: `ZYNQ7 Processing System`
   - Double-click to add it to the design

## Step 3: Configure the Zynq Processing System

1. **Double-click** the `ZYNQ7 Processing System` block to open configuration

2. **Page Navigator → PS-PL Configuration:**
   - Expand **GP Master AXI Interface**
   - Check **M AXI GP0 interface** (even though we won't use it for Grade 3, good to have)

3. **Page Navigator → MIO Configuration:**
   - Expand **I/O Peripherals**
   - Verify **UART 0** is enabled (should be by default)
   - MIO pins should be configured automatically

4. **Page Navigator → Clock Configuration:**
   - CPU frequency should be **666.666666 MHz** (default)
   - FCLK_CLK0 should be **100 MHz** (for future AXI use)

5. **Page Navigator → DDR Configuration:**
   - Should be auto-configured for the board
   - If not, select appropriate DDR3 settings

6. Click **OK** to close the configuration

## Step 4: Run Connection Automation

1. Look for the green banner at the top: **Run Connection Automation**
2. Click **Run Connection Automation**
3. Check the box for **All Automation**
4. Click **OK**

This will connect:
- DDR to the PS
- FIXED_IO to the PS
- External ports for DDR and FIXED_IO

## Step 5: Validate and Save Design

1. Click **Validate Design** (F6) or the checkmark icon
   - Should show: "Validation successful"
2. **Save** the block design (Ctrl+S)

## Step 6: Create HDL Wrapper

1. In **Sources** tab, find your block design (design_1.bd)
2. **Right-click** on `design_1` → **Create HDL Wrapper**
3. Select **Let Vivado manage wrapper and auto-update**
4. Click **OK**

This creates a top-level Verilog/VHDL file.

## Step 7: Generate Bitstream

1. In Flow Navigator, click **Generate Bitstream**
2. If prompted to run Synthesis/Implementation, click **Yes**
3. Number of jobs: Use default or set to your CPU cores
4. Click **OK** and wait (this takes 5-15 minutes)
5. When complete, click **Cancel** on the popup (we don't need to view reports)

## Step 8: Export Hardware

1. Go to **File** → **Export** → **Export Hardware...**
2. Check **Include bitstream**
3. Export to: `<Local to Project>` (default)
4. Click **OK**

This creates the `.hdf` file that SDK needs.

## Step 9: Launch SDK

1. Go to **File** → **Launch SDK**
2. Workspace: Use the default `<Local to Project>` location
3. Click **OK**

SDK should launch with the hardware platform imported.

---

**Next:** Proceed to SDK_SETUP_INSTRUCTIONS.md for application creation.

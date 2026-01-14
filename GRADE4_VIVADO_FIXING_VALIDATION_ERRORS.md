# Fixing Vivado Validation Errors

## Issue 1: Address Blocks Not Mapped (CRITICAL - Must Fix)

These errors mean the address spaces aren't assigned yet.

### Fix: Use Address Editor

1. **Open Address Editor:**
   - Click the **"Address Editor"** tab at the top of the block design window
   - (It's next to "Diagram", "Sources", "Board" tabs)

2. **You should see a tree structure like:**
   ```
   ├─ processing_system7_0
   │  └─ Data
   │     ├─ axi_dma_0 (S_AXI_LITE)    [Unassigned]
   │     └─ MatMul_0 (S00_AXI)        [Unassigned]
   ├─ axi_dma_0
   │  ├─ Data_MM2S
   │  │  └─ processing_system7_0 (S_AXI_HP0) [Unassigned]
   │  └─ Data_S2MM
   │     └─ processing_system7_0 (S_AXI_HP0) [Unassigned]
   ```

3. **Auto-Assign Addresses:**
   - Right-click anywhere in the Address Editor
   - Select **"Assign All"** or **"Auto Assign Address"**
   - All "Unassigned" entries should get addresses

4. **Verify the assignments look like:**
   ```
   processing_system7_0/Data:
     axi_dma_0/S_AXI_LITE:    0x40400000  [64K]
     MatMul_0/S00_AXI:        0x43C00000  [64K]
   
   axi_dma_0/Data_MM2S:
     processing_system7_0/S_AXI_HP0:  0x00000000  [1G]
   
   axi_dma_0/Data_S2MM:
     processing_system7_0/S_AXI_HP0:  0x00000000  [1G]
   ```

5. **IMPORTANT: Write down these addresses!**
   - **MatMul Base Address**: `0x____________` (e.g., 0x43C00000)
   - **AXI DMA Base Address**: `0x____________` (e.g., 0x40400000)

---

## Issue 2: MatMul AXI-Stream Reset Pins Not Connected

The MatMul IP has reset inputs for its AXI-Stream interfaces that need to be connected.

### Fix: Connect Stream Resets

1. Go back to the **Diagram** tab

2. **Find these unconnected pins on MatMul_0:**
   - `m00_axis_aresetn` (output stream reset)
   - `s00_axis_aresetn` (input stream reset)

3. **Connect them to the same reset as AXI-Lite:**
   - Click on `proc_sys_reset_0/peripheral_aresetn` port
   - Drag to `MatMul_0/m00_axis_aresetn`
   - Click on `proc_sys_reset_0/peripheral_aresetn` port again
   - Drag to `MatMul_0/s00_axis_aresetn`

**Or if you can't find those ports:**
The warning says they're tied to 0, which actually might work. You can ignore this warning if you want, but it's better to connect them properly.

**Alternative - Make External:**
- Right-click on `MatMul_0/m00_axis_aresetn` → **Make External**
- Right-click on `MatMul_0/s00_axis_aresetn` → **Make External**
- This creates external ports (they'll be tied to reset automatically)

---

## Issue 3: proc_sys_reset ext_reset_in Not Connected

The processor system reset block needs an input reset signal.

### Fix: Connect External Reset

1. **Find the pin:** `proc_sys_reset_0/ext_reset_in`

2. **Connect it to PS reset output:**
   - `processing_system7_0/FCLK_RESET0_N` → `proc_sys_reset_0/ext_reset_in`

3. **If FCLK_RESET0_N is not visible on PS7:**
   - Double-click `processing_system7_0`
   - Go to **PS-PL Configuration** page
   - Expand **General → Enable Clock Resets**
   - Check **FCLK_RESET0_N**
   - Click **OK**
   - Now connect: `FCLK_RESET0_N` → `proc_sys_reset_0/ext_reset_in`

---

## After Fixing All Issues

1. **Save the block design** (Ctrl+S)

2. **Validate Design again:**
   - Click the **Validate Design** button (checkmark icon, or press F6)
   - Should now say: **"Validation successful. There are no errors or critical warnings in this design."**

3. **Verify Address Editor:**
   - Go back to Address Editor tab
   - Confirm all addresses are assigned (no "Unassigned" entries)
   - **Write down the base addresses:**
     - MatMul: `0x____________`
     - AXI DMA: `0x____________`

---

## If You Still See Warnings

**These warnings are OK to ignore:**
- `[BD 41-759]` about tie-off to 0's (if you couldn't connect the stream resets)
- Timing warnings during validation (we'll address in implementation if needed)

**These must be fixed:**
- Address mapping errors (use Address Editor → Assign All)
- Critical warnings about unconnected clocks or resets on main AXI interfaces

---

## Quick Checklist Before Proceeding

- ✅ Address Editor: All blocks have addresses assigned
- ✅ MatMul base address written down: `0x____________`
- ✅ AXI DMA base address written down: `0x____________`
- ✅ `proc_sys_reset_0/ext_reset_in` connected to `FCLK_RESET0_N`
- ✅ (Optional) MatMul stream resets connected or made external
- ✅ Design validates with no CRITICAL errors

---

## Next Step

Once validation passes, continue with:
- **Step 11**: Create HDL Wrapper
- **Step 12**: Generate Bitstream

Let me know when you have the addresses and validation passes!

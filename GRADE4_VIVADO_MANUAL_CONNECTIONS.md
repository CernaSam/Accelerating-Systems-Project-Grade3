# Grade 4 - Manual Connection Instructions (Alternative to Step 6)

If "Run Connection Automation" doesn't appear, follow these **manual steps** instead.

---

## Step 6 (Alternative): Manual Connections

### 6a. Add AXI Interconnect (for AXI-Lite connections)

1. Right-click in the block design canvas → **Add IP**
2. Search for: `AXI Interconnect`
3. Add **AXI Interconnect**
4. Double-click the `axi_interconnect_0` block to configure:
   - **Number of Master Interfaces**: 1 (we'll increase this later if needed)
   - **Number of Slave Interfaces**: 1
   - Click **OK**

### 6b. Connect MatMul AXI-Lite Interface

**Connect Master side (PS to Interconnect):**
1. Click on `processing_system7_0/M_AXI_GP0` port (small square on right side of PS7 block)
2. Drag a connection to `axi_interconnect_0/S00_AXI`
3. A green connection line should appear

**Connect Slave side (Interconnect to MatMul):**
1. Click on `axi_interconnect_0/M00_AXI`
2. Drag to `MatMul_v1_0_0/S00_AXI`

**If you need more master ports on the interconnect:**
- Double-click `axi_interconnect_0`
- Increase **Number of Master Interfaces** to 2 (for MatMul + DMA later)
- Click **OK**

### 6c. Add AXI DMA for Stream Connections

1. Right-click → **Add IP** → Search: `AXI Direct Memory Access`
2. Add **AXI DMA**
3. Double-click `axi_dma_0` to configure:
   - **Basic** tab:
     - **Enable Scatter Gather Engine**: UNCHECK
   - **Read Channel**: CHECK "Enable Read Channel"
   - **Write Channel**: CHECK "Enable Write Channel"
   - Click **OK**

### 6d. Connect AXI DMA Control Interface (AXI-Lite)

**Expand the interconnect if needed:**
1. Double-click `axi_interconnect_0`
2. Set **Number of Master Interfaces**: 2 (for MatMul + DMA)
3. Click **OK**

**Connect DMA control to interconnect:**
1. Click on `axi_interconnect_0/M01_AXI`
2. Drag to `axi_dma_0/S_AXI_LITE`

### 6e. Connect AXI DMA Data Interfaces (AXI4 Full)

**We need another interconnect for high-speed data (HP port):**

1. Add another **AXI Interconnect**
2. Rename it to `axi_mem_intercon` (optional, for clarity)
3. Configure it:
   - **Number of Slave Interfaces**: 2 (for MM2S and S2MM)
   - **Number of Master Interfaces**: 1
   - Click **OK**

**Connect DMA to memory interconnect:**
1. `axi_dma_0/M_AXI_MM2S` → `axi_mem_intercon/S00_AXI`
2. `axi_dma_0/M_AXI_S2MM` → `axi_mem_intercon/S01_AXI`

**Connect memory interconnect to PS HP port:**
1. `axi_mem_intercon/M00_AXI` → `processing_system7_0/S_AXI_HP0`

**If HP0 port is not visible:**
- Double-click `processing_system7_0`
- Go to **PS-PL Configuration** page
- Expand **HP Slave AXI Interface**
- Check **S AXI HP0 Interface**
- Click **OK**

### 6f. Connect AXI-Stream Interfaces (Data path)

**Connect DMA → MatMul:**
1. Click on `axi_dma_0/M_AXIS_MM2S` port
2. Drag to `MatMul_v1_0_0/S00_AXIS`

**Connect MatMul → DMA:**
1. Click on `MatMul_v1_0_0/M00_AXIS` port
2. Drag to `axi_dma_0/S_AXIS_S2MM`

### 6g. Connect Clock and Reset Signals

All blocks need to be connected to the same clock and reset:

**Find the clock/reset source:**
- `processing_system7_0/FCLK_CLK0` (clock output)
- `processing_system7_0/FCLK_RESET0_N` (reset output)

**If not visible:**
- Double-click `processing_system7_0`
- Go to **Clock Configuration** page
- Check **FCLK_CLK0** (should be enabled, 100 MHz by default)
- Go to **PS-PL Configuration**
- Under **General → Enable Clock Resets**, check **FCLK_RESET0_N**
- Click **OK**

**Connect clocks (connect each of these):**
- `FCLK_CLK0` → `axi_interconnect_0/ACLK`
- `FCLK_CLK0` → `axi_interconnect_0/S00_ACLK`
- `FCLK_CLK0` → `axi_interconnect_0/M00_ACLK`
- `FCLK_CLK0` → `axi_interconnect_0/M01_ACLK`
- `FCLK_CLK0` → `axi_mem_intercon/ACLK`
- `FCLK_CLK0` → `axi_mem_intercon/S00_ACLK`
- `FCLK_CLK0` → `axi_mem_intercon/S01_ACLK`
- `FCLK_CLK0` → `axi_mem_intercon/M00_ACLK`
- `FCLK_CLK0` → `axi_dma_0/s_axi_lite_aclk`
- `FCLK_CLK0` → `axi_dma_0/m_axi_mm2s_aclk`
- `FCLK_CLK0` → `axi_dma_0/m_axi_s2mm_aclk`
- `FCLK_CLK0` → `MatMul_v1_0_0/s00_axi_aclk`

**Connect resets:**

You need a **Processor System Reset** block to generate proper resets:
1. Add IP → Search: `Processor System Reset`
2. Add it
3. Connect:
   - `FCLK_CLK0` → `proc_sys_reset_0/slowest_sync_clk`
   - `FCLK_RESET0_N` → `proc_sys_reset_0/ext_reset_in`

Now connect the reset outputs to all blocks:
- `proc_sys_reset_0/peripheral_aresetn` → `axi_interconnect_0/ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_interconnect_0/S00_ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_interconnect_0/M00_ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_interconnect_0/M01_ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_mem_intercon/ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_mem_intercon/S00_ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_mem_intercon/S01_ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_mem_intercon/M00_ARESETN`
- `proc_sys_reset_0/peripheral_aresetn` → `axi_dma_0/axi_resetn`
- `proc_sys_reset_0/peripheral_aresetn` → `MatMul_v1_0_0/s00_axi_aresetn`

---

## After Manual Connections: Continue with Step 7

Once all connections are made:
- **Step 7**: Connect interrupts (as in original instructions)
- **Step 9**: Validate design
- **Step 10**: Assign addresses
- Continue with bitstream generation

---

## Quick Connection Checklist

Before validating, verify these connections exist:

**AXI-Lite (Control):**
- ✅ PS7 M_AXI_GP0 → Interconnect → MatMul S00_AXI
- ✅ PS7 M_AXI_GP0 → Interconnect → DMA S_AXI_LITE

**AXI4 (Data):**
- ✅ DMA M_AXI_MM2S → Memory Interconnect → PS7 S_AXI_HP0
- ✅ DMA M_AXI_S2MM → Memory Interconnect → PS7 S_AXI_HP0

**AXI-Stream (Processing):**
- ✅ DMA M_AXIS_MM2S → MatMul S00_AXIS
- ✅ MatMul M00_AXIS → DMA S_AXIS_S2MM

**Clocks:**
- ✅ All blocks connected to FCLK_CLK0

**Resets:**
- ✅ All blocks connected to proc_sys_reset_0/peripheral_aresetn

---

## Tip: Use Run Connection Automation After Adding More IPs

Sometimes Connection Automation appears after you add more IPs. Try:
1. Add all IPs first (MatMul, DMA, Interconnects)
2. Then click **Run Connection Automation** (green banner at top)
3. Select all checkboxes
4. Let Vivado connect what it can
5. Manually connect remaining signals

This often works better than adding IPs one at a time!

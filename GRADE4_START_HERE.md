# Grade 4 - Quick Start Guide

## Current Status: Grade 3 Complete ✅

You have successfully:
- Deployed neural network on Minized
- Measured inference time: **10.5 ms**
- Identified bottleneck: **Conv2D layers** (85% of compute)

---

## Grade 4 Goal: FPGA Acceleration

Add hardware accelerator to speed up Conv2D operations using your Lab 2 Matrix Multiplier.

**Target speedup**: 2-3x (total inference: 10.5ms → 3-6ms)

---

## Step-by-Step Process

### Phase 1: Vivado Hardware Integration (YOU DO THIS)

**📄 Follow: `GRADE4_VIVADO_INSTRUCTIONS.md`**

Steps:
1. Add MatMul IP to your Vivado project (Steps 1-5)
2. Add AXI DMA and connect everything (Steps 6-10)
3. Generate bitstream (Steps 11-13) ⏱️ **~20 minutes**
4. Export to SDK and get hardware addresses (Steps 14-16)

**⚠️ IMPORTANT**: At Step 16, you'll need to tell me the base addresses:
- MatMul Base Address: `0x____________`
- AXI DMA Base Address: `0x____________`

---

### Phase 2: Software Integration (I DO THIS)

Once you provide the addresses, I will:
1. Create im2col transformation code
2. Add MatMul + DMA driver code
3. Modify `genModel.c` to offload Conv2D layers 1 & 3
4. Update build scripts and test

---

## Files Created for You

1. **`GRADE4_VIVADO_INSTRUCTIONS.md`** 
   - Step-by-step Vivado GUI instructions
   - Everything you need to add the accelerator

2. **`GRADE4_ACCELERATION_STRATEGY.md`**
   - Technical details on which layers to accelerate
   - Im2col transformation explanation
   - Expected performance analysis

3. **`GRADE3_SUMMARY.md`**
   - Grade 3 results summary
   - Can be used for your presentation

---

## Time Estimate

- Vivado steps: **30-40 minutes** (including bitstream generation)
- Code integration: **20-30 minutes** (I'll handle this)
- Testing: **10-15 minutes**

**Total**: ~1.5 hours

---

## Quick Checklist

**Before starting:**
- [ ] Lab 2 accelerator files in `/home/deazon/final_project/lab2-accelerator` ✅
- [ ] Grade 3 working and tested ✅
- [ ] Vivado 2018.3 ready
- [ ] Existing project: `final_project.xpr`

**During Vivado work:**
- [ ] Add Lab 2 IP repository
- [ ] Add MatMul and AXI DMA to block design
- [ ] Connect all AXI interfaces
- [ ] Validate design (no errors)
- [ ] Generate bitstream
- [ ] Export hardware to SDK

**After Vivado:**
- [ ] Note MatMul base address
- [ ] Note AXI DMA base address
- [ ] Provide addresses to me
- [ ] I'll implement the code changes

---

## Need Help?

If you encounter issues:
1. **Connection errors**: Check GRADE4_VIVADO_INSTRUCTIONS.md Step 6
2. **Validation errors**: Run Connection Automation again
3. **Bitstream fails**: Check for timing violations (we can fix)
4. **Missing drivers**: Regenerate BSP (Step 15)

---

## Ready to Start?

**👉 Open `GRADE4_VIVADO_INSTRUCTIONS.md` and begin with Step 1!**

When you complete Step 16 and have the base addresses, come back and tell me the values.

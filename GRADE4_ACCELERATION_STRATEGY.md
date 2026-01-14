# Grade 4 - Acceleration Strategy

## Target Layers for FPGA Offload

Based on Grade 3 analysis, we will accelerate the **most compute-intensive Conv2D layers**:

### Layer 1: CONV_2D (3×3, stride 2, 16 filters)
- **Input**: 28×28×1 (784 elements)
- **Output**: 14×14×16 (3,136 elements)
- **Kernel**: 3×3×1×16 (144 weights)
- **Operation**: ~25K MACs
- **Why accelerate**: Large input size, significant compute

### Layer 3: CONV_2D (3×3, 32 filters)
- **Input**: 14×14×16 (3,136 elements)
- **Output**: 14×14×32 (6,272 elements)
- **Kernel**: 3×3×16×32 (4,608 weights)
- **Operation**: ~92K MACs
- **Why accelerate**: **BIGGEST bottleneck** - most MACs in entire network

**Total acceleration target**: ~117K MACs (~85% of compute)

---

## Im2col Transformation

Conv2D can be converted to matrix multiplication using **im2col** (image to column):

### Example: 3×3 Conv on 4×4 input
```
Input (4×4):          Im2col Matrix (9 rows × 4 cols):
┌─────────┐           ┌─────────────────┐
│ 1 2 3 4 │           │ 1 2 5 6 │ ← patch 1
│ 5 6 7 8 │    =>     │ 2 3 6 7 │ ← patch 2
│ 9 A B C │           │ 5 6 9 A │ ← patch 3
│ D E F G │           │ 6 7 A B │ ← patch 4
└─────────┘           └─────────────────┘

Kernel (3×3 → 9 weights):   Result (1×4):
┌─────┐                     ┌─────────┐
│ w1  │                     │ o1 o2   │
│ w2  │    ×  Im2col  =>    │ o3 o4   │
│ ... │                     └─────────┘
│ w9  │
└─────┘
```

**Matrix dimensions for MatMul accelerator:**
- Layer 1: 9×196 im2col matrix × 9×16 kernel = 196×16 output
- Layer 3: 144×196 im2col matrix × 144×32 kernel = 196×32 output

---

## MatMul IP Configuration

Your Lab 2 accelerator is configured for **16×16 matrices (DIM_LOG=4)**.

### Option 1: Keep 16×16 and tile larger operations
- Break Layer 1/3 into multiple 16×16 chunks
- More PS overhead but no hardware changes needed

### Option 2: Reconfigure IP for larger matrices (if time permits)
- Change `DIM_LOG` to 5 (32×32) or 6 (64×64)
- Requires re-synthesis
- Better for single large operation

**We'll use Option 1** (tiling) to avoid re-synthesis time.

---

## Data Flow

```
┌──────────────────────────────────────────────────────────────┐
│                       ARM Processor (PS)                      │
│                                                               │
│  1. Prepare input data                                        │
│  2. Apply im2col transformation                               │
│  3. Send matrices A, B to FPGA via AXI DMA                    │
│     ↓                                                         │
└─────┼─────────────────────────────────────────────────────────┘
      │ AXI-Stream
      ↓
┌─────┴─────────────────────────────────────────────────────────┐
│                  FPGA Accelerator (PL)                         │
│                                                                │
│  MatMul IP:                                                    │
│  - Receive matrices A, B into BRAMs                            │
│  - Perform C = A × B using MAC units                           │
│  - Send result C back via AXI-Stream                           │
│     ↓                                                          │
└─────┼──────────────────────────────────────────────────────────┘
      │ AXI-Stream  
      ↓
┌─────┴─────────────────────────────────────────────────────────┐
│                       ARM Processor (PS)                      │
│                                                                │
│  4. Receive result matrix from FPGA via AXI DMA                │
│  5. Post-process (add bias, activation, etc.)                  │
│  6. Continue to next layer                                     │
└────────────────────────────────────────────────────────────────┘
```

---

## Expected Performance

### Grade 3 (PS only):
- Total inference: ~10.5 ms
- Conv2D layers: ~9 ms (85%)

### Grade 4 (PS + PL):
**Conservative estimate (2x speedup on Conv2D):**
- Conv2D on FPGA: ~4.5 ms (2x faster)
- Other layers: ~1.5 ms (same)
- **Total: ~6 ms** (1.75x overall speedup)

**Optimistic estimate (4x speedup on Conv2D):**
- Conv2D on FPGA: ~2.2 ms (4x faster)
- Other layers: ~1.5 ms (same)
- **Total: ~3.7 ms** (2.8x overall speedup)

---

## Resource Usage Estimate

Based on Lab 2 MatMul (16×16):
- BRAMs: ~3 (A, B, R matrices)
- DSP48s: ~2-4 (MAC units)
- LUTs: ~2000 (control logic)
- FFs: ~1500 (registers)

**Zynq-7007S (on Minized) has:**
- 50 DSP48 slices
- 66K LUTs
- 106K FFs
- 4.9 Mb BRAM

**Expected usage**: < 10% of resources (plenty of headroom for optimization!)

---

## Next: Code Implementation

Once Vivado hardware is complete, I will implement:

1. **im2col.c/h** - Transformation functions
2. **matmul_accel.c/h** - Driver wrapper for MatMul IP + DMA
3. **genModel.c modifications** - Replace software Conv2D with accelerated version
4. **Timing comparison** - Measure PS-only vs PS+PL performance

**Start with the Vivado instructions in `GRADE4_VIVADO_INSTRUCTIONS.md`!**

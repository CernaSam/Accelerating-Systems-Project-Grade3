# Debug Checklist - No Serial Output

## Issue: Program runs in SDK but nothing appears on serial terminal

### Step 1: Verify SDK is actually running the program

**In SDK Console tab, you should see:**
```
Downloading Program -- /path/to/nn_inference_grade3.elf
Downloaded Program /path/to/nn_inference_grade3.elf
Resetting processor
```

**If you DON'T see this:**
- The program isn't running at all
- Check: Run → Run Configurations → make sure nn_inference_grade3.elf is selected

### Step 2: Check which serial port is UART console

The Minized has TWO USB serial connections:
- `/dev/ttyUSB0` - Usually JTAG/Debug
- `/dev/ttyUSB1` - Usually UART console (but can be swapped!)

**Test both ports:**
```bash
# Close minicom first (Ctrl+A then X)

# Test with simple cat on BOTH ports:
sudo cat /dev/ttyUSB0 &
sudo cat /dev/ttyUSB1 &

# Now click "Run" in SDK again
# Watch for output on either terminal

# Kill when done:
sudo killall cat
```

### Step 3: Verify BSP stdout is configured

**In SDK:**
1. Expand `nn_inference_grade3_bsp`
2. Right-click → **Board Support Package Settings**
3. Check **standalone** tab:
   - `stdin`: should be `ps7_uart_0` or `ps7_uart_1`
   - `stdout`: should be `ps7_uart_0` or `ps7_uart_1`
4. If wrong, change it and click **OK**
5. Right-click BSP → **Regenerate BSP Sources**
6. Rebuild application

### Step 4: Try Simple Test Program

**Replace main.c temporarily with a simple test:**

```bash
# Backup your main.c
cp /home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/main.c \
   /home/deazon/final_project/main.c.backup

# Copy test file
cp /home/deazon/final_project/test_uart_simple.c \
   /home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/main.c

# In SDK: Refresh (F5), Build, Run
```

If the test program works, the issue is in your main NN code.
If the test program ALSO doesn't work, it's a hardware/connection issue.

### Step 5: Check minicom configuration

**In minicom (Ctrl+A then O):**
- Serial Device: `/dev/ttyUSB1` (or 0)
- Baud Rate: `115200 8N1`
- Hardware Flow Control: **NO**
- Software Flow Control: **NO**

**Save as default** (Save setup as dfl)

### Step 6: Permission check

```bash
# Check if you're in dialout group
groups | grep dialout

# If not in group:
sudo usermod -a -G dialout $USER

# Then LOGOUT and login again (or reboot)
```

### Step 7: Alternative - Use screen instead

```bash
# Close minicom completely
# Try screen instead:
screen /dev/ttyUSB1 115200

# Run program in SDK
# To exit screen: Ctrl+A then K then Y
```

### Step 8: Check if program is hanging/crashing

The program might be crashing before printing anything.

**Add this at the VERY start of main():**

```c
int main(void)
{
    init_platform();
    
    // First thing - before ANY other code
    xil_printf("\n\n\rSTART\n\r");
    
    // Rest of your code...
```

If you don't see "START", the program is crashing in `init_platform()` or not running at all.

### Step 9: Verify board is powered and programmed

1. **Check board LED** - Is it on?
2. **In SDK:** Xilinx → Program FPGA
3. Select bitstream: `design_1_wrapper.bit`
4. Click **Program**
5. Should say "FPGA configured successfully"
6. Try running again

### Step 10: Check for compilation warnings

Look at the SDK Console during build:
- Are there any warnings about `printf` or `xil_printf`?
- Any linker warnings about missing libraries?

---

## Common Solutions:

### Solution 1: Wrong serial port
- Try `/dev/ttyUSB0` instead of `/dev/ttyUSB1`

### Solution 2: Not in dialout group
```bash
sudo usermod -a -G dialout $USER
# LOGOUT and login
```

### Solution 3: BSP stdout not configured
- Check BSP settings for stdout = ps7_uart_0
- Regenerate BSP
- Rebuild

### Solution 4: Program not actually running
- Check SDK Console for "Downloaded Program"
- Verify Run Configuration points to .elf file

### Solution 5: Hardware flow control enabled
- Disable in minicom settings

---

## What to check RIGHT NOW:

1. **Look at SDK Console tab** - do you see "Downloaded Program"?
2. **Try both /dev/ttyUSB0 AND /dev/ttyUSB1**
3. **Run the simple test program** (test_uart_simple.c)

Let me know what you see!

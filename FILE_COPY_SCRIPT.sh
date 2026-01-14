#!/bin/bash
# Script to copy SDK source files into Xilinx SDK project
# Run this after creating the SDK application project

echo "================================"
echo "SDK Source Files Copy Script"
echo "================================"
echo ""

# Check if SDK workspace path is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <path_to_sdk_workspace>"
    echo "Example: $0 /home/deazon/final_project/final_project.sdk"
    exit 1
fi

SDK_WORKSPACE="$1"
APP_PROJECT="$SDK_WORKSPACE/nn_inference_grade3"
SRC_DIR="./sdk_src/nn_inference_grade3/src"

# Check if application project exists
if [ ! -d "$APP_PROJECT" ]; then
    echo "ERROR: Application project not found at: $APP_PROJECT"
    echo "Please create the SDK application project first."
    exit 1
fi

# Check if source directory exists
if [ ! -d "$SRC_DIR" ]; then
    echo "ERROR: Source directory not found at: $SRC_DIR"
    exit 1
fi

echo "Copying source files to SDK project..."
echo "Source: $SRC_DIR"
echo "Destination: $APP_PROJECT/src"
echo ""

# Copy all source files
cp -r "$SRC_DIR"/* "$APP_PROJECT/src/"

if [ $? -eq 0 ]; then
    echo "✓ Files copied successfully!"
    echo ""
    echo "Files copied:"
    find "$APP_PROJECT/src" -type f -name "*.c" -o -name "*.h" | head -20
    echo "... and more"
    echo ""
    echo "Next steps:"
    echo "1. In SDK, right-click on 'nn_inference_grade3' project"
    echo "2. Select 'Refresh' (F5)"
    echo "3. Add include paths:"
    echo "   - Right-click project → Properties"
    echo "   - C/C++ Build → Settings"
    echo "   - ARM v7 gcc compiler → Directories"
    echo "   - Add:"
    echo "     \${workspace_loc:}/nn_inference_grade3/src/TinyEngine/include"
    echo "     \${workspace_loc:}/nn_inference_grade3/src/TinyEngine/third_party/CMSIS_NN/Include"
    echo "     \${workspace_loc:}/nn_inference_grade3/src/Include"
    echo "     \${workspace_loc:}/nn_inference_grade3/src/Source"
    echo "     \${workspace_loc:}/nn_inference_grade3/src/test_inputs"
    echo "4. Build the project (Ctrl+B)"
else
    echo "✗ Error copying files!"
    exit 1
fi

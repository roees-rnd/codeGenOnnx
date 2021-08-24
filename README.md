# Deploying a pretrained ONNX model to CMake compiled c code and ROS

Go throught the stages:

1. 00_pytorchToOnnx.md

    Save model from pytorch to onnx
    
    Save unit est vectors

2. 01_Matlab

    Generate c code for deployment

3. 02_CMake

    Generate code \ unit test \ timing test

4. 03_ROS

    Usage with ROS
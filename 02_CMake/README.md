# This directory implements:
1. Unit test between pytorch and generated and compiled code.
2. Timing \ CPU consumption assesment.


## Stages:

1. Clear all old source files and unit test files:

    Run:
    ```bash
    ./clearSrcUT.sh
    ```

2. Import the generated source files and unit test files from 01_Matlab stage:

    Run:
    ```bash
    ./importFiles.sh
    ```

3. Build and run test:

    cd to src/build and run
    ```bash
    >> cmake ..
    >> make
    ```
    run the unit test:
    ```bash
    ./src
    ```
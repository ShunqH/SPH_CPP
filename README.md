# SPH 1D CPP

This is an SPH code for solving the 1D Sod Shock Tube problem.

## Running the Simulation

1. **Compile the code:**
    ```bash
    make
    ```

2. **Navigate to the `bin` directory:**
    ```bash
    cd ./bin
    ```

3. **Run the simulation:**
    ```bash
    sod.sph -i ../input/sod.in
    ```

## Analyzing the Output

You can use the Python script located in `./pyscript` to read the output files.

## Modifying the Setup

To change the setup, edit the file located at:
```bash
./input/sod.in



# RISC-V_Kernel_Project_Build_System
This project implements a basic process kernel to simulate multitasking, allowing the creation and management of multiple processes with unique IDs and names. It includes timer-based scheduling, process initialization, and an idle process as a fallback. The focus is on understanding low-level system programming concepts in a simplified environment.
This Makefile is designed to compile and manage a basic kernel for a RISC-V architecture simulation. It supports building the kernel, running it in QEMU, and testing its functionality. Below are the main features and usage instructions:
Key Targets

    all: Cleans the directory and builds the main kernel binary (kernel.bin).
    clean: Removes all generated files and cleans the working directory.
    run: Runs the compiled kernel in QEMU in headless mode.
    debug: Starts the kernel in QEMU with debugging enabled.
    test: Builds and runs a test binary (test.bin), capturing output in a file.
    badges: Generates badges based on test results using anybadge.

Files and Tools

    Source files: All .S and .c files in the directory are compiled and linked.
    Compiler: RISC-V GCC (riscv64-unknown-elf-gcc).
    Emulator: QEMU (qemu-system-riscv64).
    Linker script: The kernel.lds file is used to configure the memory layout for the kernel.

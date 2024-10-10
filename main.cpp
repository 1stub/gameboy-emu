#include <iostream>

#include "cpu.hpp"

int main(){
    CPU cpu;

    // Test Case 1: Add A and B
    cpu.setRegisters(0x5, 0x0A, 0, 0, 0, 0, 0, 0); // A=5, B=10
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation

    // Check flags after operation
    //cpu.checkFlags(false, false, false, false); // A should not be zero, no carry or half-carry, no subtract

    // Test Case 2: Result is zero
    cpu.setRegisters(0x0A, 0xF6, 0, 0, 0, 0, 0, 0); // A=10, B=246
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation
    //cpu.checkFlags(true, false, false, false); // A should be zero, no carry or half-carry, no subtract

    // Test Case 3: Carry generation
    cpu.setRegisters(0xC8, 0x64, 0, 0, 0, 0, 0, 0); // A=200, B=100
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation
    //cpu.checkFlags(false, false, false, true); // A should be 44, no half-carry, no subtract, carry should be set

    // Test Case 4: Half-carry generation
    cpu.setRegisters(0x0F, 0x01, 0, 0, 0, 0, 0, 0); // A=0x0F, B=0x01
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation
    //cpu.checkFlags(false, false, true, false); // A should be 0x10, half-carry should be set, no carry or subtract
    return 0;
}


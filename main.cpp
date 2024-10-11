#include <iostream>

#include "cpu.hpp"

int main(){
    CPU cpu;

    // Test Case 1: Add A and B
    cpu.setRegisters(0x5, 0xA, 0, 0, 0, 0, 0, 0); // A=5, B=10
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation

    // Test Case 2: Result is zero
    cpu.setRegisters(0x60, 0xA0, 0, 0, 0, 0, 0, 0); 
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation


    // Test Case 3: Carry generation
    cpu.setRegisters(0xC8, 0x64, 0, 0, 0, 0, 0, 0); // A=200, B=100
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation


    // Test Case 4: Half-carry generation
    cpu.setRegisters(0xF, 0x1, 0, 0, 0, 0, 0, 0); // A=0x0F, B=0x01
    cpu.execute(0x80); // Execute ADD A, B
    cpu.printRegisters(); // Print after operation

    return 0;
}


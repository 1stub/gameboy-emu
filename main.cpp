#include <iostream>

#include "cpu.hpp"

int main(){
    CPU cpu;
    cpu.execute(0x80);
    cpu.printRegisters();

    return 0;
}


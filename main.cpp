#include <iostream>

#include "cpu.hpp"

int main(){
    CPU cpu;
    cpu.setRegisters(0x12, 0x23, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0);

    for(uint16_t opcode = 0; opcode <= 0xFF; opcode++){
        std::cout << "opcode: " << std::hex << opcode << std::endl;
        cpu.execute(opcode);
    }

    return 0;
}


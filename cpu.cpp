#include "cpu.hpp"

void CPU::execute(uint8_t opcode){
    a = 0x01;
    b = 0x01;

    switch(opcode){
        case (0x80): //ADD HL, BC
            add(&a, b);
            break;
        default: break;
    };
}

void CPU::printRegisters(){
    std::cout << "A: " << std::hex << (int)a << std::endl;
    std::cout << "B: " << std::hex << (int)b << std::endl;
    std::cout << "C: " << std::hex << (int)c << std::endl;
    std::cout << "D: " << std::hex << (int)d << std::endl;
    std::cout << "E: " << std::hex << (int)e << std::endl;
    std::cout << "F: " << std::hex << (int)f << std::endl;
    std::cout << "H: " << std::hex << (int)h << std::endl;
    std::cout << "L: " << std::hex << (int)l << std::endl;
    std::cout << "AF: " << std::hex << (int)af << std::endl;
    std::cout << "BC: " << std::hex << (int)bc << std::endl;
    std::cout << "DE: " << std::hex << (int)de << std::endl;
    std::cout << "HL: " << std::hex << (int)hl << std::endl;
}

void CPU::add(uint8_t *dst, uint8_t value){
    *dst += value; 
}

#include "cpu.hpp"

void CPU::execute(uint8_t opcode){
    switch(opcode){
        case (0x09): //ADD HL, BC
            add(&bc, hl);
            break;
        default: break;
    };
}

void CPU::add(uint16_t *dst, uint8_t value){
    dst += value; 
}

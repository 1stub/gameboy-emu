#include "cpu.hpp"

CPU::CPU(){
    a=b=c=d=e=f=h=l=0;
    hl=0;
    pc = 0x100;
    sp = 0xFFFE; //this may not be right
}

void CPU::execute(uint8_t opcode){
    switch(opcode){
        case (0x80): //ADD A, B
            add(&a, b);
            break;
        case (0x81): //ADD A, C
            add(&a, c);
            break;
        case (0x82): //ADD A, D
            add(&a, d);
            break;
        case (0x83): //ADD A, E
            add(&a, e);
            break;
        case (0x84): //ADD A, H
            add(&a, h);
            break;
        case (0x85): //ADD A, L
            add(&a, l);
            break;
        case (0x86): //ADD A, *HL
            {
                uint8_t val = read(hl);
                add(&a, val);
                break;
            }
        case (0x87): //ADD A, A
            add(&a, a);
            break;
        default: break;
    };
}

uint8_t CPU::read(uint16_t addr){ //we want value stored at addr, addr is 16 bits our reg 8
    return memory[addr]; 
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
    std::cout << "PC: " << std::hex << (int)pc << std::endl;
    std::cout << "SP: " << std::hex << (int)sp << std::endl;
}

void CPU::setRegisters(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f, uint8_t _h, uint8_t _l) {
    a = _a;
    b = _b;
    c = _c;
    d = _d;
    e = _e;
    h = _h;
    l = _l;
}

void CPU::checkFlags(bool zero, bool subtract, bool halfCarry, bool carry) {
    assert((f & (uint8_t)RegisterFlags::ZERO_FLAG) == (zero ? (uint8_t)RegisterFlags::ZERO_FLAG : 0));
    assert((f & (uint8_t)RegisterFlags::SUBTRACT_FLAG) == (subtract ? (uint8_t)RegisterFlags::SUBTRACT_FLAG : 0));
    assert((f & (uint8_t)RegisterFlags::HALF_CARRY_FLAG) == (halfCarry ? (uint8_t)RegisterFlags::HALF_CARRY_FLAG : 0));
    assert((f & (uint8_t)RegisterFlags::CARRY_FLAG) == (carry ? (uint8_t)RegisterFlags::CARRY_FLAG : 0));
}

void CPU::add(uint8_t *dst, uint8_t value){
    *dst += value;

    if(*dst & 0xFF){ //set zero flag if result is zero
        std::cout << "zero flag" << std::endl;
        f |= (uint8_t)RegisterFlags::ZERO_FLAG;
    }

    f &= (uint8_t)RegisterFlags::SUBTRACT_FLAG; //reset subtract flag
    
    if(((a & 0xF) + (*dst & 0xF)) & 0x10){ //set half carry if needed
        f |= (uint8_t)RegisterFlags::HALF_CARRY_FLAG;
    }else{
        f &= (uint8_t)RegisterFlags::HALF_CARRY_FLAG;
    }

    if(*dst > 0xFF){ //set carry if needed
        f |= (uint8_t)RegisterFlags::CARRY_FLAG;
    }else{
        f &= (uint8_t)RegisterFlags::CARRY_FLAG;
    }
}

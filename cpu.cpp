#include "cpu.hpp"

//need to implement some very basic logic to load opcodes from external source into memory, then simulate using pc to load and modify values

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

        pc++;
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

void CPU::setRegisters(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f, uint8_t _h, uint8_t _l) { //just using to debug
    a = _a;
    b = _b;
    c = _c;
    d = _d;
    e = _e;
    h = _h;
    l = _l;
}

template<RegisterFlags flag>
void CPU::setFlags(uint8_t *dst, uint8_t val){
    uint16_t fullResult = *dst + val;
    uint8_t result = (uint8_t)fullResult;

    if (flag == RegisterFlags::ZERO_FLAG && !(result & 0xFF)){
        f |= (uint8_t)RegisterFlags::ZERO_FLAG;
        std::cout << "F just after zero: " << std::hex << (int)f << std::endl;
    }
    
    if (flag == RegisterFlags::SUBTRACT_FLAG){
        f |= (uint8_t)RegisterFlags::SUBTRACT_FLAG;
        std::cout << "F just after subtract flag: " << std::hex << (int)f << std::endl;
    }
    
    if (flag == RegisterFlags::CARRY_FLAG && fullResult > 0xFF){
        f |= (uint8_t)RegisterFlags::CARRY_FLAG;
        std::cout << "F just after carry: " << std::hex << (int)f << std::endl;
    }
    
    //we set half carry if operation on low 4 order bits exceeds 15 
    if (flag == RegisterFlags::HALF_CARRY_FLAG && ((*dst & 0xF) + (val & 0xF)) & 0x10){
        f |= (uint8_t)RegisterFlags::HALF_CARRY_FLAG;
        std::cout << "F just after half carry: " << std::hex << (int)f << std::endl;
    }
}

void CPU::add(uint8_t *dst, uint8_t value){
    f &= ~f; //reset flags

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value); 
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(dst, value);
    setFlags<RegisterFlags::CARRY_FLAG>(dst, value); 

    *dst += value;
}

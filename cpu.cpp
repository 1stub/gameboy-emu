#include "cpu.hpp"

//need to implement some very basic logic to load opcodes from external source into memory, then simulate using pc to load and modify values
//looks like using blarg tests will be best here

CPU::CPU(){
    a=b=c=d=e=f=h=l=0x0;
    hl=0x0;
    pc = 0x100;
    sp = 0xFFFE; //this may not be right
}

uint16_t CPU::execute(uint8_t opcode){
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
        case (0x88):
            adc(&a, b);
            break;
        case (0x89): //ADD A, C
            adc(&a, c);
            break;
        case (0x8A): //ADD A, D
            adc(&a, d);
            break;
        case (0x8B): //ADD A, E
            adc(&a, e);
            break;
        case (0x8C): //ADD A, H
            adc(&a, h);
            break;
        case (0x8D): //ADD A, L
            adc(&a, l);
            break;
        case (0x8E): //ADD A, *HL
            {
                uint8_t val = read(hl);
                adc(&a, val);
                break;
            }
        case (0x8F): //ADD A, A
            adc(&a, a);
            break;
        case (0x90): 
            sub(&a, b);
            break;
        case (0x91): 
            sub(&a, c);
            break;
        case (0x92): 
            sub(&a, d);
            break;
        case (0x93): 
            sub(&a, e);
            break;
        case (0x94): 
            sub(&a, h);
            break;
        case (0x95): 
            sub(&a, l);
            break;
        case (0x96): 
            {
                uint8_t val = read(hl);
                sub(&a, val);
                break;
            }
        case (0x97): 
            sub(&a, a);
            break;
        case (0x98):
            sbc(&a, b);
            break;
        case (0x99): 
            sbc(&a, c);
            break;
        case (0x9A): 
            sbc(&a, d);
            break;
        case (0x9B): 
            sbc(&a, e);
            break;
        case (0x9C): 
            sbc(&a, h);
            break;
        case (0x9D): 
            sbc(&a, l);
            break;
        case (0x9E): 
            {
                uint8_t val = read(hl);
                sbc(&a, val);
                break;
            }
        case (0x9F): 
            sbc(&a, a);
            break;
        default:  break;
    };
    std::cout << "a: " << std::hex << (int)a << std::endl;
    return pc++;
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
void CPU::setFlags(uint8_t *dst, uint8_t val, uint8_t result, uint16_t fullResult){
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
    if (flag == RegisterFlags::HALF_CARRY_FLAG && (((*dst & 0xF) + (val & 0xF)) & 0x10)){
        f |= (uint8_t)RegisterFlags::HALF_CARRY_FLAG;
        std::cout << "F just after half carry: " << std::hex << (int)f << std::endl;
    }
}

template<RegisterFlags flag>
void CPU::resetFlags(){
    if(flag == RegisterFlags::ZERO_FLAG){
        f &= ~((uint8_t)RegisterFlags::ZERO_FLAG);
    }
    
    if(flag == RegisterFlags::SUBTRACT_FLAG){
        f &= ~((uint8_t)RegisterFlags::SUBTRACT_FLAG);
    }
    
    if(flag == RegisterFlags::CARRY_FLAG){ 
        f &= ~((uint8_t)RegisterFlags::CARRY_FLAG);
    }
    
    if(flag == RegisterFlags::HALF_CARRY_FLAG){
        f &= ~((uint8_t)RegisterFlags::HALF_CARRY_FLAG);
    }
}

void CPU::add(uint8_t *dst, uint8_t value){
    std::cout << "Adding " << (int)value << " to " << (int)(*dst) << std::endl;
    
    uint16_t fullResult = *dst + value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::CARRY_FLAG>(dst, value, result, fullResult); 

    *dst += value;
}

void CPU::adc(uint8_t *dst, uint8_t value){ //if carry is set we add extra 1
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    std::cout << "carry bit set: " << (int)carryBitSet << std::endl; 
    uint16_t fullResult = *dst + value + carryBitSet;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::CARRY_FLAG>(dst, value, result, fullResult);

    *dst += value + carryBitSet;
}

void CPU::sub(uint8_t *dst, uint8_t value){
    std::cout << "subtracting " << (int)value << " from " << (int)(*dst) << std::endl;
    
    uint16_t fullResult = *dst - value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::CARRY_FLAG>(dst, value, result, fullResult); 

    *dst = result;
}

void CPU::sbc(uint8_t *dst, uint8_t value){ //if carry is set we add extra 1
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    std::cout << "carry bit set: " << (int)carryBitSet << std::endl; 
    uint16_t fullResult = *dst - value - carryBitSet;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::CARRY_FLAG>(dst, value, result, fullResult);

    *dst = result;
}

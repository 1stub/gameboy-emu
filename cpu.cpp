#include "cpu.hpp"

//need to implement some very basic logic to load opcodes from external source into memory, then simulate using pc to load and modify values
//looks like using blarg tests will be best here

CPU::CPU(){
    a=b=c=d=e=f=h=l=0x0;
    af = 0x01B0;
    bc = 0x0013;
    de = 0x00D8;
    hl = 0x014D;
    pc = 0x100;
    sp = 0xFFFE; 
}

uint16_t CPU::execute(uint8_t opcode){
    switch(opcode){
        case (0x00): 
            break;
        case (0x01): 
            break;
        case (0x02): 
            break;
        case (0x03): 
            break;
        case (0x04): 
            break;
        case (0x05): 
            break;
        case (0x06): 
            break;
        case (0x07): 
            break;
        case (0x08):
            break;
        case (0x09): 
            break;
        case (0x0A): 
            break;
        case (0x0B): 
            break;
        case (0x0C): 
            break;
        case (0x0D): 
            break;
        case (0x0E): 
            break;
        case (0x0F): 
            break;
        case (0x10): 
            break;
        case (0x11): 
            break;
        case (0x12): 
            break;
        case (0x13): 
            break;
        case (0x14): 
            break;
        case (0x15): 
            break;
        case (0x16): 
            break;
        case (0x17): 
            break;
        case (0x18):
            break;
        case (0x19): 
            break;
        case (0x1A): 
            break;
        case (0x1B): 
            break;
        case (0x1C): 
            break;
        case (0x1D): 
            break;
        case (0x1E): 
            break;
        case (0x1F): 
            break;
        case (0x20): 
            break;
        case (0x21): 
            break;
        case (0x22): 
            break;
        case (0x23): 
            break;
        case (0x24): 
            break;
        case (0x25): 
            break;
        case (0x26): 
            break;
        case (0x27): 
            break;
        case (0x28):
            break;
        case (0x29): 
            break;
        case (0x2A): 
            break;
        case (0x2B): 
            break;
        case (0x2C): 
            break;
        case (0x2D): 
            break;
        case (0x2E): 
            break;
        case (0x2F): 
            break;
        case (0x30): 
            break;
        case (0x31): 
            break;
        case (0x32): 
            break;
        case (0x33): 
            break;
        case (0x34): 
            break;
        case (0x35): 
            break;
        case (0x36): 
            break;
        case (0x37): 
            break;
        case (0x38):
            break;
        case (0x39): 
            break;
        case (0x3A): 
            break;
        case (0x3B): 
            break;
        case (0x3C): 
            break;
        case (0x3D): 
            break;
        case (0x3E): 
            break;
        case (0x3F): 
            break;
        case (0x40): 
            break;
        case (0x41): 
            break;
        case (0x42): 
            break;
        case (0x43): 
            break;
        case (0x44): 
            break;
        case (0x45): 
            break;
        case (0x46): 
            break;
        case (0x47): 
            break;
        case (0x48):
            break;
        case (0x49): 
            break;
        case (0x4A): 
            break;
        case (0x4B): 
            break;
        case (0x4C): 
            break;
        case (0x4D): 
            break;
        case (0x4E): 
            break;
        case (0x4F): 
            break;
        case (0x50): 
            break;
        case (0x51): 
            break;
        case (0x52): 
            break;
        case (0x53): 
            break;
        case (0x54): 
            break;
        case (0x55): 
            break;
        case (0x56): 
            break;
        case (0x57): 
            break;
        case (0x58):
            break;
        case (0x59): 
            break;
        case (0x5A): 
            break;
        case (0x5B): 
            break;
        case (0x5C): 
            break;
        case (0x5D): 
            break;
        case (0x5E): 
            break;
        case (0x5F): 
            break;
        case (0x60): 
            break;
        case (0x61): 
            break;
        case (0x62): 
            break;
        case (0x63): 
            break;
        case (0x64): 
            break;
        case (0x65): 
            break;
        case (0x66): 
            break;
        case (0x67): 
            break;
        case (0x68):
            break;
        case (0x69): 
            break;
        case (0x6A): 
            break;
        case (0x6B): 
            break;
        case (0x6C): 
            break;
        case (0x6D): 
            break;
        case (0x6E): 
            break;
        case (0x6F): 
            break;
        case (0x70): 
            break;
        case (0x71): 
            break;
        case (0x72): 
            break;
        case (0x73): 
            break;
        case (0x74): 
            break;
        case (0x75): 
            break;
        case (0x76): 
            break;
        case (0x77): 
            break;
        case (0x78):
            break;
        case (0x79): 
            break;
        case (0x7A): 
            break;
        case (0x7B): 
            break;
        case (0x7C): 
            break;
        case (0x7D): 
            break;
        case (0x7E): 
            break;
        case (0x7F): 
            break;
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
                uint8_t val = memory->read(hl);
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
                uint8_t val = memory->read(hl);
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
                uint8_t val = memory->read(hl);
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
                uint8_t val = memory->read(hl);
                sbc(&a, val);
                break;
            }
        case (0x9F): 
            sbc(&a, a);
            break;
        case (0xA0):
            i_and(&a, b);
            break;
        case (0xA1): 
            i_and(&a, c);
            break;
        case (0xA2): 
            i_and(&a, d);
            break;
        case (0xA3): 
            i_and(&a, e);
            break;
        case (0xA4): 
            i_and(&a, h);
            break;
        case (0xA5): 
            i_and(&a, l);
            break;
        case (0xA6): 
            {
                uint8_t val = memory->read(hl);
                i_and(&a, val);
                break;
            }
        case (0xA7):
            i_and(&a, a);
            break;
        case (0xA8):
            i_xor(&a, b);
            break;
        case (0xA9): 
            i_xor(&a, c);
            break;
        case (0xAA): 
            i_xor(&a, d);
            break;
        case (0xAB): 
            i_xor(&a, e);
            break;
        case (0xAC): 
            i_xor(&a, h);
            break;
        case (0xAD): 
            i_xor(&a, l);
            break;
        case (0xAE): 
            {
                uint8_t val = memory->read(hl);
                i_xor(&a, val);
                break;
            }
        case (0xAF): 
            i_xor(&a, a);
            break;
        case (0xB0): 
            break;
        case (0xB1): 
            break;
        case (0xB2): 
            break;
        case (0xB3): 
            break;
        case (0xB4): 
            break;
        case (0xB5): 
            break;
        case (0xB6): 
            break;
        case (0xB7): 
            break;
        case (0xB8):
            break;
        case (0xB9): 
            break;
        case (0xBA): 
            break;
        case (0xBB): 
            break;
        case (0xBC): 
            break;
        case (0xBD): 
            break;
        case (0xBE): 
            break;
        case (0xBF): 
            break;
        case (0xC0): 
            break;
        case (0xC1): 
            break;
        case (0xC2): 
            break;
        case (0xC3): 
            break;
        case (0xC4): 
            break;
        case (0xC5): 
            break;
        case (0xC6): 
            break;
        case (0xC7): 
            break;
        case (0xC8):
            break;
        case (0xC9): 
            break;
        case (0xCA): 
            break;
        case (0xCB): 
            break;
        case (0xCC): 
            break;
        case (0xCD): 
            break;
        case (0xCE): 
            break;
        case (0xCF): 
            break;
        case (0xD0): 
            break;
        case (0xD1): 
            break;
        case (0xD2): 
            break;
        case (0xD3): 
            break;
        case (0xD4): 
            break;
        case (0xD5): 
            break;
        case (0xD6): 
            break;
        case (0xD7): 
            break;
        case (0xD8):
            break;
        case (0xD9): 
            break;
        case (0xDA): 
            break;
        case (0xDB): 
            break;
        case (0xDC): 
            break;
        case (0xDD): 
            break;
        case (0xDE): 
            break;
        case (0xDF): 
            break;
        case (0xE0): 
            break;
        case (0xE1): 
            break;
        case (0xE2): 
            break;
        case (0xE3): 
            break;
        case (0xE4): 
            break;
        case (0xE5): 
            break;
        case (0xE6): 
            break;
        case (0xE7): 
            break;
        case (0xE8):
            break;
        case (0xE9): 
            break;
        case (0xEA): 
            break;
        case (0xEB): 
            break;
        case (0xEC): 
            break;
        case (0xED): 
            break;
        case (0xEE): 
            break;
        case (0xEF): 
            break;
        case (0xF0): 
            break;
        case (0xF1): 
            break;
        case (0xF2): 
            break;
        case (0xF3): 
            break;
        case (0xF4): 
            break;
        case (0xF5): 
            break;
        case (0xF6): 
            break;
        case (0xF7): 
            break;
        case (0xF8):
            break;
        case (0xF9): 
            break;
        case (0xFA): 
            break;
        case (0xFB): 
            break;
        case (0xFC): 
            break;
        case (0xFD): 
            break;
        case (0xFE): 
            break;
        case (0xFF): 
            break;
        default:  break;
    };
    std::cout << "a: " << std::hex << (int)a << std::endl;
    return pc++;
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
        f |= ((uint8_t)RegisterFlags::ZERO_FLAG);
    }
    
    if(flag == RegisterFlags::SUBTRACT_FLAG){
        f |= ((uint8_t)RegisterFlags::SUBTRACT_FLAG);
    }
    
    if(flag == RegisterFlags::CARRY_FLAG){ 
        f |= ((uint8_t)RegisterFlags::CARRY_FLAG);
    }
    
    if(flag == RegisterFlags::HALF_CARRY_FLAG){
        f |= ((uint8_t)RegisterFlags::HALF_CARRY_FLAG);
    }
}

template<RegisterFlags flag>
void CPU::forceSetFlags(){
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

void CPU::i_and(uint8_t *dst, uint8_t value){ //if carry is set we add extra 1
    std::cout << "bitwise AND with: " << std::hex << (int)*dst << " && "<< (int)value << std::endl; 
    uint16_t fullResult = *dst & value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    forceSetFlags<RegisterFlags::HALF_CARRY_FLAG>();
    resetFlags<RegisterFlags::CARRY_FLAG>();

    *dst = result;
}

void CPU::i_xor(uint8_t *dst, uint8_t value){ //if carry is set we add extra 1
    std::cout << "bitwise XOR with: " << std::hex << (int)*dst << " && "<< (int)value << std::endl; 
    uint16_t fullResult = *dst ^ value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    forceSetFlags<RegisterFlags::HALF_CARRY_FLAG>();
    resetFlags<RegisterFlags::CARRY_FLAG>();

    *dst = result;
}

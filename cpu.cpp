#include "cpu.hpp"

//need to implement some very basic logic to load opcodes from external source into memory, then simulate using pc to load and modify values
//looks like using blarg tests will be best here

CPU::CPU(Memory* mem){
    memory = mem;
    a=b=c=d=e=f=h=l=0x0;
    af = 0x01B0;
    bc = 0x0013;
    de = 0x00D8;
    hl = 0x014D;
    pc = 0x100;
    sp = 0xFFFE; 
}

void CPU::run(){ 
    uint8_t opcode = memory->read(pc);
    std::cout << std::hex << (int)opcode << std::endl;
    execute(opcode);
}

void CPU::execute(uint8_t opcode){
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
        case (0x80): 
            //need to update pc and cycles every instruction call, format in docs is pc cycles         
            //i.e. for 0x80 we see 1 4
            add(&a, b);
            update(1, 4); //update pc+=1, cycles+=4; 
            break;
        case (0x81): 
            add(&a, c);
            update(1, 4);
            break;
        case (0x82): 
            add(&a, d);
            update(1, 4);
            break;
        case (0x83): 
            add(&a, e);
            update(1, 4);
            break;
        case (0x84): 
            add(&a, h);
            update(1, 4);
            break;
        case (0x85): 
            add(&a, l);
            update(1, 4);
            break;
        case (0x86): 
            {
                uint8_t val = memory->read(hl);
                add(&a, val);
                update(1, 8);
                break;
            }
        case (0x87): 
            add(&a, a);
            update(1, 4);
            break;
        case (0x88):
            adc(&a, b);
            break;
        case (0x89): 
            adc(&a, c);
            break;
        case (0x8A): 
            adc(&a, d);
            break;
        case (0x8B): 
            adc(&a, e);
            break;
        case (0x8C): 
            adc(&a, h);
            break;
        case (0x8D): 
            adc(&a, l);
            break;
        case (0x8E): 
            {
                uint8_t val = memory->read(hl);
                adc(&a, val);
                break;
            }
        case (0x8F): 
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
            i_or(&a, b);
            break;
        case (0xB1): 
            i_or(&a, c);
            break;
        case (0xB2):
            i_or(&a, d);
            break;
        case (0xB3):
            i_or(&a, e);
            break;
        case (0xB4):
            i_or(&a, h);
            break;
        case (0xB5):
            i_or(&a, l);
            break;
        case (0xB6):
            {
                uint8_t val = memory->read(hl);
                i_or(&a, val);
                break;
            }
        case (0xB7):
            i_or(&a, a);
            break;
        case (0xB8):
            cp(&a, b);
            break;
        case (0xB9): 
            cp(&a, c);
            break;
        case (0xBA):
            cp(&a, d);
            break;
        case (0xBB): 
            cp(&a, e);
            break;
        case (0xBC): 
            cp(&a, h);
            break;
        case (0xBD):
            cp(&a, l);
            break;
        case (0xBE):
            {
                uint8_t val = memory->read(hl);
                cp(&a, val);
                break;
            }
        case (0xBF):
            cp(&a, a);
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
}

void CPU::update(uint8_t pc_inc, uint8_t cycles_inc){
    pc+=pc_inc;
    cycles+=cycles_inc;
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

void CPU::setRegisters(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f, uint8_t _h, uint8_t _l, uint16_t _pc, uint16_t _sp) { //just using to debug
    a = _a;
    b = _b;
    c = _c;
    d = _d;
    e = _e;
    f = _f;
    h = _h;
    l = _l;
    pc = _pc;
}

std::vector<uint8_t> CPU::getRegisters() const {
    std::vector<uint8_t> regs;

    regs.push_back(a);
    regs.push_back(b);
    regs.push_back(c);
    regs.push_back(d);
    regs.push_back(e);
    regs.push_back(f);
    regs.push_back(h);
    regs.push_back(l);

    return regs;
}

bool CPU::compareRegisters(const std::vector<uint8_t>& expected) {
    bool success = true;

    if ((int)a != expected[0]) {
        std::cout << "Mismatch in register A. Expected: " << std::hex << (int)expected[0] 
                  << ", Got: " << (int)a << std::endl;
        success = false;
    }
    if ((int)b != expected[1]) {
        std::cout << "Mismatch in register B. Expected: " << std::hex << (int)expected[1]
                  << ", Got: " << (int)b << std::endl;
        success = false;
    }
    if ((int)c != expected[2]) {
        std::cout << "Mismatch in register C. Expected: " << std::hex << (int)expected[2]
                  << ", Got: " << (int)c << std::endl;
        success = false;
    }
    if ((int)d != expected[3]) {
        std::cout << "Mismatch in register D. Expected: " << std::hex << (int)expected[3]
                  << ", Got: " << (int)d << std::endl;
        success = false;
    }
    if ((int)e != expected[4]) {
        std::cout << "Mismatch in register E. Expected: " << std::hex << (int)expected[4]
                  << ", Got: " << (int)e << std::endl;
        success = false;
    }
    if ((int)f != expected[5]) {
        std::cout << "Mismatch in register F. Expected: " << std::hex << (int)expected[5]
                  << ", Got: " << (int)f << std::endl;
        success = false;
    }
    if ((int)h != expected[6]) {
        std::cout << "Mismatch in register H. Expected: " << std::hex << (int)expected[6]
                  << ", Got: " << (int)h << std::endl;
        success = false;
    }
    if ((int)l != expected[7]) {
        std::cout << "Mismatch in register L. Expected: " << std::hex << (int)expected[7] 
                  << ", Got: " << (int)l << std::endl;
        success = false;
    }

    return success;
}

template<RegisterFlags flag>
void CPU::setFlags(const bool setOrReset){
    if (flag == RegisterFlags::ZERO_FLAG){
        setOrReset ? f |= (uint8_t)RegisterFlags::ZERO_FLAG : f &= ~(uint8_t)RegisterFlags::ZERO_FLAG;
    }
    
    if (flag == RegisterFlags::SUBTRACT_FLAG){ 
        setOrReset ? f |= (uint8_t)RegisterFlags::SUBTRACT_FLAG : f &= ~(uint8_t)RegisterFlags::SUBTRACT_FLAG;
    }
    
    if (flag == RegisterFlags::CARRY_FLAG){ 
        setOrReset ? f |= (uint8_t)RegisterFlags::CARRY_FLAG : f &= ~(uint8_t)RegisterFlags::CARRY_FLAG;
    }
    
    //we set half carry if operation on low 4 order bits exceeds 15 
    if (flag == RegisterFlags::HALF_CARRY_FLAG ){ 
        setOrReset ? f |= (uint8_t)RegisterFlags::HALF_CARRY_FLAG : f &= ~(uint8_t)RegisterFlags::HALF_CARRY_FLAG;
    }
}


//this works for 0x80. always need to reset flags if it doesnt need to be set to 1
void CPU::add(uint8_t *dst, uint8_t value){
    std::cout << "Adding " << (int)value << " to " << (int)(*dst) << std::endl;
    
    uint16_t fullResult = *dst + value;
    
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) + (value & 0x0F)) > 0x0F);
    *dst = fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::adc(uint8_t *dst, uint8_t value) {
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    std::cout << "carry bit set: " << (int)carryBitSet << std::endl; 

    uint16_t fullResult = *dst + value + carryBitSet;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) + (value & 0x0F) + carryBitSet) > 0x0F);
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);

    *dst = (uint8_t)fullResult;
}

void CPU::sub(uint8_t *dst, uint8_t value) {
    std::cout << "Subtracting " << (int)value << " from " << (int)(*dst) << std::endl;

    uint16_t fullResult = *dst - value;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) < (value & 0x0F)));
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);

    *dst = (uint8_t)fullResult;
}

void CPU::sbc(uint8_t *dst, uint8_t value) {
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    std::cout << "carry bit set: " << (int)carryBitSet << std::endl;

    uint16_t fullResult = *dst - value - carryBitSet;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) < ((value & 0x0F) + carryBitSet)));
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);

    *dst = (uint8_t)fullResult;
}

void CPU::i_and(uint8_t *dst, uint8_t value) {
    std::cout << "Bitwise AND with: " << std::hex << (int)*dst << " && " << (int)value << std::endl; 
    uint16_t fullResult = *dst & value;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(true);
    setFlags<RegisterFlags::CARRY_FLAG>(false);

    *dst = (uint8_t)fullResult;
}

void CPU::i_xor(uint8_t *dst, uint8_t value) {
    std::cout << "Bitwise XOR with: " << std::hex << (int)*dst << " && " << (int)value << std::endl; 
    uint16_t fullResult = *dst ^ value;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(false);

    *dst = (uint8_t)fullResult;
}

void CPU::i_or(uint8_t *dst, uint8_t value) {
    std::cout << "Bitwise OR with: " << std::hex << (int)*dst << " && " << (int)value << std::endl; 
    uint16_t fullResult = *dst | value;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(false);

    *dst = (uint8_t)fullResult;
}

void CPU::cp(uint8_t *dst, uint8_t value) {
    std::cout << "CP with: " << std::hex << (int)*dst << " && " << (int)value << std::endl; 
    uint16_t fullResult = *dst - value;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) < (value & 0x0F)));
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);
}

/*void CPU::adc(uint8_t *dst, uint8_t value){ //if carry is set we add extra 1
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

void CPU::i_and(uint8_t *dst, uint8_t value){ 
    std::cout << "bitwise AND with: " << std::hex << (int)*dst << " && "<< (int)value << std::endl; 
    uint16_t fullResult = *dst & value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    forceSetFlags<RegisterFlags::HALF_CARRY_FLAG>();
    resetFlags<RegisterFlags::CARRY_FLAG>();

    *dst = result;
}

void CPU::i_xor(uint8_t *dst, uint8_t value){ 
    std::cout << "bitwise XOR with: " << std::hex << (int)*dst << " && "<< (int)value << std::endl; 
    uint16_t fullResult = *dst ^ value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    forceSetFlags<RegisterFlags::HALF_CARRY_FLAG>();
    resetFlags<RegisterFlags::CARRY_FLAG>();

    *dst = result;
}

void CPU::i_or(uint8_t *dst, uint8_t value){ 
    std::cout << "bitwise XOR with: " << std::hex << (int)*dst << " && "<< (int)value << std::endl; 
    uint16_t fullResult = *dst | value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    resetFlags<RegisterFlags::SUBTRACT_FLAG>();
    resetFlags<RegisterFlags::HALF_CARRY_FLAG>();
    resetFlags<RegisterFlags::CARRY_FLAG>();

    *dst = result;
}

//dont update dst, just check dst-value to see what flags would get set
void CPU::cp(uint8_t *dst, uint8_t value){  
    std::cout << "CP with: " << std::hex << (int)*dst << " && "<< (int)value << std::endl; 
    uint16_t fullResult = *dst - value;
    uint8_t result = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(dst, value, result, fullResult);
    forceSetFlags<RegisterFlags::SUBTRACT_FLAG>();
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(dst, value, result, fullResult);
    setFlags<RegisterFlags::CARRY_FLAG>(dst, value, result, fullResult);
}*/

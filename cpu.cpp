#include "cpu.hpp"

//need to implement some very basic logic to load opcodes from external source into memory, then simulate using pc to load and modify values
//looks like using blarg tests will be best here

CPU::CPU(Memory* mem){
    memory = mem;
    cycles=0;
    a=b=c=d=e=f=h=l=0x0;
    af = 0x01B0;
    bc = 0x0013;
    de = 0x00D8;
    hl = 0x014D;
    pc = 0x100;
    sp = 0xFFFE; 
    ime = false;
}

void CPU::cycle(){
    if (ticks < static_cast<int>(cycles)) {
        ticks++;
        return;
    }
    ticks = 0;
    uint8_t opcode = memory->read(pc);
    execute(opcode); 
}

void CPU::update(uint8_t pc_inc, uint8_t cycles_inc){
    pc += pc_inc;
    cycles = cycles_inc;
}

void CPU::execute(uint8_t opcode){
    switch(opcode){
        case (0x00):
            update(1,4);
            break;
        case (0x01):
            {
                uint8_t c_upd = memory->read(pc+1);
                uint8_t b_upd = memory->read(pc+2);
                ld(&b,b_upd);
                ld(&c, c_upd);
                update(3,12);
            }
            break;
        case (0x02):
            ld(&bc, a);
            update(1,8);
            break;
        case (0x03):
            bc++;
            update(1,8);
            break;
        case (0x04):
            inc(&b);
            update(1,4);
            break;
        case (0x05):
            dec(&b);
            update(1,4);
            break;
        case (0x06):
            ld(&b, memory->read(pc+1));
            update(2,8);
            break;
        case (0x07):
            rlca(&a);
            update(1,4);
            break;
        case (0x08):
            {
                uint16_t addr = memory->read16(pc+1); 
                uint8_t low = sp & 0x00FF;
                uint8_t high = sp >> 8;
                ld(&addr, low); addr++; 
                ld(&addr, high); 
                update(3,20);
                break;
            }
        case (0x09):
            add(&hl, bc);
            update(1,8);
            break;
        case (0x0A):
            {
                ld(&a, memory->read(bc));
                update(1,8);
                break;
            }
        case (0x0B):
            bc--;
            update(1,8);
            break;
        case (0x0C):
            inc(&c);
            update(1,4);
            break;
        case (0x0D): 
            dec(&c);
            update(1,4);
            break;
        case (0x0E):
            ld(&c, memory->read(pc+1));
            update(2,8);
            break;
        case (0x0F):
            rrca(&a);
            update(1,4);
            break;
        case (0x10): //ignoring STOP for now
            update(2,4);
            break;
        case (0x11):
            {
                uint8_t e_upd = memory->read(pc+1);
                uint8_t d_upd = memory->read(pc+2);
                ld(&e,e_upd);
                ld(&d, d_upd);
                update(3,12);
            }
            break;
        case (0x12):
            ld(&de, a);
            update(1,8);
            break;
        case (0x13): 
            de++;
            update(1,8);
            break;
        case (0x14): 
            inc(&d);
            update(1,4);
            break;
        case (0x15):
            dec(&d);
            update(1,4);
            break;
        case (0x16):
            ld(&d, memory->read(pc+1));
            update(2,8);
            break;
        case (0x17): 
            rla(&a);
            update(1,4);
            break;
        case (0x18):
            jr<RegisterFlags::NO_FLAG>(false, true);
            break;
        case (0x19):
            add(&hl, de);
            update(1,8);
            break;
        case (0x1A):
            {
                ld(&a, memory->read(de));
                update(1,8);
                break;
            }
            break;
        case (0x1B):
            de--;
            update(1,8);
            break;
        case (0x1C):
            inc(&e);
            update(1,4);
            break;
        case (0x1D): 
            dec(&e);
            update(1,4);
            break;
        case (0x1E):
            ld(&e, memory->read(pc+1));
            update(2,8);
            break;
        case (0x1F):
            rra(&a);
            update(1,4);
            break;
        case (0x20):
            jr<RegisterFlags::ZERO_FLAG>(false, false);
            break;
        case (0x21):
            {
                uint8_t l_upd = memory->read(pc+1);
                uint8_t h_upd = memory->read(pc+2);
                ld(&l,l_upd);
                ld(&h, h_upd);
                update(3,12);
            }
            break;
        case (0x22):
            ld(&hl, a);
            hl++;
            update(1,8);
            break;
        case (0x23): 
            hl++;
            update(1,8);
            break;
        case (0x24):
            inc(&h);
            update(1,4);
            break;
        case (0x25): 
            dec(&h);
            update(1,4);
            break;
        case (0x26):
            ld(&h, memory->read(pc+1));
            update(2,8);
            break;
        case (0x27):
            daa(&a);
            update(1,4);
            break;
        case (0x28):
            jr<RegisterFlags::ZERO_FLAG>(true, false);
            break;
        case (0x29):
            add(&hl, hl);
            update(1,8);
            break;
        case (0x2A):
            {
                ld(&a, memory->read(hl));
                hl++;
                update(1,8);
                break;
            }
            break;
        case (0x2B):
            hl--;
            update(1,8);
            break;
        case (0x2C): 
            inc(&l);
            update(1,4);
            break;
        case (0x2D): 
            dec(&l);
            update(1,4);
            break;
        case (0x2E):
            ld(&l, memory->read(pc+1));
            update(2,8);
            break;
        case (0x2F):
            cpl();
            update(1,4);
            break;
        case (0x30):
            jr<RegisterFlags::CARRY_FLAG>(false, false);
            break;
        case (0x31):
            {
                uint8_t first_val = memory->read(pc+1);
                uint8_t second_val = memory->read(pc+2);
                uint16_t concat = 0;
                concat |= first_val;
                concat |= (second_val << 8);
                ld(&sp, concat);
                update(3,12);
            }
            break;
        case (0x32):
            ld(&hl, a);
            hl--;
            update(1,8);
            break;
        case (0x33): 
            sp++;
            update(1,8);
            break;
        case (0x34):
            inc(&hl);
            update(1,12);
            break;
        case (0x35): 
            dec(&hl);
            update(1,12);
            break;
        case (0x36):
            ld(&hl, memory->read(pc+1));
            update(2,12);
            break;
        case (0x37): 
            scf();
            update(1,4);
            break;
        case (0x38):
            jr<RegisterFlags::CARRY_FLAG>(true, false);
            break;
        case (0x39):
            add(&hl, sp);
            update(1,8);
            break;
        case (0x3A): 
            {
                ld(&a, memory->read(hl));
                hl--;
                update(1,8);
                break;
            }
            break;
        case (0x3B):
            sp--;
            update(1,8);
            break;
        case (0x3C):
            inc(&a);
            update(1,4);
            break;
        case (0x3D):
            dec(&a);
            update(1,4);
            break;
        case (0x3E):
            ld(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0x3F): 
            ccf();
            update(1,4);
            break;
        case 0x40: 
            ld(&b, b);
            update(1, 4);
            break;
        case 0x41: 
            ld(&b, c);
            update(1, 4);
            break;
        case 0x42: 
            ld(&b, d);
            update(1, 4);
            break;
        case 0x43: 
            ld(&b, e);
            update(1, 4);
            break;
        case 0x44: 
            ld(&b, h);
            update(1, 4);
            break;
        case 0x45: 
            ld(&b, l);
            update(1, 4);
            break;
        case 0x46: {
            uint8_t val = memory->read(hl);
            ld(&b, val);
            update(1, 8);
            break;
        }
        case 0x47: 
            ld(&b, a);
            update(1, 4);
            break;

        case 0x48: 
            ld(&c, b);
            update(1, 4);
            break;
        case 0x49: 
            ld(&c, c);
            update(1, 4);
            break;
        case 0x4A: 
            ld(&c, d);
            update(1, 4);
            break;
        case 0x4B: 
            ld(&c, e);
            update(1, 4);
            break;
        case 0x4C: 
            ld(&c, h);
            update(1, 4);
            break;
        case 0x4D: 
            ld(&c, l);
            update(1, 4);
            break;
        case 0x4E: {
            uint8_t val = memory->read(hl);
            ld(&c, val);
            update(1, 8);
            break;
        }
        case 0x4F: 
            ld(&c, a);
            update(1, 4);
            break;
        case 0x50: 
            ld(&d, b);
            update(1, 4);
            break;
        case 0x51: 
            ld(&d, c);
            update(1, 4);
            break;
        case 0x52: 
            ld(&d, d);
            update(1, 4);
            break;
        case 0x53: 
            ld(&d, e);
            update(1, 4);
            break;
        case 0x54: 
            ld(&d, h);
            update(1, 4);
            break;
        case 0x55: 
            ld(&d, l);
            update(1, 4);
            break;
        case 0x56: {
            uint8_t val = memory->read(hl);
            ld(&d, val);
            update(1, 8);
            break;
        }
        case 0x57: 
            ld(&d, a);
            update(1, 4);
            break;

        case 0x58: 
            ld(&e, b);
            update(1, 4);
            break;
        case 0x59: 
            ld(&e, c);
            update(1, 4);
            break;
        case 0x5A: 
            ld(&e, d);
            update(1, 4);
            break;
        case 0x5B: 
            ld(&e, e);
            update(1, 4);
            break;
        case 0x5C: 
            ld(&e, h);
            update(1, 4);
            break;
        case 0x5D: 
            ld(&e, l);
            update(1, 4);
            break;
        case 0x5E: {
            uint8_t val = memory->read(hl);
            ld(&e, val);
            update(1, 8);
            break;
        }
        case 0x5F: 
            ld(&e, a);
            update(1, 4);
            break;
        case 0x60: 
            ld(&h, b);
            update(1, 4);
            break;
        case 0x61: 
            ld(&h, c);
            update(1, 4);
            break;
        case 0x62: 
            ld(&h, d);
            update(1, 4);
            break;
        case 0x63: 
            ld(&h, e);
            update(1, 4);
            break;
        case 0x64: 
            ld(&h, h);
            update(1, 4);
            break;
        case 0x65: 
            ld(&h, l);
            update(1, 4);
            break;
        case 0x66: {
            uint8_t val = memory->read(hl);
            ld(&h, val);
            update(1, 8);
            break;
        }
        case 0x67: 
            ld(&h, a);
            update(1, 4);
            break;

        case 0x68: 
            ld(&l, b);
            update(1, 4);
            break;
        case 0x69: 
            ld(&l, c);
            update(1, 4);
            break;
        case 0x6A: 
            ld(&l, d);
            update(1, 4);
            break;
        case 0x6B: 
            ld(&l, e);
            update(1, 4);
            break;
        case 0x6C: 
            ld(&l, h);
            update(1, 4);
            break;
        case 0x6D: 
            ld(&l, l);
            update(1, 4);
            break;
        case 0x6E: {
            uint8_t val = memory->read(hl);
            ld(&l, val);
            update(1, 8);
            break;
        }
        case 0x6F: 
            ld(&l, a);
            update(1, 4);
            break;
        case 0x70: {
            uint8_t val = b;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }
        case 0x71: {
            uint8_t val = c;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }
        case 0x72: {
            uint8_t val = d;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }
        case 0x73: {
            uint8_t val = e;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }
        case 0x74: {
            uint8_t val = h;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }
        case 0x75: {
            uint8_t val = l;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }
        case 0x76: 
            // HALT implementation will go here in the future
            
            update(-1, 0);
            break;
        case 0x77: {
            uint8_t val = a;
            memory->m_Rom[hl]=val;
            update(1, 8);
            break;
        }

        case 0x78: 
            ld(&a, b);
            update(1, 4);
            break;
        case 0x79: 
            ld(&a, c);
            update(1, 4);
            break;
        case 0x7A: 
            ld(&a, d);
            update(1, 4);
            break;
        case 0x7B: 
            ld(&a, e);
            update(1, 4);
            break;
        case 0x7C: 
            ld(&a, h);
            update(1, 4);
            break;
        case 0x7D: 
            ld(&a, l);
            update(1, 4);
            break;
        case 0x7E: {
            uint8_t val = memory->read(hl);
            ld(&a, val);
            update(1, 8);
            break;
        }
        case 0x7F: 
            ld(&a, a);
            update(1, 4);
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
            update(1, 4);
            break;
        case (0x89): 
            adc(&a, c);
            update(1, 4);
            break;
        case (0x8A): 
            adc(&a, d);
            update(1, 4);
            break;
        case (0x8B): 
            adc(&a, e);
            update(1, 4);
            break;
        case (0x8C): 
            adc(&a, h);
            update(1, 4);
            break;
        case (0x8D): 
            adc(&a, l);
            update(1, 4);
            break;
        case (0x8E): 
            {
                uint8_t val = memory->read(hl);
                adc(&a, val);
                update(1, 8);
                break;
            }
        case (0x8F): 
            adc(&a, a);
            update(1, 4);
            break;
        case (0x90): 
            sub(&a, b);
            update(1, 4);
            break;
        case (0x91): 
            sub(&a, c);
            update(1, 4);
            break;
        case (0x92): 
            sub(&a, d);
            update(1, 4);
            break;
        case (0x93): 
            sub(&a, e);
            update(1, 4);
            break;
        case (0x94): 
            sub(&a, h);
            update(1, 4);
            break;
        case (0x95): 
            sub(&a, l);
            update(1, 4);
            break;
        case (0x96): 
            {
                uint8_t val = memory->read(hl);
                update(1, 8);
                sub(&a, val);
                break;
            }
        case (0x97): 
            sub(&a, a);
            update(1, 4);
            break;
        case (0x98):
            sbc(&a, b);
            update(1, 4);
            break;
        case (0x99): 
            sbc(&a, c);
            update(1, 4);
            break;
        case (0x9A): 
            sbc(&a, d);
            update(1, 4);
            break;
        case (0x9B): 
            sbc(&a, e);
            update(1, 4);
            break;
        case (0x9C): 
            sbc(&a, h);
            update(1, 4);
            break;
        case (0x9D): 
            sbc(&a, l); 
            update(1, 4);
            break;
        case (0x9E): 
            {
                uint8_t val = memory->read(hl);
                update(1, 8);
                sbc(&a, val);
                break;
            }
        case (0x9F): 
            sbc(&a, a);
            update(1, 4);
            break;
        case (0xA0):
            i_and(&a, b);
            update(1, 4);
            break;
        case (0xA1): 
            i_and(&a, c);
            update(1, 4);
            break;
        case (0xA2): 
            i_and(&a, d);
            update(1, 4);
            break;
        case (0xA3): 
            i_and(&a, e);
            update(1, 4);
            break;
        case (0xA4): 
            i_and(&a, h);
            update(1, 4);
            break;
        case (0xA5): 
            i_and(&a, l);
            update(1, 4);
            break;
        case (0xA6): 
            {
                uint8_t val = memory->read(hl);
                update(1, 8);
                i_and(&a, val);
                break;
            }
        case (0xA7):
            i_and(&a, a);
            update(1, 4);
            break;
        case (0xA8):
            i_xor(&a, b);
            update(1, 4);
            break;
        case (0xA9): 
            i_xor(&a, c);
            update(1, 4);
            break;
        case (0xAA): 
            i_xor(&a, d);
            update(1, 4);
            break;
        case (0xAB): 
            i_xor(&a, e);
            update(1, 4);
            break;
        case (0xAC): 
            i_xor(&a, h);
            update(1, 4);
            break;
        case (0xAD): 
            i_xor(&a, l);
            update(1, 4);
            break;
        case (0xAE): 
            {
                uint8_t val = memory->read(hl);
                update(1, 8);
                i_xor(&a, val);
                break;
            }
        case (0xAF): 
            i_xor(&a, a);
            update(1, 4);
            break;
        case (0xB0):
            i_or(&a, b);
            update(1, 4);
            break;
        case (0xB1): 
            i_or(&a, c);
            update(1, 4);
            break;
        case (0xB2):
            i_or(&a, d);
            update(1, 4);
            break;
        case (0xB3):
            i_or(&a, e);
            update(1, 4);
            break;
        case (0xB4):
            i_or(&a, h);
            update(1, 4);
            break;
        case (0xB5):
            i_or(&a, l);
            update(1, 4);
            break;
        case (0xB6):
            {
                uint8_t val = memory->read(hl);
                i_or(&a, val);
                update(1, 8);
                break;
            }
        case (0xB7):
            i_or(&a, a);
            update(1, 4);
            break;
        case (0xB8):
            cp(&a, b);
            update(1, 4);
            break;
        case (0xB9): 
            cp(&a, c);
            update(1, 4);
            break;
        case (0xBA):
            cp(&a, d);
            update(1, 4);
            break;
        case (0xBB): 
            cp(&a, e);
            update(1, 4);
            break;
        case (0xBC): 
            cp(&a, h);
            update(1, 4);
            break;
        case (0xBD):
            cp(&a, l);
            update(1, 4);
            break;
        case (0xBE):
            {
                uint8_t val = memory->read(hl);
                cp(&a, val);
                update(1, 8);
                break;
            }
        case (0xBF):
            cp(&a, a);
            update(1, 4);
            break;
        case (0xC0):
            retc<RegisterFlags::ZERO_FLAG>(false, false);
            break;
        case (0xC1):
            pop(&bc);
            break;
        case (0xC2):
            jr16<RegisterFlags::ZERO_FLAG>(false, false);
            break;
        case (0xC3):
            jr16<RegisterFlags::NO_FLAG>(true, true);
            break;
        case (0xC4):
            call<RegisterFlags::ZERO_FLAG>(false, false);
            break;
        case (0xC5):
            push(&bc);
            break;
        case (0xC6):
            add(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xC7): 
            rst(0x00); 
            break;
        case (0xC8):
            retc<RegisterFlags::ZERO_FLAG>(true, false);
            break;
        case (0xC9):
            ret();
            update(0,16); //pc updating handeled in ret
            break;
        case (0xCA):
            jr16<RegisterFlags::ZERO_FLAG>(true, false);
            break;
        case (0xCB):
            //we run our extended execution on the next value in memory (it would be an opcode)
            extended_execute(memory->read(pc+1));
            update(0,4);
            break;
        case (0xCC):
            call<RegisterFlags::ZERO_FLAG>(true, false);
            break;
        case (0xCD):
            call<RegisterFlags::NO_FLAG>(false, true);
            break;
        case (0xCE):
            adc(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xCF): 
            rst(0x08);
            break;
        case (0xD0):
            retc<RegisterFlags::CARRY_FLAG>(false, false);
            break;
        case (0xD1):
            pop(&de);
            break;
        case (0xD2):
            jr16<RegisterFlags::CARRY_FLAG>(false, false);
            break;
        case (0xD3):
            break;
        case (0xD4):
            call<RegisterFlags::CARRY_FLAG>(false, false);
            break;
        case (0xD5):
            push(&de);
            break;
        case (0xD6):
            sub(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xD7):
            rst(0x10);
            break;
        case (0xD8):
            retc<RegisterFlags::CARRY_FLAG>(true, false);
            break;
        case (0xD9):
            //why the heck did i have ime here?
            //ime = true;
            ret();
            update(0,16); //pc updating handeled in ret
            break;
        case (0xDA):
            jr16<RegisterFlags::CARRY_FLAG>(true, false);
            break;
        case (0xDB): 
            break;
        case (0xDC):
            call<RegisterFlags::CARRY_FLAG>(true, false);
            break;
        case (0xDD): 
            break;
        case (0xDE):
            sbc(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xDF): 
            rst(0x18);
            break;
        case (0xE0):
            memory->m_Rom[0xFF00+memory->read(pc+1)] = a;
            update(2,12);
            break;
        case (0xE1):
            pop(&hl);
            break;
        case (0xE2): 
            memory->m_Rom[0xFF00 + c] = a;
            update(1,8);
            break;
        case (0xE3): 
            break;
        case (0xE4): 
            break;
        case (0xE5): 
            push(&hl);
            break;
        case (0xE6): 
            i_and(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xE7): 
            rst(0x20);
            break;
        case (0xE8):{ //its pretty stupid to handle the logic here - didnt want to make a new function
                int8_t val = memory->read(pc+1);
                setFlags<RegisterFlags::ZERO_FLAG>(false);
                setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
                setFlags<RegisterFlags::CARRY_FLAG>(((sp&0xFF) + (val&0xFF)) > 0xFF);
                setFlags<RegisterFlags::HALF_CARRY_FLAG>(((sp & 0x0F) + (val & 0x0F)) > 0x0F);

                sp += val;    
                update(2,16);
            }
            break;
        case (0xE9): //TODO NEXT! 
            pc=hl;
            update(0,4);
            break;
        case (0xEA):
            {
                uint8_t low = memory->read(pc+1);
                uint8_t high = memory->read(pc+2); 
                uint16_t addr = low | (high << 8); 
                memory->m_Rom[addr] = a;
                update(3,16);
                break;
            }
        case (0xEB): 
            break;
        case (0xEC): 
            break;
        case (0xED): 
            break;
        case (0xEE): 
            i_xor(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xEF): 
            rst(0x28);
            break;
        case (0xF0):
            {
                uint16_t n = memory->read(pc+1);
                a = memory->read(0xFF00 + n);
                update(2,12);
                break;
            }
        case (0xF1):
            pop(&af);
            break;
        case (0xF2):
            {
                a = memory->read(0xFF00+c);
                update(1,8);
                break;
            }
        case (0xF3):
            ime = false;
            update(1,4);
            break;
        case (0xF4): 
            break;
        case (0xF5): 
            push(&af);
            break;
        case (0xF6): 
            i_or(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xF7): 
            rst(0x30);
            break;
        case (0xF8):
            {
                int8_t val = memory->read(pc+1);
                hl = sp + val;
                setFlags<RegisterFlags::ZERO_FLAG>(false);
                setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
                setFlags<RegisterFlags::CARRY_FLAG>(((sp&0xFF) + (val&0xFF)) > 0xFF);
                setFlags<RegisterFlags::HALF_CARRY_FLAG>(((sp & 0x0F) + (val & 0x0F)) > 0x0F);
                update(2,12);
                break;
            }
        case (0xF9):
            ld(&sp,hl);
            update(1,8);
            break;
        case (0xFA):
            {
                uint8_t low = memory->read(pc+1);
                uint8_t high = memory->read(pc+2); 
                uint16_t addr = low | (high << 8); 
                a = memory->read(addr);
                update(3,16);
                break;
            }
        case (0xFB):
            ime = true;
            update(1,4);
            break;
        case (0xFC): 
            break;
        case (0xFD): 
            break;
        case (0xFE): 
            cp(&a, memory->read(pc+1));
            update(2,8);
            break;
        case (0xFF): 
            rst(0x38);
            break;
        default:  break;
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
    sp = _sp;
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

bool CPU::compareRegisters(const std::vector<uint16_t>& expected, const std::vector<std::pair<uint16_t, uint8_t>>& expectedMemory) {
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
    if ((int)pc != expected[8]) {
        std::cout << std::hex << (int)pc << std::endl;
        std::cout << "Mismatch in PC. Expected: " << std::hex << (int)expected[8] 
                  << ", Got: " << (int)pc << std::endl;
        success = false;
    }
    if ((int)sp != expected[9]) {
        std::cout << std::hex << (int)sp << std::endl;
        std::cout << "Mismatch in SP. Expected: " << std::hex << (int)expected[9] 
                  << ", Got: " << (int)sp << std::endl;
        success = false;
    }
    for (const auto& [address, expectedValue] : expectedMemory) {
        uint8_t actualValue = memory->read(address);  // Assuming m_memory->read() retrieves a byte at a given address
        if (actualValue != expectedValue) {
            std::cout << "Mismatch in memory at address 0x" << std::hex << address
                      << ". Expected: 0x" << (int)expectedValue 
                      << ", Got: 0x" << (int)actualValue << std::endl;
            success = false;
        }
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

void CPU::add(uint8_t *dst, uint8_t value){
    uint16_t fullResult = *dst + value;
    
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) + (value & 0x0F)) > 0x0F);
    *dst = fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::add(uint16_t *dst, uint16_t value){
    uint32_t fullResult = *dst + value;
    
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFFFF);
    //we are checking for overflow from bit 11 rather than 3 since 16 bit values
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);
    *dst = (uint16_t)fullResult;

    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::adc(uint8_t *dst, uint8_t value) {
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;

    uint16_t fullResult = *dst + value + carryBitSet;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) + (value & 0x0F) + carryBitSet) > 0x0F);
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);
    *dst = (uint8_t)fullResult;
    
    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);

}

void CPU::sub(uint8_t *dst, uint8_t value) {
    uint16_t fullResult = *dst - value;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) < (value & 0x0F)));
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);
    *dst = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
}

void CPU::sbc(uint8_t *dst, uint8_t value) {
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;

    uint16_t fullResult = *dst - value - carryBitSet;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) < ((value & 0x0F) + carryBitSet)));
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);
    *dst = (uint8_t)fullResult;

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
}

void CPU::i_and(uint8_t *dst, uint8_t value) {
    *dst &= value;

    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(true);
    setFlags<RegisterFlags::CARRY_FLAG>(false);
}

void CPU::i_xor(uint8_t *dst, uint8_t value) {
    *dst ^= value;

    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(false);
}

void CPU::i_or(uint8_t *dst, uint8_t value) {
    *dst |= value;

    setFlags<RegisterFlags::ZERO_FLAG>(*dst == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(false);
}

void CPU::cp(uint8_t *dst, uint8_t value) {
    uint16_t fullResult = *dst - value;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*dst & 0x0F) < (value & 0x0F)));
    setFlags<RegisterFlags::CARRY_FLAG>(fullResult > 0xFF);

    setFlags<RegisterFlags::ZERO_FLAG>(fullResult == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
}

void CPU::ld(uint8_t *dst, uint8_t value){
    *dst = value;
    //no flag setting necessary
}

void CPU::ld(uint16_t *dst, uint16_t value){
    *dst = value;
    //no flag setting necessary
}

void CPU::ld(uint16_t *addr, uint8_t value){
    memory->m_Rom[*addr] = value;
    //no flag setting necessary
}

void CPU::inc(uint8_t *reg){
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((*reg & 0x0F)+(1&0x0F))&0x10);
    *reg += 1;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::inc(uint16_t *reg){
    uint8_t mem_val = memory->read(*reg);
    uint8_t val = mem_val + 1;
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(((mem_val & 0x0F) == 0x0F));
    memory->m_Rom[*reg] = val;

    setFlags<RegisterFlags::ZERO_FLAG>(val == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::dec(uint8_t *reg){
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(!(*reg & 0x0F)); //carry from bit 4 into 3 if low order nibble is 0x0
    *reg -=1 ;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
}

void CPU::dec(uint16_t *reg){
    uint8_t mem_val = memory->read(*reg);
    uint8_t val = mem_val - 1;
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(!(mem_val & 0x0F));
    memory->m_Rom[*reg] = val;

    setFlags<RegisterFlags::ZERO_FLAG>(val == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
}

//if carry flag unset, 8 bit value d is added to the pc
//we check value stored at pc+1 and treat as a SIGNED int
template<RegisterFlags flag>
void CPU::jr(bool n, bool bypass){ //is if we want to find nc or nz
    auto checkFlag = [this, n](RegisterFlags _flag) -> bool {
        return n ? (f & (uint8_t)_flag) : !(f & (uint8_t)_flag);  
    };
    RegisterFlags condition;
    if(!bypass){
        condition = (flag == RegisterFlags::CARRY_FLAG) ? RegisterFlags::CARRY_FLAG : RegisterFlags::ZERO_FLAG;
    }

    if(bypass || checkFlag(condition)){
        pc += (int8_t)memory->read(pc+1); //here we have to cast to a signed int
        update(2,12);
    }else{
        update(2,8);
    }
}

//i use this n bool here often, if it is false we are checking NC or NZ. Otherwise we 
//check C or Z flags for true
template<RegisterFlags flag>
void CPU::jr16(bool n, bool bypass){
    auto checkFlag = [this, n](RegisterFlags _flag) -> bool {
        return n ? (f & (uint8_t)_flag) : !(f & (uint8_t)_flag);  
    };
    RegisterFlags condition;
    if(!bypass){
        condition = (flag == RegisterFlags::CARRY_FLAG) ? RegisterFlags::CARRY_FLAG : RegisterFlags::ZERO_FLAG;
    }
    

    if(bypass || checkFlag(condition)){
        uint16_t addr;
        uint8_t lowOrder = memory->read(pc+1);
        uint8_t highOrder = memory->read(pc+2);
        addr = lowOrder | (highOrder << 8);
        pc = addr; 
        update(0,16);
    }else{
        update(3,12);
    }
}

void CPU::rlca(uint8_t *reg){
    //carry bit does not rotate through
    bool willCarry = *reg & (1<<7);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);

    setFlags<RegisterFlags::ZERO_FLAG>(false);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);

    *reg <<= 1;
    if(willCarry) *reg += 1; //if we overflowed, we need to loop back around and set 1st bit
}

void CPU::rrca(uint8_t *reg){
    //carry bit does not rotate through
    bool willCarry = *reg & (0x01);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);

    setFlags<RegisterFlags::ZERO_FLAG>(false);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);

    *reg >>= 1;
    if(willCarry) *reg |= (1<<7);
}

void CPU::rra(uint8_t *reg){
    //carry bit does rotate through 
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    bool willCarry = *reg & (0x01);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);

    setFlags<RegisterFlags::ZERO_FLAG>(false);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);

    *reg >>= 1;
    if(carryBitSet) *reg |= (1<<7);
}

void CPU::rla(uint8_t *reg){
    //rotate through carry flag
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    bool willCarry =  *reg & (1<<7);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);

    setFlags<RegisterFlags::ZERO_FLAG>(false);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);

    *reg <<= 1;
    if(carryBitSet) *reg += 1;
}

void CPU::daa(uint8_t *reg){
    //https://blog.ollien.com/posts/gb-daa/ 
    //working with binary coded decimal numbers
    //this means instead of 0-255 in a byte, we now have 0-99
    //if half carry add 0x06
    //if full carry add 0x60
    //so effectively we are just updating register a based on flags and convert to BCD

    uint8_t offset = 0;
    uint8_t unconverted_reg = *reg;
    bool should_carry = false;
    bool half_carry = f & ((uint8_t)RegisterFlags::HALF_CARRY_FLAG);
    bool carry = f & ((uint8_t)RegisterFlags::CARRY_FLAG);
    bool subtract = f & ((uint8_t)RegisterFlags::SUBTRACT_FLAG);

    if((subtract == 0 && ((unconverted_reg & 0x0F) > 0x09)) || half_carry == 1){
        offset |= 0x06;
    }
    if((subtract == 0 && unconverted_reg > 0x99) || carry == 1){
        offset |= 0x60;
        should_carry = true;
    }

    *reg = subtract ? unconverted_reg - offset : unconverted_reg + offset;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(
            (unconverted_reg > 0x99 && subtract == 0) ||
            should_carry 
    );
}

void CPU::scf(){
   setFlags<RegisterFlags::CARRY_FLAG>(true);
   setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
   setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::cpl(){
    a = ~a;
    setFlags<RegisterFlags::SUBTRACT_FLAG>(true);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(true);
}

void CPU::ccf(){ 
    bool carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? true : false;
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(!carryBitSet);
}

template<RegisterFlags flag>
void CPU::retc(bool n, bool bypass){ //n is if we want to find nc or nz
    auto checkFlag = [this, n](RegisterFlags _flag) -> bool {
        return n ? (f & (uint8_t)_flag) : !(f & (uint8_t)_flag);  
    };
    RegisterFlags condition;
    if(!bypass){
        condition = (flag == RegisterFlags::CARRY_FLAG) ? RegisterFlags::CARRY_FLAG : RegisterFlags::ZERO_FLAG;
    }

    if(bypass || checkFlag(condition)){
        ret();
        update(0,20);
    }else{
        update(1,8);
    }
}

void CPU::ret(){ 
    uint16_t addr;
    uint8_t low = memory->read(sp);
    sp++;
    uint8_t high = memory->read(sp);
    sp++;
    addr = low | (high << 8);
    pc = addr;
}

template<RegisterFlags flag>
void CPU::call(bool n, bool bypass){
    auto checkFlag = [this, n](RegisterFlags _flag) -> bool {
        return n ? (f & (uint8_t)_flag) : !(f & (uint8_t)_flag);  
    };
    RegisterFlags condition;
    if(!bypass){
        condition = (flag == RegisterFlags::CARRY_FLAG) ? RegisterFlags::CARRY_FLAG : RegisterFlags::ZERO_FLAG;
    }
    if(bypass || checkFlag(condition)){
        uint16_t addr = memory->read(pc + 1) | (memory->read(pc + 2) << 8);

        sp--;
        memory->m_Rom[sp] = ((pc + 3) >> 8);   // Push high byte of PC
        sp--;
        memory->m_Rom[sp] = ((pc + 3) & 0x00FF); // Push low byte of PC

        pc = addr;
        update(0, 24);
    }else update(3,12);
}

void CPU::rst(uint8_t n){
    uint16_t addr = n | (0x00 << 8);

    pc++;
    sp--;
    memory->m_Rom[sp] = (pc >> 8);   // Push high byte of PC
    sp--;
    memory->m_Rom[sp] = (pc & 0x00FF); // Push low byte of PC

    pc = addr;
    update(0, 16);
}

void CPU::pop(uint16_t *reg){
    uint16_t addr;
    uint8_t low = memory->read(sp);
    sp++;
    uint8_t high = memory->read(sp);
    sp++;
    addr = low | (high << 8);
    *reg = addr;
    update(1,12);
    f &= ~0x0F; //clear low order nibble of f
}

void CPU::push(uint16_t *reg){
    sp--;
    memory->m_Rom[sp] = (*reg >> 8);
    sp--;
    memory->m_Rom[sp] = (*reg & 0x00FF);
    update(1,16);
}

void CPU::extended_execute(uint8_t opcode){
    switch(opcode){
        case (0x00): 
            rlc(&b);
            update(2, 8);
            break;
        case (0x01): 
            rlc(&c);
            update(2, 8);
            break;
        case (0x02): 
            rlc(&d);
            update(2, 8);
            break;
        case (0x03): 
            rlc(&e);
            update(2, 8);
            break;
        case (0x04): 
            rlc(&h);
            update(2, 8);
            break;
        case (0x05): 
            rlc(&l);
            update(2, 8);
            break;
        case (0x06):
            {
                uint8_t val = memory->read(hl);
                rlc(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x07):
            rlc(&a);
            update(2, 8);
            break;
        case (0x08):
            rrc(&b);
            update(2,8);
            break;
        case (0x09): 
            rrc(&c);
            update(2,8);
            break;
        case (0x0A): 
            rrc(&d);
            update(2,8);
            break;
        case (0x0B): 
            rrc(&e);
            update(2,8);
            break;
        case (0x0C): 
            rrc(&h);
            update(2,8);
            break;
        case (0x0D): 
            rrc(&l);
            update(2,8);
            break;
        case (0x0E): 
            {
                uint8_t val = memory->read(hl);
                rrc(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x0F):
            rrc(&a);
            update(2,8);
            break;
        case (0x10):
            rl(&b);
            update(2, 8);
            break;
        case (0x11):
            rl(&c);
            update(2, 8);
            break;
        case (0x12):
            rl(&d);
            update(2, 8);
            break;
        case (0x13):
            rl(&e);
            update(2, 8);
            break;
        case (0x14):
            rl(&h);
            update(2, 8);
            break;
        case (0x15):
            rl(&l);
            update(2, 8);
            break;
        case (0x16):
            {
                uint8_t val = memory->read(hl);
                rl(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x17):
            rl(&a);
            update(2, 8);
            break;
        case (0x18):
            rr(&b);
            update(2,8);
            break;
        case (0x19):
            rr(&c);
            update(2,8);
            break;
        case (0x1A):
            rr(&d);
            update(2,8);
            break;
        case (0x1B):
            rr(&e);
            update(2,8);
            break;
        case (0x1C):
            rr(&h);
            update(2,8);
            break;
        case (0x1D):
            rr(&l);
            update(2,8);
            break;
        case (0x1E): 
            {
                uint8_t val = memory->read(hl);
                rr(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x1F):
            rr(&a);
            update(2,8);
            break;
        case (0x20):
            sla(&b);
            update(2,8);
            break;
        case (0x21):
            sla(&c);
            update(2,8);
            break;
        case (0x22):
            sla(&d);
            update(2,8);
            break;
        case (0x23):
            sla(&e);
            update(2,8);
            break;
        case (0x24):
            sla(&h);
            update(2,8);
            break;
        case (0x25):
            sla(&l);
            update(2,8);
            break;
        case (0x26):
            {
                uint8_t val = memory->read(hl);
                sla(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x27):
            sla(&a);
            update(2,8);
            break;
        case (0x28):
            sra(&b);
            update(2,8);
            break;
        case (0x29):
            sra(&c);
            update(2,8);
            break;
        case (0x2A):
            sra(&d);
            update(2,8);
            break;
        case (0x2B):
            sra(&e);
            update(2,8);
            break;
        case (0x2C):
            sra(&h);
            update(2,8);
            break;
        case (0x2D):
            sra(&l);
            update(2,8);
            break;
        case (0x2E):
            {
                uint8_t val = memory->read(hl);
                sra(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x2F):
            sra(&a);
            update(2,8);
            break;
        case (0x30):
            swap(&b);
            update(2,8);
            break;
        case (0x31):
            swap(&c);
            update(2,8);
            break;
        case (0x32):
            swap(&d);
            update(2,8);
            break;
        case (0x33):
            swap(&e);
            update(2,8);
            break;
        case (0x34):
            swap(&h);
            update(2,8);
            break;
        case (0x35):
            swap(&l);
            update(2,8);
            break;
        case (0x36):
            {
                uint8_t val = memory->read(hl);
                swap(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x37):
            swap(&a);
            update(2,8);
            break;
        case (0x38):
            srl(&b);
            update(2,8);
            break;
        case (0x39):
            srl(&c);
            update(2,8);
            break;
        case (0x3A):
            srl(&d);
            update(2,8);
            break;
        case (0x3B):
            srl(&e);
            update(2,8);
            break;
        case (0x3C):
            srl(&h);
            update(2,8);
            break;
        case (0x3D):
            srl(&l);
            update(2,8);
            break;
        case (0x3E): 
            {
                uint8_t val = memory->read(hl);
                srl(&val);
                memory->m_Rom[hl] = val;
                update(2, 16);
                break;
            }
        case (0x3F):
            srl(&a);
            update(2,8);
            break;
        case 0x40: 
            bit(0, &b); 
            update(2, 8); 
            break;
        case 0x41: 
            bit(0, &c); 
            update(2, 8); 
            break;
        case 0x42: 
            bit(0, &d); 
            update(2, 8); 
            break;
        case 0x43: 
            bit(0, &e); 
            update(2, 8);
            break;
        case 0x44: 
            bit(0, &h); 
            update(2, 8); 
            break;
        case 0x45: 
            bit(0, &l); 
            update(2, 8);
            break;
        case 0x46:
            {
                uint8_t val = memory->read(hl);
                bit(0, &val); 
                update(2, 12); 
                break;
            }
        case 0x47: 
            bit(0, &a);
            update(2, 8);
            break;
        case 0x48: 
            bit(1, &b);
            update(2, 8);
            break;
        case 0x49: 
            bit(1, &c);
            update(2, 8);
            break;
        case 0x4A: 
            bit(1, &d);
            update(2, 8);
            break;
        case 0x4B: 
            bit(1, &e);
            update(2, 8);
            break;
        case 0x4C: 
            bit(1, &h);
            update(2, 8);
            break;
        case 0x4D: 
            bit(1, &l);
            update(2, 8);
            break;
        case 0x4E:
            {
                uint8_t val = memory->read(hl);
                bit(1, &val); 
                update(2, 12);
                break;
            }
        case 0x4F: 
            bit(1, &a);
            update(2, 8);
            break;
        case 0x50: 
            bit(2, &b);
            update(2, 8); 
            break;
        case 0x51: 
            bit(2, &c);
            update(2, 8);
            break;
        case 0x52: 
            bit(2, &d);
            update(2, 8);
            break;
        case 0x53: 
            bit(2, &e); 
            update(2, 8);
            break;
        case 0x54: 
            bit(2, &h);
            update(2, 8);
            break;
        case 0x55: 
            bit(2, &l);
            update(2, 8);
            break;
        case 0x56: 
            {
                uint8_t val = memory->read(hl);
                bit(2, &val); 
                update(2, 12);
                break;
            }
        case 0x57: 
            bit(2, &a);
            update(2, 8);
            break;
        case 0x58: 
            bit(3, &b); 
            update(2, 8);
            break;
        case 0x59: 
            bit(3, &c); 
            update(2, 8);
            break;
        case 0x5A: 
            bit(3, &d); 
            update(2, 8);
            break;
        case 0x5B: 
            bit(3, &e);
            update(2, 8);
            break;
        case 0x5C: 
            bit(3, &h);
            update(2, 8);
            break;
        case 0x5D: 
            bit(3, &l);
            update(2, 8);
            break;
        case 0x5E: 
            {
                uint8_t val = memory->read(hl);
                bit(3, &val); 
                update(2, 12);
                break;
            }
        case 0x5F: 
            bit(3, &a);
            update(2, 8); 
            break;
        case 0x60: 
            bit(4, &b);
            update(2, 8);
            break;
        case 0x61: 
            bit(4, &c);
            update(2, 8);
            break;
        case 0x62: 
            bit(4, &d);
            update(2, 8);
            break;
        case 0x63: 
            bit(4, &e);
            update(2, 8); 
            break;
        case 0x64: 
            bit(4, &h);
            update(2, 8);
            break;
        case 0x65: 
            bit(4, &l); 
            update(2, 8);
            break;
        case 0x66: 
            {
                uint8_t val = memory->read(hl);
                bit(4, &val); 
                update(2, 12);
                break;
            }
        case 0x67: 
            bit(4, &a);
            update(2, 8);
            break;
        case 0x68:
            bit(5, &b); 
            update(2, 8);
            break;
        case 0x69:
            bit(5, &c); 
            update(2, 8);
            break;
        case 0x6A:
            bit(5, &d); 
            update(2, 8);
            break;
        case 0x6B: 
            bit(5, &e); 
            update(2, 8);
            break;
        case 0x6C:
            bit(5, &h); 
            update(2, 8); 
            break;
        case 0x6D:
            bit(5, &l); 
            update(2, 8); 
            break;
        case 0x6E: 
            {
                uint8_t val = memory->read(hl);
                bit(5, &val); 
                update(2, 12);
                break;
            }
        case 0x6F: 
            bit(5, &a);
            update(2, 8);
            break;
        case 0x70: 
            bit(6, &b);
            update(2, 8);
            break;
        case 0x71: 
            bit(6, &c); 
            update(2, 8);
            break;
        case 0x72: 
            bit(6, &d); 
            update(2, 8);
            break;
        case 0x73: 
            bit(6, &e);
            update(2, 8);
            break;
        case 0x74: 
            bit(6, &h);
            update(2, 8);
            break;
        case 0x75: 
            bit(6, &l);
            update(2, 8);
            break;
        case 0x76: 
            {
                uint8_t val = memory->read(hl);
                bit(6, &val); 
                update(2, 12);
                break;
            }
        case 0x77: 
            bit(6, &a);
            update(2, 8);
            break;
        case 0x78: 
            bit(7, &b);
            update(2, 8); 
            break;
        case 0x79: 
            bit(7, &c);
            update(2, 8);
            break;
        case 0x7A: 
            bit(7, &d);
            update(2, 8);
            break;
        case 0x7B:
            bit(7, &e); 
            update(2, 8);
            break;
        case 0x7C:
            bit(7, &h);
            update(2, 8); 
            break;
        case 0x7D:
            bit(7, &l);
            update(2, 8);
            break;
        case 0x7E:
            {
                uint8_t val = memory->read(hl);
                bit(7, &val); 
                update(2, 12);
                break;
            }
        case 0x7F:
            bit(7, &a); 
            update(2, 8);
            break;
        //was taking too long to do manually, chatGPT generated rest hence different format (slightly)
        case 0x80: res(0, &b); update(2, 8); break;
        case 0x81: res(0, &c); update(2, 8); break;
        case 0x82: res(0, &d); update(2, 8); break;
        case 0x83: res(0, &e); update(2, 8); break;
        case 0x84: res(0, &h); update(2, 8); break;
        case 0x85: res(0, &l); update(2, 8); break;
        case 0x86: {
            uint8_t val = memory->read(hl);
            res(0, &val); 
            memory->m_Rom[hl] = val; 
            update(2, 16); 
            break;
        }
        case 0x87: res(0, &a); update(2, 8); break;
        case 0x88: res(1, &b); update(2, 8); break;
        case 0x89: res(1, &c); update(2, 8); break;
        case 0x8A: res(1, &d); update(2, 8); break;
        case 0x8B: res(1, &e); update(2, 8); break;
        case 0x8C: res(1, &h); update(2, 8); break;
        case 0x8D: res(1, &l); update(2, 8); break;
        case 0x8E: {
            uint8_t val = memory->read(hl);
            res(1, &val); 
            memory->m_Rom[hl] = val; 
            update(2, 16); 
            break;
        }
        case 0x8F: res(1, &a); update(2, 8); break;
        case 0x90: res(2, &b); update(2, 8); break;
        case 0x91: res(2, &c); update(2, 8); break;
        case 0x92: res(2, &d); update(2, 8); break;
        case 0x93: res(2, &e); update(2, 8); break;
        case 0x94: res(2, &h); update(2, 8); break;
        case 0x95: res(2, &l); update(2, 8); break;
        case 0x96: {
            uint8_t val = memory->read(hl);
            res(2, &val); 
            memory->m_Rom[hl] = val; 
            update(2, 16); 
            break;
        }
        case 0x97: res(2, &a); update(2, 8); break;
        case 0x98: res(3, &b); update(2, 8); break;
        case 0x99: res(3, &c); update(2, 8); break;
        case 0x9A: res(3, &d); update(2, 8); break;
        case 0x9B: res(3, &e); update(2, 8); break;
        case 0x9C: res(3, &h); update(2, 8); break;
        case 0x9D: res(3, &l); update(2, 8); break;
        case 0x9E: {
            uint8_t val = memory->read(hl);
            res(3, &val); 
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0x9F: res(3, &a); update(2, 8); break;
        case 0xA0: res(4, &b); update(2, 8); break;
        case 0xA1: res(4, &c); update(2, 8); break;
        case 0xA2: res(4, &d); update(2, 8); break;
        case 0xA3: res(4, &e); update(2, 8); break;
        case 0xA4: res(4, &h); update(2, 8); break;
        case 0xA5: res(4, &l); update(2, 8); break;
        case 0xA6: {
            uint8_t val = memory->read(hl);
            res(4, &val); 
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xA7: res(4, &a); update(2, 8); break;
        case 0xA8: res(5, &b); update(2, 8); break;
        case 0xA9: res(5, &c); update(2, 8); break;
        case 0xAA: res(5, &d); update(2, 8); break;
        case 0xAB: res(5, &e); update(2, 8); break;
        case 0xAC: res(5, &h); update(2, 8); break;
        case 0xAD: res(5, &l); update(2, 8); break;
        case 0xAE: {
            uint8_t val = memory->read(hl);
            res(5, &val); 
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xAF: res(5, &a); update(2, 8); break;
        case 0xB0: res(6, &b); update(2, 8); break;
        case 0xB1: res(6, &c); update(2, 8); break;
        case 0xB2: res(6, &d); update(2, 8); break;
        case 0xB3: res(6, &e); update(2, 8); break;
        case 0xB4: res(6, &h); update(2, 8); break;
        case 0xB5: res(6, &l); update(2, 8); break;
        case 0xB6: {
            uint8_t val = memory->read(hl);
            res(6, &val); 
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xB7: res(6, &a); update(2, 8); break;

        case 0xB8: res(7, &b); update(2, 8); break;
        case 0xB9: res(7, &c); update(2, 8); break;
        case 0xBA: res(7, &d); update(2, 8); break;
        case 0xBB: res(7, &e); update(2, 8); break;
        case 0xBC: res(7, &h); update(2, 8); break;
        case 0xBD: res(7, &l); update(2, 8); break;
        case 0xBE: {
            uint8_t val = memory->read(hl);
            res(7, &val); 
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xBF: res(7, &a); update(2, 8); break;
        case 0xC0: set(0, &b); update(2, 8); break;
        case 0xC1: set(0, &c); update(2, 8); break;
        case 0xC2: set(0, &d); update(2, 8); break;
        case 0xC3: set(0, &e); update(2, 8); break;
        case 0xC4: set(0, &h); update(2, 8); break;
        case 0xC5: set(0, &l); update(2, 8); break;
        case 0xC6: {
            uint8_t val = memory->read(hl);
            set(0, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xC7: set(0, &a); update(2, 8); break;
        case 0xC8: set(1, &b); update(2, 8); break;
        case 0xC9: set(1, &c); update(2, 8); break;
        case 0xCA: set(1, &d); update(2, 8); break;
        case 0xCB: set(1, &e); update(2, 8); break;
        case 0xCC: set(1, &h); update(2, 8); break;
        case 0xCD: set(1, &l); update(2, 8); break;
        case 0xCE: {
            uint8_t val = memory->read(hl);
            set(1, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xCF: set(1, &a); update(2, 8); break;
        case 0xD0: set(2, &b); update(2, 8); break;
        case 0xD1: set(2, &c); update(2, 8); break;
        case 0xD2: set(2, &d); update(2, 8); break;
        case 0xD3: set(2, &e); update(2, 8); break;
        case 0xD4: set(2, &h); update(2, 8); break;
        case 0xD5: set(2, &l); update(2, 8); break;
        case 0xD6: {
            uint8_t val = memory->read(hl);
            set(2, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xD7: set(2, &a); update(2, 8); break;
        case 0xD8: set(3, &b); update(2, 8); break;
        case 0xD9: set(3, &c); update(2, 8); break;
        case 0xDA: set(3, &d); update(2, 8); break;
        case 0xDB: set(3, &e); update(2, 8); break;
        case 0xDC: set(3, &h); update(2, 8); break;
        case 0xDD: set(3, &l); update(2, 8); break;
        case 0xDE: {
            uint8_t val = memory->read(hl);
            set(3, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xDF: set(3, &a); update(2, 8); break;
        case 0xE0: set(4, &b); update(2, 8); break;
        case 0xE1: set(4, &c); update(2, 8); break;
        case 0xE2: set(4, &d); update(2, 8); break;
        case 0xE3: set(4, &e); update(2, 8); break;
        case 0xE4: set(4, &h); update(2, 8); break;
        case 0xE5: set(4, &l); update(2, 8); break;
        case 0xE6: {
            uint8_t val = memory->read(hl);
            set(4, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xE7: set(4, &a); update(2, 8); break;
        case 0xE8: set(5, &b); update(2, 8); break;
        case 0xE9: set(5, &c); update(2, 8); break;
        case 0xEA: set(5, &d); update(2, 8); break;
        case 0xEB: set(5, &e); update(2, 8); break;
        case 0xEC: set(5, &h); update(2, 8); break;
        case 0xED: set(5, &l); update(2, 8); break;
        case 0xEE: {
            uint8_t val = memory->read(hl);
            set(5, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xEF: set(5, &a); update(2, 8); break;
        case 0xF0: set(6, &b); update(2, 8); break;
        case 0xF1: set(6, &c); update(2, 8); break;
        case 0xF2: set(6, &d); update(2, 8); break;
        case 0xF3: set(6, &e); update(2, 8); break;
        case 0xF4: set(6, &h); update(2, 8); break;
        case 0xF5: set(6, &l); update(2, 8); break;
        case 0xF6: {
            uint8_t val = memory->read(hl);
            set(6, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xF7: set(6, &a); update(2, 8); break;
        case 0xF8: set(7, &b); update(2, 8); break;
        case 0xF9: set(7, &c); update(2, 8); break;
        case 0xFA: set(7, &d); update(2, 8); break;
        case 0xFB: set(7, &e); update(2, 8); break;
        case 0xFC: set(7, &h); update(2, 8); break;
        case 0xFD: set(7, &l); update(2, 8); break;
        case 0xFE: {
            uint8_t val = memory->read(hl);
            set(7, &val);
            memory->m_Rom[hl] = val;  
            update(2, 16); 
            break;
        }
        case 0xFF: set(7, &a); update(2, 8); break;
        default:  break;
    };
}

void CPU::rlc(uint8_t *reg){
    bool carryValue = *reg & (1<<7);
    
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(carryValue);
    *reg <<= 1;
    if(carryValue) *reg += 1;


    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::rlc(uint16_t *reg){ //for hl
    bool carryValue = *reg & (1<<7);
    
    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(carryValue);
    *reg <<= 1;
    if(carryValue) *reg += 1;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::rrc(uint8_t *reg){
    //carry bit does not rotate through
    bool willCarry = *reg & (0x01);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);
    *reg >>= 1;
    if(willCarry) *reg |= (1<<7);

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);

}


void CPU::rl(uint8_t *reg){
    //rotate through carry flag
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;
    bool willCarry =  *reg & (1<<7);
    *reg <<= 1;
    if(carryBitSet) *reg += 1;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::rr(uint8_t *reg){
    //rotate through carry flag
    bool willCarry = *reg & (0x01);
    uint8_t carryBitSet = (f & (uint8_t)RegisterFlags::CARRY_FLAG) ? 1 : 0;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);
    *reg >>= 1;
    if(carryBitSet) *reg |= (1<<7);

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::sla(uint8_t *reg){
    //shift left arithmetically
    bool willCarry = *reg & (1 << 7);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);
    *reg <<= 1;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::sra(uint8_t *reg){
    //shift right arithmetically, bit 7 of reg unchanged
    bool willCarry = *reg & (0x01);
    bool highOrder =  *reg & (1 << 7);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);
    *reg >>= 1;
    if(highOrder) *reg |= (1 << 7);

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::swap(uint8_t *reg){
    //swap upper 4 bits with lower 4
    uint8_t low = *reg << 4;
    uint8_t high = *reg >> 4;

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(false);
    *reg = low | high;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::srl(uint8_t *reg){
    //shift right logically
    bool willCarry = *reg & (0x01);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(false);
    setFlags<RegisterFlags::CARRY_FLAG>(willCarry);
    *reg >>= 1;

    setFlags<RegisterFlags::ZERO_FLAG>(*reg == 0);
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::bit(uint8_t bitNo, uint8_t *reg){
    bool isSet = *reg & (1<<bitNo);

    setFlags<RegisterFlags::HALF_CARRY_FLAG>(true);
    setFlags<RegisterFlags::ZERO_FLAG>(!isSet); //we set the zero flag if the bit is... NOT SET!
    setFlags<RegisterFlags::SUBTRACT_FLAG>(false);
}

void CPU::set(uint8_t bitNo, uint8_t *reg){
    *reg |= (1<<bitNo);
}

void CPU::res(uint8_t bitNo, uint8_t *reg){
    *reg &= ~(1<<bitNo);
}

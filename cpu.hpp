#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <iostream>
#include <assert.h>

enum class RegisterFlags : uint8_t{
    ZERO_FLAG = (1 << 7),
    SUBTRACT_FLAG = (1 << 6),
    HALF_CARRY_FLAG = (1 << 5),
    CARRY_FLAG = (1 << 4)
};

//emulation of Sharp LR35902 8bit cpu
class CPU{
    public:
        CPU();
        uint16_t execute(uint8_t opcode); //we need to return the next instruction pc points to 
        void printRegisters();
        void setRegisters(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f, uint8_t _h, uint8_t _l);
        template<RegisterFlags f>
        void setFlags(uint8_t *dst, uint8_t val, uint8_t result, uint16_t fullResult); 
        template<RegisterFlags flag>
        void resetFlags();
        uint8_t read(uint16_t addr);
        
        //instructions
        void add(uint8_t *dst, uint8_t value); 
        void adc(uint8_t *dst, uint8_t value);
        void sub(uint8_t *dst, uint8_t value);
        void sbc(uint8_t *dst, uint8_t value);
    private:
        //we can use bitwise operations with these flags to set the flag bits in our registers
        uint8_t memory[0xFFFF]; //roms are 256kb 

        uint16_t pc; //program counter
        uint16_t sp; //stack pointer
        //registers can be accessed as either the individual 8bit or combined 16 bit. f is for flags
        struct {
            union {
                struct {
                    uint8_t f;
                    uint8_t a;
                };
                uint16_t af;
            };
        };

        struct {
            union {
                struct {
                    uint8_t c;
                    uint8_t b;
                };
                uint16_t bc;
            };
        };

        struct {
            union {
                struct {
                    uint8_t e;
                    uint8_t d;
                };
                uint16_t de;
            };
        };

        struct {
            union {
                struct {
                    uint8_t l;
                    uint8_t h;
                };
                uint16_t hl;
            };
        };
};

#endif

#ifndef CPU_HPP
#define CPU_HPP

#include "memory.hpp"

#include <cstdint>
#include <vector>
#include <iostream>
#include <assert.h>

enum class RegisterFlags{
    ZERO_FLAG = (1 << 7),
    SUBTRACT_FLAG = (1 << 6),
    HALF_CARRY_FLAG = (1 << 5),
    CARRY_FLAG = (1 << 4)
};

//emulation of Sharp LR35902 8bit cpu
class CPU{
    public:
        CPU(Memory* mem);
        void run(); //handles the entire fetch, decode, execute cycle
        void execute(uint8_t opcode); //we need to return the next instruction pc points to 
        void update(uint8_t pc_inc, uint8_t cycles_inc);
        void printRegisters();
        void setRegisters(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f, uint8_t _h, uint8_t _l, uint16_t _pc, uint16_t _sp);
        std::vector<uint8_t> getRegisters() const;
        bool compareRegisters(const std::vector<uint8_t>& expected);
        
        template<RegisterFlags f>
        void setFlags(const bool setOrReset); 

        uint8_t read(uint16_t addr);
        
        //instructions
        void add(uint8_t *dst, uint8_t value); 
        void adc(uint8_t *dst, uint8_t value);
        void sub(uint8_t *dst, uint8_t value);
        void sbc(uint8_t *dst, uint8_t value);
        void i_and(uint8_t *dst, uint8_t value);
        void i_xor(uint8_t *dst, uint8_t value);
        void i_or(uint8_t *dst, uint8_t value);
        void cp(uint8_t *dst, uint8_t value);
    private:
        //we can use bitwise operations with these flags to set the flag bits in our registers
        uint16_t pc; //program counter
        uint16_t sp; //stack pointer
        uint64_t cycles; //keep track of how many cycles for instructions
        bool ime; //enable/disable intererupts
        Memory* memory;
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

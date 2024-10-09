#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <iostream>

//emulation of Sharp LR35902 8bit cpu
class CPU{
    public:
        void execute(uint8_t opcode);
        void printRegisters();

        void add(uint8_t *dst, uint8_t value); //src=hl, dst=bc
    private:
        //we can use bitwise operations with these flags to set the flag bits in our registers
        enum class RegisterFlags{
            ZERO_FLAG = (1 << 7),
            SUBTRACT_FLAG = (1 << 6),
            HALF_CARRY_FLAG = (1 << 5),
            CARRY_FLAG = (1 << 4)
        };

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

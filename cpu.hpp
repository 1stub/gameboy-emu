#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

//emulation of Sharp LR35902 8bit cpu
class Cpu{
    public:

    private:
        uint16_t pc; //program counter
        uint16_t sp; //stack pointer
        //registers can be accessed as either the individual 8bit or combined 16 bit.
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

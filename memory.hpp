#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

class Memory{
    public:
        Memory();
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);
    private:
        uint8_t m_Rom[0xFFFF]; //roms are 256kb 
};

#endif

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

class Memory{
    public:
        Memory();
    private:
        uint8_t m_Rom[0xFFFF]; //roms are 256kb 
};

#endif

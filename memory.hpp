#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

class Memory{
    public:
        Memory();
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);
    
        uint8_t m_Rom[0x10000];  
    private:
        uint8_t ie; //interupt enable
        uint8_t _if; //interrtupt flag, if is reserved so added _ prefix
};

#endif

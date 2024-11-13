#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>

class Memory{
    public:
        Memory();
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);
        uint16_t read16(uint16_t addr);
        void loadRom(std::string location);
        char performSerialTransfer();

        int m_dividerCounter = 0;
        uint8_t m_Rom[0x10000];  
        std::string serial_output;
};

#endif

#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "memory.hpp"
#include "cpu.hpp"

class Emulator{
    public:
        Emulator(CPU* cpu, Memory* mem);
        void emulate(); //this is the main loop where all the "magic" happens
    private:
        CPU* m_cpu;
        Memory* m_memory;
};

#endif

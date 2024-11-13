#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "memory.hpp"
#include "cpu.hpp"

#include <chrono>
#include <thread>

class Emulator{
    public:
        Emulator(CPU* cpu, Memory* mem);
        void emulate(); //this is the main loop where all the "magic" happens
        void updateTimers(uint64_t cycles);
        void doInterrupts();
        void serviceInterrupt(int interrupt);
        void updateGraphics(int cycles);
        void setLCDStatus();
    private:
        int m_ScanlineCounter = 456;
        CPU* m_cpu;
        Memory* m_memory;
};

#endif

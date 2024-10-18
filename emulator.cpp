#include "emulator.hpp"

Emulator::Emulator(CPU* cpu, Memory* mem){
   m_cpu = cpu;
   m_memory = mem;
}

void Emulator::run();

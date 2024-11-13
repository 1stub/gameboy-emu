#include <iostream>

#include "cpu.hpp"
#include "emulator.hpp"
#include "jsonTesting.hpp"

int main(int argc, char *argv[]){
    Memory* memory = new Memory(); 
    CPU* cpu = new CPU(memory);
    Emulator *emu = new Emulator(cpu, memory); 

    memory->loadRom(argv[1]);
    emu->emulate();

    //jsonTesting jsonTesting(cpu, memory);
    //if(!jsonTesting.test()) std::cout << "All tests passed successfully." << std::endl; 
    delete(emu);
    delete(memory);
    delete(cpu);
    return 0;
}


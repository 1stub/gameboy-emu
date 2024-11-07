#include <iostream>

#include "cpu.hpp"
#include "jsonTesting.hpp"

int main(int argc, char *argv[]){
    Memory* memory = new Memory(); 
    CPU* cpu = new CPU(memory);

    memory->loadRom(argv[1]);
    while(true){
        cpu->cycle();
    }

    //jsonTesting jsonTesting(cpu, memory);
    //if(!jsonTesting.test()) std::cout << "All tests passed successfully." << std::endl;
    delete(memory);
    delete(cpu);
    return 0;
}


#include <iostream>

#include "cpu.hpp"
#include "jsonTesting.hpp"

int main(){
    Memory* memory = new Memory(); 
    CPU* cpu = new CPU(memory);

    jsonTesting jsonTesting(cpu, memory);
    
    if(!jsonTesting.test()) std::cout << "All tests passed successfully." << std::endl;
    free(memory);
    free(cpu);
    return 0;
}


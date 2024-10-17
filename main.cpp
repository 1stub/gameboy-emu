#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "cpu.hpp"

using json = nlohmann::json;

int main(){
    Memory* memory = new Memory(); 
    CPU cpu(memory);
    std::ifstream f("./GameboyCPUTests/v2/80.json");
   
    json data = json::parse(f);

    /*for(uint16_t opcode = 0; opcode <= 0xFF; opcode++){
        std::cout << "opcode: " << std::hex << opcode << std::endl;
        cpu.execute(opcode);
    }*/
    
    for(const auto& test : data){
        std::vector<uint8_t> expected;
        expected.push_back(test["final"]["a"]);
        expected.push_back(test["final"]["b"]);
        expected.push_back(test["final"]["c"]);
        expected.push_back(test["final"]["d"]);
        expected.push_back(test["final"]["e"]);
        expected.push_back(test["final"]["f"]);
        expected.push_back(test["final"]["h"]);
        expected.push_back(test["final"]["l"]);
        expected.push_back(test["final"]["pc"]);
       
        uint16_t programCounter = test["initial"]["pc"].get<uint16_t>();

        cpu.setRegisters(
            test["initial"]["a"], 
            test["initial"]["b"], 
            test["initial"]["c"], 
            test["initial"]["d"], 
            test["initial"]["e"], 
            test["initial"]["f"], 
            test["initial"]["h"], 
            test["initial"]["l"],
            programCounter - 1,
            test["initial"]["sp"]
        );

        for(const auto& addr : test["initial"]["ram"]){ //populate memory
            uint16_t address = addr[0].get<uint16_t>();
            uint8_t value = addr[1].get<uint8_t>();
            memory->m_Rom[address] = value;
        }
       
        cpu.run();
        cpu.compareRegisters(expected);

   }

    free(memory);
    return 0;
}


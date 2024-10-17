#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "cpu.hpp"

using json = nlohmann::json;

int main(){
    CPU cpu;
    std::ifstream f("./cpu_instrs/80.json");
   
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
        
        cpu.setRegisters(
            test["initial"]["a"], 
            test["initial"]["b"], 
            test["initial"]["c"], 
            test["initial"]["d"], 
            test["initial"]["e"], 
            test["initial"]["f"], 
            test["initial"]["h"], 
            test["initial"]["l"]
        );
       
        cpu.execute(0x80);

        cpu.compareRegisters(expected);
   }

    return 0;
}


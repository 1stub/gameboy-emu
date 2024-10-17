#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "cpu.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

int main(){
    Memory* memory = new Memory(); 
    CPU cpu(memory);
    static bool wasError = false;
    
    std::string directory = "./sm83/v1/";
    for(int i = 0x40; i <= 0xBF; i++){
        if(wasError) break;
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << i << ".json";
        std::string filename = ss.str();

        fs::path filePath = directory + filename;
        if(!fs::exists(filePath)){
            std::cerr << "Failed to open " << filename << std::endl;
            break;
        }
        
        std::ifstream f(filePath);
        json data = json::parse(f);
        
        for(const auto& test : data){
            std::vector<uint16_t> expected;
            expected.push_back(test["final"]["a"]);
            expected.push_back(test["final"]["b"]);
            expected.push_back(test["final"]["c"]);
            expected.push_back(test["final"]["d"]);
            expected.push_back(test["final"]["e"]);
            expected.push_back(test["final"]["f"]);
            expected.push_back(test["final"]["h"]);
            expected.push_back(test["final"]["l"]);
            expected.push_back(test["final"]["pc"]);
            expected.push_back(test["final"]["sp"]);
        
            cpu.setRegisters(
                test["initial"]["a"], 
                test["initial"]["b"], 
                test["initial"]["c"], 
                test["initial"]["d"], 
                test["initial"]["e"], 
                test["initial"]["f"], 
                test["initial"]["h"], 
                test["initial"]["l"],
                test["initial"]["pc"],
                test["initial"]["sp"]
            );

            for(const auto& addr : test["initial"]["ram"]){ //populate memory
                uint16_t address = addr[0].get<uint16_t>();
                uint8_t value = addr[1].get<uint8_t>();

                //since we are not running a rom we need to modify data that would otherwise be restricted
                memory->m_Rom[address] = value;
            }
        
            cpu.run();
            if(!cpu.compareRegisters(expected)){
                std::cerr << "ERROR" << std::endl;
                wasError = true;
            }
            if(wasError) break;
        }
   }
    if(!wasError) std::cout << "All tests passed successfully." << std::endl;
    free(memory);
    return 0;
}


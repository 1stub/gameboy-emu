#ifndef JSONTESTING_HPP
#define JSONTESTING_HPP

#include "cpu.hpp"
#include "memory.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>

//this code is not necessary for the emulator to work. just wanted to move out my code for testhing json files into its own header
class jsonTesting{
    public:
        jsonTesting(CPU* cpu, Memory* mem){
            m_cpu = cpu;
            m_memory = mem;
        };
        bool test(){
            namespace fs = std::filesystem;
            using json = nlohmann::json;

            static bool wasError = false;
            std::string directory = "./sm83/v1/";
            uint8_t low = 0xD9;
            uint8_t hi = 0xD9;
            for(int i = low; i <= hi; i++){
                if(i == 0x10) i++;
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
                    m_cpu->ticks = 0;
                    m_cpu->cycles = 0;
                    if(wasError) break;
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
                
                    m_cpu->setRegisters(
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
                        m_memory->m_Rom[address] = value;
                    }
                    for(const auto &cycle : test["cycles"]){
                        m_cpu->cycle();
                    }
                    if(!m_cpu->compareRegisters(expected)){

                        std::cerr << "ERROR" << std::endl;
                        wasError = true;
                    }
                    if(wasError) break;
                }
            }
            return wasError;
        };
    private:
        Memory* m_memory;
        CPU* m_cpu;
        bool readFlag;
        bool memoryRequestFlag;
        bool writeFlag;
};

#endif

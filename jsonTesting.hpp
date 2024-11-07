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


        bool test() {
            namespace fs = std::filesystem;

            static bool wasError = false;
            std::string directory = "./sm83/v1/";
            bool processMainInstrs = true;

            // Loop for regular instruction set files
            if(processMainInstrs){
                for (int i = 0x00; i <= 0xFF; i++) {
                    if (wasError) break;
                    if (i == 0x10) continue; //STOP instruction

                    std::stringstream ss;
                    ss << std::hex << std::setw(2) << std::setfill('0') << i << ".json";
                    std::string filename = ss.str();

                    std::cout << filename << std::endl;

                    fs::path filePath = directory + filename;
                    if (!fs::exists(filePath)) {
                        std::cerr << "Failed to open " << filename << std::endl;
                        continue;
                    }
                    
                    // Process the JSON file
                    if (!processInstructionFile(filePath)) {
                        wasError = true;
                        break;
                    }
                }
            }
            
            // Loop for extended `CB`-prefixed instruction set files
            for (int i = 0x00; i <= 0xFF; i++) {
                if (wasError) break;
                
                std::stringstream ss;
                ss << "cb " << std::hex << std::setw(2) << std::setfill('0') << i << ".json";
                std::string filename = ss.str();
   
                std::cout << filename << std::endl;

                fs::path filePath = directory + filename;
                if (!fs::exists(filePath)) {
                    std::cerr << "Failed to open " << filename << std::endl;
                    continue;
                }
            
                // Process the JSON file
                if (!processInstructionFile(filePath)) {
                    wasError = true;
                    break;
                }
            }

            return wasError;
        };

        bool processInstructionFile(const std::filesystem::path& filePath) {
            using json = nlohmann::json;
            std::ifstream f(filePath);
            if (!f.is_open()) {
                std::cerr << "Could not open file: " << filePath << std::endl;
                return false;
            }

            json data;
            f >> data;

            for (const auto& test : data) {
                m_cpu->ticks = 0;
                m_cpu->cycles = 0;
                
                // Set expected registers
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

                // Initialize CPU registers
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

                // Populate memory with initial values
                for (const auto& addr : test["initial"]["ram"]) {
                    uint16_t address = addr[0].get<uint16_t>();
                    uint8_t value = addr[1].get<uint8_t>();
                    m_memory->m_Rom[address] = value;
                }

                // Run cycles
                for (const auto& cycle : test["cycles"]) { //ignore warnings, need cpu to cycle correct amount
                    m_cpu->cycle();
                }

                // Verify final RAM state
                std::vector<std::pair<uint16_t, uint8_t>> expectedMemory;
                for (const auto& addr : test["final"]["ram"]) {
                    uint16_t address = addr[0].get<uint16_t>();
                    uint8_t value = addr[1].get<uint8_t>();
                    expectedMemory.emplace_back(address, value);
                }

                // Compare registers and memory
                if (!m_cpu->compareRegisters(expected, expectedMemory)) {
                    std::cerr << "ERROR" << std::endl;
                    return false;
                }
            }

            return true;
        };

    private:
        Memory* m_memory;
        CPU* m_cpu;
};

#endif

#include "memory.hpp"

Memory::Memory(){
    m_Rom[0xFF05] = 0x00 ; //Timer Counter (TIMA)
    m_Rom[0xFF06] = 0x00 ; //Timer Modulo (TMA)
    m_Rom[0xFF07] = 0x00 ; //Timer Control (TAC)
    m_Rom[0xFF10] = 0x80 ;
    m_Rom[0xFF11] = 0xBF ;
    m_Rom[0xFF12] = 0xF3 ;
    m_Rom[0xFF14] = 0xBF ;
    m_Rom[0xFF16] = 0x3F ;
    m_Rom[0xFF17] = 0x00 ;
    m_Rom[0xFF19] = 0xBF ;
    m_Rom[0xFF1A] = 0x7F ;
    m_Rom[0xFF1B] = 0xFF ;
    m_Rom[0xFF1C] = 0x9F ;
    m_Rom[0xFF1E] = 0xBF ;
    m_Rom[0xFF20] = 0xFF ;
    m_Rom[0xFF21] = 0x00 ;
    m_Rom[0xFF22] = 0x00 ;
    m_Rom[0xFF23] = 0xBF ;
    m_Rom[0xFF24] = 0x77 ;
    m_Rom[0xFF25] = 0xF3 ;
    m_Rom[0xFF26] = 0xF1 ;
    m_Rom[0xFF40] = 0x91 ;
    m_Rom[0xFF42] = 0x00 ;
    m_Rom[0xFF43] = 0x00 ;
    m_Rom[0xFF45] = 0x00 ;
    m_Rom[0xFF47] = 0xFC ;
    m_Rom[0xFF48] = 0xFF ;
    m_Rom[0xFF49] = 0xFF ;
    m_Rom[0xFF4A] = 0x00 ;
    m_Rom[0xFF4B] = 0x00 ;
    m_Rom[0xFFFF] = 0x00 ;
}

//may need to modify for usage with raw pointer for addr, not sure yet.
void Memory::write(uint16_t addr, uint8_t data){
    if(addr < 0x8000){ //do nothing, this is ROM
    }

    //here we write to ECHO ram, so it needs to be reflected in RAM
    else if(addr >= 0xE000 && addr <= 0xFE00){
        m_Rom[addr] = data;
        write(addr - 0x2000, data);
    }

    //restricted, dont do anything if write here occurs
    else if(addr >= 0xFEA0 && addr < 0xFEFF){
    
    }
    
    else if(addr == 0xFFFF){
        //cpu enable register, used with HALT
    }

    //now we ehausted all cases of invalid memory writing, so only areas left are fine to write to.
    else{
        m_Rom[addr] = data;
    }
}

uint8_t Memory::read(uint16_t addr){
    return m_Rom[addr];
}

uint16_t Memory::read16(uint16_t addr){
    return m_Rom[addr] | (m_Rom[addr+1] << 8);
}

void Memory::loadRom(std::string location){
}


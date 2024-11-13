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
    m_Rom[0xFF40] = 0x91 ; //LCD Control (R/W)
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

void Memory::write(uint16_t addr, uint8_t data){
    if(addr == 0xFF04){ //writing to DIV and LY reset it to zero
        m_Rom[0xFF04] = 0x00;
        m_dividerCounter = 0;
    }

    else if(addr == 0xFF44){
        m_Rom[0xFF44] = 0x00;
    }

    else{ //this shouldnt be done, but while I figure out how to flesh out writing its fine
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
    //this doesnt work...
    std::ifstream input(location, std::ios::binary);

    if (!input) {
        throw std::runtime_error("Failed to open ROM file.");
    }

    //seek to end of .gb file and get its size
    input.seekg(0, std::ios::end);
    std::streamsize size = input.tellg();
    input.seekg(0, std::ios::beg);
    
    if (size > sizeof(m_Rom)) {
        throw std::runtime_error("ROM file is too large to fit into memory.");
    }
    
    if (!input.read(reinterpret_cast<char*>(m_Rom), size)) {
        throw std::runtime_error("Failed to read ROM data.");
    }
}

char Memory::performSerialTransfer(){
    char data = (char)m_Rom[0xFF01];
    m_Rom[0xFF02] &= 0x7F; //clear the transfer flag
    return data;
}


#include "emulator.hpp"

#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07

Emulator::Emulator(CPU* cpu, Memory* mem){
   m_cpu = cpu;
   m_memory = mem;
}

void Emulator::emulate(){
    while(true){
        uint64_t cycles = m_cpu->cycle();
        updateTimers(cycles);
        doInterrupts(); 

        //ideally this would be handled within write() in mmu, but my approach is scuffed
        //so this is what we got lmao
        if(m_memory->read(0xFF02) & 0x80){
            char val = m_memory->performSerialTransfer();
            if(val == 'F'){
                //std::cout << "ENCOUNTERED ERROR" << std::endl;
                m_cpu->printRegisters();
                break;
            }
            if(val == 'P'){ 
                std::cout << "PASSED" << std::endl;
                break;
            }
        }
    }
}


//my thinking is that this doesnt work due to writing to DIV not resetting it to zero
void Emulator::updateTimers(uint64_t cycles){
    //our timer control, TAC is at 0xFF07, second bit is the control bit
    static int timerCounter = 0;
    static int dividerCounter = 0;
    
    dividerCounter += cycles;
    if(dividerCounter >= 256){ //was working here
        dividerCounter -= 256;
        m_memory->m_Rom[DIV]++;
    }

    uint8_t TAC_v = m_memory->read(TAC);
    if(TAC_v & (1 << 2)){
        timerCounter += cycles;

        int timerThreshold = 0;
        uint8_t speed = TAC_v & 0x03;
        switch(speed){ //we read the speed at which our clock should update
            case 0x00: timerThreshold = 1024; break; //freq 4096
            case 0x01: timerThreshold = 16; break; //freq 262114
            case 0x02: timerThreshold = 64; break; //freq 65536
            case 0x03: timerThreshold = 256; break; //freq 16382
            default: break;
        }
        if(timerCounter >= timerThreshold){
            timerCounter -= timerThreshold;
            if(m_memory->read(TIMA) >= 0xFF){ //timer counter overflow
                m_memory->write(TIMA, m_memory->read(TMA)); //reset to value specified in TMA (0xFF06)
                serviceInterrupt(2); //service timer interupt 
            }else{
                m_memory->m_Rom[TIMA]++; //increase TIMA by val in TMA if there is not overflow
            }
        }
    }
}

void Emulator::doInterrupts(){
    if(m_cpu->ime){
        uint8_t req = m_memory->read(0xFF0F); //this is the IF
        uint8_t flag = m_memory->read(0xFFFF); //this is the IE
        if(req > 0){ //make sure there was an interrupt request
            for(int i = 0; i < 5; i++){ //vblank highest priority to be serviced
                if(req & (1 << i)){
                    if(flag & (1 << i)){ //make sure that the request bit and corresponding flag are set
                        serviceInterrupt(i); 
                    }
                }
            }
        }
    }
}

void Emulator::serviceInterrupt(int interrupt){
    m_cpu->ime = false;
    uint8_t req = m_memory->read(0xFF0F);
    req &= ~(1 << interrupt); //clear the bit for this interrupt
    m_memory->write(0xFF0F, req);

    m_cpu->push(&m_cpu->pc); //save current execution address by pushing to stack

    switch(interrupt){ //here we are calling the corresponding interrupt vector per pandocs
        case 0: m_cpu->pc = 0x40; break; //vblank
        case 1: m_cpu->pc = 0x48; break; //LCD
        case 2: m_cpu->pc = 0x50; break; //Timer
        case 3: m_cpu->pc = 0x58; break; //serial
        case 4: m_cpu->pc = 0x60; break; //Joypad
    }
}

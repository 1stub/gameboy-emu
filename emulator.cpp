#include "emulator.hpp"

Emulator::Emulator(CPU* cpu, Memory* mem){
   m_cpu = cpu;
   m_memory = mem;
}

void Emulator::emulate(){
    while(true){
        m_cpu->cycle();
        doInterrupts(); 

        //ideally this would be handled within write() in mmu, but my approach is scuffed
        //so this is what we got lmao
        if(m_memory->read(0xFF02) & 0x80) m_memory->performSerialTransfer();
    }
  
    //it seems that the IME just allows us to service interrupts.
    //so if IME == false then we cant do antyhing with interrups until it becomes true.
    //im thinkling I should move this logic outside of my cpu, for the sake of not clogging up this file even worse
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
    m_memory->m_Rom[0xFF0F] = req;

    m_cpu->push(&m_cpu->pc); //save current execution address by pushing to stack

    switch(interrupt){ //here we are calling the corresponding interrupt vector per pandocs
        case 0: m_cpu->pc = 0x40; break; //vblank
        case 1: m_cpu->pc = 0x48; break; //LCD
        case 2: m_cpu->pc = 0x50; break; //Timer
        case 3: m_cpu->pc = 0x58; break; //serial
        case 4: m_cpu->pc = 0x60; break; //Joypad
    }
}

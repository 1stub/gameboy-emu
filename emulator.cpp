#include "emulator.hpp"

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
        if(m_memory->read(0xFF02) & 0x80) m_memory->performSerialTransfer();
    }
  
    //it seems that the IME just allows us to service interrupts.
    //so if IME == false then we cant do antyhing with interrups until it becomes true.
    //im thinkling I should move this logic outside of my cpu, for the sake of not clogging up this file even worse
}

void Emulator::updateTimers(uint64_t cycles){
    //our timer control, TAC is at 0xFF07, second bit is the control bit
    static const int CLOCKSPEED = 4194304;
    static int timerCounter = 1024;
    static int dividerCounter = 0;
    static uint8_t dividerRegister = 0;
    
    //currently working to sort out the DIV register
    //0xFF04

    dividerRegister += cycles;

    if(dividerCounter >= 0xFF){ //was working here
        dividerCounter = 0;
    }

    uint8_t TAC = m_memory->read(0xFF07);
    if((m_memory->read(TAC)) & (1 << 2)){
        timerCounter -= cycles;

        if(timerCounter <= 0){ //if we have done enough cycles to update our timerCOunter
            uint8_t mask = (1 << 2) - 1; //the two lowest bits represent speeds
            uint8_t speed = TAC & mask;
            switch(speed){ //we read the speed at which our clock should update
                case 0x00: timerCounter = 1024; break; //freq 4096
                case 0x01: timerCounter = 16; break; //freq 262114
                case 0x02: timerCounter = 64; break; //freq 65536
                case 0x03: timerCounter = 256; break; //freq 16382
                default: break;
            }

            if(m_memory->read(0xFF05) > 0xFF){ //timer counter overflow
                m_memory->m_Rom[0xFF05] = m_memory->read(0xFF06); //reset to value specified in TMA (0xFF06)
                serviceInterrupt(2); //service timer interupt 
            }else{
                m_memory->m_Rom[0xFF05] = m_memory->read(0xFF05) + m_memory->read(0xFF06); //increase 0xFF05 by val in 0xFF06 if there is not overflow
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

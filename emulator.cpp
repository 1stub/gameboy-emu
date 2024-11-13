#include "emulator.hpp"
#include <chrono>

#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07
#define LCDC 0xFF40
#define LY 0xFF44
#define IF 0xFF0F

Emulator::Emulator(CPU* cpu, Memory* mem){
   m_cpu = cpu;
   m_memory = mem;
}

void Emulator::emulate(){
    //eventually I will have this ise sf::Time from sfml rather than chrono
    const bool debug = true; //false == print blargg output, true == print reg contents
    const int cyclesPerFrame= 69905; //cpu speed / 60
    const int frameRate = 60; 
    const auto timePerFrame = std::chrono::milliseconds(1000 / frameRate);
    bool doneExecution = false;
    while(true){
        int currentCycle = 0;
        auto frameStartTime = std::chrono::steady_clock::now();

        while(currentCycle < cyclesPerFrame){
            if(debug) m_cpu->printRegisters();
            uint64_t cycles = m_cpu->cycle(); //returns T cycles (4,8,12,...) for each instr
            currentCycle += cycles;
            updateTimers(cycles);
            updateGraphics(cycles);
            doInterrupts(); 

            //ideally this would be handled within write() in mmu, but my approach is scuffed
            //so this is what we got lmao
            if(m_memory->read(0xFF02) & 0x80){
                char val = m_memory->performSerialTransfer();
                if(!debug){
                    if(val == ' ') std::cout << std::endl;
                    else std::cout << val;
                }
                if(debug){
                    if(val == 'F' || val == 'P'){
                        //this allows us to break when we reach a F or P in serial output
                        doneExecution = true;
                        break;
                    }
                }
            }
        }

        if(doneExecution) return;

        auto frameEndTime = std::chrono::steady_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime);

        if (frameDuration < timePerFrame) {
            //we dont need multithreading, we just need to force the thread the cpu is running on to sleep
            std::this_thread::sleep_for(timePerFrame - frameDuration);
        } else {
            std::cerr << "Frame took too long: " << frameDuration.count() << " ms\n";
        }
    }
}


//my thinking is that this doesnt work due to writing to DIV not resetting it to zero
void Emulator::updateTimers(uint64_t cycles){
    //our timer control, TAC is at 0xFF07, second bit is the control bit
    static int timerCounter = 0;
    
    m_memory->m_dividerCounter += cycles;
    if(m_memory->m_dividerCounter >= 256){ //was working here
        m_memory->m_dividerCounter -= 256;
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
        if(timerCounter > timerThreshold){
            timerCounter -= timerThreshold;
            if(m_memory->read(TIMA) == 0xFF){ //timer counter overflow
                m_memory->write(TIMA, m_memory->read(TMA)); //reset to value specified in TMA (0xFF06)
                serviceInterrupt(2); //service timer interupt 
            }else{
                m_memory->write(TIMA, m_memory->read(TIMA)+1); //increase TIMA by val in TMA if there is not overflow
            }
        }
    }
}

//when we want to interrupt, we first need to set the IF flag corresponding bit to our interrupt. then the rest is
//handled in our interrrupt processing logic
void Emulator::requestInterrupt(int interrupt){
    uint8_t data = m_memory->read(IF);
    data |= (1 << interrupt);
    m_memory->write(IF, data);
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

//currently dealing with speed issues regarding our graphics here

void Emulator::updateGraphics(int cycles){
    //in regards to my current issues with reading from LY,
    //LY stores what scan line we are on. SO in order to read
    //correct values, we need some manner to track where we actually are.
    //once we have rendered the whole window, LY should be 0x90 = 144 because
    //that means we scanned 144 lines of the window and our screen is 160x144 
    
    setLCDStatus();

    if(m_memory->read(LCDC) & (1 << 7)){ //LCD Enabled
        m_ScanlineCounter -= cycles; 
    }else return;

    if(m_ScanlineCounter <= 0){
        m_memory->m_Rom[LY]++;
        uint8_t curLine = m_memory->read(LY);

        m_ScanlineCounter = 456;

        //below lines create some issues
        //i think the problem is that we need the interupt to be requested
        //the IF register needs to be bitset in order to service given interrtupt

        if(curLine == 144) requestInterrupt(0); //vblank
        else if(curLine > 153) m_memory->m_Rom[LY] = 0;
        else if(curLine < 144) { } //draw scan line
        else { /*do nothing*/ }
    }
}

void Emulator::setLCDStatus(){
    uint8_t status = m_memory->read(0xFF41);

    if (!(m_memory->read(LCDC) & (1 << 7))) // Check if LCD is disabled
    {
        // Set the mode to 1 during LCD disable and reset scanline
        m_ScanlineCounter = 456;
        m_memory->m_Rom[LY] = 0;
        status &= 0xFC; // Clear bits 0 and 1
        status |= 0x01; // Set bit 0
        m_memory->write(0xFF41, status);
        return;
    }

    uint8_t currentline = m_memory->read(LY);
    uint8_t currentmode = status & 0x03;

    uint8_t mode = 0;
    bool reqInt = false;

    // In V-Blank, set mode to 1
    if (currentline >= 144)
    {
        mode = 1;
        status |= 0x01;  // Set bit 0
        status &= ~0x02; // Clear bit 1
        reqInt = status & (1 << 4);
    }
    else
    {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        // Mode 2
        if (m_ScanlineCounter >= mode2bounds)
        {
            mode = 2;
            status |= 0x02;  // Set bit 1
            status &= ~0x01; // Clear bit 0
            reqInt = status & (1 << 5);
        }
        // Mode 3
        else if (m_ScanlineCounter >= mode3bounds)
        {
            mode = 3;
            status |= 0x03; // Set bits 1 and 0
        }
        // Mode 0
        else
        {
            mode = 0;
            status &= ~0x03; // Clear bits 1 and 0
            reqInt = status & (1 << 3);
        }
    }

    // If entering a new mode, request an interrupt
    if (reqInt && (mode != currentmode))
    {
        requestInterrupt(1); // Request LCD interrupt
    }

    // Check the coincidence flag
    if (currentline == m_memory->read(0xFF45))
    {
        status |= (1 << 2); // Set bit 2
        if (status & (1 << 6))
        {
            requestInterrupt(1); // Request interrupt if bit 6 is set
        }
    }
    else
    {
        status &= ~(1 << 2); // Clear bit 2
    }

    m_memory->write(0xFF41, status);
}

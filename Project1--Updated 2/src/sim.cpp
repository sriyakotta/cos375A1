#include <stdio.h>
#include "MemoryStore.h"
#include "RegisterInfo.h"
#include "EndianHelpers.h"
#include <fstream>
#include <iostream>
using namespace std; 

union REGS 
{
    RegisterInfo reg;
    uint32_t registers[32] {0};
};

union REGS regData;

// TODO: fill in the missing hex values of the OP_IDs (opcodes)
enum OP_IDS
{
    //R-type opcodes...
    OP_ZERO = 0x0, // zero
    //I-type opcodes...
    OP_ADDI = 0x8, // addi
    OP_ADDIU = 0x9, // addiu
    OP_ANDI = 0xc, // andi
    OP_BEQ = 0x4, // beq
    OP_BNE = , // bne
    OP_LBU = , // lbu
    OP_LHU = , // lhu
    OP_LUI = , // lui
    OP_LW = , // lw
    OP_ORI = , // ori
    OP_SLTI = , // slti
    OP_SLTIU = , // sltiu
    OP_SB = , // sb
    OP_SH = , // sh
    OP_SW = , // sw
    OP_BLEZ = , // blez
    OP_BGTZ = , // bgtz
    //J-type opcodes...
    OP_J = , // j
    OP_JAL =  // jal
};

// TODO: fill in the missing hex values of FUNCT_IDs (function IDs)
enum FUNCT_IDS
{
    FUN_ADD = 0x20, // add
    FUN_ADDU = 0x21, // add unsigned (addu)
    FUN_AND = 0x24, // and
    FUN_JR = , // jump register (jr)
    FUN_NOR = , // nor
    FUN_OR = , // or
    FUN_SLT = , // set less than (slt)
    FUN_SLTU = , // set less than unsigned (sltu)
    FUN_SLL = , // shift left logical (sll)
    FUN_SRL = , // shift right logical (srl)
    FUN_SUB = , // substract (sub)
    FUN_SUBU =  // substract unsigned (subu)
};

// extract specific bits [start, end] from a 32 bit instruction
uint extractBits(uint32_t instruction, int start, int end)
{
    int bitsToExtract = start - end + 1;
    uint32_t mask = (1 << bitsToExtract) - 1;
    uint32_t clipped = instruction >> end;
    return clipped & mask;
}

// sign extend smol to a 32 bit unsigned int
uint32_t signExt(uint16_t smol) 
{
    uint32_t x = smol;
    uint32_t extension = 0xffff0000;
    return (smol & 0x8000) ? x ^ extension : x;
}

// dump registers and memory
void dump(MemoryStore *myMem) {

    dumpRegisterState(regData.reg);
    dumpMemoryState(myMem);
}

int main(int argc, char** argv) {

    // open instruction file
    ifstream infile;
    infile.open(argv[1], ios::binary | ios::in);

    // get length of the file and read instruction file into a buffer
    infile.seekg(0, ios::end);
    int length = infile.tellg();
    infile.seekg (0, ios::beg);

    char *buf = new char[length];
    infile.read(buf, length);
    infile.close();

    // initialize memory store with buffer contents
    MemoryStore *myMem = createMemoryStore();
    int memLength = length / sizeof(buf[0]);
    int i;
    for (i = 0; i < memLength; i++) {
        myMem->setMemValue(i * BYTE_SIZE, buf[i], BYTE_SIZE);
    }

    // initialize registers and our program counter
    regData.reg = {};
    uint32_t PC = 0;
    bool err = false;
    
    // variables to handle branch delay slot execution
    bool encounteredBranch = false;
    bool executedDelaySlot = false; 
    uint32_t savedBranch = 0;       // saved (delayed) branch instruction
    uint32_t savedPC = 0;           // PC when the branch wa encountered (PC for the instruction in memory after the branch instruction)
    
    // start simulation
    // TODO: complete simulation loop and implement branch delay logic
    while (!err) {
        // fetch current instruction
        uint32_t instruction;
        myMem->getMemValue(PC, instruction, WORD_SIZE);

        // increment PC & reset zero register
        PC += 4;
        regData.registers[0] = 0;

        // check for halt instruction
        if (instruction == 0xfeedfeed) {
            dump(myMem);
            return 0;
        }

        // TODO: parse instruction by completing function calls to extractBits()
        // and set operands accordingly
        uint32_t opcode = extractBits(instruction, , );
        uint32_t rs = extractBits(instruction, , );
        uint32_t rt = extractBits(instruction, , );
        uint32_t rd = extractBits(instruction, , );
        uint32_t shamt = extractBits(instruction, , );
        uint32_t funct = extractBits(instruction, , );
        uint16_t immediate = extractBits(instruction, , );
        uint32_t address = extractBits(instruction, , );

        int32_t signExtImm = 
        uint32_t zeroExtImm =

        uint32_t branchAddr = 
        uint32_t jumpAddr = // assumes PC += 4 just happened

        switch(opcode) {
            case OP_ZERO: // R-type instruction 
                switch(funct) {
                    case FUN_ADD:                         

                    case FUN_ADDU: 

                    case FUN_AND: 

                    case FUN_JR: 

                    case FUN_NOR: 

                    case FUN_OR: 

                    case FUN_SLT: 

                    case FUN_SLTU: 

                    case FUN_SLL: 

                    case FUN_SRL: 

                    case FUN_SUB:  
                    
                    case FUN_SUBU: 

                    default:
                        fprintf(stderr, "\tIllegal operation...\n");
                        err = true;
                }
                break;

            case OP_ADDI: 
                
            case OP_ADDIU: 
                regData.registers[rt] = regData.registers[rs] + signExtImm;
                break;
            case OP_ANDI: 

            case OP_BEQ: 
                
            case OP_BNE:
                
            case OP_BLEZ: 
                
            case OP_BGTZ: 
                
            case OP_J: 
                
            case OP_JAL: 
                
            case OP_LBU: 

            case OP_LHU: 
            
            case OP_LUI: 
                
            case OP_LW: 
                
            case OP_ORI: 
                
            case OP_SLTI: 
                
            case OP_SLTIU: 
                
            case OP_SB: 
                
            case OP_SH: 
            
            case OP_SW: 
             
            default:
                fprintf(stderr, "\tIllegal operation...\n");
                err = true;
        }
    }

    // dump and exit with error
    dump(myMem);
    exit(127);
    return -1;  
}




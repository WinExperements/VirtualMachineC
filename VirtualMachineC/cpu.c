#include "cpu.h"
#include "port.h"
#include "devs/console.h"
#include<stdio.h>

cpu_t cpu;
void pushC(int);
int popC();

void cpu_init() {
    cpu.sp = 256; // top of memory
    console_add();
}

int fetch() {
   return cpu.memory[cpu.pc++];
}

void cpu_start() {
    cpu.running = 1;
    while(cpu.running) {
        switch(fetch()) {
        case LDR:
            cpu.regs[fetch()] = fetch();
            break;
        case STR:
            cpu.memory[fetch()] = cpu.regs[fetch()];
            break;
        case MOV:
            cpu.memory[fetch()] = cpu.memory[fetch()];
            break;
        case MOVR:
            cpu.regs[fetch()] = cpu.regs[fetch()];
            break;
        case PUSH:
            pushC(cpu.regs[fetch()]);
            break;
        case POP:
            cpu.regs[fetch()] = popC();
            break;
        case ADD: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] + cpu.regs[num2];
            } break;
        case SUB: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] - cpu.regs[num2];
           } break;
        case DIV: {
          int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] / cpu.regs[num2];
        } break;
        case MUL: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] * cpu.regs[num2];
        } break;
        case JMP:
            cpu.pc = cpu.pc + fetch();
            break;
        case CALL:
            cpu.ret = cpu.pc+2;
            cpu.pc = cpu.pc + fetch();
            break;
        case CMP: {
            int cmpVal1 = cpu.regs[fetch()];
            int cmpVal2 = cpu.regs[fetch()];
            if (cmpVal1 == cmpVal2) cpu.eq = 1; else if (cmpVal1 > cmpVal2) cpu.great = 1;
            else if (cmpVal1 < cmpVal2) cpu.less = 1; else if (cmpVal1 >= cmpVal2) {cpu.eq = 1; cpu.great = 1;}
            else if (cmpVal1 <= cmpVal2) {cpu.eq = 1; cpu.less = 1;}
        } break;
        case JEQ:
            if (cpu.eq) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case JNE:
            if (!cpu.eq) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case JG:
            if (cpu.great) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case JNQ:
            if (!cpu.great) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case JLE:
            if (cpu.less) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case JLEQ:
            if (cpu.less || cpu.eq) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case JGQ:
            if (cpu.great || cpu.eq) {
                cpu.pc = cpu.pc+fetch();
            }
            break;
        case INB:
            cpu.regs[fetch()] = port_read(fetch());
            break;
        case OUTB: {
            int data = cpu.regs[fetch()];
            int port = fetch();
            port_write(port,data);
        } break;
        case HLT:
            cpu.running = 0;
            break;
        case ADDI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] + num2;
           } break;
        case SUBI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] - num2;
           } break;
        case DIVI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] / cpu.regs[num2];
           } break;
        case MULI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] * cpu.regs[num2];
           } break;
        case AND: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] & cpu.regs[num2];
           } break;
        case ANDI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] & num2;
           } break;
        case OR: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] | cpu.regs[num2];
           } break;
        case ORI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] & num2;
           } break;
        case XOR: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] ^ cpu.regs[num2];
           } break;
        case XORI: {
            int num = fetch();
            int num1 = fetch();
            int num2 = fetch();
            cpu.regs[num] = cpu.regs[num1] ^ num2;
           } break;
        }
    }
}
cpu_t cpu_getCPU() {
    return cpu;
}
void cpu_dump() {
    printf("Dump:\nPC = %d\nSP = %d\nRET = %d",cpu.pc,cpu.sp,cpu.ret);
    for (int i = 0; i < 10; i++) {
        printf("\nreg%d = %d",i,cpu.regs[i]);
    }
    printf("\nDump of memory: \n");
    for (int m = 0; m < 256; m++) {
        printf("%d ",cpu.memory[m]);
    }
    printf("\n");
}
void cpu_setCPU(cpu_t cput) {
    cpu = cput;
}
void pushC(int data) {
    cpu.memory[cpu.sp] = data;
    cpu.sp = cpu.sp-1;
}
int popC() {
    int curSp = cpu.sp;
    cpu.sp = cpu.sp+1;
    return cpu.memory[curSp+1];
}

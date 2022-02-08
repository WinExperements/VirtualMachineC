#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cpu.h"
#include "devs/console.h"
#include "devs/display.h"

void addPrint(char *,int);
cpu_t cpu;
int prgPointer;

int main(int argc,char *argv[]) {
    cpu_init();
    cpu = cpu_getCPU();
    addPrint("Hello!",6);
    addPrint("\nERROR",7);
    cpu.memory[prgPointer++] = HLT;
    cpu_setCPU(cpu);
    cpu_start();
    if (argc > 1 && !strcmp("--save",argv[1])) {
        FILE *f = fopen("dump.bin","w");
        if (!f) return 1;
        if (fwrite(cpu.memory,sizeof(int),prgPointer-1,f) != prgPointer-1) {fclose(f); return 0;}
        fclose(f);
        printf("\nDump saved!\n");
    }
    return 0;
}
void addPrint(char *msg,int size) {
    cpu.memory[prgPointer++] = LDR;
    cpu.memory[prgPointer++] = 0;
    cpu.memory[prgPointer++] = CONSOLE_START;
    cpu.memory[prgPointer++] = OUTB;
    cpu.memory[prgPointer++] = 0;
    cpu.memory[prgPointer++] = 0;
    for (int i = 0; i < size; i++) {
            cpu.memory[prgPointer++] = LDR;
        cpu.memory[prgPointer++] = 0;
        cpu.memory[prgPointer++] = msg[i];
        cpu.memory[prgPointer++] = OUTB;
        cpu.memory[prgPointer++] = 0;
        cpu.memory[prgPointer++] = 0;
    }
    cpu.memory[prgPointer++] = LDR;
    cpu.memory[prgPointer++] = 0;
    cpu.memory[prgPointer++] = CONSOLE_END;
    cpu.memory[prgPointer++] = OUTB;
    cpu.memory[prgPointer++] = 0;
    cpu.memory[prgPointer++] = 0;
}

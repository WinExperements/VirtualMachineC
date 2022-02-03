#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
int main()
{
    int i = 0;
    cpu_init();
    cpu_t cpu = cpu_getCPU();
    cpu.memory[i++] = LDR;
    cpu.memory[i++] = 0;
    cpu.memory[i++] = 25;
    cpu.memory[i++] = LDR;
    cpu.memory[i++] = 1;
    cpu.memory[i++] = 15;
    cpu.memory[i++] = ADD;
    cpu.memory[i++] = 2;
    cpu.memory[i++] = 0;
    cpu.memory[i++] = 1;
    cpu.memory[i++] = HLT;
    cpu_setCPU(cpu);
    cpu_start();
    cpu_dump();
    getchar();
    return 0;
}

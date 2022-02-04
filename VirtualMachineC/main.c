#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include<string.h>
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
    cpu.memory[i++] = PUSH;
    cpu.memory[i++] = 1;
    cpu.memory[i++] = POP;
    cpu.memory[i++] = 3;
    cpu.memory[i++] = HLT;
    cpu_setCPU(cpu);
    cpu_start();
    cpu_dump();
    getchar();
    printf("Do you want to export current program? Enter Y or N: ");
    char buff[1];
    scanf("%s",buff);
    if (!strcmp("Y",buff) || !strcmp("y",buff)) {
        printf("Saving!\n");
        FILE *f = fopen("prgDump.bin","w");
        if (!f) {
            printf("Save fail: Failed to open file!\n");
            exit(1);
        }
        if (fwrite(cpu.memory,sizeof(int),256,f) != 256) {
            printf("Save fail: Failed to write dump to file!\n");
            exit(1);
        }
        fclose(f);
        printf("Saved!\n");
    } else {
        printf("OK, exit!\n");
    }
    printf("Goodbay!\n");
    return 0;
}

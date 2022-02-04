#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

typedef struct {
    int sp;
    int pc;
    int ret;
    int memory[256];
    int regs[10];
    int running;
} cpu_t;
typedef enum Opcode {
    // == Memory instructions ===
    LDR,
    STR,
    MOV,
    MOVR,
    PUSH,
    POP,
    // == Math and logic ==
    ADD,
    SUB,
    DIV,
    MUL,
    AND,
    OR,
    XOR,
    // jump
    JMP,
    CALL,
    // == if jump ==
    JEQ,
    JNE,
    JG,
    JNQ,
    JLE,
    JNL,
    // == i/o ==
    INB,
    OUTB,
    // == control ==
    HLT
} Opcode;
void cpu_init();
void cpu_start();
void cpu_dump();
cpu_t cpu_getCPU();
void cpu_setCPU(cpu_t);


#endif // CPU_H_INCLUDED

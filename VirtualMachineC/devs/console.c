#include "../port.h"
#include "console.h"
#include<stdio.h>
int writeChar = 0;

void console_add() {
    device_t dev;
    dev.name = "Serial port console";
    dev.write = console_write;
    dev.read = console_read;
    port_addDev(dev);
}
void console_write(int data) {
    if (writeChar) {
        printf("%c",data);
        return;
    }
    if (data == CONSOLE_START) {
        writeChar = 1;
        return;
    }
    if (data == CONSOLE_END) {
        writeChar = 0;
        return;
    }
}
int console_read() {
    char code[1];
    scanf("%c",code);
    return code[0];
}

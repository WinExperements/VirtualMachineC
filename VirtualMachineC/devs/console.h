#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED
#define CONSOLE_START 0x15F
#define CONSOLE_END -1


void console_add();
void console_write(int data);
int console_read();

#endif // CONSOLE_H_INCLUDED

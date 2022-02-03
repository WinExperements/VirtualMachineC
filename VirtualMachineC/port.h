#ifndef PORT_H_INCLUDED
#define PORT_H_INCLUDED

typedef struct {
    int used;
    char *name;
    void (*write)(int);
    int (*read)();
} device_t;
void port_addDev(device_t);
void port_write(int,int);
int port_read(int);

#endif // PORT_H_INCLUDED

#include "port.h"
#include<stdio.h>
device_t devs[25];
int freePort;

void port_addDev(device_t dev) {
    dev.used = 1;
    devs[freePort++] = dev;
}
void port_write(int port,int data) {
    device_t dev = devs[port];
    if (!dev.used) {
        printf("No device with port %d\n",port);
        return;
    }
    dev.write(data);
}
int port_read(int port) {
    device_t dev = devs[port];
    if (!dev.used) {
        printf("No device with port %d\n",port);
        return -1;
    }
    return dev.read();
}

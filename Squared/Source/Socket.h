#ifndef __socket_h
#define __socket_h

#include "board.h"

#define GAMEPORT 12333

void initSockets();
void closeSockets();
void startServer();
void sendData(char* packet);
void clientConnect(char* addr);


#endif
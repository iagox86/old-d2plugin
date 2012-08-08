#pragma once

#include <winsock.h>

// The prototype for this one MUST match the prototype for winsock.send().
int sendData(SOCKET s, const char *buf, int length, int flags);

void leaveGame();
#ifndef __SocketMulticast__
#define __SocketMulticast__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "PaqueteDatagrama.h"
#include <arpa/inet.h>

class SocketMulticast{

public:
    SocketMulticast(int = 0);
    ~SocketMulticast();
    
    int recibe(PaqueteDatagrama & p, char *ipE);
    
    int envia(PaqueteDatagrama & p, unsigned char TTL);

    int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);
private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    struct timeval timeout;
    int s;
};

#endif

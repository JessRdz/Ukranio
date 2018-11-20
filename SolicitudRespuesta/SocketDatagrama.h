#ifndef __SocketDatagrama__
#define __SocketDatagrama__

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

class SocketDatagrama{

public:
    SocketDatagrama(int = 0);
    ~SocketDatagrama();
    
    int recibe(PaqueteDatagrama & p);
    
    int envia(PaqueteDatagrama & p);

    int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);
private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    struct timeval timeout;
    int s;
};

#endif

#include "SocketMulticast.h"


SocketMulticast::SocketMulticast(int puerto)
{
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero((char *)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(puerto);
    bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}

SocketMulticast::~SocketMulticast()
{
    //close(s);
}


int SocketMulticast::recibe(PaqueteDatagrama & p, char *ipE)
{
    struct ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(ipE);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast));

    unsigned int addr_len = sizeof(direccionForanea);
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    int regreso = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);
    
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    //std::cout << "Mensaje recibido de: " << inet_ntoa(direccionForanea.sin_addr) << ":" << ntohs(direccionForanea.sin_port) << std::endl;
    //std::cout << "Puerto: " << p.obtienePuerto() << endl;
    //std::cout << "IP: " << p.obtieneDireccion() << endl;
    return regreso;
}

int SocketMulticast::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos)
{
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;

    unsigned int addr_len = sizeof(direccionForanea);
    bzero((char *)&direccionForanea, sizeof(direccionForanea));

    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    int regreso = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);
    if (regreso < 0) {
        if (errno == EWOULDBLOCK) {
            fprintf(stderr, "Tiempo para recepción transcurrido\n");
            return -1;
        }
        else
            fprintf(stderr, "Error en recvfrom\n");
    }

    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    //std::cout << "Mensaje recibido de: " << inet_ntoa(direccionForanea.sin_addr) << ":" << ntohs(direccionForanea.sin_port) << std::endl;
    //std::cout << "Puerto: " << p.obtienePuerto() << endl;
    //std::cout << "IP: " << p.obtieneDireccion() << endl;
    return regreso;
}


int SocketMulticast::envia(PaqueteDatagrama & p, unsigned char TTL)
{
    setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &TTL, sizeof(TTL));

    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
    
    return sendto(s,p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}



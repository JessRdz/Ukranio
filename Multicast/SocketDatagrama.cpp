#include "SocketDatagrama.h"

SocketDatagrama::SocketDatagrama(int puerto) {
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
	direccionLocal.sin_port = htons(puerto);
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama() {
	close(s);
}	

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
	unsigned int clilen = sizeof(direccionForanea);
	recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0,(struct sockaddr *)&direccionForanea, &clilen);
	p.inicializaPuerto(htons(direccionForanea.sin_port));
	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
	printf("%s: %d \n",p.obtieneDireccion(),p.obtienePuerto());
}

int SocketDatagrama::envia(PaqueteDatagrama &p) {
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());

	sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}
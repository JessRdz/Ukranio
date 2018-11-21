#ifndef _SOCKETDATAGRAMA_H_
#define _SOCKETDATAGRAMA_H_

#include "PaqueteDatagrama.h"
class SocketDatagrama {
	public:
		SocketDatagrama(int);
		~SocketDatagrama();				
		int recibe(PaqueteDatagrama &p);	//Recibe un paquete tipo datagrama proveniente de este socket
		int envia(PaqueteDatagrama &p);		//Envía un paquete tipo datagrama desde este socket
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s; //ID socket
};

#endif
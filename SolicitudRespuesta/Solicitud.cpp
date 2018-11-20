#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud() {
	socketlocal = new SocketDatagrama(0);
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {

	
	struct mensaje msj;
	msj.messageType = 0;

	msj.requestId = id;

	id++;

	memcpy(msj.IP, IP, 16);

	msj.puerto = puerto;
	msj.operationId = operationId;
	memcpy(msj.arguments, arguments, 100);

	//SocketDatagrama socket(puerto);
	PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
	PaqueteDatagrama paq1(sizeof(msj));

	int n = -1;
	int i;
	for (i = 0; i < 7 && n == -1; i++) {
		socketlocal->envia(paq);

		n = socketlocal->recibeTimeout(paq1,0,50000);
	}

	if (i == 7) {
		cout << "Servidor no disponible, intente más tarde..." << endl;
		return NULL;
	}

	char* resultado;
	resultado = paq1.obtieneDatos();
	
	return resultado;
}
#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl) {

	socketlocal = new SocketDatagrama(pl);

}

struct mensaje* Respuesta::getRequest() {

	struct mensaje *palabras;
	PaqueteDatagrama paq(sizeof(mensaje));
	socketlocal->recibe(paq);
	palabras = (struct mensaje*) paq.obtieneDatos();
	palabras->puerto = paq.obtienePuerto();
	memcpy(palabras->IP, paq.obtieneDireccion());
	
	return palabras;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {

	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	PaqueteDatagrama paq((char*) m1, 100, ipCliente, puertoCliente);
	socketlocal->envia(paq);

}
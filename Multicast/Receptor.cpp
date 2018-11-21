#include "SocketMulticast.h"
#include <pthread.h>
using namespace std;

int main(int argc, char *argv[]) {
	char ip[16];
	unsigned int numero[2]; 
	int res = 0;

	strcpy(ip,argv[1]);
	int puerto = atoi(argv[2]);
	
	SocketMulticast sd(puerto);
	PaqueteDatagrama p(2 * sizeof(unsigned int));
	while(1) {
		cout << "Escuchando..." << endl;
		sd.recibe(p, ip);

		unsigned int datos[2];
		memcpy(datos,(unsigned int *)p.obtieneDatos(), 2*sizeof(unsigned int));
		cout << "Se recibio: " << datos[0] << " y " << datos[1] << endl;

	}


	return 0;
}
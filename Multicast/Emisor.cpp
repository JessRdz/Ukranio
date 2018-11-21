#include "SocketMulticast.h"
#include <pthread.h>
using namespace std;

int main(int argc, char *argv[]) {
	char ip[16];
	unsigned int numero[2]; 
	int res = 0;

	strcpy(ip,argv[1]);
	int puerto = atoi(argv[2]);
	int TTL = atoi(argv[3]);

	numero[0] = 1;
	numero[1] = 3;

	PaqueteDatagrama p1((char *)numero,2*sizeof(unsigned int),ip,puerto);

	SocketMulticast sd(puerto);
	sd.envia(p1, TTL);

	


	return 0;
}
#include "Solicitud.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char*argv[]) {

	char *ip;
	int puerto;
	int operacion = 1;
	int n;

	ip =argv[1];
	puerto = atoi(argv[2]);

	cout << "Ingresa el valor de n: ";
	cin >> n;

	char argumentos[100];
	int deposito = 1;
	int dinero;
	*((int *)argumentos) = deposito;
	char *res;
	int dineroCuenta = 0; 

	Solicitud cliente;
	for (int i = 0; i < n; i++) {
		res = cliente.doOperation(ip, puerto, 1, argumentos);
		if (res != NULL) {
			dinero = *((int *)res);
			cout << "Dinero en la cuenta: $" << dinero << endl;
			if (dinero != dineroCuenta) {
				cout << "Inconsistencia de dinero en la cuenta." << endl;
				break;
			}
		}
		else {
				cout << "Dinero "  << endl;
			break;
		}

		res = cliente.doOperation(ip, puerto, 2, argumentos);
		if (res != NULL) {
			dinero = *((int *)res);
			dineroCuenta++;
			cout << "Deposito realizado, nuevo saldo: $" << dinero << endl;
			if (dinero != dineroCuenta) {
				cout << "Inconsistencia, se perdió algún depósito." << endl;
				break;
			}
		}
		else {
			
			break;
		}

	}
	

	return 0;
}
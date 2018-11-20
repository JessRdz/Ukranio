#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <thread>
#include <atomic>
#include <mutex>
using namespace std;

int variable = 0;
atomic<int> global(0);
mutex m;

void funcion(int valor) {

	printf("Hilo %ld Valor recibido: %d\n", this_thread::get_id(), valor);
	sleep(2);
}

void funcion1(int valor, atomic<int>& variable) {
	for (int i = 0; i < valor; i++)
		global++;
	sleep(1);
}

void funcion2(int valor, atomic<int>& variable) {
	for (int i = 0; i < valor; i++)
		global--;
	sleep(1);
}

int main() {

	thread th1(funcion1, 1000, ref(global)), th2(funcion2,1000, ref(global));
	printf("Proceso principal espera que los hilos terminen\n");

	th1.join();
	th2.join();
	cout << "El hilo principal termina: " << global << endl;
	exit(0);
}

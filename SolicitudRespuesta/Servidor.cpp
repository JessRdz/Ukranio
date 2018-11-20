#include <cstdlib>
#include <string>
#include "Respuesta.h"

using namespace std;


int main() {

  Respuesta respuesta(7200);
  int nbd = 0;
  
  cout << "Servidor iniciado correctamente : " << endl;
  while(1) {
    struct mensaje msj;
    struct mensaje m1;
    //msj = respuesta.getRequest();
    memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
    
    switch(msj.operationId) {
      case 1:
        
        memcpy(m1.arguments, (char *)&nbd, sizeof(int));
       
        m1.messageType = 1;
        memcpy(m1.IP, msj.IP, 16);//------------------
        
        m1.puerto = msj.puerto;
        m1.requestId = msj.requestId;

        respuesta.sendReply((char*) m1.arguments,&msj.IP[0], msj.puerto);
        cout << "Consulta de saldo: " << nbd << endl;
        break;

      case 2:
        nbd += *((int*)msj.arguments);
        memcpy(m1.arguments, (char *)&nbd, sizeof(int));
       
        m1.messageType = 1;
        memcpy(m1.IP, msj.IP, 16);//------------------
        
        m1.puerto = msj.puerto;
        m1.requestId = msj.requestId;
        
        respuesta.sendReply((char*) m1.arguments,&msj.IP[0], msj.puerto);
        cout << "Deposito: " << *((int*)msj.arguments) << endl << endl;
        break;

      default:
        cout << "Error en el numero de operación" << endl;
        cout << "numero: " << msj.operationId << endl;
        exit(-1);
    }
  }
  

  return 0;
}
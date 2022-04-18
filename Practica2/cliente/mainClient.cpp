#include <iostream>
#include "filemanager_stub.h"
#include "clientConn.h"
#include <cstring>
// Juan Pedrajas y Alvaro Garcia

int main(int argc,char** argv)
{
  filemanager_stub *fm=new filemanager_stub("./targetPath");
  ClientConn* conn = new ClientConn(fm);

  string comando;
  string fichero;

  do{
    std::cout <<  '\n';
    std::cout << "Bienvenido al servidor de ficheros:" << '\n';
    std::cout << "list files ( muestra ficheros )" << '\n';
    std::cout << "download ( descarga un fichero )" << '\n';
    std::cout << "exit now ( salir del programa )" << '\n';

    std::cin >> comando >> fichero;

    std::cout << comando << " " << fichero << '\n';


    if(strcmp(comando.c_str(),"download") == 0){

      char* ficheroProcesado = new char[strlen(fichero.c_str()) + 1];
      memcpy(ficheroProcesado,fichero.c_str(),strlen(fichero.c_str()) + 1);

      conn->download(ficheroProcesado);

      delete ficheroProcesado;

    } else if(strcmp(comando.c_str(),"upload") == 0){
      char* ficheroProcesado = new char[strlen(fichero.c_str()) + 1];
      memcpy(ficheroProcesado,fichero.c_str(),strlen(fichero.c_str()) + 1);

      conn->upload(ficheroProcesado);

      delete ficheroProcesado;
    } else if(strcmp(comando.c_str(),"list") == 0){
      conn->listFiles();
    }

  }while (strcmp(comando.c_str(),"exit") != 0);

  delete conn;

  delete fm;

  return 0;
}

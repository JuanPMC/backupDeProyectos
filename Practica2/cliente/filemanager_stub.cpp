#include "filemanager_stub.h"
/**
 * @brief filemanager_stub::filemanager_stub Constructor de la clase filemanager_stub. Recibe por parámetros el directorio
 * que usará esta clase para indexar, almacenar y leer ficheros. Se aconseja usar una ruta completa al directorio,
 * desde la raiz del sistema de ficheros.
 *
 * @param path Ruta al directorio que se desa usar
 */
 // Juan Pedrajas y Alvaro Garcia

#define OP_LIST 'L'
#define OP_WRITE 'W'
#define OP_READ 'R'
#define OP_EXIT 'X'
#define OP_OK 'O'

filemanager_stub::filemanager_stub(string path)
{
  int dataLen = 0;
  char* ip = new char[strlen(IP_SERVER) + 1];
  memcpy(ip,IP_SERVER,strlen(IP_SERVER) + 1);
  std::cout<<"Iniciando cliente\n";
  this->serverId = initClient(ip,PORT_SERVER);

  // control de errores
  if(this->serverId == -1){
    std::cout<<"No se encuentra el servidor: Fichero "<< __FILE__ << " Line: " << __LINE__ <<"\n";
  }else{
    std::cout<<"Iniciado\n";
    // enviar nombre de directorio
    const char* nombreOriginal = path.c_str();
    char* directorio = new char[strlen(nombreOriginal) + 1]; // copiar el \0
    memcpy(directorio,nombreOriginal,strlen(nombreOriginal) + 1);

    sendMSG(this->serverId,(void*)directorio,strlen(directorio) + 1);

    delete directorio;
  }
}

filemanager_stub::~filemanager_stub()
{
  std::cout << "cerrando conn" << '\n';
  char msg = OP_EXIT;
  char* buffer = nullptr;
  int dataLen = 0;
  char state = 0;

  // enviar mesaje de terminar
  sendMSG(this->serverId,(void*)&msg,sizeof(char));
  // para completar
  recvMSG(this->serverId,(void**)&buffer,&dataLen);

  state = buffer[0];

  if(state!=OP_OK){
    std::cout << "ERROR cerando conexion" << '\n';
  }
  delete buffer;
}

/**
 * @brief filemanager_stub::listFiles Sirve para acceder a la lista de ficheros almacenados en la ruta
 * que se usó en el contructor de la clase
 * @return Una copia de la lista de ficheros almacenada en "files". Esta copia hay que liberarla
 * después de haber sido usada. Para ello se ofrece la función "freeListedFiles"
 */
vector<string*>* filemanager_stub::listFiles(){
  vector<string*>* flist=new vector<string*>();
  char msg = OP_LIST;
  char* buffer = nullptr;
  int tamanioVector = 0;
  int dataLen = 0;

  // enviar mesaje de operacion
  sendMSG(this->serverId,(void*)&msg,sizeof(char));

  // recivir tamanio
  recvMSG(this->serverId,(void**)&buffer,&dataLen);
  memcpy(&tamanioVector,buffer,sizeof(int));
  delete buffer;

  // loop recivir el vector
  for(int i = 0;i < tamanioVector; i++){
    recvMSG(this->serverId,(void**)&buffer,&dataLen);
    flist->push_back(new string(buffer));
    delete buffer;
  }

  return flist;
}
/**
 * @brief filemanager_stub::freeListedFiles Función de apoyo, libera una lista de ficheros devuelta por la función "listFiles"
 * @param fileList Puntero a una lista de strings devuelta por la función "listFiles"
 */
void filemanager_stub::freeListedFiles(vector<string*>* fileList)
{
  for(vector<string*>::iterator i=fileList->begin();i!= fileList->end();++i)
  {
      delete *i;
  }
  delete fileList;
}
/**
 * @brief filemanager_stub::readFile Dado el nombre de un fichero almacenado en el directorio que se usó en el contructor,
 * se inicializará la variable "data" con un puntero al contenido del fichero, y la variable dataLength con el
 * tamaño del mismo en bytes.
 *
 * @param fileName Nombre del fichero a leer
 * @param data Datos del fichero. Deberá de liberarse después de ser usado
 * @param dataLength Longitud del fichero en bytes
 */

void filemanager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength)
{
  char msg = OP_READ;
  char* buffer = nullptr;
  int dataLen = 0;
  unsigned long int *dataLengthTemp = nullptr;

  std::cout << "filename in stub: "<< fileName << '\n';

  // enviar codigo de operacion
  sendMSG(this->serverId,(void*)&msg,sizeof(char));

  // enviar nombre de ficheros
  sendMSG(this->serverId,(void*)fileName,strlen(fileName) + 1); // +1 pra contar el \0

  // Esperar a recivir respuesta dataLength
  recvMSG(this->serverId,(void**)&dataLengthTemp,&dataLen);
  dataLength = *dataLengthTemp;
  delete dataLengthTemp;
  // Esperar a recivir respuesta data
  recvMSG(this->serverId,(void**)&buffer,&dataLen);
  data = new char[dataLen];
  memcpy(data,buffer,dataLen);

  delete buffer;
}


/**
 * @brief filemanager_stub::readFile Dado un nuevo nombre de un fichero que se quiere almacenar  en el directorio que se usó en el contructor,
 * se escribirá el contenido del array de datos almacenado en "data", siendo dataLength el
 * tamaño del mismo en bytes. Sobreescribirá el fichero que hubiera en el directorio si tiene el mismo nombre.
 *
 * @param fileName Nombre del fichero a escribir
 * @param data Datos del fichero. Deberá de liberarse después de ser usado
 * @param dataLength Longitud del fichero en bytes
 */

void filemanager_stub::writeFile(char* fileName, char* &data, unsigned long int dataLength)
{
  char msg = OP_WRITE;
  char* buffer = nullptr;
  int dataLen = 0;

  // enviar codigo de operacion
  sendMSG(this->serverId,(void*)&msg,sizeof(char));

  // enviar nombre de ficheros
  sendMSG(this->serverId,(void*)fileName,strlen(fileName) + 1); // +1 pra contar el \0

  // enviar DATOS y dataLen
  sendMSG(this->serverId,(void*)data,dataLength);

  // recivir confirmacion
  recvMSG(this->serverId,(void**)&buffer,&dataLen);

  msg = buffer[0];

  if(msg!=OP_OK){
    std::cout << "ERROR cerando conexion" << '\n';
  }
  delete buffer;

}

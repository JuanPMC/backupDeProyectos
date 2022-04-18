#include "clientConn.h"
// Juan Pedrajas y Alvaro Garcia
ClientConn::ClientConn(filemanager_stub* fmStub){
  this->fmStub = fmStub;
  this->fm = new FileManager("./");
}

ClientConn::~ClientConn(){
  delete fm;
}

void ClientConn::upload(char* fileName){
  char* data = nullptr;
  unsigned long int dataLen = 0;

  fm->readFile(fileName,data,dataLen);

  fmStub->writeFile(fileName,data,dataLen);

  delete data;
}

void ClientConn::download(char* fileName){
  char* data = nullptr;
  unsigned long int dataLen = 0;
  fmStub->readFile(fileName,data,dataLen);
  //printf("La data en conn : %i\n", strlen(data));
  fm->writeFile(fileName,data,dataLen);

  delete data;
}

void ClientConn::listFiles(){
  vector<string*>* vfiles=fmStub->listFiles();
  for(unsigned int i=0;i<vfiles->size();++i)
  {
      cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;
  }
}

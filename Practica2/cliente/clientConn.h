#include "filemanager.h"
#include "filemanager_stub.h"
// Juan Pedrajas y Alvaro Garcia
class ClientConn
{
    filemanager_stub* fmStub = nullptr;
    FileManager* fm = nullptr;
public:
    ClientConn(filemanager_stub *fmStub);
    ~ClientConn();
    void upload(char* fileName);
    void download(char* fileName);
    void listFiles();
};

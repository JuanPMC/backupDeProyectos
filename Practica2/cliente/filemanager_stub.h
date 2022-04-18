#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <dirent.h>
// Juan Pedrajas y Alvaro Garcia

// Cliente
#include "utils.h"

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 31001

using namespace std;

class filemanager_stub
{
    int serverId = 0;
public:
    filemanager_stub(string path);
    ~filemanager_stub();
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int & dataLength);
    void writeFile(char* fileName, char* &data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
};

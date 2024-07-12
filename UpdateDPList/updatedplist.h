#ifndef UPDATEDPLIST_H
#define UPDATEDPLIST_H

#include <stdio.h>
#include <stdarg.h>
#include <utility>
#include <time.h>

#include <nlohmann/json.hpp>

#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;

//#define MZ_DP_FILEPATH "/ccOSSecureData/VR/LPTE/WORKPLACE/KOK"
#define MZ_DP_FILEPATH "/home/sojung/UpdateDPList/DP_DYNAMIC_LIST.txt"

class UpdateDPList
{
public:
    UpdateDPList() = default;

    ~UpdateDPList() {
        close();
    }

    bool open(std::string filePath);

    void write(const string str);

    void read();

    void close();   

    void confiugureFileInfo(string targetPath);

    string getSerializeInfo();

    int getDPListCount();

    void addPhoneDevice(const string ctxNum, const string deviceName, int single, int fullFirst, int reverseLast);

    void addNormalDevice(const string deviceName);

    void removeDevice(string deviceName);
private:
    bool writeStarted = false;
    ofstream fileStream;

    string fileVersion;
    string filePath;
    string language;
    string ctxName;
    string serializeInfo;
};

#endif // UPDATEDPLIST_H

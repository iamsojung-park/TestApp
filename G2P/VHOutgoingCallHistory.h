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
#define OUTGOING_CALLHISTORY_FILEPATH "/home/sojung/Shared/TestCode/G2P/OutGoingCallHistory.txt"

class VHOutgoingCallHistory
{
public:
    VHOutgoingCallHistory() = default;
    ~VHOutgoingCallHistory() {
        close();
    }

    void confiugureFileInfo(string version, string macAddress);
    string getSerializeInfo();

    void setVersion(const string version);
    string getVersion();

    void setMacAddress(const string macAddress);
    string getMacAddress();

    void addOutGoingCallHistoryMap(const std::map<std::string, std::string>);
    std::map<std::string, std::string> getOutgoingCallHistory();
    void removeFile(string deviceName);

private:
    bool open(std::string filePath);
    void write(const string str);
    void write();
    std::string read();
    void close();

private:
    bool writeStarted = false;
    ofstream fileStream;
    string mVersion;
    string mMacAddress;
    std::map<std::string, std::string> mOutgoingCallHistorty;
};

#endif // UPDATEDPLIST_H

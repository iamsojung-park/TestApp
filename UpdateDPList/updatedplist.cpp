#include "updatedplist.h"

bool UpdateDPList::open(std::string filePath) {
    try {
        filePath = filePath;
        fileStream.open(filePath, std::ofstream::binary);
        writeStarted = true;
    } catch (const std::ofstream::failure &writeErr) {
        writeStarted = false;
    } catch (const std::exception& e) {

    } catch (...) {

    }
    return writeStarted;
}

void UpdateDPList::write(const string str) {
    try {
        string dpinfo = str;
        fileStream << dpinfo << endl;
    } catch (const std::ofstream::failure &writeErr) {
        writeStarted = false;
        fileStream.close();
    }
}

void UpdateDPList::close() {
    if(writeStarted) {
        fileStream.flush();
        fileStream.close();
        writeStarted = false;
    }
}

void UpdateDPList::read() {
    ifstream ifDpInfo;
    string filePath = MZ_DP_FILEPATH;

    ifDpInfo.open(filePath.c_str(), ios::binary);
    if(ifDpInfo){
        string serialize;
        std::getline(ifDpInfo, serialize);
        std::cout << serialize << endl;
        ifDpInfo.close();
    }else{
        std::cout << "File is not Exist" << endl;
    }
}

void UpdateDPList::confiugureFileInfo(string targetPath) {
    json fileInfo;
    fileInfo["version"] = "00";
    fileInfo["filePath"] = targetPath;  /* /ccOSSecureData/VR/LPTE/WORKPLACE/KOK */
    fileInfo["language"] = "KOK";
    this->serializeInfo = fileInfo.dump();
}

string UpdateDPList::getSerializeInfo() {
    return this->serializeInfo;
}

int UpdateDPList::getDPListCount() {
    json DPInfo;
    int dpCount = -1;
    try {
        DPInfo = json::parse(this->serializeInfo);
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
        return dpCount;
    }

    if(!DPInfo["DP_LIST"].is_null()) {
       dpCount = DPInfo["DP_LIST"].size();

       std::cout << "getDPListCount : " << dpCount << endl;

       for(int i=0; i<dpCount; i++) {
           std::cout << DPInfo["DP_LIST"].at(i).dump() << endl;
       }

       return dpCount;
    }
}

void UpdateDPList::addPhoneDevice(string ctxNum, const string deviceName, int single, int fullFirst, int reverseLast) {
    json serialize, BTinfo;

    try {
        serialize = json::parse(this->serializeInfo);
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
        return;
    }

    BTinfo["ctxNum"] = ctxNum;
    BTinfo["deviceName"] = deviceName;
    BTinfo["singleCount"] = single;
    BTinfo["fullFirstCount"] = fullFirst;
    BTinfo["reverseLastCount"] = reverseLast;

    serialize["DP_LIST"] += BTinfo;

    this->serializeInfo = serialize.dump();
}

void UpdateDPList::addNormalDevice(string deviceName) {
    json serialize, Normalinfo;

    try {
        serialize = json::parse(this->serializeInfo);
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
        return;
    }

    Normalinfo["deviceName"] = deviceName;
    serialize["DP_LIST"] += Normalinfo;

    this->serializeInfo = serialize.dump();
}

void UpdateDPList::removeDevice(string deviceName){

}


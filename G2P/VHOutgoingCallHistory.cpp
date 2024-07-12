#include "VHOutgoingCallHistory.h"

bool VHOutgoingCallHistory::open(std::string filePath) {
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

void VHOutgoingCallHistory::write() {
    std::cout << "****** write File START ******" << std::endl;
    try {
        nlohmann::json outGoingList, temp;
        outGoingList["Version"] = mVersion;
        outGoingList["macAddress"] = mMacAddress;
        auto it = mOutgoingCallHistorty.begin();
        while(it != mOutgoingCallHistorty.end()) {
            cout << "name : " << (*it).first << "   phonenumber : "<< (*it).second << std::endl;
            temp.clear();
            temp["formattedName"] = (*it).first;
            temp["PhoneNumber"] = (*it).second;
            outGoingList["OutgoingCallHistory"] += temp;
            ++it;
        }
        fileStream << outGoingList.dump(2) << endl;
        std::cout << "write : " << outGoingList.dump(2) << std::endl;
    } catch (const std::ofstream::failure &writeErr) {
        writeStarted = false;
        fileStream.close();
    }
    std::cout << "****** write File END  ******" << std::endl;
}

void VHOutgoingCallHistory::write(const string str) {
    std::cout << "****** write File ******" << std::endl;
    try {
        string dpinfo = str;
        fileStream << dpinfo << endl;
    } catch (const std::ofstream::failure &writeErr) {
        writeStarted = false;
        fileStream.close();
    }
}

void VHOutgoingCallHistory::close() {
    if(writeStarted) {
        fileStream.flush();
        fileStream.close();
        writeStarted = false;
    }
}

std::string VHOutgoingCallHistory::read() {
    ifstream ifDpInfo;
    string filePath = OUTGOING_CALLHISTORY_FILEPATH;
    string callhistoryList = "";
    ifDpInfo.open(filePath.c_str(), ios::binary);
    if(ifDpInfo.good()) {
        //std::cout << "****** Read File START ******" << std::endl;
        while(!ifDpInfo.eof()){
            string serialize;
            std::getline(ifDpInfo, serialize);
            callhistoryList += serialize;
        }
        //std::cout << callhistoryList << endl;
        ifDpInfo.close();
        //std::cout << "****** Read File END ******" << std::endl;
    }
    else {
        std::cout << "File is not Exist" << endl;
    }
    return callhistoryList;
}

void VHOutgoingCallHistory::confiugureFileInfo(string version, string macAddress) {
    json fileInfo;
    fileInfo["Version"] = "20230712";
    this->mVersion = version;
    this->mMacAddress = macAddress;
}

void VHOutgoingCallHistory::setVersion(const string version)
{
    this->mVersion = version;
}

string VHOutgoingCallHistory::getVersion()
{
    //return this->mVersion;
    std::string history = read();
    json readData;
    std::map<string, string> historyMap;
    std::string version;
    try {
        readData = json::parse(history);
        if(!readData.is_null()) {
            version = readData["Version"].get<std::string>();
            std::cout << "version : " << version << std::endl;
        }
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
    }
    return version;
}

void VHOutgoingCallHistory::setMacAddress(const string macAddress)
{
    this->mMacAddress = macAddress;
}

string VHOutgoingCallHistory::getMacAddress()
{
    std::string history = read();
    json readData;
    std::map<string, string> historyMap;
    std::string macAddress;
    try {
        readData = json::parse(history);
        if(!readData.is_null()) {
            macAddress = readData["macAddress"].get<std::string>();
            std::cout << "macAddress : " << macAddress << std::endl;
        }
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
    }
    return macAddress;
}

void VHOutgoingCallHistory::addOutGoingCallHistoryMap(const std::map<std::string, std::string> history)
{
    std::cout << "addOutGoingCallHistoryMap" << endl;
    this->mOutgoingCallHistorty = history;
    open(OUTGOING_CALLHISTORY_FILEPATH);
    write();
    close();
//    auto iter = mOutgoingCallHistorty.begin();
//    while(iter != mOutgoingCallHistorty.end()) {
//        cout << "name : " << (*iter).first << " number : " << (*iter).second << std::endl;
//        ++iter;
//    }
}

std::map<string, string> VHOutgoingCallHistory::getOutgoingCallHistory()
{
    std::string history = read();
    json readData;
    std::map<string, string> historyMap;

    try {
        readData = json::parse(history);
        if(readData.is_object()) {
            json callHistory = readData["OutgoingCallHistory"].get<json>();
            std::cout << "object size : " << callHistory.size() << std::endl;
            for(int i=0; i < callHistory.size(); i++) {
                //std::string key = callHistory.at(i).begin().key();
                //std::string value = callHistory.at(i).begin().value();
                std::string key = callHistory.at(i)["formattedName"].get<string>();
                std::string value = callHistory.at(i)["PhoneNumber"].get<string>();
                std::cout << "formattedName : " << key <<"  PhoneNumber : " << value << std::endl;
                historyMap.insert(std::make_pair(key, value));
            }
        }
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
    }
    return historyMap;
}

void VHOutgoingCallHistory::removeFile(string deviceName){

}


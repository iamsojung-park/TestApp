#include "VHOchData.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "VHLog.h"

using json = nlohmann::json;

VHOchData::VHOchData()
{

}

void VHOchData::addOch(std::string name, std::string timestamp)
{
    // 맵에 새로운 쌍을 추가한다. 중복 이름이 있는 경우 최신 timestamp로 대체된다
    ochs[name] = timestamp;
    // 맵의 크기가 10보다 크면
    if (ochs.size() > 10) {
        // 가장 오래된 쌍을 찾는다
        auto oldOch = ochs.begin();
        for(auto iter = ochs.begin(); iter != ochs.end() ; iter++) {
            if(oldOch->second.compare(iter->second) < 0) {
                oldOch = iter;
            }
        }
        // 가장 오래된 쌍을 삭제한다
        ochs.erase(oldOch);
    }
}

// OchManager의 내용을 출력하는 메소드
void VHOchData::printOch() {
    std::cout << "VHOchData contains " << ochs.size() << " pairs:\n"; // 맵의 크기 출력
    for (auto& och : ochs) { // 맵의 각 쌍에 대해
        std::cout << och.first << " : " << och.second << "\n"; // 이름과 타임스탬프 출력
    }
    std::cout << std::endl;
}

void VHOchData::saveToJson()
{
    std::ofstream file("/home/youngsam/work/och.json");
    try {
        json jsonEntries;
        jsonEntries["Version"] = "versionStr";
        jsonEntries["macAddress"] = "1122334455";

        jsonEntries["OutgoingCallHistory"] = ochs;
        file << jsonEntries.dump(4, ' ');
        VHLog::debug(QString("SaveToJson %1").arg(QString::fromStdString(jsonEntries.dump(2))));
    } catch (const std::ofstream::failure &e) {
        VHLog::debug(QString("nlohmann writeErr %1").arg(QString::fromStdString(e.what())));
    }
}

void VHOchData::loadFromJson(const QString &macAddress)
{
//    if (isExistOchJsonFile(macAddress) == false) {
//        return;
//    }

//    std::ifstream fileInfo;
//    fileInfo.open(mFilePath.toStdString(), std::ios::binary);
//    QString callhistoryList;
//    if (fileInfo.good()) {
//        while (!fileInfo.eof()) {
//            std::string serialize;
//            std::getline(fileInfo, serialize);
//            callhistoryList += QString::fromStdString(serialize);
//        }
//        fileInfo.close();
//    } else {
//        VHLog::debug("outgoing callhistory file cannot open..");
//    }

//    if (callhistoryList.isEmpty() == false) {
//        try {
//            nlohmann::json readData;
//            readData = json::parse(callhistoryList.toStdString());
//            if (readData.is_null() == false && readData.contains("OutgoingCallHistory")) {
//                mSavedOchEntries.clear();
//                for (const auto &entry : readData["OutgoingCallHistory"]) {
//                    for (auto it = entry.begin(); it != entry.end(); ++it) {
//                        if (it->is_string()) {
//                            QString key = QString::fromStdString(it.key());
//                            QString value = QString::fromStdString(it.value());
//                            VHLog::debug(QString("[loadFromJson] name(%1) timestamp(%2)").arg(key).arg(value));
//                            mSavedOchEntries.append(qMakePair(key, value));
//                        }
//                    }
//                }
//            }
//        } catch (nlohmann::detail::parse_error &e) {
//            VHLog::debug(QString("nlohmann parse_error : %1").arg(e.what()));
//        }
//    }
}

#ifndef VHOCHDATA_H
#define VHOCHDATA_H

#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <QObject>

class VHOchData
{
private:
    std::map<std::string, std::string> ochs; // 이름과 타임스탬프 쌍을 저장할 맵
public:
    VHOchData();
    void addOch(std::string, std::string);


    void printOch();
    void saveToJson();
    void loadFromJson(const QString &macAddress);
};

#endif // VHOCHDATA_H

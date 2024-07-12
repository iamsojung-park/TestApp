#include <QCoreApplication>
#include "updatedplist.h"
#include "DPListManager.h"

void UnitTest();

UpdateDPList dpList;

void ParseDP() {
    json DPInfo;
    string lineString = "{\"USER_CTX\":[\"SLOT_SETTINGS\", \"SLOT_STATIONS\",\"SLOT_SETTINGS\", \"SLOT_STATIONS\"]}";
    //string lineString = "{\"BT_CTX\" : \"01\",\"device\" : \"74:9E:F5:9B:75:2E\",\"single\" : 277,\"fullFirst\" : 0 ,\"reverseLast\" : 19}";

    try {
        DPInfo = json::parse(lineString);
    }
    catch (nlohmann::detail::parse_error e) {
        std::cout << "Parse_error :  " << e.what() << endl;
        return;
    }

    if(!DPInfo["BT_CTX"].is_null()) {
        if(!DPInfo["device"].is_null() && !DPInfo["device"].empty()) {

            char device[256];
            int singleCount = 0;
            int fullFirstCount = 0;
            int reverseLastCount = 0;

            strcpy(device, DPInfo["device"].get<std::string>().c_str());
            singleCount = DPInfo["single"].get<int>();
            fullFirstCount = DPInfo["fullFirst"].get<int>();
            reverseLastCount = DPInfo["reverseLast"].get<int>();

            string ctx = DPInfo["BT_CTX"].get<std::string>();
            std::cout << "=== <BT INFO> ===" << endl;
            std::cout << "BT_CTX " << ctx << endl;
            std::cout << "device " << device << endl;
            std::cout << "single " << singleCount << endl;
            std::cout << "fullFirst " << fullFirstCount << endl;
            std::cout << "reverseLast " << reverseLastCount << endl;
            std::cout << "=============" << endl;

        }
    } else {
         if(!DPInfo["USER_CTX"].is_null()) {
            int dpCount = DPInfo["USER_CTX"].size();
            std::cout << "=== <USER DP INFO> ===" << endl;
            std::cout << "dpCount : " << dpCount << endl;

            for(int i=0; i<dpCount; i++) {
                std::cout << DPInfo["USER_CTX"].at(i).dump() << endl;
            }

            std::cout << "================" << endl;
         }
    }
}

void unitTest_PSJ() {
    //ParseDP();

    /**************** DP File write ****************/
    dpList.confiugureFileInfo(MZ_DP_FILEPATH);


    /**************** Add Device  ****************/
    dpList.addPhoneDevice("01", "77::ed::e7::ff", 10, 4, 250);
    dpList.addNormalDevice("SLOT_SETTINGS");
    dpList.addPhoneDevice("02", "ff:09::e7::3e ", 17, 300, 9);
    dpList.addNormalDevice("NAVI_PRESET");


    /**************** Get DP Count  ****************/
    std::cout << "****** Get DP Count ******" << std::endl;
    dpList.getDPListCount();


    /**************** Write DP File  ****************/
    dpList.open(MZ_DP_FILEPATH);
    dpList.write(dpList.getSerializeInfo());
    dpList.close();

    std::cout << std::endl;


    /**************** Read DP File  ****************/
    std::cout << "****** Read DP File ******" << std::endl;
    dpList.read();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //unitTest_PSJ();

    UnitTest();

    return a.exec();
}

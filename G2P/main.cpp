#include <QCoreApplication>
#include "VHOutgoingCallHistory.h"

VHOutgoingCallHistory outgoingCallHistory;

void OutGoingCallHistoryTest()
{
    std::map<std::string, std::string> testName;
    testName.insert(std::make_pair("aaa", "111"));
    testName.insert(std::make_pair("bbb", "222"));
    testName.insert(std::make_pair("ccc", "333"));
    testName.insert(std::make_pair("ddd", "444"));
    testName.insert(std::make_pair("eee", "555"));
    testName.insert(std::make_pair("fff", "666"));

    /**************** DP File write ****************/
    outgoingCallHistory.confiugureFileInfo("v1.0.0", "ABC123S1");


    /**************** add OutgoingCallHistory  ****************/
    outgoingCallHistory.addOutGoingCallHistoryMap(testName);

    std::cout << std::endl;

    /**************** Get CallHistory Map  ****************/
    std::map<std::string, std::string> value = outgoingCallHistory.getOutgoingCallHistory();
    outgoingCallHistory.getVersion();
    outgoingCallHistory.getMacAddress();
}

int main(int argc, char *argv[])
{
    OutGoingCallHistoryTest();
    return 0;
}

#include "CallHistoryManager.h"

using namespace std;
using namespace mediazen::dialog::dataManager;
using json = nlohmann::json;

set<string> ctxNameList;

FileDescriptor::FileDescriptor(const json &in)
{
    FileDescriptor::getValueFromJson(in);
}

json FileDescriptor::makeJson()
{
    json retJson;
    retJson[OUTGOINGCALLNAME] = getOutgoingCallName();
    return retJson;
}

void FileDescriptor::getValueFromJson(const json &in)
{
    std::cout << "getValueFromJson::getValueFromJson() start" << std::endl;
    // special iterator member functions for objects
    for (auto it = in.begin(); it != in.end(); ++it) {
        if(it.key() == OUTGOINGCALLNAME) {
            setOutgoingCallName(it.value());
        } else {

        }
    }
}

DPListManager::DPListManager()
{

}

DPListManager::~DPListManager()
{
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        delete *it;
        it ++;
    }
}

bool DPListManager::makeJson(json& _json)
{
    _json[VERSION]   = getVersion();
    _json[LANGUAGE]  = getLanguage();

    if(mCallName.size() > 0){
        json dpList;
        auto it = mCallName.begin();
        while(it != mCallName.end() ) {
            //dpList += (*it)->makeJson();
            _json[OUTGOINGCALLNAME] = (*it);
            ++it;
        }
        //_json["DP_LIST"] = dpList;
    }
    return true;
}


void DPListManager::dpFileRead(const string &filePath)
{
    bool retVal = false;
    ifstream ifs;
    json dpListFile;
    string text, dpinfo;

    ifs.open(filePath, ios::binary);

    if(ifs.good()) {
        while(!ifs.eof()) {
            text.clear();
            getline(ifs, text);
            dpinfo+=text;
        }
        ifs.close();

        if(!dpinfo.empty()) {
            try {
                dpListFile = json::parse(dpinfo);

                setVersion(dpListFile[VERSION]);
                setLanguage(dpListFile[LANGUAGE]);

                json dpList = dpListFile["DP_LIST"];

                if(!dpList.is_null()) {
                    for (json::iterator it = dpList.begin(); it != dpList.end(); ++it) {
                        std::cout << "DPListManager: " << (*it).dump().c_str()  << std::endl;
                        std::cout << "================================================" << std::endl;
//                        DPType dft = static_cast<DPType>((*it)["type"]);
//                        FileDescriptor *dpfd = nullptr;
//                        if(dft == DPType::NORMAL) {
//                            dpfd = new FileDescriptor(*it);
//                        } else if(dft == DPType::BLUETOOTH) {
//                            dpfd = new FileDescriptorForBT(*it);
//                        } else {
//                            //
//                        }

//                        if(dpfd != nullptr) {
//                            dpFileAdd(dpfd);
//                        }
                    }
                } else {

                }
            }
            catch (const exception &e) {
                return;
            }

        } else {

        }
    } else {

    }
}

void DPListManager::dpFileWrite(const std::string &filePath)
{
    //BaseLogServices::getServices()->Log("INFO","DPListManager","dpFileWrite()");

    nlohmann::json dpList;
    this->makeJson(dpList);

    std::string tempfile = filePath;

    std::ofstream ofs;
    ofs.open(tempfile.data(), std::ios::trunc);

    if(!ofs)
    {
        //BaseLogServices::getServices()->Log("ERROR","DPListManager","dpFileWrite() - failed to open file [%s]", tempfile);
    }
    else {
        try {
            ofs << dpList.dump(4, ' ');
        }
        catch (nlohmann::detail::exception &e) {
            //BaseLogServices::getServices()->Log("INFO","DPListManager","dpFileWrite() - nlohmann Error [%s]", e.what());
        }

        ofs.close();

        //BaseLogServices::getServices()->Log("INFO","DPListManager","dpFileWrite() - Renaming [%s]->[%s]", tempfile, filePath);

        int timeout = 0;
        while (std::rename(tempfile.data(), filePath.data()) != 0 && timeout < 20)
        {
            //usleep(100);
            timeout++;
            //BaseLogServices::getServices()->Log("INFO","DPListManager","dpFileWrite() - Renaming ...");
        }

        if (timeout == 20)
        {
            //BaseLogServices::getServices()->Log("ERROR","DPListManager","dpFileWrite() - rename failed");
        }
        else {
            //BaseLogServices::getServices()->Log("INFO","DPListManager","dpFileWrite() - rename done");
        }
    }
}

bool DPListManager::dpFileRename(const string &oldName, const string &newName)
{
    for (auto&& it: this->mDPList)
    {
        if (it->getMacAddress().compare(oldName) == 0)
        {
            it->setMacAddress(newName);

            return true;
        }
    }

    return false;
}

bool DPListManager::dpFileRemove(const string &name)
{
    bool retVal = false;
    auto it = this->mDPList.begin();
    while (it != this->mDPList.end())
    {
//        if ((*it)->getDeviceName().compare(name) == 0)
//        {
//            delete *it;

//            it = this->mDPList.erase(it);

//            retVal = true;
//        }
//        else {
//            ++it;
//        }
    }

    return retVal;
}

void DPListManager::dpFileClear()
{
    for (auto&& it: this->mDPList)
    {
        delete it;
    }

    this->mDPList.clear();
}

bool DPListManager::dpFileAdd(FileDescriptor* dpfile)
{
    std::string name = dpfile->getMacAddress();

    for (auto&& it: this->mDPList)
    {
        if (it->getMacAddress().compare(name) == 0)
        {
            return false;
        }
    }

    this->mDPList.push_back(dpfile);

    return true;
}

int DPListManager::getDPContextCount()
{

}

void DPListManager::getPhoneBookInfo(const std::string deviceName, int &nSingle, int &nFullFirst, int &nReverseLast)
{
//    for (auto&& it: this->mDPList)
//    {
//        if (it->getDeviceName().compare(deviceName) == 0)
//        {
//            if (it->getType() == DPType::BLUETOOTH)
//            {
//                FileDescriptorForBT *bt = (FileDescriptorForBT*)it;

//                nSingle         = bt->getSingleCount();
//                nFullFirst      = bt->getFullFirstCount();
//                nReverseLast    = bt->getReverseLastCount();

//                if (nSingle > 0)
//                {

//                }

//                if (nFullFirst > 0)
//                {

//                }

//                if (nReverseLast > 0)
//                {

//                }
//            }

//            return;
//        }
//    }
}

void DPListManager::readLPContextFile()
{
    std::string filePath, contextName;
    ifstream ifs(filePath);
    if (ifs.is_open())
    {
        while (ifs.eof() == false)
        {
            std::getline(ifs, contextName);
            ctxNameList.insert(contextName);
        }

        ifs.close();
    }
    else {

    }
}

std::string DPListManager::checkAvailableCtxName()
{
    std::string newCtxName;
    std::set<std::string> currentUsedCtxList;
    std::set<std::string> availableCtxList;

    // current used ctxName
    for (auto&& it: this->mDPList)
    {
        //currentUsedCtxList.insert(it->getCtxFileName());
    }

    for (auto&& it: ctxNameList)
    {
        bool bExists = false;
        for (auto&& it2: currentUsedCtxList)
        {
            if (it.compare(it2) == 0)
            {
                bExists = true;
                break;
            }
        }

        if (bExists == false)
        {
            availableCtxList.insert(it);
        }
    }

    newCtxName = *(availableCtxList.begin());

    return newCtxName;
}


void DPListManager::setCtxFileConfig(const std::string deviceName, int type, int fileSize, const std::string MD5Value)
{

}

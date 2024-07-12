#include "DPListManager.h"

using namespace mediazen::dialog::dataproduction;

const std::string VERSION           = "version";
const std::string LANGUAGE          = "language";

const std::string TYPE              = "type";
const std::string CTXFILENAME       = "ctxFileName";
const std::string DEVICENAME        = "deviceName";
const std::string MD5TYPE           = "MD5Value";
const std::string CTXFILESIZE       = "ctxfileSize";
const std::string SINGLECOUNT       = "singleCount";
const std::string FULLFIRSTCOUNT    = "fullFirstCount";
const std::string REVERSELASTCOUNT  = "reverseLastCount";


FileDescriptor::FileDescriptor(const json &in)
{
    getValueFromJson(in);
}

json FileDescriptor::makeJson()
{
    json retJson;
    retJson[TYPE]             = getType();
    retJson[CTXFILENAME]      = getCtxFileName();
    retJson[DEVICENAME]       = getDeviceName();
    retJson[MD5TYPE]          = getMD5Value();
    retJson[CTXFILESIZE]      = getCtxFileSize();

    return retJson;
}

void FileDescriptor::getValueFromJson(const json &in)
{
    std::cout << "getValueFromJson::getValueFromJson() start" << std::endl;

    // special iterator member functions for objects
    for (auto it = in.begin(); it != in.end(); ++it) {
        if(it.key() == TYPE) {
            setType(it.value());
        } else if(it.key() == CTXFILENAME){
            setCtxFileName(it.value());
        } else if(it.key() == DEVICENAME) {
            setDeviceName(it.value());
        } else if(it.key() == MD5TYPE) {
            setMD5Value(it.value());
        } else if(it.key() == CTXFILESIZE) {
            setCtxFileSize(it.value());
        } else {
            std::cout << "JSON contains unsupported key "  << it.key() << "\n";
        }
//        std::cout << it.key() << " : " << it.value() << "\n";
    }

    std::cout << "getValueFromJson::getValueFromJson() done" << std::endl;
}

FileDescriptorForBT::FileDescriptorForBT(const json &in)
{
    getValueFromJson(in);
}

json FileDescriptorForBT::makeJson()
{
    json retJson;
    retJson[TYPE]             = getType();
    retJson[CTXFILENAME]      = getCtxFileName();
    retJson[DEVICENAME]       = getDeviceName();
    retJson[MD5TYPE]          = getMD5Value();
    retJson[CTXFILESIZE]      = getCtxFileSize();
    retJson[SINGLECOUNT]      = getSingleCount();
    retJson[FULLFIRSTCOUNT]   = getFullFirstCount();
    retJson[REVERSELASTCOUNT] = getReverseLastCount();

    return retJson;
}

void FileDescriptorForBT::getValueFromJson(const json &in)
{
    std::cout << "FileDescriptorForBT::getValueFromJson() start" << std::endl;

    // special iterator member functions for objects
    for (auto it = in.begin(); it != in.end(); ++it) {
        if(it.key() == TYPE) {
            setType(it.value());
        } else if(it.key() == CTXFILENAME){
            setCtxFileName(it.value());
        } else if(it.key() == DEVICENAME) {
            setDeviceName(it.value());
        } else if(it.key() == MD5TYPE) {
            setMD5Value(it.value());
        } else if(it.key() == CTXFILESIZE) {
            setCtxFileSize(it.value());
        } else if(it.key() == SINGLECOUNT) {
            setSingleCount(it.value());
        } else if(it.key() == FULLFIRSTCOUNT) {
            setFullFirstCount(it.value());
        } else if(it.key() == REVERSELASTCOUNT) {
            setReverseLastCount(it.value());
        } else {
            std::cout << "JSON contains unsupported key "  << it.key() << "\n";
        }
        //std::cout << it.key() << " : " << it.value() << "\n";
    }

     std::cout << "FileDescriptorForBT::getValueFromJson() done" << std::endl;
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
    std::cout << "makeJson() start" << std::endl;
    _json[VERSION]   = mVersion;
    _json[LANGUAGE]  = mLanguage;

    if(mDPList.size() > 0){
        json dpList;
        auto it = mDPList.begin();
        while(it != mDPList.end() ) {
            dpList += (*it)->makeJson();
            ++it;
        }
        _json["DP_LIST"] = dpList;
    }
    std::cout << "makeJson() End" << std::endl;
    return true;
}


void DPListManager::read(const std::string &filePath)
{
    std::ifstream ifs(filePath);
    json dpListFile;
    std::string text, dpinfo;

    while(!ifs.eof()) {
        text.clear();
        std::getline(ifs, text);
        dpinfo+=text;
    }

    if(!dpinfo.empty()) {
        try {
            dpListFile = json::parse(dpinfo);
        }
        catch (const nlohmann::detail::parse_error &e) {
            std::cout << "Parse_error :  " << e.what() << std::endl;
        }
        ifs.close();

        mVersion = dpListFile[VERSION];
        mLanguage = dpListFile[LANGUAGE];
        json dpList = dpListFile["DP_LIST"];

        std::cout << "DPListManager::read(DP_LIST) " << std::endl << dpList.dump(4, ' ') << std::endl;

        if(!dpList.is_null()) {
            for (json::iterator it = dpList.begin(); it != dpList.end(); ++it) {
                std::cout << " --- \n" << *it << "\n ----\n";
                DPType dft = static_cast<DPType>((*it)["type"]);
                FileDescriptor *dpfd = nullptr;
                if(dft == DPType::NORMAL) {
                    dpfd = new FileDescriptor(*it);
                } else if(dft == DPType::BLUETOOTH) {
                    dpfd = new FileDescriptorForBT(*it);
                } else {
                    std::cout << "Value=["<< static_cast<int>(dft) << "] is not supported DP type" << std::endl;
                }

                if(dpfd != nullptr) {
                    add(dpfd);
                }
            }
        } else {
            std::cout << "There is no valid DP_LIST" << std::endl;
        }
    } else {
        std::cout << "DPListManager::read DP Info empty" << std::endl;
    }
}

void DPListManager::write(const std::string &filePath)
{
    json dpList;
    makeJson(dpList);

    std::ofstream ofs(filePath);
    ofs << dpList.dump(4, ' ');
    ofs.close();
}

bool DPListManager::rename(const std::string &oldName, const std::string &newName)
{
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(oldName.compare((*it)->getDeviceName()) == 0) {
            (*it)->setDeviceName(newName);
            return true;
        } else {
            ++it;
        }
    }

    // there is no Device name on the mDPList
    return false;
}

bool DPListManager::remove(const std::string &name)
{
    bool retVal = false;
    std::cout << "remove() start" << std::endl;
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(name.compare((*it)->getDeviceName()) == 0) {
            it = mDPList.erase(it);
            retVal = true;
        } else {
            ++it;
        }
    }
    std::cout << "remove() end" << std::endl;
    // there is no Device name on the mDPList
    return retVal;
}

void DPListManager::clear() {
    std::cout << "clear() start" << std::endl;
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        it = mDPList.erase(it);
    }
    mDPList.clear();
    std::cout << "clear() end" << std::endl;
}

bool DPListManager::add(FileDescriptor* dpfile)
{
    std::string name = dpfile->getDeviceName();
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(name.compare((*it)->getDeviceName()) == 0) {
            return false;
        } else {
            ++it;
        }
    }

    mDPList.push_back(dpfile);
    return true;
}

std::vector<std::string> DPListManager::showContents()
{
    std::vector<std::string> deviceList;
    std::cout << "showContents() start" << std::endl;
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        std::cout << (*it)->getDeviceName() << std::endl;
        deviceList.push_back((*it)->getDeviceName());
        ++it;
    }
    std::cout << "showContents() end" << std::endl;
    return deviceList;
}

void DPListManager::showCtxName()
{
    std::cout << "showCtxName() start" << std::endl;
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(!(*it)->getCtxFileName().empty()) {
            std::cout << "CtxName : " << (*it)->getCtxFileName() << std::endl;
        }
        ++it;
    }
    std::cout << "showCtxName() end" << std::endl;
}

int DPListManager::getPhoneBookListCount() {
    std::cout << "getPhoneBookCount() start" << std::endl;
    int count = 0;
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(((*it)->getType() == DPType::BLUETOOTH)){
            if(!(*it)->getCtxFileName().empty()) {
                count+=1;
                std::cout << "phonebook count : " << count << std::endl;
            }
        }
        ++it;
    }
    std::cout << "getPhoneBookCount() end" << std::endl;
    return count;
}

int DPListManager::getNormalListCount() {
    std::cout << "getNormalListCount() start" << std::endl;
    int count = 0;
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(((*it)->getType() == DPType::NORMAL)){
            if(!(*it)->getDeviceName().empty()) {
                count+=1;
                std::cout << "NormalDP count : " << count << std::endl;
            }
        }
        ++it;
    }
    std::cout << "getNormalListCount() end" << std::endl;
    return count;
}

void DPListManager::getPhoneBookInfo(const std::string deviceName, int &_singleCount, int &_fullFirstCount, int &_reverseLastCount) {
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(deviceName.compare((*it)->getDeviceName()) == 0) {
            if((*it)->getType() == DPType::BLUETOOTH){
                FileDescriptorForBT *bt = (FileDescriptorForBT*)(*it);
                _singleCount = bt->getSingleCount();
                _fullFirstCount = bt->getFullFirstCount();
                _reverseLastCount = bt->getReverseLastCount();
            }

            if(_singleCount > 0)
                std::cout << "_singleCount : " << _singleCount << std::endl;
            if(_fullFirstCount > 0)
                std::cout << "_fullFirstCount : " << _fullFirstCount << std::endl;
            if(_reverseLastCount > 0)
                std::cout << "_reverseLastCount : " << _reverseLastCount << std::endl;

            return;
        }
        ++it;
    }
}

DPType DPListManager::getDPType(const std::string deviceName){
    std::cout << "getDPType() start" << std::endl;
    DPType type = DPType::MAX;

    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(deviceName.compare((*it)->getDeviceName()) == 0) {
            if((*it)->getType() == DPType::NORMAL){
                type = DPType::NORMAL;
            }else if((*it)->getType() == DPType::BLUETOOTH) {
                type = DPType::BLUETOOTH;
            }
            std::cout << "getType : " << static_cast<int>(type) << std::endl;
            return type;
        }
        ++it;
    }
    std::cout << "getDPTyupe() end" << std::endl;
    return type;
}

std::string DPListManager::getPhoneBookCtxName(const std::string deviceName){
    DPType type = DPType::MAX;

    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if((*it)->getType() == DPType::BLUETOOTH){
            if(deviceName.compare((*it)->getDeviceName()) == 0) {
                return (*it)->getCtxFileName();
            }
        }
        ++it;
    }

    if(it == mDPList.end())
        return "No CtxName";
}


std::set<std::string> ctxNameList;

std::string removeCharsFromString(std::string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
   return str;
}

void loadContextName(){
    std::ifstream ifs("./LP_DP_CONTEXT_LIST.txt");
    std::string contextName;

    while(!ifs.eof()) {
        contextName.clear();
        std::getline(ifs, contextName);
        contextName = removeCharsFromString(contextName, "\r");
        ctxNameList.insert(contextName);
    }
    ifs.close();

    auto it = ctxNameList.begin();
    while(it != ctxNameList.end() ) {
        //std::cout << "ctxNameList : " << (*it) << std::endl;
        ++it;
    }
}

std::string DPListManager::checkAvailableCtxName() {

    std::cout << "checkAvailableCtxName() Begin "<< std::endl;

    std::string newCtxName;
    std::set<std::string> currentUsedCtxList;
    std::set<std::string> availableCtxList;

    // current used ctxName
    auto currentList = mDPList.begin();
    while(currentList != mDPList.end() ) {
        currentUsedCtxList.insert((*currentList)->getCtxFileName());
        std::cout << "current used ctxName :  "<< (*currentList)->getCtxFileName() <<std::endl;
        ++currentList;
    }

    // find available ctxName
    for (auto it = ctxNameList.begin(); it != ctxNameList.end(); ++it) {
        auto it2 = currentUsedCtxList.begin();
        for ( ; it2 != currentUsedCtxList.end(); ++it2) {
            if(!(*it).compare(*it2)) break;
        }

        if(it2 == currentUsedCtxList.end()) {
            availableCtxList.insert(*it);
        }
    }

    auto available = availableCtxList.begin();
    while(available != availableCtxList.end() ) {
        std::cout << "available :  "<< *available <<std::endl;
        ++available;
    }

    newCtxName = *(availableCtxList.begin());
    std::cout << "newCtxName : " << newCtxName << std::endl;

    std::cout << "checkAvailableCtxName() End "<< std::endl;

    return newCtxName;
}

void DPListManager::setCtxFileSize(const std::string deviceName, int type, int fileSize){
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(deviceName.compare((*it)->getDeviceName()) == 0) {
            if((*it)->getType() == DPType::BLUETOOTH){
                FileDescriptorForBT *bt = (FileDescriptorForBT*)(*it);

                if(type == SDS_DIALOG_DATA_PHONEBOOK_DP_SINGLE) {
                    if(bt->getSingleCount() > 0) {
                        bt->setSingleFileSize(fileSize);
                        std::cout << "setSingleFileSize : " << bt->getSingleFileSize() << std::endl;
                    }
                }else if(type == SDS_DIALOG_DATA_PHONEBOOK_DP_FULL_FIRST) {
                    if(bt->getFullFirstCount() > 0) {
                        bt->setFullFirstFileSize(fileSize);
                        std::cout << "setFullFirstFileSize : " << bt->getFullFirstFileSize() << std::endl;
                    }
                }else if(type == SDS_DIALOG_DATA_PHONEBOOK_DP_REVERSE_LAST) {
                    if(bt->getReverseLastCount() > 0) {
                        bt->setReverseLastFileSize(fileSize);
                        std::cout << "setReverseLastFileSize : " << bt->getReverseLastFileSize() << std::endl;
                    }
                }else {
                    std::cout << "unknown phonebook DP type" << std::endl;
                }
            }else if((*it)->getType() == DPType::NORMAL){
                (*it)->setCtxFileSize(fileSize);
                std::cout << "getCtxFileSize(Normal) : " << (*it)->getCtxFileSize()  << std::endl;
            } else {
                std::cout << "DPType::MAX" << std::endl;
            }

            return;
        }
        ++it;
    }
}

void DPListManager::setMD5Value(const std::string deviceName, int type, const std::string MD5Value){
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(deviceName.compare((*it)->getDeviceName()) == 0) {
            if((*it)->getType() == DPType::BLUETOOTH){
                FileDescriptorForBT *bt = (FileDescriptorForBT*)(*it);

                if(type == SDS_DIALOG_DATA_PHONEBOOK_DP_SINGLE) {
                    if(bt->getSingleCount() > 0) {
                        bt->setSingleMD5(MD5Value);
                        std::cout << "getSingleMD5 : " << bt->getSingleMD5() << std::endl;
                    }
                }else if(type == SDS_DIALOG_DATA_PHONEBOOK_DP_FULL_FIRST) {
                    if(bt->getFullFirstCount() > 0) {
                        bt->setFullFirstMD5(MD5Value);
                        std::cout << "getFullFirstMD5 : " << bt->getFullFirstMD5() << std::endl;
                    }
                }else if(type == SDS_DIALOG_DATA_PHONEBOOK_DP_REVERSE_LAST) {
                    if(bt->getReverseLastCount() > 0) {
                        bt->setReverseLastMD5(MD5Value);
                        std::cout << "getReverseLastMD5 : " << bt->getReverseLastMD5() << std::endl;
                    }
                }else {
                    std::cout << "unknown phonebook DP type" << std::endl;
                }
            }else if((*it)->getType() == DPType::NORMAL){
                (*it)->setMD5Value(MD5Value);
                std::cout << "getMD5Value(Normal) : " << (*it)->getMD5Value() << std::endl;
            } else {
                std::cout << "DPType::MAX" << std::endl;
            }

            return;
        }
        ++it;
    }
}

int DPListManager::getCtxFileSize(const std::string deviceName, int type){
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(deviceName.compare((*it)->getDeviceName()) == 0) {
            if((*it)->getType() == DPType::BLUETOOTH){
                FileDescriptorForBT *bt = (FileDescriptorForBT*)(*it);
                if((type == SDS_DIALOG_DATA_PHONEBOOK_DP_SINGLE) && (bt->getSingleCount() > 0)) {
                    std::cout << "getSingleFileSize : " << bt->getSingleFileSize() << std::endl;
                    return bt->getSingleFileSize();
                }else if((type == SDS_DIALOG_DATA_PHONEBOOK_DP_FULL_FIRST) && (bt->getFullFirstCount() > 0)) {
                    std::cout << "getFullFirstFileSize : " << bt->getFullFirstFileSize() << std::endl;
                    return bt->getFullFirstFileSize();
                }else if((type == SDS_DIALOG_DATA_PHONEBOOK_DP_REVERSE_LAST) && (bt->getReverseLastCount() > 0)) {
                    std::cout << "getReverseLastCount : " << bt->getReverseLastFileSize() << std::endl;
                    return bt->getReverseLastFileSize();
                }else {
                    return -1;
                    std::cout << "unknow type" << std::endl;
                }
            }else if((*it)->getType() == DPType::NORMAL){
                std::cout << "getCtxFileSize : " << (*it)->getCtxFileSize() << std::endl;
                return (*it)->getCtxFileSize();
            }
        }
        ++it;
    }
}

std::string DPListManager::getMD5Value(const std::string deviceName, int type){
    auto it = mDPList.begin();
    while(it != mDPList.end() ) {
        if(deviceName.compare((*it)->getDeviceName()) == 0) {
            if((*it)->getType() == DPType::BLUETOOTH){
                FileDescriptorForBT *bt = (FileDescriptorForBT*)(*it);
                if((type == SDS_DIALOG_DATA_PHONEBOOK_DP_SINGLE) && (bt->getSingleCount() > 0)) {
                    std::cout << "getSingleMD5 : " << bt->getSingleMD5() << std::endl;
                    return bt->getSingleMD5();
                }else if((type == SDS_DIALOG_DATA_PHONEBOOK_DP_FULL_FIRST) && (bt->getFullFirstCount() > 0)) {
                    std::cout << "getFullFirstMD5 : " << bt->getFullFirstMD5() << std::endl;
                    return bt->getFullFirstMD5();
                }else if((type == SDS_DIALOG_DATA_PHONEBOOK_DP_REVERSE_LAST) && (bt->getReverseLastCount() > 0)) {
                    std::cout << "getReverseLastMD5 : " << bt->getReverseLastMD5() << std::endl;
                    return bt->getReverseLastMD5();
                }
            } else if((*it)->getType() == DPType::NORMAL){
                std::cout << "getMD5Value : " << (*it)->getMD5Value() << std::endl;
                return (*it)->getMD5Value();
            }
        }
        ++it;
    }
}


void UnitTest()
{
    mediazen::dialog::dataproduction::DPListManager aaa;
    std::ifstream file;
    std::string filePath = "./DP_DYNAMIC_LIST.txt";

    aaa.clear();

    loadContextName();

    aaa.setLanguage("KOK");
    aaa.setVersion(01);

    file.open(filePath, std::ios::binary);

    if(file.good()) {
        aaa.read("./DP_DYNAMIC_LIST.txt");
    }else {
        std::cout << "DP_DYNAMIC_LIST.txt does not exist... create file !!" << std::endl;

        std::ofstream oData;
        oData.open(filePath, std::ios::binary);
        oData.close();
    }

    aaa.add(new mediazen::dialog::dataproduction::FileDescriptor("SLOT_SETTINGS", "SLOT_SETTINGS", "dsf123r", 100));
    aaa.add(new mediazen::dialog::dataproduction::FileDescriptorForBT("06", "deviceName2", 101,202,303));
    //aaa.add(new mediazen::dialog::dataproduction::FileDescriptorForBT("07", "deviceName5", 101,202,303));
    //aaa.add(new mediazen::dialog::dataproduction::FileDescriptorForBT("05", "deviceName1", 11,22,33));

    aaa.remove("deviceName2");

//    aaa.setMD5Value("SLOT_SETTINGS", 0, "qwerty");
//    aaa.setMD5Value("deviceName2", 1, "fffffff");
//    aaa.setMD5Value("deviceName2", 2, "hhhhhhhh");
//    aaa.setMD5Value("deviceName2", 3, "kkkkkkkk");

//    aaa.setCtxFileSize("SLOT_SETTINGS", 0, 7645);
//    aaa.setCtxFileSize("deviceName2", 1, 9999);
//    aaa.setCtxFileSize("deviceName2", 2, 4567);
//    aaa.setCtxFileSize("deviceName2", 3, 8901);

//    std::string hashValue = aaa.getMD5Value("deviceName2", 1);
//    std::cout << "deviceName2 MD5(single) : " << hashValue << std::endl;

//    hashValue.clear();
//    hashValue = aaa.getMD5Value("deviceName2", 2);
//    std::cout << "deviceName2 MD5(full) : " << hashValue << std::endl;

//    hashValue.clear();
//    hashValue = aaa.getMD5Value("deviceName2", 3);
//    std::cout << "deviceName3 MD5(Last) : " << hashValue << std::endl;

//    hashValue.clear();
//    hashValue = aaa.getMD5Value("SLOT_SETTINGS", 0);
//    std::cout << "SLOT_SETTINGS MD5(hash) : " << hashValue << std::endl;

    aaa.write("./DP_DYNAMIC_LIST.txt");
    aaa.read("./DP_DYNAMIC_LIST.txt");

    aaa.clear();

    aaa.write("./DP_DYNAMIC_LIST.txt");
    aaa.read("./DP_DYNAMIC_LIST.txt");

}

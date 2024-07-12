#ifndef DPLISTMANAGER_H
#define DPLISTMANAGER_H

#define VERSION                         "version"
#define LANGUAGE                        "language"
#define TYPE                            "type"
#define OUTGOINGCALLNAME                "formattedName"
#define DEVICENAME                      "deviceName"
#define MD5TYPE                         "MD5Value"
#define CTXFILESIZE                     "ctxfileSize"
#define SINGLECOUNT                     "singleCount"
#define FULLFIRSTCOUNT                  "fullFirstCount"
#define REVERSELASTCOUNT                "reverseLastCount"

#include <nlohmann/json.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <set>

namespace mediazen{
namespace dialog{
namespace dataManager{

class FileDescriptor
{
public:

    FileDescriptor()
    {
    }

    FileDescriptor(const nlohmann::json &in);
    FileDescriptor(const std::string &_Name, const std::string &_MacAddress, const std::string &_md5Value, unsigned int _FileSize)
        :mName(_Name), mMacAddress(_MacAddress), mMd5Value(_md5Value),mCallHistoryFileSize(_FileSize)
    {
    }

    virtual ~FileDescriptor() { }

    std::string getOutgoingCallName() const
    {
        return mName;
    }

    void setOutgoingCallName(const std::string &value)
    {
        mName = value;
    }

    std::string getMacAddress() const
    {
        return mMacAddress;
    }

    void setMacAddress(const std::string &value)
    {
        mMacAddress = value;
    }

    std::string getMD5Value() const
    {
        return mMd5Value;
    }

    void setMD5Value(const std::string &value)
    {
        mMd5Value = value;
    }

    unsigned int getCallHistoryFileSize() const
    {
        return mCallHistoryFileSize;
    }

    void setCallHistoryFileSize(unsigned int value)
    {
        mCallHistoryFileSize = value;
    }

    virtual nlohmann::json makeJson(void);
    virtual void getValueFromJson(const nlohmann::json &in);

private:
    std::string mName;
    std::string mMacAddress;
    std::string mMd5Value;
    unsigned int mCallHistoryFileSize = 0;
};

class DPListManager
{
public:
    DPListManager();
    ~DPListManager();

    void setLanguage(const std::string &lang)
    {
        mLanguage = lang;
    }

    void setVersion(const unsigned int &version)
    {
        mVersion = version;
    }

    std::string getLanguage() const
    {
        return mLanguage;
    }

    unsigned int  getVersion()
    {
        return mVersion;
    }

    bool makeJson(nlohmann::json& _json);
    void dpFileRead(const std::string &filePath);
    void dpFileWrite(const std::string &filePath);
    bool dpFileRename(const std::string &oldName, const std::string &newName);
    bool dpFileRemove(const std::string &name);
    void dpFileClear();
    bool dpFileAdd(FileDescriptor *dpfile);

    std::string                 checkAvailableCtxName();
    void                        readLPContextFile();
    int                         getDPContextCount();
    void                        getPhoneBookInfo(const std::string deviceName, int &_singleCount, int &_fullFirstCount, int &_reverseLastCount);
    void                        setCtxFileConfig(const std::string deviceName, int type, int fileSize, const std::string MD5Value);

private:
    unsigned int mVersion = 0;
    std::string mLanguage = "UNKNOWN";
    std::vector<std::string> mCallName;
    std::vector<FileDescriptor*> mDPList;
};

} // dataproduction
} // dialog
} // mediazen

#endif // DPLISTMANAGER_H

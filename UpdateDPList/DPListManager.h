#ifndef DPLISTMANAGER_H
#define DPLISTMANAGER_H

#include <stdio.h>
#include <stdarg.h>
#include <utility>
#include <time.h>

#include <nlohmann/json.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <set>

using json = nlohmann::json;

#define SDS_DIALOG_DATA_PHONEBOOK_DP_SINGLE                 1
#define SDS_DIALOG_DATA_PHONEBOOK_DP_FULL_FIRST             2
#define SDS_DIALOG_DATA_PHONEBOOK_DP_REVERSE_LAST           3

namespace mediazen{
namespace dialog{
namespace dataproduction{

enum class DPType {
    NORMAL,
    BLUETOOTH,
    MAX
};

class FileDescriptor
{
public:

    FileDescriptor() {    setType(DPType::NORMAL);    }
    FileDescriptor(const json &in);
    FileDescriptor(const std::string &_ctxFileName, const std::string &_deviceName,
                     const std::string &_MD5Value, unsigned int _ctxFileSize)
        :ctxFileName(_ctxFileName), deviceName(_deviceName), MD5Value(_MD5Value),ctxFileSize(_ctxFileSize)
    {
        setType(DPType::NORMAL);
    }
    virtual ~FileDescriptor() { }

    DPType getType() const                          { return type;          }
    void setType(const DPType value)                { type = value;         }
    std::string getCtxFileName() const              { return ctxFileName;   }
    void setCtxFileName(const std::string &value)   { ctxFileName = value;  }
    std::string getDeviceName() const               { return deviceName;    }
    void setDeviceName(const std::string &value)    { deviceName = value;   }
    std::string getMD5Value() const                 { return MD5Value;      }
    void setMD5Value(const std::string &value)      { MD5Value = value;     }
    unsigned int getCtxFileSize() const             { return ctxFileSize;   }
    void setCtxFileSize(unsigned int value)         { ctxFileSize = value;  }
    virtual json makeJson(void);
    virtual void getValueFromJson(const json &in);

private:
    DPType  type;
    std::string ctxFileName;
    std::string deviceName;
    std::string MD5Value;
    unsigned int ctxFileSize = 0;
};

class FileDescriptorForBT : public FileDescriptor
{
public:
    FileDescriptorForBT(){    setType(DPType::BLUETOOTH); }
    FileDescriptorForBT(const json &in);
    FileDescriptorForBT(const std::string &_ctxFileName, const std::string &_deviceName,
                          const int &_singleCount, const int &_fullFirstCount, const int &_reverseLastCount)
        : singleCount(_singleCount), fullFirstCount(_fullFirstCount),reverseLastCount(_reverseLastCount)
    {
        setType(DPType::BLUETOOTH);
        setCtxFileName(_ctxFileName);
        setDeviceName(_deviceName);
    }
    virtual ~FileDescriptorForBT() { }

    int  getSingleCount() const         { return singleCount;       }
    void setSingleCount(int value)      { singleCount = value;      }
    int  getFullFirstCount() const      { return fullFirstCount;    }
    void setFullFirstCount(int value)   { fullFirstCount = value;   }
    int  getReverseLastCount() const    { return reverseLastCount;  }
    void setReverseLastCount(int value) { reverseLastCount = value; }

    int  getSingleFileSize() const         { return singleFileSize;       }
    void setSingleFileSize(int value)      { singleFileSize = value;      }
    int  getFullFirstFileSize() const      { return fullFirstFileSize;    }
    void setFullFirstFileSize(int value)   { fullFirstFileSize = value;   }
    int  getReverseLastFileSize() const    { return reverseLastFileSize;  }
    void setReverseLastFileSize(int value) { reverseLastFileSize = value; }

    void            setSingleMD5(const std::string &_singleMD5)                 { singleMD5 = _singleMD5;      }
    std::string     getSingleMD5() const                                        { return singleMD5;    }
    void            setFullFirstMD5(const std::string &_fullFirstMD5)           { fullFirstMD5 = _fullFirstMD5;   }
    std::string     getFullFirstMD5() const                                     { return fullFirstMD5;    }
    void            setReverseLastMD5(const std::string &_reverseLastMD5)       { reverseLastMD5 = _reverseLastMD5; }
    std::string     getReverseLastMD5() const                                   { return reverseLastMD5; }

    json makeJson(void);
    virtual void getValueFromJson(const json &in);

private:
    int                 singleCount             = 0;
    int                 fullFirstCount          = 0;
    int                 reverseLastCount        = 0;

    int                 singleFileSize          = 0;
    int                 fullFirstFileSize       = 0;
    int                 reverseLastFileSize     = 0;

    std::string         singleMD5;
    std::string         fullFirstMD5;
    std::string         reverseLastMD5;
};

class DPListManager
{
public:
    DPListManager();
    ~DPListManager();

    std::string getLanguage() const { return mLanguage; }
    void setLanguage(const std::string &lang) { mLanguage = lang; }
    void setVersion(const unsigned int &version) { mVersion = version; }

    bool makeJson(json& _json);
    void read(const std::string &filePath);
    void write(const std::string &filePath);
    bool rename(const std::string &oldName, const std::string &newName);
    bool remove(const std::string &name);
    void clear();
    bool add(FileDescriptor *dpfile);

    std::vector<std::string>    showContents();
    std::string                 getPhoneBookCtxName(const std::string deviceName);
    void                        showCtxName();
    int                         getPhoneBookListCount();
    int                         getNormalListCount();
    void                        getPhoneBookInfo(const std::string deviceName, int &_singleCount, int &_fullFirstCount, int &_reverseLastCount);
    std::string                 checkAvailableCtxName();
    DPType                      getDPType(const std::string deviceName);
    void                        setCtxFileSize(const std::string deviceName, int type, int fileSize);
    int                         getCtxFileSize(const std::string deviceName, int type);
    void                        setMD5Value(const std::string deviceName, int type, const std::string MD5Value);
    std::string                 getMD5Value(const std::string deviceName, int type);

private:
    unsigned int mVersion = 0;
    std::string mLanguage = "UNKNOWN";

    std::vector<FileDescriptor*> mDPList;
};

} // dataproduction
} // dialog
} // mediazen

#endif // DPLISTMANAGER_H

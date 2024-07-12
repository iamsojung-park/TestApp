#ifndef VHCONTACT_H
#define VHCONTACT_H

#include <QMap>
#include <QVector>
#include <QPair>
#include <QMetaType>
//#include "prompt_lid.h"
#include <QObject>
#include <QCoreApplication>
#include <memory>

enum class NumberType : int {
    UNKNOWN = 0,
    CELL = 1,
    HOME = 2,
    WORK = 3,
    ETC = 4,
};

class VHContact
{
    Q_DECLARE_TR_FUNCTIONS(VHContact)
public:
    VHContact();
    ~VHContact();

    VHContact(const VHContact& rhs);
    VHContact(VHContact&& rhs) noexcept;
    VHContact &operator=(const VHContact& rhs);
    VHContact &operator=(VHContact&& rhs) noexcept;

    bool operator==(const VHContact & object) const;
    void setFirstName(QString nameStr);
    QString getFirstName() const;
    void setLastName(QString nameStr);
    QString getLastName() const;
    void setFullName(QString nameStr);
    QString getFullName() const;
    void setFormattedName(QString nameStr);
    QString getFormattedName() const;

    QString getFirstNameNormalized() const;
    QString getLastNameNormalized() const;
    QString getFormattedNameNormalized() const;

    bool validate();

    void addNumber(NumberType numberTypeKey, QString numberValueStr);
    int removeNumber(NumberType numberTypeKey);
    QMultiMap<NumberType, QString> getNumberMap() const;
    QMultiMap<NumberType, QString> getNumberMapInKoreanPhoneNumberFormat() const;
    QString getFirstNumber() const;

    NumberType getFirstNumberType() const;
    QStringList getNumber(NumberType numberType) const;
    QStringList getNumberListInKoreanPhoneNumberFormat() const;
    int getNumberCount() const;
    void clearNumbers();
    void setDBIndex(int idx);
    int getDBIndex(void) const;
    void setTimeStamp(QString timeStamp);
    QString getTimeStamp();

//    static PromptLID getCallPromptLID(NumberType numberType);
//    static PromptLID getNoCategoryPromptLID(NumberType numberType);
//    static PromptLID getNoCategorySelectNumberPromptLID(NumberType numberType);
//    static PromptLID getCallInsteadPromptLID(NumberType numberType);

    static QString makeCallContent(QString name = "", NumberType type = NumberType::UNKNOWN);
    static QString toString(NumberType numberType);
//    static QString makeCallVRText(QString name = "", NumberType type = NumberType::UNKNOWN,  bool isColorEnable = true);
    NumberType getNumberType(QString digits) const;
    bool hasNumber(QString digits) const;
//    bool hasKoreanPhoneNumber() const;

    void setConfidence(int confidence);
    int getConfidence() const;

    void setUserPhotoExist(bool value);
    bool getUserPhotoExist() const;

    void setUserPhotoData(std::string rawData);
    std::string getUserPhotoData() const;

    void print();

    int getProbabilityCategory() const;
    void setProbabilityCategory(int probabilityCategory);

    void setNameCategoryList(QString numberType);
    QStringList getNameCategoryList() const;

    void setDPList(QString str);
    QStringList getDPList() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;

//    QString firstName;
//    QString lastName;
//    QString fullName;
//    QString formattedName;
//    QString firstNameNormalized;
//    QString lastNameNormalized;
//    QString formattedNameNormalized;
//    int dbIndex = -1;
//    QString timeStamp;
//    QMultiMap<NumberType, QString> mCategoryMap;
//    int mConfidence = -1;
//    int mProbabilityCategory = -1;
//    bool mUserPhotoExist = false;
//    std::string mUserPhotoData = "";
//    QStringList mNameCategoryList;
//    QStringList mDpList;
};

Q_DECLARE_METATYPE(VHContact)
Q_DECLARE_METATYPE(NumberType)

#endif // VHCONTACT_H

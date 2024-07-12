#include "VHContact.h"
#include <QObject>
#include <QString>
//#include "VHDPNormalizer.h"
//#include "VHLog.h"
//#include "VHSystemProperty.h"
//#include "VHConstant.h"
//#include "VHUtil.h"
#include <iostream>

class VHLog {
public:
    static void debug(QString log) {
        std::cout << log.toStdString() << std::endl;
    }
};


class VHContact::Impl {
public:
    QString firstName;
    QString lastName;
    QString fullName;
    QString formattedName;
    QString firstNameNormalized;
    QString lastNameNormalized;
    QString formattedNameNormalized;
    QString timeStamp;
    QMultiMap<NumberType, QString> mCategoryMap;
    std::string mUserPhotoData = "";
    QStringList mNameCategoryList;
    QStringList mDpList;
    int mConfidence = -1;
    int mProbabilityCategory = -1;
    int dbIndex = -1;
    bool mUserPhotoExist = false;
};

VHContact::VHContact()
    : m_pImpl(new Impl)
{
}

VHContact::~VHContact()
{
}

VHContact::VHContact(const VHContact &rhs)
:m_pImpl(new Impl(*rhs.m_pImpl))
{

}

VHContact::VHContact(VHContact &&rhs) noexcept
{
    if (this != &rhs) {
        m_pImpl = std::move(rhs.m_pImpl);
    }
}

VHContact &VHContact::operator=(const VHContact &rhs)
{
    if (this != &rhs) {
        m_pImpl->firstName                  = rhs.m_pImpl->firstName;
        m_pImpl->lastName                   = rhs.m_pImpl->lastName;
        m_pImpl->fullName                   = rhs.m_pImpl->fullName;
        m_pImpl->formattedName              = rhs.m_pImpl->formattedName;
        m_pImpl->firstNameNormalized        = rhs.m_pImpl->firstNameNormalized;
        m_pImpl->lastNameNormalized         = rhs.m_pImpl->lastNameNormalized;
        m_pImpl->formattedNameNormalized    = rhs.m_pImpl->formattedNameNormalized;
        m_pImpl->timeStamp                  = rhs.m_pImpl->timeStamp;
        m_pImpl->mCategoryMap               = rhs.m_pImpl->mCategoryMap;
        m_pImpl->mUserPhotoData             = rhs.m_pImpl->mUserPhotoData;
        m_pImpl->mNameCategoryList          = rhs.m_pImpl->mNameCategoryList;
        m_pImpl->mDpList                    = rhs.m_pImpl->mDpList;
        m_pImpl->mConfidence                = rhs.m_pImpl->mConfidence;
        m_pImpl->mProbabilityCategory       = rhs.m_pImpl->mProbabilityCategory;
        m_pImpl->dbIndex                    = rhs.m_pImpl->dbIndex;
        m_pImpl->mUserPhotoExist            = rhs.m_pImpl->mUserPhotoExist;
    }
    return *this;
}

VHContact &VHContact::operator=(VHContact &&rhs) noexcept
{
    std::cout << __PRETTY_FUNCTION__ << " " << __LINE__ << std::endl;
    if (this != &rhs) {
        m_pImpl = std::move(rhs.m_pImpl);
    }
    return *this;
}

bool VHContact::operator==(const VHContact &object) const
{
    bool isSameName = object.getFormattedName().compare(getFormattedName()) == 0;
    bool isSameDBIndex = object.getDBIndex() == getDBIndex();
    return isSameName && isSameDBIndex;
}

void VHContact::setFirstName(QString nameStr)
{
    m_pImpl->firstName = nameStr;
    m_pImpl->firstNameNormalized = nameStr + "Normalized";
//    firstNameNormalized = VHDPNormalizer::normalize(nameStr);
}

void VHContact::setLastName(QString nameStr)
{
    m_pImpl->lastName = nameStr;
    m_pImpl->lastNameNormalized = nameStr + "Normalized";
    // lastNameNormalized = VHDPNormalizer::normalize(nameStr);
}

void VHContact::setFormattedName(QString nameStr)
{
    m_pImpl->formattedName = nameStr;
    m_pImpl->formattedNameNormalized = nameStr + "Normalized";
//    formattedNameNormalized = VHDPNormalizer::normalize(nameStr);
}

QString VHContact::getFirstName() const
{
    return m_pImpl->firstName;
}

QString VHContact::getLastName() const
{
    return m_pImpl->lastName;
}

void VHContact::setFullName(QString nameStr)
{
    m_pImpl->fullName = nameStr;
}

QString VHContact::getFullName() const
{
    return m_pImpl->fullName;
}

QString VHContact::getFormattedName() const
{
    return m_pImpl->formattedName;
}

QString VHContact::getFirstNameNormalized() const
{
    return m_pImpl->firstNameNormalized;
}

QString VHContact::getLastNameNormalized() const
{
    return m_pImpl->lastNameNormalized;
}

QString VHContact::getFormattedNameNormalized() const
{
    return m_pImpl->formattedNameNormalized;
}

bool VHContact::validate()
{
    if (m_pImpl->firstNameNormalized.isEmpty() && m_pImpl->lastNameNormalized.isEmpty()) {
        if (m_pImpl->formattedNameNormalized.isEmpty()) {
            return false;
        }
        else {
            VHLog::debug(QString("[VHContact] Warning: first <- formatted (before first:[%1] last:[%2] formatted:[%3])")
                         .arg(m_pImpl->firstNameNormalized)
                         .arg(m_pImpl->lastNameNormalized)
                         .arg(m_pImpl->formattedNameNormalized));
            setFirstName(m_pImpl->formattedName);
            return true;
        }
    }
    else {
        if (m_pImpl->formattedNameNormalized.isEmpty()) {
            if (m_pImpl->firstNameNormalized.isEmpty() == false) {
                VHLog::debug(QString("[VHContact] Warning: formatted <- first (before first:[%1] last:[%2] formatted:[%3])")
                             .arg(m_pImpl->firstNameNormalized)
                             .arg(m_pImpl->lastNameNormalized)
                             .arg(m_pImpl->formattedNameNormalized));
                setFormattedName(m_pImpl->firstName);
            }
            else {
                VHLog::debug(QString("[VHContact] Warning: formatted <- last (before first:[%1] last:[%2] formatted:[%3])")
                             .arg(m_pImpl->firstNameNormalized)
                             .arg(m_pImpl->lastNameNormalized)
                             .arg(m_pImpl->formattedNameNormalized));
                setFormattedName(m_pImpl->lastName);
            }
        }
        return true;
    }
}

void VHContact::addNumber(NumberType numberTypeKey, QString numberValueStr)
{
    m_pImpl->mCategoryMap.insert(numberTypeKey, numberValueStr.remove("-"));
}

int VHContact::removeNumber(NumberType numberTypeKey)
{
    return m_pImpl->mCategoryMap.remove(numberTypeKey);
}

QMultiMap<NumberType, QString> VHContact::getNumberMap() const
{
    return m_pImpl->mCategoryMap;
}

QMultiMap<NumberType, QString> VHContact::getNumberMapInKoreanPhoneNumberFormat() const
{
    QMultiMap<NumberType, QString> resultMap;
    for (auto iterator = m_pImpl->mCategoryMap.begin(); iterator != m_pImpl->mCategoryMap.end(); iterator++) {
        QString number = iterator.value();
        if (number.startsWith("+")) {
            number.remove("+");
        }
        number.replace("-","");
//        if (number.contains(QRegularExpression(constants::FirstKoreanPhoneNumberFormat)) ||
//                number.contains(QRegularExpression(constants::SecondKoreanPhoneNumberForamt)) ||
//                number.contains(QRegularExpression(constants::ThirdKoreanPhoneNumberFormat))) {
//            resultMap.insert(iterator.key(), iterator.value());
//        }
    }
    return resultMap;
}

QString VHContact::getFirstNumber() const
{
    if (getNumberCount() > 0) {
        return getNumber(m_pImpl->mCategoryMap.firstKey()).at(0);
    }
    else {
        return "";
    }
}

NumberType VHContact::getFirstNumberType() const
{
    if (getNumberCount() > 0) {
        return m_pImpl->mCategoryMap.firstKey();
    }
    else {
        return NumberType::UNKNOWN;
    }
}

QStringList VHContact::getNumber(NumberType numberType) const
{
    QStringList numberList;
    auto i = m_pImpl->mCategoryMap.find(numberType);
    while (i != m_pImpl->mCategoryMap.end() && (i.key() == numberType) ) {
        numberList.append(i.value());
        ++i;
    }

    return numberList;
}

QStringList VHContact::getNumberListInKoreanPhoneNumberFormat() const
{
    QStringList numberList;
    for (auto iterator = m_pImpl->mCategoryMap.begin(); iterator != m_pImpl->mCategoryMap.end(); iterator++) {
        QString number = iterator.value();
        if (number.startsWith("+")) {
            number.remove("+");
        }
        number.replace("-","");
//        if (number.contains(QRegularExpression(constants::FirstKoreanPhoneNumberFormat)) ||
//                number.contains(QRegularExpression(constants::SecondKoreanPhoneNumberForamt)) ||
//                number.contains(QRegularExpression(constants::ThirdKoreanPhoneNumberFormat))) {
//            numberList.append(iterator.value());
//        }
    }
    return numberList;
}

int VHContact::getNumberCount() const
{
    return m_pImpl->mCategoryMap.size();
}

void VHContact::clearNumbers()
{
    m_pImpl->mCategoryMap.clear();
}


//PromptLID VHContact::getCallPromptLID(NumberType numberType)
//{
//    switch (numberType) {
//        case NumberType::CELL:
//            return PromptLID::LID_PRM_0061; // <전화번호부 저장 이름> 휴대폰으로 전화할게요.
//        case NumberType::HOME:
//            return PromptLID::LID_PRM_0062;
//        case NumberType::WORK:
//            return PromptLID::LID_PRM_0063;
//        case NumberType::ETC:
//            return PromptLID::LID_PRM_0064;
//        default:
//            return PromptLID::LID_PRM_0060;
//    }
//}

//PromptLID VHContact::getNoCategoryPromptLID(NumberType numberType)
//{
//    VHLog::debug(QString("%1").arg(__FUNCTION__));
//    switch (numberType) {
//        case NumberType::CELL:
//            return PromptLID::LID_PRM_0075; // <전화번호부 저장 이름> 휴대폰 번호가 없어요.
//        case NumberType::HOME:
//            return PromptLID::LID_PRM_0076;
//        case NumberType::WORK:
//            return PromptLID::LID_PRM_0077;
//        default: // NumberType::ETC
//            return PromptLID::LID_PRM_0078;
//    }
//}

//PromptLID VHContact::getNoCategorySelectNumberPromptLID(NumberType numberType)
//{
//    VHLog::debug(QString("%1").arg(__FUNCTION__));
//    switch (numberType) {
//        case NumberType::CELL:
//            return PromptLID::LID_PRM_0071;
//        case NumberType::HOME:
//            return PromptLID::LID_PRM_0072;
//        case NumberType::WORK:
//            return PromptLID::LID_PRM_0073;
//        default: // NumberType::ETC
//            return PromptLID::LID_PRM_0074;
//    }
//}

//PromptLID VHContact::getCallInsteadPromptLID(NumberType numberType)
//{
//    VHLog::debug(QString("%1").arg(__FUNCTION__));
//    switch (numberType) {
//        case NumberType::CELL:
//            return PromptLID::LID_PRM_0079; // 휴대폰으로 전화할게요.
//        case NumberType::HOME:
//            return PromptLID::LID_PRM_0080;
//        case NumberType::WORK:
//            return PromptLID::LID_PRM_0081;
//        default: // NumberType::ETC
//            return PromptLID::LID_PRM_0082;
//    }
//}

//QString VHContact::makeCallContent(QString name, NumberType type)
//{
//    QString text;
//    if (name.isEmpty()) {
//        switch (type) {
//            case NumberType::CELL:
//                text = tr("LID_PRMOST_0079"); //Calling on Mobile.
//                break;
//            case NumberType::HOME:
//                text = tr("LID_PRMOST_0080");
//                break;
//            case NumberType::WORK:
//                text = tr("LID_PRMOST_0081");
//                break;
//            case NumberType::ETC:
//                text = tr("LID_PRMOST_0082");
//                break;
//            default: // NumberType::UNKNOWN
//                text = tr("LID_PRMOST_0060");
//                break;
//        }
//    }
//    else {
//        switch (type) {
//            case NumberType::CELL:
//                text = tr("LID_PRMOST_0061"); //Calling <Contact name> on Mobile.
//                break;
//            case NumberType::HOME:
//                text = tr("LID_PRMOST_0062");
//                break;
//            case NumberType::WORK:
//                text = tr("LID_PRMOST_0063");
//                break;
//            case NumberType::ETC:
//                text = tr("LID_PRMOST_0064");
//                break;
//            default: // NumberType::UNKNOWN
//                text = tr("LID_PRMOST_0060");
//                break;
//        }
//        text = text.arg(name);
//    }
//    return text;
//}

QString VHContact::toString(NumberType numberType)
{
    switch (numberType) {
        case NumberType::CELL:
            return tr("LID_OST_0245");
        case NumberType::HOME:
            return tr("LID_OST_0246");
        case NumberType::WORK:
            return tr("LID_OST_0247");
        case NumberType::ETC:
            return tr("LID_OST_0248");
        default: // NumberType::UNKNOWN
            return "Unknown";
    }
}

//QString VHContact::makeCallVRText(QString name, NumberType type, bool isColorEnable)
//{
//    QString text;
//    if (name.isEmpty()) {
//        text = tr("LID_CMD_PHN_002");
//    }
//    else {
//        switch (type) {
//            case NumberType::CELL:
//                text = tr("LID_CMD_PHN_005");
//                break;
//            case NumberType::HOME:
//                text = tr("LID_CMD_PHN_007");
//                break;
//            case NumberType::WORK:
//                text = tr("LID_CMD_PHN_006");
//                break;
//            case NumberType::ETC:
//                text = tr("LID_CMD_PHN_008");
//                break;
//            default: // NumberType::UNKNOWN
//                text = tr("LID_CMD_PHN_004");
//                break;
//        }
//        text.replace(text.indexOf("<") + 1, text.indexOf(">") - text.indexOf("<") - 1, name);
//    }
//    return VHSystemProperty::getInstance()->makeDisplayedCommand(text, isColorEnable);
//}

bool VHContact::hasNumber(QString digits) const
{
    auto map = getNumberMap();
    auto it = map.begin();
    while (it != map.end()) {
        if (it.value() == digits.remove("-")) {
            return true;
        }
        ++it;
    }

    return false;
}

//bool VHContact::hasKoreanPhoneNumber() const
//{
//    auto map = getNumberMap();
//    auto it = map.begin();
//    QRegularExpression firstExp(constants::FirstKoreanPhoneNumberFormat);
//    QRegularExpression secondExp(constants::SecondKoreanPhoneNumberForamt);
//    QRegularExpression thirdExp(constants::ThirdKoreanPhoneNumberFormat);
//    while (it != map.end()) {
//        QString number = it.value();
//        if (number.startsWith("+")) {
//            number.remove("+");
//        }
//        number.replace("-","");

//        if (number.contains(firstExp) || number.contains(secondExp) || number.contains(thirdExp)) {
//            return true;
//        }
//        ++it;
//    }
//    return false;
//}

void VHContact::print()
{
    VHLog::debug(QString("dbIndex: [%1]").arg(m_pImpl->dbIndex));
    VHLog::debug(QString("timeStamp: [%1]").arg(m_pImpl->timeStamp));

    VHLog::debug(QString("firstName: [%1]").arg(m_pImpl->firstName));
    VHLog::debug(QString("firstNameNormalized: [%1]").arg(m_pImpl->firstNameNormalized));

    VHLog::debug(QString("lastName: [%1]").arg(m_pImpl->lastName));
    VHLog::debug(QString("lastNameNormalized: [%1]").arg(m_pImpl->lastNameNormalized));

    VHLog::debug(QString("fullName: [%1]").arg(m_pImpl->fullName));

    VHLog::debug(QString("formattedName: [%1]").arg(m_pImpl->formattedName));
    if (m_pImpl->formattedName.size() > 0) {
        VHLog::debug(QString("formattedName first char: [0x%1]")
                     .arg(m_pImpl->formattedName.at(0).unicode(), 4, 16, QChar('0')));
    }
    VHLog::debug(QString("formattedNameNormalized: [%1]").arg(m_pImpl->formattedNameNormalized));
    VHLog::debug(QString("confidence: [%1]").arg(m_pImpl->mConfidence));
    for (auto iterator = m_pImpl->mCategoryMap.begin(); iterator != m_pImpl->mCategoryMap.end(); iterator++) {
        VHLog::debug(QString("category: [%1]").arg(toString(iterator.key())));
        VHLog::debug(QString("digits: [%1]").arg(iterator.value()));
    }
    for (auto iterator = m_pImpl->mDpList.begin(); iterator != m_pImpl->mDpList.end(); iterator++) {
        VHLog::debug(QString("mDpList: [%1]").arg(*iterator));
    }
}

int VHContact::getProbabilityCategory() const
{
    return m_pImpl->mProbabilityCategory;
}

void VHContact::setProbabilityCategory(int probabilityCategory)
{
    m_pImpl->mProbabilityCategory = probabilityCategory;
}

void VHContact::setNameCategoryList(QString numberType)
{
//    if (numberType == "") numberType = VHUtil::toString(NumberType::ETC);
    m_pImpl->mNameCategoryList.append(numberType);
}

QStringList VHContact::getNameCategoryList() const
{
    return m_pImpl->mNameCategoryList;
}

void VHContact::setDPList(QString str)
{
    m_pImpl->mDpList.push_back(str);
}

QStringList VHContact::getDPList() const
{
    return m_pImpl->mDpList;
}

NumberType VHContact::getNumberType(QString digits) const
{
    auto map = getNumberMap();
    auto it = map.begin();
    while (it != map.end()) {
        if (it.value() == digits.remove("-")) {
            return it.key();
        }
        ++it;
    }
    return NumberType::UNKNOWN;
}

void VHContact::setDBIndex(int idx)
{
    m_pImpl->dbIndex = idx;
}

int VHContact::getDBIndex() const
{
    return m_pImpl->dbIndex;
}

void VHContact::setTimeStamp(QString timeStamp)
{
    this->m_pImpl->timeStamp = timeStamp;
}

QString VHContact::getTimeStamp()
{
    return m_pImpl->timeStamp;
}

void VHContact::setConfidence(int confidence)
{
    m_pImpl->mConfidence = confidence;
}

int VHContact::getConfidence() const
{
    return m_pImpl->mConfidence;
}

void VHContact::setUserPhotoExist(bool value)
{
    if(m_pImpl->mUserPhotoExist != value) {
//        VHLog::debug(QString("%1 (%2)").arg(Q_FUNC_INFO).arg(value));
        m_pImpl->mUserPhotoExist = value;
    }
}

bool VHContact::getUserPhotoExist() const
{
    return m_pImpl->mUserPhotoExist;
}

void VHContact::setUserPhotoData(std::string rawData)
{
    if(!rawData.empty()) {
//        VHLog::debug(QString("%1").arg(Q_FUNC_INFO));
        m_pImpl->mUserPhotoData = rawData;
    }
}

std::string VHContact::getUserPhotoData() const
{
    return m_pImpl->mUserPhotoData;
}

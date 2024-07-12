#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "base.h"
#include "time.h"

//#include "../ParseJSON/base.h"

using namespace std;
using json = nlohmann::json;

string weatherJson = "{\"vrResult\": {\"recognitionText\": \"What's the weather tomorrow\",\"nlu\": {\"domain\": \"Weather\",\"intent\": \"Search\",\"slot\": {\"Date\": {\"literal\": \"tomorrow\"}},\"score\": \"9893\"}}}";

string weather = "";

void ParseJSON(string weatherJson)
{
    cout << "weather JSON : " << weatherJson << endl;

    json slot_data;
    slot_data = json::parse(weatherJson);

    try {
        if(slot_data.find("literal") == slot_data.end()) {
            std::string date = slot_data["literal"];
            cout << "slot.date : " << date << endl;
        }
    }
    catch (nlohmann::detail::parse_error e) {
        cout << "nlohmann Error [" << e.what() << "]" << endl;
    }

}

static const std::string kEncodeLookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char kPadCharacter = '=';

string createHoundRequestInfo() {
    json json_temp;
    json array_domain;
    std::string string_temp;

    json_temp["ClientID"]                            = "BETA4g6x0ScMTydBwPTovA==";  // BETA4g6x0ScMTydBwPTovA==
    json_temp["ClientKey"]                           = "wx2TIhJ9pSJFxOZ9ZjVthum4d4XZK_WKLwMTQ0K6ku3btRTe2WYpslh4KE4_UGrh65EFGwI9VGAwLzA6GalW2g==";  // wx2TIhJ9pSJFxOZ9ZjVthum4d4XZK_WKLwMTQ0K6ku3btRTe2WYpslh4KE4_UGrh65EFGwI9VGAwLzA6GalW2g==
    json_temp["InstallationID"]                      = "176b008-c10f-4217-a28a-c8f03cf15351";

    json_temp["DeviceName"]                          = "LGE_PRM_AVN6";
    json_temp["InputLanguageEnglishName"]            = "English";
    json_temp["InputLanguageNativeName"]             = "English";
    json_temp["Country"]                             = "en";
    json_temp["UnitPreference"]                      = "US";         // Meter,Mile

    json_temp["ServerDeterminesEndOfAudio"]                     = false;
    json_temp["ResultUpdateAllowed"]                            = true;
    json_temp["ObjectByteCountPrefix"]                          = true;
    json_temp["AutoSync"]                                       = true;
    json_temp["UseContactData"]                                 = true;
    json_temp["DisambiguateResultsBeforeAction"]                = true;
    json_temp["ExcludeMapNavigationOutsideNorthAmerica"]        = true;
    json_temp["ControllableTrackPlaying"]                       = false;
    json_temp["PartialTranscriptsDesired"]                      = false;
    json_temp["LocationPreferenceOn"]                           = false;
    json_temp["Charging"]                                       = false;
    json_temp["VoiceActivityDetection"]["MaxSilenceSeconds"]    = 10;

    //array_domain.push_back("SMS");
    array_domain+="SMS";
    //array_domain+="Call";
    json_temp["Domains"]["Only"]["DomainNames"] = array_domain;

    string_temp =  json_temp.dump();

    cout<< "Hound Request Info : " << json_temp.dump(2) << endl;

    return string_temp;
}

void kakaoMusic() {
    json root, jsonVrServiceResult;
    std::string json= "{\"cpContents\":{\"hmcCommandData\":{\"paramK\":{\"song\":{\"origin\":\"아무노래\",\"value\":\"아무노래\"},\"artist\":{\"origin\":\"지코\",\"value\":\"지코\"}},\"domain\":\"Music\",\"intention\":\"PlaySong\"},\"type\":\"HMCommand\"},\"linkInstruction\":\"link\"}";
    string kakaoHmcCommandData_;

    try {
        root = json::parse(json);
    }
    catch (nlohmann::detail::parse_error e) {
    }

    if (!root.empty()) {
        jsonVrServiceResult = root["cpContents"]["hmcCommandData"]["paramK"];
        //jsonVrServiceResult = root["cpContents"];

        if(!jsonVrServiceResult.is_null()){
            //kakaoHmcCommandData_ = jsonVrServiceResult.get<std::string>();
            kakaoHmcCommandData_ = jsonVrServiceResult.dump();
            std::cout << "kakaoMusic" << endl << kakaoHmcCommandData_ << endl;
        }
    }else{
        std::cout << "kakaoMusic json empty" << endl;
    }


}

void kakaoDomain() {
    json root, jsonVrServiceResult;
    std::string json = "{\"vrActionResult\":{\"cpActionData\":{\"ttsText\":\"6월 6일 추첨한 제 914회차 로또 당첨번호는, 16, 19, 24, 33, 42, 44고, 2등 보너스번호는 27이예요.\",\"mediaURL\":\"http\",\"mediaFormat\":\"AUDIO_MPEG\",\"cpMeta\":{\"topic\":\"lotto\",\"token\":\"shado\"}},\"cpActionType\":\"Synthesizer\"},\"linkInstruction\":\"link\"}";
    std::string topic;
    try {
        root = json::parse(json);
    }
    catch (nlohmann::detail::parse_error e) {
    }

    if (!root.empty()) {
        jsonVrServiceResult = root["vrActionResult"]["cpActionData"]["cpMeta"]["topic"];

        if(!jsonVrServiceResult.is_null()){
            topic = jsonVrServiceResult.get<std::string>();
            //kakaoHmcCommandData_ = jsonVrServiceResult.dump();
            std::cout << "topic" << endl << topic << endl;
        }
    }else{
        std::cout << "topic json empty" << endl;
    }
}

void makeJson() {
    json ws_header;

    //ws_header["language"] = "KO";
    //ws_header["intermediates"] = false;
    //ws_header["cmd"] = "join";

    ws_header["cp"] = "3";

    std::cout << "makeJson : " << ws_header << endl;

}

void parseNamzProtocol() {
    json root, namzEvent;
    std::string json = "{\"topic\" : \"asr:ko\", \"payload\" : {}, \"event\" : \"close\"}";
    std::string event;

    try {
        root = json::parse(json);
    }
    catch (nlohmann::detail::parse_error e) {
    }

    if (!root.empty()) {
        namzEvent = root["event"];

        if(!namzEvent.is_null()){
            event = namzEvent.get<std::string>();
            //kakaoHmcCommandData_ = jsonVrServiceResult.dump();
            std::cout << "namzEvent" << endl << event << endl;
        }
    }else{
        std::cout << "namzEvent json empty" << endl;
    }
}

void DoNotSetFinalize() {
    json root, poiEntity;
    std::string json = "{\"cpContents\":{\"hmcCommandData\":{\"paramK\":{\"sys_location_to\":{\"origin\":\"스타벅스\",\"value\":\"스타벅스\"},\"car_navi_utterance\":{\"origin\":\"길안내 스타벅스\",\"value\":\"길안내 스타벅스\"}},\"domain\":\"P3Navi\",\"utterence\":\"길안내 스타벅스\",\"intention\":\"SetDestination\"},\"type\":\"HMCommand\"},\"linkInstruction\":\"link\"}";
    std::string event;

    try {
        root = json::parse(json);
    }
    catch (nlohmann::detail::parse_error e) {
    }

    if (!root.empty()) {
        poiEntity = root["cpContents"]["hmcCommandData"]["paramK"];

        if(!poiEntity.is_null()){
            event = poiEntity.get<std::string>();
            //kakaoHmcCommandData_ = jsonVrServiceResult.dump();
            std::cout << "poiEntity" << endl << event << endl;
        }
    }else{
        std::cout << "poiEntity json empty" << endl;
    }
}

void find_HVR_format() {
    json root;
    std::string json = "{\"resultInfo\":{\"dmResult\":{\"CarType\":\"RG3\",\"ActionType\":\"Guidance\",\"Prompt\":\"블루투스 음악 틀어줘\"},\"Recommend\":\"True\"},\"version\":\"v0.1.20.04.17\"}";
    std::string json2 = "{\"resultInfo\":{\"dmResult\":{\"CarType\":\"RG3\",\"ActionType\":\"Guidance\",\"Prompt\":\"블루투스 음악 틀어줘\"}},\"version\":\"v0.1.20.04.17\"}";
    std::string Recommend;

    try {
        root = json::parse(json2);
    }
    catch (nlohmann::detail::parse_error e) {
    }

    if (!root.empty()) {
        //Recommend = root["resultInfo"]["Recommend"];

        if(!root["resultInfo"]["Recommend"].is_null()){
            if(!Recommend.compare("True")) {
                std::cout << "[Recommend]" << endl << Recommend << endl;
            }
        } else {
            std::cout << "Recommend field null" << endl << endl;
        }
    }else{
        std::cout << "Recommend field empty" << endl;
    }
}

void makeDPJson() {
    string serialzedString;
    json BtInfo;
    BtInfo["BT_CTX"]        = "01";
    BtInfo["device"]        = "abcdefg";
    BtInfo["single"]        = 11;
    BtInfo["fullFirst"]     = 2;
    BtInfo["reverseLast"]   = 50;

    serialzedString = BtInfo.dump();

    std::cout << "BtInfo : " << serialzedString << endl;

    /* ======================================================= */
    json UserInfo, array;
    array.push_back("SLOT_SETTINGS");
    array.push_back("SLOT_STATIONS");
    UserInfo["USER_CTX"] = array;

    std::cout << "UserInfo : " << UserInfo << endl;

}

void ParseDP() {
    json DPInfo;
    string lineString = "{\"USER_CTX\":[\"SLOT_SETTINGS\", \"SLOT_STATIONS\"]}";
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

#include <unistd.h>

void vcrm_time() {
    clock_t beginTime = clock();
    cout << "time begin "<< endl;

    sleep(5);

    clock_t endTime = clock();
    cout << "time end "<< endl;

    clock_t elapsed = endTime - beginTime;

    cout << "elapsed : " << elapsed << endl;
}

void elapsedTime() {
    vector<string> vec(100000, "bonjour");
    vector<string> tmp;

    // 시작 시간
    clock_t startTime = clock();

    cout << "startTime : " << startTime << endl;

    // 시간 측정할 수행 코드
    for (vector<string>::size_type i = 0; i != vec.size(); ++i)
    {
        tmp.push_back(vec[i]);
    }

    // 종료 시간
    clock_t endTime = clock();

    cout << "endTime : " << endTime << endl;

    // Millisecond
    clock_t elapsed = 0;
    elapsed = endTime - startTime;

    cout << "elapsed : " << elapsed << endl;

    // Second
    double timeInSecond = 0.0;
    timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

    //cout << "Elapsed: " << timeInSecond << "s(" << elapsed << "ms)" << "\n";
}

#include "stdlib.h"

void gotoLable() {

    int num;
EXIT :
    scanf("%d", &num);
    if(num >=0) {
        cout << "num : " << num <<endl;
        goto EXIT;
    }

    cout << "exit text()" <<endl;
}

void isEmptycheck() {

    std::string strValue = "";
    json root;
    if(strValue.empty()){
        cout << "empty !!" << endl;
        cout << "strValue : " << strValue << endl;
        root["Longitude"] = std::stod("27.54");
        cout << "Longitude : " << root.dump() << endl;

    }else {
        cout << "not empty !!" << endl;
    }
}

#include <vector>
using byte = std::uint8_t;

std::string base64_encode(const std::vector<byte>& input)
{
    std::string encoded;
    encoded.reserve(((input.size() / 3) + (input.size() % 3 > 0)) * 4);

    std::uint32_t temp{};
    auto it = input.begin();

    for(std::size_t i = 0; i < input.size() / 3; ++i)
    {
        if(it != input.end())
            temp  = (*it++) << 16;
        if(it != input.end())
            temp += (*it++) << 8;
        if(it != input.end())
            temp += (*it++);

        try {
            encoded.append(1, kEncodeLookup.at((temp & 0x00FC0000) >> 18));
            encoded.append(1, kEncodeLookup.at((temp & 0x0003F000) >> 12));
            encoded.append(1, kEncodeLookup.at((temp & 0x00000FC0) >> 6));
            encoded.append(1, kEncodeLookup.at(temp & 0x0000003F));
        } catch (std::out_of_range &e) {

        }
    }

    switch(input.size() % 3)
    {
    case 1:
        if(it != input.end())
            temp = (*it++) << 16;

        try {
            encoded.append(1, kEncodeLookup.at((temp & 0x00FC0000) >> 18));
            encoded.append(1, kEncodeLookup.at((temp & 0x0003F000) >> 12));
            encoded.append(2, kPadCharacter);
        } catch (std::out_of_range &e) {

        }

        break;
    case 2:
        if(it != input.end())
            temp  = (*it++) << 16;
        if(it != input.end())
            temp += (*it++) << 8;

        try {
            encoded.append(1, kEncodeLookup.at((temp & 0x00FC0000) >> 18));
            encoded.append(1, kEncodeLookup.at((temp & 0x0003F000) >> 12));
            encoded.append(1, kEncodeLookup.at((temp & 0x00000FC0) >> 6));
            encoded.append(1, kPadCharacter);
        } catch (std::out_of_range &e) {

        }

        break;
    }

    return encoded;
}

bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}


std::vector<byte> base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::vector<byte> ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    if(in_ < encoded_string.size()) {
        char_array_4[i++] = encoded_string[in_];
        in_++;
    }

    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = kEncodeLookup.find(char_array_4[i]);

      char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret.push_back(char_array_3[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = 0; j < i; j++)
      char_array_4[j] = kEncodeLookup.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

    for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
  }

  return ret;
}

void parseCCVR()
{
    json root;
    std::string json = "{\"Result\" : \"00\", \"resultInfo\":{\"sttResult\":{\"recognitionText\":\"엔진오일 교체주기 알려줘\"},\"nluResult\":{},\"dmResult\":{\"carType\":\"RS4\",\"domain\":\"CCVR_QA\",\"intent\":\"JarvisQA\",\"slot\":{},\"actionType\":\"HMCommand\",\"action\":{\"displayText\":\"\",\"procedure\":\"TTS\",\"ttsText\":\"10,000 km 마다 엔진오일 교체를 권장합니다.\",\"cpContentType\":\"qaResult\",\"cpContent\":{\"qaResult\":{\"qaflag\":\"1\",\"question\":\"엔진오일 교체주기 알려줘\",\"answer\":\"10,000 km 마다 엔진오일 교체를 권장합니다.\"}}}}},\"version\":\"D004\"}";

    try {
        root = json::parse(json);
    }
    catch (nlohmann::detail::parse_error e) {
    }

    if (!root.empty()) {
        //Recommend = root["resultInfo"]["Recommend"];

        if(!root["resultInfo"]["dmResult"]["action"].is_null()){
            string result = root["resultInfo"]["dmResult"]["action"].dump();
            std::cout << "action : " << result << endl;
        } else {
            std::cout << "actionResult field null" << endl << endl;
        }
    }else{
        std::cout << "root empty" << endl;
    }
}

string changeSecureStringExceptForRightDigits(string input, int digitCount)
{
    string output;
    if (true == input.empty()) {
        output.clear();
        return "";
    }

    output = input;
    int inputStringSize = input.length();
    int changeSize = inputStringSize - digitCount;
    if(changeSize > 0 ){
        for(int i= inputStringSize-changeSize; i<inputStringSize; i++) {
            output.replace(i,1,"*");
        }
    }
    else {
        for(int i = 0; i < inputStringSize; i++) {
            output.replace(i,1,"*");
        }
    }

    return output;
}

void test() {
    QString searchKeyword = "기기 연결 설정";
    QString answerTarget = "기기 연결 설정";
    cout << "indexOf result ?: " << searchKeyword.indexOf(answerTarget) << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string houndRequestInfo, encodedString;

    //std::cout << "strlen : " << strlen("AudioPlayer.PlayState;Synthesizer.SpeakState#Synthesizer.SpeakStopped#STOPPED#shadow//ca692373-4944-4909-a307-4fbdc3b79a99");
    //std::cout << "strlen 2 : " << strlen("AudioPlayer.PlayState#AudioPlayer.Stopped#STOPPED#kakao/5b3355b41073e946641d9e85/rO0ABXNyACtjb20ua2FrYW8uc2VhcmNoLmRhLmR0by5yZXNwb25zZS5Tb3VuZFRva2VuAAAAAAAAYGgCAARKABRhY2N1bXVsYXRpb25EdXJhdGlvbkoADWxpbWl0RHVyYXRpb25aABFwbGF5Q29udGludWVMaW1pdEwACXNvdW5kVHlwZXQAEkxqYXZhL2xhbmcvU3RyaW5nO3hwAAAAAAAFSsAAAAAAABt3QAF0ABFtb3NxdWl0b19yZXBlbGxlcg==");
    //std::cout << "strlen 3 : " << strlen("kakao/5b3355b41073e946641d9e85/rO0ABXNyACtjb20ua2FrYW8uc2VhcmNoLmRhLmR0by5yZXNwb25zZS5Tb3VuZFRva2VuAAAAAAAAYGgCAARKABRhY2N1bXVsYXRpb25EdXJhdGlvbkoADWxpbWl0RHVyYXRpb25aABFwbGF5Q29udGludWVMaW1pdEwACXNvdW5kVHlwZXQAEkxqYXZhL2xhbmcvU3RyaW5nO3hwAAAAAAAFSsAAAAAAABt3QAF0ABFtb3NxdWl0b19yZXBlbGxlcg==");

    //std::cout << "smartVUI : " << strlen("AudioPlayer.PlayState#AudioPlayer.Stopped#STOPPED#kakao/5953379d9418c2172f3eba8d/zodiac_1591078633;Synthesizer.SpeakState#Synthesizer.SpeakFinished#FINISHED#shadow//37715fb8-6488-42a2-af48-d6eccd817177");
    //ParseJSON(weatherJson);

    //houndRequestInfo = createHoundRequestInfo();
    //cout << "Hound Request Info : " << houndRequestInfo << endl << endl << endl;

    //std::vector<byte> data(std::begin(houndRequestInfo), std::end(houndRequestInfo));

    //encodedString = base64_encode(data);
    //cout << "base64_encode  : " << encodedString << endl;


    //makeJson();
    //std::cout << endl;
    //kakaoMusic();

    //kakaoDomain();

    //parseNamzProtocol();

    //DoNotSetFinalize();

    //find_HVR_format();

    //makeDPJson();

    //vcrm_time();

    //elapsedTime();

    //gotoLable();

    //isEmptycheck();

    //ParseDP();

    //parseCCVR();

    test();

#if 0
    std::string exceptionVin;
    std::string VIN = "KMRGTEST018031301";
    exceptionVin = changeSecureStringExceptForRightDigits(VIN, 8);

    std::cout << "output : " << exceptionVin << endl;
#endif
    return a.exec();
}


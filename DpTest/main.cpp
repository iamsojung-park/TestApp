#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <test.h>

using namespace std;

bool isTripleByteCharacter(const char *text){
    bool utf8_3byte = false;

    std::cout << "text length : " << strlen(text) << std::endl;

    if(static_cast<unsigned char>(text[0]) > 0xDF) {
        /** Indic, Thai, Korean, Japanese
             1110xxxx 10xxxxxx 10xxxxxx */
        for(int i =0; i < strlen(text); i++) {
            if((text[i] & 0xE08080) == 0xE08080) {
                std::cout << "UTF8_3byte" <<std::endl;
                utf8_3byte = true;
            }
        }
    }

    return utf8_3byte;
}


vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter)) {
        internal.push_back(temp);
    }

    return internal;
}

    /**
        1. 대표명령어인 경우, byte 따지지 않고 DP
        2.이형명령어인 경우,
        - 한글 한음절 3byte —> 4byte 이상만 DP
        - 한글외 한음절 대부분 1byte —> 3byte 이상만 DP
    **/
#define SDS_DIALOG_RESULT_DATA_SIZE                 1024
#define SDS_LINE_DATA_BUFFER_LEN                    512
#define SDS_PATH_NAME_LEN                           256
#define SDS_TAG_NAME_LEN                            128
#define SDS_MAX_SLOT                                4

typedef struct _T_MZT_TH_SLOTINFO {
    int                           id;                                         	/* Slot ID */
    char                          tag[SDS_TAG_NAME_LEN];                          /* Slot TAG */
    char                          value[SDS_DIALOG_RESULT_DATA_SIZE];         	/* Slot Value */
    int                   		score;                                      	/* Slot Score */
} T_DM_SLOT_INFO;

typedef struct _T_MZT_TH_NBESTINFO {
    int                           commandID;
    int                           score;
    char                          screenText[SDS_DIALOG_RESULT_DATA_SIZE];        /* Screen Text*/
    char                          domain[SDS_TAG_NAME_LEN];                       /* Domain */
    char                          engineResult[SDS_DIALOG_RESULT_DATA_SIZE];      /* Engine Result*/
    char                          intention[SDS_TAG_NAME_LEN];                    /* Intention */

    int                           slot_Count;                                     /* Slot Count(bound 0 to 3) */
    T_DM_SLOT_INFO                xSlotInfo[SDS_MAX_SLOT];

} T_DM_NBEST_INFO;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::list<std::string> dp_list;
    std::list<std::string>::iterator iter;

    std::list<std::string> dp_list_spread;
    std::vector<std::string>::iterator split_iter;

    T_DM_NBEST_INFO A;
    T_DM_NBEST_INFO B[50];

    std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
    std::cout << "sizeof(B) = " << sizeof(B) << std::endl;

    /** Insert Test Command */
    dp_list.push_back("AAA BBB CCC DDD");
    dp_list.push_back("NFC card key");
    dp_list.push_back("Setting Search AS");
    dp_list.push_back("Device key information");
    dp_list.push_back("Reset");
    dp_list.push_back("대 이상만");
    dp_list.push_back("Auto Connection of Proopprity");
    dp_list.push_back("Auto Connection Proopprity");
    dp_list.push_back("Message Notification");
    dp_list.push_back("AM");
    dp_list.push_back("FM");
    dp_list.push_back("홈");

    for(iter = dp_list.begin(); iter != dp_list.end(); ++iter){
        /** Full */
        dp_list_spread.push_back(*iter);

        vector<string> line_vector = split(*iter, ' ');
        /** Partial */
        for(split_iter = line_vector.begin(); split_iter != line_vector.end(); ++split_iter){
            std::cout << "[Partial] : " << *split_iter << std::endl;
            if(std::string(*split_iter).length() >= 4){
                dp_list_spread.push_back(*split_iter);
            }else{
                if(!isTripleByteCharacter(std::string(*split_iter).c_str())){
                    if(std::string(*split_iter).length() >= 3){
                        dp_list_spread.push_back(*split_iter);
                    }
                }
                else{
                    std::cout << "Hangul, Japaness,..1Character, Do not pushBack!!!!" << std::endl;
                }
            }
        }

        /** Combination */
        int splittedCount = line_vector.size();   //ex) split_count 4
        int curCombinationCount = splittedCount -1;         //  cur_split 4 - 1 = 3
        int curSplittedPos = 0;

        while(curCombinationCount > 1){
            //std::cout << "[1]splittedCount : " << line_vector.size() << std::endl;
            //std::cout << "[1]curCombinationCount : " << splittedCount -1 << std::endl;
            //std::cout << "[1]curSplittedPos : " << curSplittedPos << std::endl;

            while(splittedCount - curSplittedPos >= curCombinationCount){
                //std::cout << "[2]splittedCount : " << line_vector.size() << std::endl;
                //std::cout << "[2]curCombinationCount : " << curCombinationCount << std::endl;
                //std::cout << "[2]curSplittedPos : " << curSplittedPos << std::endl;

                string tempString;

                for(int i = 0; i < curCombinationCount; i++){
                    tempString += line_vector.at(curSplittedPos+i) + " ";
                }

                std::cout << "tempString : " << tempString << std::endl;

                dp_list_spread.push_back(tempString);
                curSplittedPos++;
            }
            curCombinationCount--;
            curSplittedPos = 0;
        }
    }

    /** Step Sort */
    dp_list_spread.sort([](std::string a, std::string b){return (a<b);});
    /** Step Deduplication */
    dp_list_spread.erase(unique(dp_list_spread.begin(), dp_list_spread.end()),dp_list_spread.end());

    /** Step Print Original List */
    for(iter = dp_list.begin(); iter != dp_list.end(); ++iter){
        std::cout << "         dp_list :: "<< *iter <<std::endl;
    }
    /** Step Print Spread List */
    for(iter = dp_list_spread.begin(); iter != dp_list_spread.end(); ++iter){
        std::cout << "               dp_list_spread :: "<< *iter <<std::endl;
    }

    std::cout << "END TEST :: " <<std::endl;
    return a.exec();
}

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/* plain old ASCII */
#define isutf8_1byte(c)		(0x00<=c && c <= 0x7f)	/* 0xxxxxxx */

enum class BracketPairs {
    braces,         // {}
    parentheses,    // ()
    brackets,       // []
    angle_brackets, // <>
    MAX
};

///////////////////////////////////////////////////////////
//  문자열에서 bracket pair가 존재하는 경우, bracket 종류와 위치에 대한 값을 리턴한다.
//  Bracket pair가 여러 개 존재하더라도 첫 번째 쌍이 매치한 이후는 무시한다
///////////////////////////////////////////////////////////
BracketPairs hasBracketPairs(std::string &s, std::size_t &bracketStart, std::size_t &bracketEnd)
{
    BracketPairs ret = BracketPairs::MAX;
    std::string allStartBraces = "{([<";
//    std::string allEndBraces = "})]>";
    std::size_t sLength = s.length();

    auto foundStart = s.find_first_of(allStartBraces, 1); // 첫 글자가 bracket 문자인 경우는 무시
    auto foundEnd   = std::string::npos;

    while(foundStart != std::string::npos) {
//        std::cout << "found start bracket !!! " << s.at(foundStart) << std::endl;
        char firstBracketChar = s.at(foundStart);
        switch (firstBracketChar) {
        case '{':
            foundEnd = s.find_first_of('}', foundStart);
            break;
        case '(':
            foundEnd = s.find_first_of(')', foundStart);
            break;
        case '[':
            foundEnd = s.find_first_of(']', foundStart);
            break;
        case '<':
            foundEnd = s.find_first_of('>', foundStart);
            break;
        default:
            std::cout << "Error - not supported bracket charactor !!!";
            break;
        }
        if(foundEnd != std::string::npos && foundEnd != (sLength-1)) { // 마지막 글자가 bracket 문자인 경우는 무시
//            std::cout << "found bracket pairs !!!" << std::endl;
            //ret = static_cast<BracketPairs>(allStartBraces.find(firstBracketChar));
            switch (firstBracketChar) {
            case '{': ret = BracketPairs::braces;           break;
            case '(': ret = BracketPairs::parentheses;      break;
            case '[': ret = BracketPairs::brackets;         break;
            case '<': ret = BracketPairs::angle_brackets;   break;
            default:  ret = BracketPairs::MAX;              break;
            }
            bracketStart= foundStart;
            bracketEnd  = foundEnd;
            break;
        }
        foundStart = s.find_first_of(allStartBraces, foundStart+1);
    }

//    std::cout << "bracket pair results : " << static_cast<int>(ret) << std::endl;
    return ret;
}

///////////////////////////////////////////////////////////
//  문자열에서 bracket pair가 존재하는 경우, 사양에 따라 조합하여 vector에 추가한다.
//    Case 1: A B  => A B
//    Case 2: A [B] C => A B C, A C, B C
//    Case 3: [A] B => A B
//    Case 4: A [B] => A B
///////////////////////////////////////////////////////////
void newDpComposition(std::string s, std::vector<std::string> &output)
{
    std::size_t bracketStart = std::string::npos;
    std::size_t bracketEnd = std::string::npos;
    BracketPairs pairs = hasBracketPairs(s, bracketStart, bracketEnd);

    output.push_back(s);
    if(pairs != BracketPairs::MAX) {
        std::string strA = s.substr(0, bracketStart);
        std::string strB = s.substr(bracketStart+1, bracketEnd-(bracketStart+1));
        std::string strC = s.substr(bracketEnd+1);
        std::string strD = s.substr(bracketStart);

        output.push_back(strA + strC);
        std::cout << "newDpComposition(1): " << strA + strC << std::endl;
        output.push_back(strB + strC);
        std::cout << "newDpComposition(2): " << strB + strC << std::endl;
        output.push_back(strD);
        std::cout << "newDpComposition(3): " << strD << std::endl;
    }
    else {
        std::cout << "newDpComposition BracketPairs::MAX " << std::endl;
    }
}
unsigned char* convert(const std::string& s);

#include <string.h>
void newDpComposition2()
{
    char str[] = "홍길동 연구 /현대자동차 ★연구소";
    char* ptr = strchr(str, '/'); // W로 시작하는 문자 검색
    int count = 0;

    while (ptr != NULL) // 검색된 문자가 없을 때까지 반복
    {
        std::cout << ptr << std::endl;
        ptr = strchr(ptr + 1, '/'); // 리턴된 포인터 +1 계속 검색
    }
}

///////////////////////////////////////////////////////////
//    Case : A B C => A, A B, A B C
///////////////////////////////////////////////////////////
void makeNewDPSplitList(std::string s, std::string delimiter, std::vector<std::string> &output)
{
    size_t pos_start = 0, delim_len = delimiter.length();
    std::string token;
    size_t pos_end = s.length();

    output.push_back (s);

    while ((pos_end = s.find_last_of(delimiter, pos_end -1)) != std::string::npos) {
        output.push_back(s.substr (0, pos_end));
    }
}

std::vector<std::string> findSpecialCharacters(unsigned char *pSource)
{
    unsigned char               *pSrcPos = (unsigned char*)pSource;
    long long                   uc;
    std::vector<std::string>    chunk;
    std::cout << "2222222222" << std::endl;
    std::cout << "findSpecialCharacters : " << *pSource << std::endl;

    if(pSource == NULL){
        std::cout << "pSource nullptr" << std::endl;
        return chunk;
    }

    while (*pSrcPos != 0) {
        uc = 0;
        uc = *pSrcPos;

        //if (isutf8_1byte(uc)) {
        std::cout << "uc : " << uc << std::endl;

        if(uc >= 32 && uc <= 47) {
            std::string s( reinterpret_cast< char const* >(*pSrcPos));
            std::cout << "chunk.push_back" << s << std::endl;
            chunk.push_back(s);
        }
        pSrcPos++;
        //    continue;
        //}
        //else {
        //    std::cout << "pSrcPos++" << std::endl;
        //    pSrcPos++;
        //}
    }

    return chunk;
}

unsigned char* convert(const std::string& s){
    std::cout << "convert string : " << s << std::endl;
    unsigned char* bytes= new unsigned char[s.size()+1];
    std::copy(s.begin(),s.end(),bytes);
    return bytes;
}

void test() {
    char* ptr = "";
}

int main(int argc, char *argv[])
{
    std::cout << "New DP rule for VR HMI" << std::endl;

    std::string input1 = "김보현 {연구} 현대자동차 연구소";
    std::string input2 = "김보현 <연구 {현대자동차}> 연구소";
    std::string input3 = "김보현 [연구 현대자동차 연구소]";
    std::string input4 = "[김보현] (연구 현대)자동차 연구소";
    std::string input5 = "은희 [준희] 엄마";
    std::string input6 = "김 [보] 연구";
    std::string input10 = "세진[명진]승민";

    std::vector<std::string> result;
    newDpComposition(input1, result);
    newDpComposition(input2, result);
    newDpComposition(input3, result);
    newDpComposition(input4, result);
    newDpComposition(input5, result);
    newDpComposition(input6, result);
    newDpComposition(input10, result);
    for(std::string it : result) {
        std::cout << it << std::endl;
    }



//    std::cout << "1111111" << std::endl;
//    std::string input7 = "홍길동 연구 /현대자동차 ★연구소";
//    std::cout << "convert(input7) : " << convert(input7) << std::endl;
//    std::vector<std::string> specialCharacters = findSpecialCharacters(convert(input7));
//    auto it = specialCharacters.begin();
//    while(it != specialCharacters.end()) {
//        std::cout << "chunk" << *it << std::endl;
//    }

//    std::cout << "3333333" << std::endl;
    /*
    std::cout << "\n\n\nNew DP Split rule for VR Service" << std::endl;

    std::string input11 = "김보현 연구 현대자동차 연구소";

    std::vector<std::string> resultService;
    makeNewDPSplitList(input11, " ", resultService);
    for(std::string it : resultService) {
        std::cout << it << std::endl;
    }
    */

    return 1;
}

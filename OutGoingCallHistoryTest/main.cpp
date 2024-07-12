#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp> // JSON 라이브러리 사용
#include "VHLog.h"
#include "VHOchData.h"

using namespace std;
using json = nlohmann::json;

class OchManager {
private:
    map<string, string> ochs; // 이름과 타임스탬프 쌍을 저장할 맵
    const int MAX_SIZE = 10; // 최대 저장 가능한 쌍의 개수
public:
    // 생성자
    OchManager() {
        ochs.clear(); // 맵을 비웁니다.
    }

    // 이름과 타임스탬프 쌍을 추가하는 메소드
    void addOch(string name, string timestamp) {
        if (ochs.size() == MAX_SIZE) { // 맵이 꽉 찼으면
            ochs.erase(ochs.begin()); // 가장 오래된 쌍을 제거합니다.
        }
        ochs[name] = timestamp; // 새로운 쌍을 추가합니다.
    }

    // OchManager의 내용을 JSON 포맷으로 저장하는 메소드
    void saveOch(string filename) {
        json j; // JSON 객체 생성
        for (auto& och : ochs) { // 맵의 각 쌍에 대해
            j[och.first] = och.second; // JSON 객체에 키와 값으로 추가합니다.
        }
        ofstream file(filename); // 파일 스트림 생성
        file << j.dump(4); // JSON 객체를 파일에 저장합니다. 4는 들여쓰기 크기입니다.
        file.close(); // 파일 스트림 닫기
    }

    // JSON 포맷으로 저장된 OchManager의 내용을 읽어오는 메소드
    void loadOch(string filename) {
        ifstream file(filename); // 파일 스트림 생성
        json j; // JSON 객체 생성
        file >> j; // 파일에서 JSON 객체를 읽어옵니다.
        file.close(); // 파일 스트림 닫기
        ochs.clear(); // 맵을 비웁니다.
        for (auto& item : j.items()) { // JSON 객체의 각 항목에 대해
            ochs[item.key()] = item.value(); // 맵에 쌍으로 추가합니다.
        }
    }

    // OchManager의 내용을 출력하는 메소드
    void printOch() {
        cout << "OchManager contains " << ochs.size() << " pairs:\n"; // 맵의 크기 출력
        for (auto& och : ochs) { // 맵의 각 쌍에 대해
            cout << och.first << " : " << och.second << "\n"; // 이름과 타임스탬프 출력
        }
        std::cout << std::endl;
    }
};

void printlist(std::map<std::string, std::string>& ochs) {
    std::cout << "OchManager contains " << ochs.size() << " pairs:\n"; // 맵의 크기 출력
    for (auto& och : ochs) { // 맵의 각 쌍에 대해
        std::cout << och.first << " : " << och.second << "\n"; // 이름과 타임스탬프 출력
    }
    std::cout << std::endl;
}

int main() {
//    OchManager om; // OchManager 객체 생성

//    om.addOch("Iris", "20231025T134314"); // 이름과 타임스탬프 쌍 추가
//    om.addOch("Alice", "20231025T134315");
//    om.addOch("Charlie", "20231025T134316");
//    om.addOch("David", "20231025T134317");
//    om.addOch("Eve", "20231025T134318");
//    om.addOch("Frank", "20231025T134319");
//    om.addOch("Grace", "20231025T134320");
//    om.addOch("Henry", "20231025T134321");
//    om.addOch("Bob", "20231025T134322");
//    om.addOch("Jack", "20231025T134323");

//    om.printOch(); // OchManager의 내용 출력

//    om.saveOch("och.json"); // OchManager의 내용을 JSON 포맷으로 저장

//    om.addOch("Kate", "20231025T134324"); // 새로운 쌍 추가
//    om.addOch("Leo", "20231025T134325"); // 새로운 쌍 추가

//    om.printOch(); // OchManager의 내용 출력

//    om.loadOch("och.json"); // JSON 포맷으로 저장된 OchManager의 내용을 읽어옴

//    om.printOch(); // OchManager의 내용 출력

    VHOchData om;
    om.addOch("Iris", "20231025T134314"); // 이름과 타임스탬프 쌍 추가
    om.addOch("Alice", "20231025T134315");
    om.addOch("Charlie", "20231025T134316");
    om.addOch("David", "20231025T134317");
    om.addOch("Eve", "20231025T134318");
    om.addOch("Frank", "20231025T134319");
    om.addOch("Grace", "20231025T134320");
    om.addOch("Henry", "20231025T134321");
    om.addOch("Bob", "20231025T134322");
    om.addOch("Jack", "20231025T134323");

    om.printOch(); // OchManager의 내용 출력

//    om.saveToJson("och.json"); // OchManager의 내용을 JSON 포맷으로 저장
    om.saveToJson(); // OchManager의 내용을 JSON 포맷으로 저장

    om.addOch("Kate", "20231025T134324"); // 새로운 쌍 추가
    om.addOch("Leo", "20231025T134325"); // 새로운 쌍 추가

    om.printOch(); // OchManager의 내용 출력


}

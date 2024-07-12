#include <QCoreApplication>
#include "VHContact.h"
#include <iostream>


VHContact VHContactTest(VHContact input)
{
    std::cout << std::endl;

    //input.print();

    VHContact t2 = input;

    t2.setDBIndex(222);
    t2.setFirstName("t2FirstName");
    t2.setFullName("t2FullName");
    //t2.print();

    return t2;
}

int main(int argc, char *argv[])
{
    QList<VHContact> contacts;

    VHContact t1;
    t1.setDPList("dpList");
    t1.setDBIndex(111);
    t1.setFullName("현차");
    t1.setFirstName("firstName");
    t1.setLastName("lastName");
    t1.setTimeStamp("xxxxxxxx");
    t1.setConfidence(1234);

    VHContact t2;
    t2.setDPList("dpList");
    t2.setDBIndex(111);
    t2.setFullName("현차 홍길동");
    t2.setFirstName("firstName");
    t2.setLastName("lastName");
    t2.setTimeStamp("xxxxxxxx");
    t2.setConfidence(1234);

    VHContact t3;
    t3.setDPList("dpList");
    t3.setDBIndex(111);
    t3.setFullName("현차 가길동");
    t3.setFirstName("firstName");
    t3.setLastName("lastName");
    t3.setTimeStamp("xxxxxxxx");
    t3.setConfidence(1234);

    VHContact t4;
    t4.setDPList("dpList");
    t4.setDBIndex(111);
    t4.setFullName("현차나길동");
    t4.setFirstName("firstName");
    t4.setLastName("lastName");
    t4.setTimeStamp("xxxxxxxx");
    t4.setConfidence(1234);

    VHContact t5;
    t5.setDPList("dpList");
    t5.setDBIndex(111);
    t5.setFullName("현차다길동");
    t5.setFirstName("firstName");
    t5.setLastName("lastName");
    t5.setTimeStamp("xxxxxxxx");
    t5.setConfidence(1234);

    contacts.push_back(t1);
    contacts.push_back(t2);
    contacts.push_back(t3);
    contacts.push_back(t4);
    contacts.push_back(t5);

    //t1.print();
    //VHContact t3 = VHContactTest(t1);
    //t3.print();

    QString name = "현차";
    QString nameWithSpace = "현차" + QString(" ");

    for (auto contact : contacts) {
        QString fullName = contact.getFullName();
        //std::cout << "fullName : " << fullName.toStdString() << std::endl;
        //QString nameWithSpace = name + ' ';

        //std::cout << "nameWithSpace : " << nameWithSpace.toStdString() << std::endl;
//        if(fullName.startsWith(name)){
//            if(fullName.length() == name.length()) {
//                std::cout << "matched name(1) : "<<fullName.toStdString() << std::endl;
//            }
//        }
//        else if(fullName.startsWith(nameWithSpace)){
//            std::cout << "matched name(2) : "<<fullName.toStdString() << std::endl;
//        }
        if(fullName.toStdString().find(name.toStdString()) == 0){
            if(fullName.length() == name.length()) {
                std::cout << "matched name(1) : "<<fullName.toStdString() << std::endl;
            }
        }

        if(fullName.toStdString().find(nameWithSpace.toStdString()) == 0){
            std::cout << "matched name(2) : "<<fullName.toStdString() << std::endl;
        }
    }

    return 0;
}

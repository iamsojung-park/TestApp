#include "VHLog.h"
#include <QString>
#include <iostream>



void VHLog::debug(QString message)
{
    std::cout << message.toStdString() << std::endl;
}

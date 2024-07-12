#ifndef BASE_H
#define BASE_H

typedef int MZBOOL;
typedef int MZINT;
typedef signed char MZINT8;
typedef short MZINT16;
typedef long MZINT32;
typedef unsigned int MZUINT;
typedef unsigned char MZUINT8;
typedef unsigned short MZUINT16;
typedef unsigned long MZUINT32;
typedef unsigned long long MZUINT64;
typedef char MZCHAR8;
typedef char MZCHAR;       // UTF-8 encoding
typedef wchar_t MZALTCHAR;
typedef unsigned char MZBYTE;
typedef float MZFLOAT;
typedef unsigned int MZSIZE;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif


#include <pthread.h>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <map>
#include <list>
#include <stdio.h>
#include <stdarg.h>
#include <utility>
#include <time.h>

#include <nlohmann/json.hpp>


#include <string>
#include <fstream>
#include <iostream>


#endif // BASE_H
